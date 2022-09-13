<h1 align="center">Just Renderer</h1>

<table>
<tr>
<td>
<p align="left"><img src="test/ajax_normal.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by Normals Integrator</b></p>
<p align="center"> 768px768p, ssp=1</p>
</td>
<td>
<p align="center"><img src="test/ajax_simple.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by Simple Integrator</b></p>
<p align="center"> 768px768p, ssp=32</p>
</td>
<td>
<p align="center"><img src="test/ajax_ao.png" alt="bunny_normal" width="100%">
<p align="center"><b> Ajax by AO Integrator</b></p>
<p align="center"> 768px768p, ssp=512</p>
</td>
</tr>
</table>

# Introduction

`Just Renderer` 是一款计划通过不断迭代最终实现离线渲染（软光追和软光栅）和实时渲染（OpenGL）的渲染器。 以往实现了玩具级的软光追渲染器和软光栅化渲染器，本项目将重新实现这两个渲染器的功能。

在学习 `nori` 和 `pbrt` 的过程中，对离线光线追踪有了更深的认识，因此本项目借鉴了两款渲染器的框架和代码实现。实时渲染部分计划采用 `OpenGL` 搭建，会在以后学习 `OpenGL` 的过程中逐渐实现。

本项目的目的是复现学术论文的趁手工具以及提升个人在图形学方面的工程实践能力，有很多对优秀代码的模仿和借鉴，例如使用 `Transform` 简化相机相关一系列变换实现的 `pbrt`、 使用充满魔法数字的 `toSRGB` 函数的 `mitusba1`。
# Features

## 纹理相关 `Common`

- [ ] 邻近过滤
- [ ] 双线性插值
- [ ] 三线性插值
- [ ] Mipmap
- [ ] Image Block
- [ ] Filter

## 相机相关 `Common`

- [x] 透视投影相机
- [ ] 正交投影相机

## 几何相关 `Common`

- [x] 轴对齐包围盒
- [ ] 非轴对齐包围盒
- [ ] 任意边界块

## 加速结构 `RayTracing`

- [x] BVH
- [x] Oct-Tree
- [ ] Kd-Tree

## 采样器 `RayTracing`

- [x] Independent Sampler
- [x] Random Sampler
- [x] Trapezoidal Sampler

## 积分器 `RayTracing`

- [x] Normal Integrator
- [x] Simple Integrator
- [x] AO Integrator
- [x] Whitted Integrator

## BxDF `RayTracing`

## 抗锯齿 `Rasterizer`

- [ ] SSAA
- [ ] MSAA


# References

> 1. https://wjakob.github.io/nori/
> 2. https://www.pbr-book.org/3ed-2018/contents
> 3. https://github.com/nothings/stb