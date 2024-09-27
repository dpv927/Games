<div align="center">
  <h1>Sphere Uniform Points Generation</h1>
  <img src="https://github.com/user-attachments/assets/ddc17c58-0b38-4bcd-991c-8e331a5c561d" alt="image" width="500" height="500">
</div>

## About

This program tries to generate uniform points inside a sphere located in the middle of 
a window. This procedure is just an extension of my [Circle Uniform Points Generator](https://github.com/dpv927/raylib/tree/main/CirclePointsGen),
but this time the points are not attached to a grid.

## Theory

The basic procedure is written in python using `matplotlib` and `numpy`, then 
ported to rust using raylib. You can run the demo script with the following command:

```bash
python sphere.py
```

The result must be similar to this image:

<div align="center">
  <img src="https://github.com/user-attachments/assets/d48800a1-cf83-41ef-95e5-e548ccaf4af4" alt="image" width="500" height="500">
</div>

## References

- <a href="https://blogs.sas.com/content/iml/2016/04/06/generate-points-uniformly-in-ball.html">Generate points uniformly inside a d-dimensional ball </a>
