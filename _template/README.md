# {{TITLE}}

Self-contained working folder for a single blog post. Nothing here depends on
another blog folder.

| Path                    | What goes in it                                                      |
|-------------------------|----------------------------------------------------------------------|
| `post.mdx`              | The post itself (front matter + body). The deliverable.               |
| `meta.yaml`             | Publishing metadata: targets, URLs, runtime, review state.             |
| `assets/images/source/` | Originals — raw screenshots, exports, photos. Never edited in place.   |
| `assets/images/export/` | Publish-ready images: cropped, resized, compressed, renamed.            |
| `assets/diagrams/`      | Editable diagram sources (`.mmd`, `.drawio`, `.excalidraw`).             |
| `scripts/`              | Code that produces the post's results. Own deps, own entry points.      |
| `snippets/`             | Short, runnable code fragments quoted inline in the post.              |
| `data/`                 | Small sample inputs / captured outputs the post refers to.              |
| `output/`               | Run artifacts: logs, generated charts, benchmark dumps. Gitignored.     |

## Writing MDX

`post.mdx` is MDX, so it accepts JSX components alongside Markdown. Three ways
it is stricter than plain Markdown — all three are compile errors, not warnings:

1. **Comments** are `{/* ... */}`. HTML comments (`<!-- -->`) do not work; MDX
   tries to parse them as JSX.
2. **Bare `<` and `{` are syntax.** `<` starts a JSX tag, `{` starts a JS
   expression. Escape them as `\<` and `\{`, or wrap them in backticks. This
   catches you on things like `<100ms`, `{id}`, and `a < b`.
3. **JSX blocks need blank lines** around them to be treated as blocks.

Plain prose, headings, lists, links, tables, and fenced code all behave exactly
as in Markdown. If a post uses no components, valid Markdown is valid MDX once
those characters are escaped.

## Conventions

- Image naming: `NN-short-description.png` (`01-cluster-topology.png`) so the
  order matches the post. Only files in `export/` are referenced from `post.mdx`.
- Every image in `export/` should trace back to something in `source/` or
  `diagrams/`, so it can be regenerated.
- Anything in `output/` must be reproducible by running something in `scripts/`.

## Reproduce

```
cd scripts
# see scripts/README.md for setup + run commands
```
