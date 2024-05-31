# Usage

This solver takes $x_{min}, x_{max}, y_{min}, y_{max}, N$ and finds integral of witten down function $f(x)$ over area $[x_{min}; x_{max}] \times [y_{min}; y_{max}]$ by splitting it to evenly spaces grid with $N+1$ points over each axes,
then by splitting each one of remaining rectangles into two triangles and by finding integral over each triangle by function $$\frac{S(triangle)}{3} * (f(A) + f(B) + f(c))$$ which have $O(n^{-2})$ absolute error


To calculate your integral, firstly setup grid.txt file, which includes all information about your vertices, edges and triangles. To do so, launch
```bash
./2D_integral_solver setup N x_min x_max y_min y_max
```
Then after you have grid.txt file, use this command to have answer
```bash
./2D_integral_solver calculate
```
