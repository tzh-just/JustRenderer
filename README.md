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

`Just Renderer` 是一款基于以往制作的两款玩具级软光追和软光栅，复用二者可重复的部分，从而整合了离线渲染和实时渲染的软渲染器。在学习 `nori` 和 `pbrt` 的过程中，对离线渲染有了更深的认识，因此本项目借鉴了两款渲染器的框架和代码实现。本项目的目的是复现学术论文的趁手工具以及提升个人在图形学方面的工程实践能力。
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