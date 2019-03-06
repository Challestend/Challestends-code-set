https://www.luogu.org/problemnew/show/T70829



「Croi0001D1T3」Challestend and Binomial Inversion



idea/题面/思路/std/数据/spj：[$\color{red}\mathsf{rehtorbegnaro}$](https://www.luogu.org/space/show?uid=63352)



Challestend有一个$+\infty$行$m$列的矩阵$C$，行列均从$0$开始编号，其中的所有数都是有理数。

这个矩阵是如下定义的：

$$(a+b^{\tfrac{1}{m}})^{n}=\sum_{i=0}^{m-1}C[n][i]b^{\tfrac{i}{m}}$$

Challestend现在想知道$\sum_{i=0}^{m-1}C[n][i]$的值。但是他很快发现，答案可能会很大，所以他希望你舍去答案整数部分亿位及以上的数字。



仅一行，包含四个整数$n,m,a,b$。



仅一行，包含一个实数。你可以保留任意多位小数，只要你的答案与标准答案的绝对误差不超过$10^{-4}$即算作正确。



__样例#1解释__

$$(2+\sqrt{2})^{3}=20+14\sqrt{2}$$

__数据范围与约定__

对于$30\%$的数据，$n\leqslant 20$。

对于另外$10\%$的数据，$m=1$。

对于$100\%$的数据，$0\leqslant n\leqslant 9\times 10^{18}$，$1\leqslant m\leqslant 24$，$1\leqslant a,b\lt 2^{31}$。
