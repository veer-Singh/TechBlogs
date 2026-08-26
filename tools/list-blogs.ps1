<#
.SYNOPSIS
    Table of every blog with its status, pulled from each post.mdx front matter.
#>
$root = Split-Path -Parent $PSScriptRoot

Get-ChildItem (Join-Path $root 'blogs') -Directory | ForEach-Object {
    $post = Join-Path $_.FullName 'post.mdx'
    $status = 'no post.mdx'; $title = ''
    if (Test-Path $post) {
        $head = Get-Content $post -TotalCount 20
        $status = ($head | Select-String -Pattern '^status:\s*(\S+)').Matches.Groups[1].Value
        $title  = ($head | Select-String -Pattern '^title:\s*"?([^"]*)"?').Matches.Groups[1].Value
    }
    $images = @(Get-ChildItem (Join-Path $_.FullName 'assets\images\export') -File -ErrorAction SilentlyContinue | Where-Object { $_.Name -ne ".gitkeep" }).Count

    [pscustomobject]@{
        Folder = $_.Name
        Title  = $title
        Status = $status
        Images = $images
    }
} | Sort-Object Folder | Format-Table -AutoSize
