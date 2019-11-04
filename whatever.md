$$F(x)=\sum_{i=0}^{c-1}f_{i}x^{i}$$

试求

$$\sum_{i_{1}=1}^{m}\cdots\sum_{i_{n}=1}^{m}F((i_{1},\cdots,i_{n}))$$

$$\begin{aligned}
\sum_{i_{1}=1}^{m}\cdots\sum_{i_{n}=1}^{m}F((i_{1},\cdots,i_{n}))&=\sum_{d=1}^{m}F(d)\sum_{i_{1}=1}^{m}\cdots\sum_{i_{n}=1}^{m}[(i_{1},\cdots,i_{n})=d]\\
&=\sum_{d=1}^{m}F(d)\sum_{i_{1}=1}^{m/d}\cdots\sum_{i_{n}=1}^{m/d}[(i_{1},\cdots,i_{n})=1]\\
&=\sum_{d=1}^{m}F(d)\sum_{i_{1}=1}^{m/d}\cdots\sum_{i_{n}=1}^{m/d}\sum_{x|i_{1},\cdots,x|i_{n}}\mu(x)\\
&=\sum_{d=1}^{m}F(d)\sum_{x=1}^{m/d}\lfloor\cfrac{m}{dx}\rfloor^{n}\mu(x)\\
&=\sum_{i=1}^{m}\lfloor\cfrac{m}{i}\rfloor^{n}\sum_{j|i}F(j)\mu(\cfrac{i}{j})
\end{aligned}$$

$$\begin{aligned}
f(N)&=\sum_{i=1}^{N}\sum_{j|i}F(j)\mu(\cfrac{i}{j})\\
&=\sum_{j=1}^{N}F(j)\text{sum}\mu(\lfloor\cfrac{N}{j}\rfloor)
\end{aligned}$$

$1\leqslant n\lt 2^{31}$，$1\leqslant m\leqslant 10^{8}$，$1\leqslant c\leqslant 200$，$0\leqslant f_{i}\lt 998244353$，$6\text{s}/512\text{MB}$。

$$\begin{aligned}
F(x)&=\sum_{i=0}^{n-1}f_{i}x^{i}\\
G(x)&=\sum_{i=0}^{m-1}g_{i}x^{i}\\
\sum_{d|N}F(d)G(\cfrac{N}{d})&=\sum_{d|N}\sum_{i=0}^{n-1}\sum_{j=0}^{m-1}f_{i}g_{j}d^{i}(\cfrac{N}{d})^{j}\\&=\sum_{d|N}\sum_{k=0}\sum_{i-j=k}f_{i}g_{j}N^{j}d^{k}\\
&=\sum_{d|N}\sum_{k=0}^{c-1}h_{k}d^{k}\\
&=\sum_{k=0}^{c-1}h_{k}\sum_{d|N}d^{k}\\
&=\sum_{k=0}^{c-1}h_{k}\sigma^{k}(N)\\
\sigma(N)&=\prod_{i}\sum_{j=0}^{r_{i}}p_{i}^{j}\\
&=\prod_{i}\cfrac{p_{i}^{r_{i}+1}-1}{p_{i}-1}\\
\sigma^{k}(N)&=\prod_{i}\sum_{j=0}^{r_{i}}p_{i}^{kj}\\
&=\prod_{i}\cfrac{p_{i}^{k(r_{i}+1)}-1}{p_{i}^{k}-1}
\end{aligned}$$

$$O(n\operatorname{prmcnt}N\log\operatorname{mod})$$

$$\begin{aligned}
g_{i}&={n\choose i}\left(2^{2^{n-i}}-[i\gt 0]\right)\\
h_{i}&=2^{2^{i}}-[i\lt n]\\
g_{i}&={n\choose i}h_{n-i}\\
&=\sum_{j=i}^{n}{j\choose i}f_{j}\\
f_{i}&=\sum_{j=i}^{n}(-1)^{j-i}{j\choose i}g_{j}\\
&=\sum_{j=i}^{n}(-1)^{j-i}{j\choose i}{n\choose j}h_{n-j}\\
\sum_{i=0}^{n}[K\mid i]f_{i}&=\sum_{i=0}^{n}[K\mid i]\sum_{j=i}^{n}(-1)^{j-i}{j\choose i}{n\choose j}h_{n-j}\\
&=\sum_{i=0}^{n}\cfrac{1}{K}\sum_{k=0}^{K-1}\omega_{K}^{ki}\sum_{j=i}^{n}(-1)^{j-i}{j\choose i}{n\choose j}h_{n-j}\\
&=\cfrac{1}{K}\sum_{j=0}^{n}(-1)^{j}{n\choose j}h_{n-j}\sum_{k=0}^{K-1}\sum_{i=0}^{j}(-1)^{i}{j\choose i}\omega_{K}^{ki}\\
&=\cfrac{1}{K}\sum_{j=0}^{n}(-1)^{j}{n\choose j}h_{n-j}\sum_{k=0}^{K-1}(1-\omega_{K}^{k})^{j}
\end{aligned}$$

$$\begin{aligned}
F_{k}(x)&=\sum_{i\geqslant 0}i^{k}m^{i}x^{i}\\
&=\sum_{i\geqslant 0}\sum_{j=0}^{k}{k\brace j}i^{\underline{j}}m^{i}x^{i}\\
&=\sum_{j=0}^{k}{k\brace j}\sum_{i\geqslant 0}i^{\underline{j}}m^{i}x^{i}\\
G_{k}&=\sum_{i\geqslant 0}i^{\underline{k}}m^{i}x^{i}\\
G_{k}-G_{k-1}&=\sum_{i\geqslant 0}\left(i^{\underline{k}}-i^{\underline{k-1}}\right)m^{i}x^{i}\\
&=\sum_{i\geqslant 0}(i-k)i^{\underline{k-1}}m^{i}x^{i}\\
&=\sum_{i\geqslant 0}i\cdot i^{\underline{k-1}}m^{i}x^{i}-k\sum_{i\geqslant 0}i^{\underline{k-1}}m^{i}x^{i}\\
&=\sum_{i\geqslant 0}(i+1)^{\underline{k}}m^{i}x^{i}-(k+1)\sum_{i\geqslant 0}i^{\underline{k-1}}m^{i}x^{i}\\
&=\sum_{i\geqslant 0}i^{\underline{k}}m^{i-1}x^{i-1}-(k+1)\sum_{i\geqslant 0}i^{\underline{k-1}}m^{i}x^{i}\\
&=\cfrac{1}{mx}G_{k}-(k+1)G_{k-1}\\
G_{k}&=-\cfrac{mkx}{mx-1}G_{k-1}
\end{aligned}$$

$$
-\\
-\\
-\\
-\\
-\\
-\\
-\\
-\\
$$
