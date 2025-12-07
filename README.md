# 🔮 miniRT - Ray Tracing Engine

> "Simulating the physics of light, one pixel at a time."

[![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MinilibX-ff69b4?style=for-the-badge)](https://github.com/42Paris/minilibx-linux)
[![Math](https://img.shields.io/badge/Math-Linear_Algebra-orange?style=for-the-badge)](https://en.wikipedia.org/wiki/Linear_algebra)

![Main Render](assets/mini-RT1.png)
*("Rainbow Ring" test render generated with the engine)*

## 🔦 Introduction

**miniRT** is a physics-based rendering engine (Ray Tracing) written from scratch in C. Unlike traditional rasterization, this project simulates the real behavior of light rays: rays are cast from the camera, intersections with geometric objects are calculated, and pixel color is determined based on lighting and shadows.

The goal is to demonstrate a solid mastery of **linear algebra** (vectors, matrices, dot products) and **code optimization** without relying on external graphics engines.

---

## 🖼️ Gallery & Physics Capabilities

### The "Cornell Box" (Lighting Test)
This classic scene demonstrates the engine's ability to handle multiple geometries (planes, spheres, cylinders) and calculate cast shadows ("Hard Shadows") with precision from a point light source.

![Cornell Box](assets/mini-RT2.png)

### Technical Features
* **Geometric Primitives:**
    * **Spheres:** Analytical intersection (quadratic equation).
    * **Planes:** Infinite vector intersection.
    * **Cylinders:** Finite curved surface with caps (the most complex calculation in the project).
* **Lighting (Simplified Phong Model):**
    * **Ambient Light:** Constant base illumination.
    * **Diffuse Light:** Calculated based on the angle of incidence between the light ray and the surface normal (`N · L`).
* **Camera:** Full 3D positioning and orientation with variable FOV.

---

## 🛠️ Installation & Usage

The project requires a Unix environment (Linux/Mac) and the MinilibX graphics library (included or system-installed).

```bash
# 1. Clone the repository
git clone [https://github.com/grabier/miniRT.git](https://github.com/grabier/miniRT.git)

# 2. Compile the executable
cd miniRT && make

# 3. Run a scene
./miniRT scenes/scene_7.rt
