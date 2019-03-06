https://www.luogu.org/problemnew/show/T65749



「Croi0001D1T1」Challestend and Hyperrectangle



idea/题面/思路/std/数据：[$\color{red}\mathsf{rehtorbegnaro}$](https://www.luogu.org/space/show?uid=63352)



Challestend有一个高维立方体。

这个立方体是$n$维的，它的$n$个边长分别是$a_{1},a_{2},\cdots,a_{n}$。一开始整个立方体都是白色的。现在Challestend给这个立方体的表面涂上了一层黑色，然后将它切成了$\prod_{i=1}^{n}a_{i}$个$n$个边长都是$1$的小立方体。

一个很明显的事实是，这些小立方体被涂成黑色的面数不一定相等。立方体$2^{n}$个顶点处的小立方体可能有$n$面被涂成黑色，完全在内部的小立方体可能还是白色。

现在Challestend想知道，对于$[0,2n]$上的每一个整数$i$，有多少个小立方体恰有$i$面被涂成黑色。因为答案可能会很大，他只想知道其对$998244353$取模的结果。



第一行包含一个整数$n$。

第二行包含$n$个整数，分别是$a_{1},a_{2},\cdots,a_{n}$。



仅一行，包含$2n+1$个整数，第$i$个整数表示有多少个小立方体恰有$i-1$面被涂成黑色。对$998244353$取模。



__数据范围及约定__

对于$20\%$的数据，$n\leqslant 20$。

对于另外$20\%$的数据，所有$a_{i}$相等。

对于$100\%$的数据，$4\leqslant n\leqslant 30000$，$1\leqslant a_{i}\lt 2^{64}$。

数据（很罕见地）有梯度。
