import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg') 
import numpy as np

# Generate points uniformly inside a circular region in 2-D 
# https://blogs.sas.com/content/iml/2016/03/30/generate-uniform-2d-ball.html

radius = 2
twopi = np.pi * 2
num_points = 10000
tile_size = 10

theta = np.random.uniform(0, twopi, num_points)
r = np.sqrt(np.random.uniform(0, radius, num_points))

x = r * np.cos(theta)
y = r * np.sin(theta)

plt.scatter(x, y)
plt.show()
