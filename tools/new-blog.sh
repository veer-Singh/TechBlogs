#!/usr/bin/env bash
# Scaffold a new, self-contained blog folder from _template.
# Usage: ./tools/new-blog.sh "Scaling Kafka Consumers" [slug] [YYYY-MM-DD]
set -euo pipefail

title="${1:?usage: new-blog.sh \"Title\" [slug] [date]}"
slug="${2:-$(printf '%s' "$title" | tr '[:upper:]' '[:lower:]' | sed -E 's/[^a-z0-9]+/-/g; s/^-+|-+$//g')}"
date="${3:-$(date +%F)}"
author="${USER:-${USERNAME:-unknown}}"

root="$(cd "$(dirname "$0")/.." && pwd)"
target="$root/blogs/$date-$slug"

[ -d "$root/_template" ] || { echo "Template not found: $root/_template" >&2; exit 1; }
[ -e "$target" ] && { echo "Blog already exists: $target" >&2; exit 1; }

cp -R "$root/_template" "$target"

find "$target" -type f \( -name '*.md' -o -name '*.mdx' -o -name '*.yaml' \) -print0 |
  while IFS= read -r -d '' f; do
    sed -i \
      -e "s|{{TITLE}}|$title|g" \
      -e "s|{{SLUG}}|$slug|g" \
      -e "s|{{DATE}}|$date|g" \
      -e "s|{{AUTHOR}}|$author|g" "$f"
  done

echo "Created $target"
echo "Next  : edit $target/post.mdx"
