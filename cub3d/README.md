*This project has been created as part of the 42 curriculum by tmura, tyokoyam.*

# Description

### Project Goal & Overview

The goal of this project is to create a pseudo-3D first-person graphical engine from scratch using Raycasting techniques, reminiscent of 90s classic masterpieces like *Wolfenstein 3D*. The entire engine is built in C, utilizing the MinilibX graphical library.

This software features a fully custom raycaster powered by the DDA (Digital Differential Analyzer) algorithm to achieve fast and optimized wall collision detection. It dynamically calculates the precise perpendicular wall distance to completely eliminate fisheye distortion, rendering clean, textured walls based on the player's position and orientation in real-time.

---

# Instructions

### Compilation MANDATORY

Run the following command in your terminal to compile the project:

```bash
make

```

### Compilation BONUS

```bash
make bonus

```


### Execution MANDATORY

Once the compilation is successful, run the executable by passing a valid `.cub` map file as an argument:

```bash
./cub3D maps/mandatory.cub

```
### Execution BONUS

```bash
./cub3D bonus maps/bonus.cub

```

# Resources

### Technical References

The following resources were instrumental in understanding and implementing the raycasting and sprite rendering systems:

* **Lode's Computer Graphics Tutorial - Raycasting Part 1 (Basics & DDA)**
[https://lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html)
*(Referenced for fundamental raycasting concepts, mathematical formulas, and fast grid-intersection logic using DDA)*
* **Lode's Computer Graphics Tutorial - Raycasting Part 3 (Sprites)**
[https://lodev.org/cgtutor/raycasting3.html](https://lodev.org/cgtutor/raycasting3.html)
*(Referenced for 3D coordinate transformation for sprites, Z-buffer occlusion handling, and texture mapping calculations)*
* **魚眼レンズよさようなら！完璧Raycasting実装への道 (note by fumix)**
[https://note.com/fumix/n/n8186825c2fff](https://note.com/fumix/n/n8186825c2fff)
*(Referenced as a visual and intuitive guide to grasp the underlying behavior of grid-line intersections within the DDA loop)*

### AI Usage

During development, an AI (LLM) was utilized as a **collaborative sounding board** to deeply grasp complex technical concepts. The AI was engaged for conceptual breakdown, logic auditing.
