import numpy as np
import matplotlib.pyplot as plt
import math
import random

# Generación de la permutación pseudoaleatoria
permutation = list(range(256))
random.shuffle(permutation)
p = permutation * 2  # Se duplica para evitar overflow en indexación

# Definición de los gradientes para el cálculo de Perlin Noise
gradients = [
    (1, 1, 0), (-1, 1, 0), (1, -1, 0), (-1, -1, 0),
    (1, 0, 1), (-1, 0, 1), (1, 0, -1), (-1, 0, -1),
    (0, 1, 1), (0, -1, 1), (0, 1, -1), (0, -1, -1)
]

def fade(t):
    return t * t * t * (t * (t * 6 - 15) + 10)

def lerp(t, a, b):
    return a + t * (b - a)

def grad(hash, x, y, z):
    g = gradients[hash % 12]
    return g[0] * x + g[1] * y + g[2] * z

def perlin_noise(x, y, z):
    X = math.floor(x) & 255
    Y = math.floor(y) & 255
    Z = math.floor(z) & 255
    x -= math.floor(x)
    y -= math.floor(y)
    z -= math.floor(z)
    u, v, w = fade(x), fade(y), fade(z)
    A = p[X] + Y
    AA, AB = p[A] + Z, p[A + 1] + Z
    B = p[X + 1] + Y
    BA, BB = p[B] + Z, p[B + 1] + Z
    return lerp(w, 
        lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
             lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
             lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1)))
    ) * 0.5 + 0.5  # Normaliza el resultado de -1 a 1 a 0 a 1


# Generamos el chunk de ruido
#chunk = np.zeros((size, size))

def gen_perlin(x,y):
    scale = 16.
    return perlin_noise(x/scale, y/scale, 0)

#for i in range(size):
#    for j in range(size):
#        x, y = i/scale, j/scale
#        chunk[i][j] = perlin_noise(x, y, z)