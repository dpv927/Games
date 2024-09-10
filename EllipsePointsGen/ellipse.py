import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg') 
import numpy as np

# Generate random uniform points in an ellipse
# https://blogs.sas.com/content/iml/2023/08/28/random-uniform-ellipse.html

def rand_ellipse(n, s, seed=None):
    if seed is not None:
        np.random.seed(seed)
    
    d = len(s)
    mu = np.zeros(d)

    # X ~ N(0, I_d)
    X = np.random.normal(mu, 1, size=(n, d))
    # U ~ U(0,1) 
    u = np.random.uniform(0, 1, size=n)
    # r proportional to d-th root of U
    r = u**(1/d)
    # Compute norms of X
    X_norm = np.linalg.norm(X, axis=1)
    # Uniform points in unit disk/ball
    Z = (r[:, np.newaxis] * X) / X_norm[:, np.newaxis]
    # Diagonal matrix with the sigma values
    L = np.diag(s)
    
    # Uniform points in the ellipse/ellipsoid
    return Z @ L.T               


seed = 12345
n = 1000
sigmas = [10, 3]
Y = rand_ellipse(n, sigmas, seed)

# Plotting the generated points
plt.figure(figsize=(6, 6))
plt.scatter(Y[:, 0], Y[:, 1], alpha=0.5)
plt.gca().set_aspect('equal', adjustable='box')
plt.title("1,000 Random Points in an Ellipse")
plt.grid(True)
plt.show()
