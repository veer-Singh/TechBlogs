# All About the Camera

Explainer post covering two things end to end: the physical parts of a camera
module (lens → aperture → shutter → CFA → sensor), and the ISP pipeline that
turns the sensor's RAW Bayer output into YUV.

Reference hardware throughout: **Sony IMX623** (RGGB, f/2.0, electronic rolling
shutter, HDR split-pixel) feeding a **MAX96717** serializer over GMSL2.

## Status

Draft. Prose complete, both images in place. Needs a technical review pass and a
publishing target.

## Images

Recovered from the Joplin resource store
(`~/.config/joplin-desktop/resources/`) and imported:

| File                                | Was Joplin resource                | Shows                               |
|-------------------------------------|------------------------------------|-------------------------------------|
| `01-camera-sensor-parts.png`        | `4cc560a1797046b6bd00ed9b5b9b3e66` | Camera module cross-section diagram |
| `02-isp-pipeline.png`               | `51b1bf2df45e47ada4ab5956442a31e9` | ISP pipeline block diagram          |

Originals are in `assets/images/source/`; `export/` currently holds unmodified
copies, since both diagrams were already clean and publish-ready. Re-export from
`source/` if a target platform needs different dimensions.

### Hand-authored SVG diagrams (Part 3 — `color_balancing.md`)

Schematics drawn directly as SVG, no source file — edit the `.svg` in `export/`:

| File                             | Shows                                                        |
|----------------------------------|-------------------------------------------------------------|
| `setting-exposure-triangle.svg`  | shutter / gain / aperture feeding one EV, each side-effect  |
| `setting-ev-stops.svg`           | one stop = one EV = ×2 light; same EV via any control       |
| `setting-bit-depth.svg`          | ideal ramp vs 3-bit / 5-bit quantisation (banding)          |
| `setting-hdr-merge.svg`          | 3 sub-exposures → weighted merge → tone curve to display    |
| `setting-white-balance.svg`      | grey card under 3000 K → R/B gains → neutral; Kelvin scale  |
| `setting-denoise-sharpen.svg`    | one edge: noisy → denoised (softened) → sharpened (halo)    |
| `setting-autofocus.svg`          | CDAF contrast hill-climb (hunting) vs PDAF phase disparity  |

These are schematic explainers, not photo examples. Real before/after captures
(HDR on/off, WB presets, NR sweep, focus sweep) could replace or supplement them
later if the post gets a shoot.

## Notes on this draft

- The duplicated "The pipeline splits into three domains…" paragraph in the
  original notes was collapsed to a single instance (it now serves as the intro
  to the ISP section).
- "focal lens" in the notes was normalized to **focal length** throughout.
- The focus / focal-plane explanation was pulled out of the Aperture bullet into
  its own callout, since it describes a geometric plane rather than a component —
  which is the point the paragraph itself makes.
- The three ISP domains were given `###` headings (RAW / Demosaic / RGB / YUV) so
  the mental model is skimmable.

## Possible additions

- A `scripts/` demo that walks a real RAW frame through black level → demosaic →
  CCM → gamma with a saved image at each stage. Would turn this from an explainer
  into something reproducible.
- A short note on where the ISP physically lives in the automotive case (on-SoC
  vs. in-sensor), since the GMSL2 link carries RAW.
