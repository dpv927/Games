<div align="center">
<h1>RGBbg</h1>
</div>

## About

Just a window with a colored background, which changes smoothly through the colors
Red-Green-Blue, without passing through black and white. The objective is not to go
for very dark or very white colors, but a softer intermediate ones.

## How its made

To do this, we start at `RGB(255,0,0)` (red), and increase the level of green, while
decreasing the intensity of red (both by one point). For example, a normal
iteration will be:

```
RGB(255,0,0,0)
RGB(224,1,0)
RGB(253,2,0)
...
```

This way, when green reaches the value 255, red will stabilize at 0. After that,
the procedure is repeated for blue and green components, as it was done for red-blue:

```
RGB(0,255,0)
RGB(0,254,1)
RGB(0,253,2)
...
```

Finally, the same will be done but this time with the green and the red, being now the
green the one that decreases its value, and the red the one that increases it. 

```
RGB(0,0,255)
RGB(0,1,254)
RGB(0,2,253)
...
```
