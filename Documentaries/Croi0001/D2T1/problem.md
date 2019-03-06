https://www.luogu.org/problemnew/show/T67080



「Croi0001D2T1」Challestend and Anarchy Heap



idea/题面/思路/std/数据：[$\color{red}\mathsf{rehtorbegnaro}$](https://www.luogu.org/space/show?uid=63352)



Challestend有一个小根堆。

相信您应该已经十分清楚小根堆是什么。如果您是一位STL选手并且忘记了如何实现小根堆，不要担心，请仔细阅读下面的伪代码

![](https://cdn.luogu.org/upload/pic/49317.png)

一般来讲，其中的`Cmp()`应该返回一个布尔型变量，如果给定的第一个参数小于第二个参数，其值为`true`，否则为`false`。

不过不幸的是，Challestend十分喜欢乱搞，他写了一个奇怪的`Cmp()`，这个函数等概率地随机返回`true`或`false`。

现在Challestend要实现以下函数

![](https://cdn.luogu.org/upload/pic/49319.png)

他想知道，`Challestend()`的返回值期望是多少。因为答案可能会很大并且会有很多位小数，他只想知道其对$998244353$取模的结果。



第一行包含一个整数$T$，表示数据组数。

接下来$T$行，每行一个整数$n$。



对于每组数据，输出一行一个整数。



__样例#1解释__

`CalculateFibonacciNumber(1)`返回$1$。调用`Insert(1)`以后，堆里只有一个$1$，此时`GetMininumValue()`的返回值只能是$1$。

`CalculateFibonacciNumber(2)`返回$1$。调用`Insert(1)`以后，堆里有两个$1$，此时`GetMininumValue()`的返回值只能是$1$。

__数据范围与约定__

对于$30\%$的数据，$n\leqslant 10^{7}$。

对于$100\%$的数据，$T\leqslant 400$，$1\leqslant n\lt 2^{64}$。
