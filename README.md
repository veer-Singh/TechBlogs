# TECH_BLOGS

A workspace holding many independent tech blog posts. **Each post is one folder
under `blogs/` that owns everything it needs** — content, images, scripts and
dependencies — so posts never interfere with each other and any one of them can
be zipped, handed off, or deleted on its own.

## Layout

```
TECH_BLOGS/
├── blogs/                       # one folder per post, fully self-contained
│   └── YYYY-MM-DD-slug/
│       ├── post.mdx             # the post (MDX: front matter + body)
│       ├── meta.yaml            # publishing metadata
│       ├── README.md            # what this post is, how to reproduce it
│       ├── assets/
│       │   ├── images/source/   # originals, untouched
│       │   ├── images/export/   # publish-ready, referenced by post.mdx
│       │   └── diagrams/        # editable diagram sources
│       ├── scripts/             # this post's code + its own deps
│       ├── snippets/            # code quoted inline in the post
│       ├── data/                # sample inputs / captured outputs
│       └── output/              # run artifacts (gitignored)
│
├── _template/                   # blueprint copied for every new post
├── shared/
│   ├── lib/                     # helpers genuinely reused across posts
│   ├── templates/               # reusable post outlines
│   └── styles/                  # house style, terminology, image style guide
├── tools/                       # workspace-level scripts (scaffold, image prep)
└── README.md
```

## Create a new post

```powershell
.\tools\new-blog.ps1 -Title "Scaling Kafka Consumers"
# -> blogs/2026-08-21-scaling-kafka-consumers/
```

Bash equivalent: `./tools/new-blog.sh "Scaling Kafka Consumers"`

## Ground rules

1. **No cross-blog imports.** A blog folder may read from `shared/`, never from
   another blog. If two posts need the same code, it moves to `shared/lib/`.
2. **Dependencies live inside the blog.** Each `scripts/` folder gets its own
   `.venv` / `node_modules` so one post's version pins can't break another's.
3. **`export/` is the only image source for `post.mdx`.** Keep originals in
   `source/` so images can always be regenerated.
4. **`output/` is disposable.** Anything there must be reproducible from
   `scripts/`.
5. **Date-prefixed folder names** (`YYYY-MM-DD-slug`) keep posts sorted and
   unambiguous.

## Status at a glance

`status:` in each post's front matter is the single source of truth
(`draft` → `review` → `published`).

```powershell
.\tools\list-blogs.ps1
```
