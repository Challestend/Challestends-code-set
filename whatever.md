$$\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{m}F((i,j))&=\sum_{d=1}^{n,m}\sum_{k|d}F(k)\sum_{i=1}^{n/d}\sum_{j=1}^{m/d}\sum_{x|i,x|j}\mu(x)\\
&=\sum_{d=1}^{n,m}\sum_{k|d}F(k)\sum_{x=1}^{n/d,m/d}\lfloor\cfrac{n}{dx}\rfloor\lfloor\cfrac{m}{dx}\rfloor\mu(x)\\
&=\sum_{i=1}^{n,m}\sum_{j|i}F(j)\mu(\cfrac{i}{j})\lfloor\cfrac{n}{i}\rfloor\lfloor\cfrac{m}{i}\rfloor\\
\sum_{i=1}^{n}\sum_{j|i}F(j)\mu(\cfrac{i}{j})&=\sum_{j=1}^{n}F(j)\text{sum}\mu(\lfloor\cfrac{n}{j}\rfloor)
\end{aligned}$$

$$\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{k|i,k|j}F(k)&=\sum_{d=1}^{n,m}\sum_{k|d}F(k)\sum_{i=1}^{n/d}\sum_{j=1}^{m/d}\sum_{x|i,x|j}\mu(x)\\
&=\sum_{d=1}^{n,m}\sum_{k|d}F(k)\sum_{x=1}^{n/d,m/d}\lfloor\cfrac{n}{dx}\rfloor\lfloor\cfrac{m}{dx}\rfloor\mu(x)\\
&=\sum_{i=1}^{n,m}\sum_{j|i}\sum_{k|j}F(k)\mu(\cfrac{i}{j})\lfloor\cfrac{n}{i}\rfloor\lfloor\cfrac{m}{i}\rfloor\\
\sum_{i=1}^{n}\sum_{j|i}\sum_{k|j}F(k)\mu(\cfrac{i}{j})&=\sum_{j=1}^{n}\sum_{k|j}F(k)\text{sum}\mu(\lfloor\cfrac{n}{j}\rfloor)
\end{aligned}$$

$n,m\leqslant 10^{7}$，$k\leqslant 1000$，$5\text{s}/512\text{MB}$。
