# Scripts for this blog

Dependencies are installed **inside this folder** so this blog cannot break
another one.

## Python

```powershell
py -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install -r requirements.txt
python main.py
```

## Node

```powershell
npm install
npm start
```

## Rules

- One clear entry point (`main.py` / `index.js`); helpers alongside it.
- Write generated files to `../output/`, never next to the source.
- Read inputs from `../data/`.
- Keep secrets in `.env` (gitignored) and document the required keys here.

### Required environment variables

| Name | Purpose |
|------|---------|
|      |         |
