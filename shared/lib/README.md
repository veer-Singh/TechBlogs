# shared/lib

Only code used by **two or more** blogs belongs here (chart theming, logging
setup, data loaders). Anything used by one post stays in that post's `scripts/`.

Keep modules dependency-light — a blog importing from here should not inherit a
heavy dependency tree it doesn't otherwise need.
