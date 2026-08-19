// XSS：<script> 标签（raw 画像：不经过 SQL 解析，直接匹配归一化文本）
rule script_tag {
    severity: HIGH
    profile: raw
    description: "XSS：<script> 标签"
    pattern: Text(contains = "<script")
}
