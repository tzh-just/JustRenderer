<h1 align="center">Just Renderer</h1>

<table>
<tr>
<td>
<p align="left"><img src="test/ajax_normal.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by Normals Integrator</b></p>
<p align="center"> 768px768p, spp=1</p>
</td>
<td>
<p align="center"><img src="test/ajax_simple.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by Simple Integrator</b></p>
<p align="center"> 768px768p, spp=32</p>
</td>
<td>
<p align="center"><img src="test/ajax_ao.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by Ambient Occlusion Integrator</b></p>
<p align="center"> 768px768p, ssp=512</p>
</td>
</tr>
</table>

# Introduction

`Just Renderer` 基于以往实现了的软光追和软光栅项目，提取二者可复用的部分，以实现一个整合了光线追踪和光栅化的软渲染器，并通过重构使得项目更加易于扩展和维护。

为了打造一个用于复现学术论文的趁手工具以及在学习图形学的过程中提升工程实践能力，本项目对许多优秀的渲染器实现进行了模仿和借鉴，例如 `pbrt`、 `mitsuba` 和 `nori`。

# Features

## Common

### Texture

- [ ] `Nearest Neighbor Filtering`
- [ ] `Bilinear Filtering`
- [ ] `Trilinear Filtering`
- [ ] `Mipmap`
- [ ] `Image Block`

### Camera

- [x] `Perspective Camera`
- [ ] `Orthographic Camera`

### Bounds

- [x] `Axis-Aligned Bounding Box`
- [ ] `Oriented Bounding Box`

## Ray Tracing

### Accelerator

- [x] `BVH`
- [x] `OctTree`
- [ ] `Kd-Tree`

### Sampler

- [x] `Independent`
- [x] `Random`
- [x] `Trapezoidal`

### Integrator

- [x] `Normals`
- [x] `Simple`
- [x] `Ambient Occlusion`
- [x] `Whitted Style`

## Rasterization

### Anti-Alias

- [ ] `Super Sample`
- [ ] `Multi Sample`


# References

> 1. https://github.com/cs440-epfl/nori-base-2022
> 2. https://github.com/mmp/pbrt-v3
> 3. https://github.com/mitsuba-renderer/mitsuba
> 4. https://github.com/nothings/stb