<div align="center">
  <h1>Circle Points Generation</h1>
  <img src="https://github.com/user-attachments/assets/d0e35404-9e34-4a44-8d0c-050845c368aa" alt="image" width="500" height="500">
</div>

## About

This program tries to generate points inside a circle located in the middle of 
a window. This procedure is useful for the first phase of room generation in
a game named TinyKeep, where rooms (rectangles) are generated within a given radius
for later calculations.

Because dungeons are composed of tiles, the points generated for the circle will not
be calculated for the (x,y) coordinates of the window, but for the tile grid, unless
the tile size is 1. Because of this, approximations are made for the points and some
of the generated points may end up outside the circle, although these small errors 
do not significantly affect the results in later steps of the TinyKeep algorithm.

## References

- <a href="https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly">Generate a random point within a circle (uniformly)</a> 
- <a href="https://www.reddit.com/r/gamedev/comments/1dlwc4/procedural_dungeon_generation_algorithm_explained/">TinyKeep's Procedural Dungeon Generation</a>
