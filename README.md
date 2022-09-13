<h1 align="center">Just Renderer</h1>

# Introduction

`Just Renderer` 基于以前制作的玩具级软光追渲染器 `Just Tracer` 和软光栅渲染器 `Just Rasterizer`，迭代为整合离线渲染和实时渲染的软渲染器。

本项目诞生于学习 `nori` 和 `pbrt` 的过程中，由于图形学的知识体系有了新的认识和纠正，于是借鉴了两款渲染器的框架和代码实现。但最终目的是个人用于复现学术论文的趁手工具以及学习图形学的工程实践。

# Features

## General

### Texture
- [x] Load `TGA` File
- [ ] Nearest Neighbor Interpolation
- [ ] Bi-linear Interpolation
- [ ] Tri-linear Interpolation
- [ ] Mipmap

### Model
- [x] Load `OBJ` File
- [x] Mesh

### Camera
- [x] Perspective Camera

### Math
- [x] Vector
- [x] Point
- [x] Normal
- [x] Color
- [x] Matrix4x4
- [x] Bounding Box

### Tool
- [x] Timer
- [x] Random Number Generator

## Ray Tracing

### Acceleration Structure
- [x] BVH
- [x] Oct-Tree

### Sampler
- [x] Independent Sampler
- [x] Random Sampler
- [x] Trapezoidal Sampler

### Integrator
- [x] Normal Integrator
- [x] Simple Integrator
- [x] AO Integrator
- [x] Whitted Integrator

# Gallery
渲染结果展示都来自于 Nori 渲染器作业所提供的参数和模型。

## Bunny
<img src="test/bunny_normal.tga" alt="bunny_normal" width="50%">

## Ajax
<img src="test/ajax_normal.tga" alt="bunny_normal" width="50%">
<img src="test/ajax_simple.tga" alt="bunny_normal" width="50%">
<img src="test/ajax_ao.tga" alt="bunny_normal" width="50%">


