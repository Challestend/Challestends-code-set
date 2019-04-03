$$\begin{aligned}
\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=0}^{n-2j}d(\cfrac{(i+2j)^{2}-i^{2}}{4})&=\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=0}^{n-2j}d(j(j+i))\\
&=\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=0}^{n-2j}\sum_{x|j}\sum_{y|(j+i)}[x\perp y]\\
&=\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=0}^{n-2j}\sum_{x|j}\sum_{y|(j+i)}\sum_{z|x,z|y}\mu(z)\\
&=\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=0}^{n-2j}\sum_{z|j,z|(j+i)}d(\cfrac{j}{z})d(\cfrac{j+i}{z})\mu(z)\\
&=\sum_{j=1}^{\tfrac{n}{2}}\sum_{z|j}d(\cfrac{j}{z})d(\cfrac{j}{z})\mu(z)+\sum_{j=1}^{\tfrac{n}{2}}\sum_{i=1}^{n-2j}\sum_{z|j,z|i}d(\cfrac{j}{z})d(\cfrac{j+i}{z})\mu(z)\\
&=\sum_{d=1}^{\tfrac{n}{2}}\sum_{i=1}^{\tfrac{n}{2d}}d^{2}(i)\mu(d)+\sum_{d=1}^{\tfrac{n}{2}}\sum_{j=1}^{\tfrac{n}{2d}}d(j)\sum_{i=1}^{\tfrac{n-2jd}{d}}d(j+i)\mu(d)\\
&=\sum_{d=1}^{\tfrac{n}{2}}\left(\sum_{i=1}^{\tfrac{n}{2d}}d^{2}(i)+\sum_{j=1}^{\tfrac{n}{2d}}d(j)\sum_{i=1}^{\tfrac{n-2jd}{d}}d(j+i)\right)\mu(d)\\
&=\sum_{d=1}^{\tfrac{n}{2}}\left(\sum_{i=1}^{\tfrac{n}{2d}}d^{2}(i)+\sum_{j=1}^{\tfrac{n}{2d}}d(j)\sum_{i=1}^{\tfrac{n-2jd}{d}+j}d(i)-\sum_{j=1}^{\tfrac{n}{2d}}d(j)\sum_{i=1}^{j}d(i)\right)\mu(d)
\end{aligned}$$

$$\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{n}[i\perp j]=2\sum_{i=1}^{n}\varphi(i)-1
\end{aligned}$$

$$\begin{aligned}
G_{i}&=C_{m}^{i}C_{n}^{is}\cfrac{(is)!}{(s!)^{i}}(m-i)^{n-is}\\
G_{i}&=\sum_{j=i}^{l}C_{j}^{i}F_{j}\\
F_{i}&=\sum_{j=i}^{l}(-1)^{j-i}C_{j}^{i}G_{j}\\
&=\sum_{j=i}^{l}(-1)^{j-i}C_{j}^{i}C_{m}^{j}C_{n}^{js}\cfrac{(js)!}{(s!)^{j}}(m-j)^{n-js}\\
&=\sum_{j=i}^{l}(-1)^{j-i}\cfrac{j!m!n!(js)!}{i!(j-i)!j!(m-j)!(js)!(n-js)!(s!)^{j}}(m-j)^{n-js}\\
&=\cfrac{m!n!}{i!}\sum_{j=i}^{l}\cfrac{(-1)^{j-i}}{(j-i)!}\cfrac{(m-j)^{n-js}}{(m-j)!(n-js)!(s!)^{j}}
\end{aligned}$$
