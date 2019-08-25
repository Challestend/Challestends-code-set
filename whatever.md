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
