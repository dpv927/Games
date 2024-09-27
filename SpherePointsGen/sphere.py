import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
matplotlib.use('TkAgg') 
import numpy as np

np.random.seed(12345)
D = 3
N = 1000     # Tamaño de la muestra = número de observaciones
radius = 2   # Radio de la bola

# Generar Y ~ MVN(0, I(d)), una matriz de N filas y
# d columnas con distribución normal estándar
Y = np.random.normal(0, 1, size=(N, D))

# Generar U ~ U(0,1), un vector de N 
# muestras uniformes
u = np.random.uniform(0, 1, size=N)

# Calcular r proporcional a la raíz
# d-ésima de U
r = radius * u**(1/D)

# Calcular la norma de cada fila en Y
norm_Y = np.linalg.norm(Y, axis=1)

# Generar X, los puntos uniformemente distribuidos
# en la bola d-dimensional
X = (r[:, np.newaxis] * Y) / norm_Y[:, np.newaxis]

# Plotting the generated points
# Crear una figura 3D
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
x, y, z = X[:, 0], X[:, 1], X[:, 2]

# Crear el diagrama de dispersión
ax.scatter(x, y, z, alpha=0.5)

# Configurar etiquetas
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Mostrar el gráfico
plt.show()
