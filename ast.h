#pragma once

// ============================================================
// AST 中间层（waf::AstNode）
// ------------------------------------------------------------
// 设计要点：
//   * 语义规则不关心具体 SQL 文本，只关心结构化的 AST。
//   * AST 是"通用结构"，不是针对每种 SQL 方言的强类型 C++ 类，
//     便于规则插件与主引擎共享同一份头文件、跨 .so 传递。
//   * 每个节点 = kind（节点类型）+ attrs（标量属性）+ children（有序子节点）
//     + named（语义角色，如 left/right/operand）。
//   * 本文件 header-only，规则插件编译时只需包含它，无需链接引擎。
// ============================================================

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace waf {

struct AstNode {
    std::string kind;                             // "Query" / "Select" / "BinaryExpr" / ...
    std::map<std::string, std::string> attrs;     // op, value, name, union, ...
    std::vector<std::unique_ptr<AstNode>> children;
    std::map<std::string, AstNode*> named;        // 语义角色：left / right / operand / low / high

    AstNode() = default;
    explicit AstNode(std::string k) : kind(std::move(k)) {}

    void setAttr(const std::string& key, std::string value) {
        attrs[key] = std::move(value);
    }

    bool hasAttr(const std::string& key) const {
        return attrs.count(key) != 0;
    }

    // 缺失属性返回空串；规则模式里 "" 匹配缺失属性属于可接受边界。
    const std::string& attr(const std::string& key) const {
        static const std::string kEmpty;
        auto it = attrs.find(key);
        return it == attrs.end() ? kEmpty : it->second;
    }

    AstNode* addChild(std::unique_ptr<AstNode> child) {
        AstNode* raw = child.get();
        children.push_back(std::move(child));
        return raw;
    }

    // 附加子节点并登记语义角色（角色指向同一子节点）。
    AstNode* addNamed(const std::string& role, std::unique_ptr<AstNode> child) {
        AstNode* raw = child.get();
        children.push_back(std::move(child));
        named[role] = raw;
        return raw;
    }

    const AstNode* namedChild(const std::string& role) const {
        auto it = named.find(role);
        return it == named.end() ? nullptr : it->second;
    }

    // 调试用：缩进打印整棵 AST。
    std::string dump(int indent = 0) const {
        std::ostringstream os;
        os << std::string(indent * 2, ' ') << kind;
        if (!attrs.empty()) {
            os << " {";
            bool first = true;
            for (const auto& kv : attrs) {
                if (!first) os << ", ";
                first = false;
                os << kv.first << "=" << kv.second;
            }
            os << "}";
        }
        os << "\n";
        for (const auto& c : children) {
            os << c->dump(indent + 1);
        }
        return os.str();
    }
};

using AstPtr = std::unique_ptr<AstNode>;

}  // namespace waf
