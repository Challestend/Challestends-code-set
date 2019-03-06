https://www.luogu.org/problemnew/show/T69650



「Croi0001D2T3」Challestend and the Second War against Duliu



全名：Challestend and the Second War against Duliu

idea/思路/std/数据：[$\color{red}{\mathsf{Juan\_feng}}$](https://www.luogu.org/space/show?uid=66965)

题面：[$\color{red}\mathsf{rehtorbegnaro}$](https://www.luogu.org/space/show?uid=63352)

第一次毒瘤战争结束2019年后，JF逃出SLYZ中心大监狱，重新建立政权，试图将世界分块。于是机房人民普遍奋起反抗。



Challestend便是其中的一员。

为了有效地与强大的JF抗衡，Challestend组建了$n$支军队。

第$i$支军队一开始隶属于地区$p_{i}$，有$w_{i}$名士兵。除此之外，为了防止士兵们颓废，Challestend还在每支军队内部派遣了一名间谍。不过，这些间谍的监视方式有些奇怪，第$i$支军队内部的间谍会统计隶属地区在$l_{i}$到$r_{i}$之间的士兵的数量，包括直接隶属于这些地区的士兵，和隶属于这些地区的军队的士兵。

Challestend希望能够迅速执行以下四种操作：

1. 给出$x,y$，统计第$x$支到第$y$支军队内部的间谍的统计信息之和。
2. 给出$x,y,k$，向地区$x$到$y$每个地区派遣$k$名士兵。注意，这些士兵不属于任何军队。
3. 给出$x,k$，向地区$x$的每支军队派遣$k$名士兵。注意，这些士兵有具体的所属军队。
4. 给出$x,y$，令第$x$支军队归属地区$y$。



第一行包含两个整数$n,m$。

接下来$n$行，每行包含四个整数$p_{i},w_{i},l_{i},r_{i}$。

接下来$m$行，每行有如下四种可能：

1. `1 x y`，表示一次操作$1$。
2. `2 x y k`，表示一次操作$2$。
3. `3 x k`，表示一次操作$3$。
4. `4 x y`，表示一次操作$4$。



对于每一次操作$1$，输出一行一个整数。对$998244353$取模。



__数据范围与约定__

待定。
