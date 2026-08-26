# House style

## Writing
- Second person, active voice. Short paragraphs.
- Lead with the problem, not the tooling.
- Every claim that came from a run should point at something in `scripts/` or `output/`.

## Code in posts
- Snippets must be runnable as written, or explicitly marked as elided with `...`.
- Keep snippet files in the blog's `snippets/` folder and quote from them, so the
  code in the post is code that actually ran.

## Images
- Width 1600px for screenshots, PNG; diagrams exported at 2x.
- Light background, no OS chrome unless the window matters.
- Redact hostnames, tokens and internal URLs before an image leaves `source/`.
- Name files `NN-short-description.png` in post order.

## Terminology
| Use          | Not                    |
|--------------|------------------------|
| Kubernetes   | k8s (in prose)         |
| repository   | repo (in prose)        |
