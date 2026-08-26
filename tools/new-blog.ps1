<#
.SYNOPSIS
    Scaffold a new, self-contained blog folder from _template.
.EXAMPLE
    .\tools\new-blog.ps1 -Title "Scaling Kafka Consumers"
    .\tools\new-blog.ps1 -Title "Tracing gRPC" -Slug "grpc-tracing" -Date 2026-09-01
#>
param(
    [Parameter(Mandatory = $true)][string]$Title,
    [string]$Slug,
    [string]$Date,
    [string]$Author = $env:USERNAME
)

$ErrorActionPreference = 'Stop'
$root     = Split-Path -Parent $PSScriptRoot
$template = Join-Path $root '_template'

if (-not (Test-Path $template)) { throw "Template not found: $template" }

if (-not $Slug) {
    $Slug = $Title.ToLower() -replace "[^a-z0-9]+", "-"
    $Slug = $Slug.Trim('-')
}
if (-not $Date) { $Date = Get-Date -Format 'yyyy-MM-dd' }

$folder = Join-Path (Join-Path $root 'blogs') "$Date-$Slug"
if (Test-Path $folder) { throw "Blog already exists: $folder" }

Copy-Item -Path $template -Destination $folder -Recurse
Write-Host "Created $folder"

# Substitute placeholders in the text files.
$map = @{ '{{TITLE}}' = $Title; '{{SLUG}}' = $Slug; '{{DATE}}' = $Date; '{{AUTHOR}}' = $Author }
$utf8NoBom = New-Object System.Text.UTF8Encoding $false
Get-ChildItem -Path $folder -Recurse -File -Include *.md, *.mdx, *.yaml | ForEach-Object {
    $text = Get-Content $_.FullName -Raw
    foreach ($k in $map.Keys) { $text = $text.Replace($k, $map[$k]) }
    # UTF-8 without BOM -- a BOM breaks YAML front-matter parsers.
    [System.IO.File]::WriteAllText($_.FullName, $text, $utf8NoBom)
}

Write-Host "Title : $Title"
Write-Host "Next  : edit $folder\post.mdx"
