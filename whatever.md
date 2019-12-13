$$\begin{aligned}
\sum_{j=1}^{n}(i,j)^{G}[i,j]^{L}x_{j}&\equiv a_{i}\\
\sum_{j=1}^{n}j^{L}(i,j)^{G-L}x_{j}&\equiv a_{i}i^{-L}\\
\sum_{d=1}^{n}d^{G-L}\sum_{j=1}^{n}[(i,j)=d]j^{L}x_{j}&\equiv a_{i}i^{-L}
\end{aligned}$$

$$\begin{aligned}
f(d)&=\sum_{j=1}^{n}[(i,j)=d]j^{L}x_{j}\\
F(d)&=\sum_{j=1}^{n}[d|(i,j)]j^{L}x_{j}\\
&=\sum_{d|j}j^{L}x_{j}\\
F(d)&=\sum_{d|k}f(k)\\
f(d)&=\sum_{d|k}F(k)\mu(\cfrac{k}{d})\\
&=\sum_{d|k}\sum_{k|j}j^{L}x_{j}\mu({\cfrac{k}{d}})\\
&=\sum_{d|j}j^{L}x_{j}\sum_{k|\tfrac{j}{d}}\mu(k)\\
&=\sum_{d|j}j^{L}x_{j}[j=d]\\
&=d^{L}x_{d}
\end{aligned}$$

$$\begin{aligned}
\sum_{d=1}^{n}d^{G-L}\sum_{j=1}^{n}[(i,j)=d]j^{L}x_{j}&\equiv a_{i}i^{-L}\\
\sum_{d=1}^{n}d^{G-L}\sum_{d|k}\sum_{j=1}^{n}[(i,j)|k]j^{L}x_{j}\mu({\cfrac{k}{d}})&\equiv a_{i}i^{-L}
\end{aligned}$$
