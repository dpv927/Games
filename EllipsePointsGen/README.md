<div align="center">
  <h1>Ellipse Points Generation</h1>
  <img src="https://github.com/user-attachments/assets/bc29ab29-6acf-452f-9e3b-72412ec2af46" alt="image" width="500" height="500">
</div>

## About

This program tries to generate uniform points inside a ellipse located in the middle of 
a window. This procedure is useful for the first phase of room generation in
a game named TinyKeep, where rooms (rectangles) are generated within a given radius
for later calculations (as <a href="https://github.com/dpv927/raylib/tree/main/CirclePointsGen">CirclePointsGen</a>).

Because dungeons are composed of tiles, the points generated for the circle will not
be calculated for the (x,y) coordinates of the window, but for the tile grid, unless
the tile size is 1. Because of this, approximations are made for the points and some
of the generated points may end up outside the circle, although these small errors 
do not significantly affect the results in later steps of the TinyKeep algorithm.

## Theory

The basic procedure is written in python using `matplotlib` and `numpy`, then 
ported to rust using raylib and adding a few things in order to make the 
algorithm usable for the TinyKeep's algorithm.

You can run the demo script with the following command:
```bash
python ellipse.py
```

The result must be similar to this image:

<div align="center">
  <img src="https://github.com/user-attachments/assets/f18d684a-0db8-40d7-a073-65643d67f846" alt="image" width="500" height="500">
</div>

## References

- <a href="https://blogs.sas.com/content/iml/2023/08/28/random-uniform-ellipse.html"> Generate random uniform points in an ellipse</a>
- <a href="https://www.reddit.com/r/gamedev/comments/1dlwc4/procedural_dungeon_generation_algorithm_explained/">TinyKeep's Procedural Dungeon Generation</a>
