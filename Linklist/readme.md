### 链表
1. 用 C 语言简单实现单链表的操作
2. 将单链表应用于解决约瑟夫问题

### 线性结构小结
![](http://po4tl1gtx.bkt.clouddn.com/FpgmoHrfoRrq-QIypz5qipCDoJvF)

### 汉诺塔问题

#### 问题的引出
汉诺塔问题是一个经典的问题。汉诺塔（Hanoi Tower），又称河内塔，源于印度一个古老传说。大梵天创造世界的时候做了三根金刚石柱子，在一根柱子上从下往上按照大小顺序摞着64片黄金圆盘。

大梵天命令婆罗门把圆盘从下面开始按大小顺序重新摆放在另一根柱子上。并且规定，任何时候，在小圆盘上都不能放大圆盘，且在三根柱子之间一次只能移动一个圆盘。问应该如何操作？

![三个盘子的情况](https://images2015.cnblogs.com/blog/702782/201611/702782-20161114211933513-1127552732.gif)

![四个盘子的情况](https://images2015.cnblogs.com/blog/702782/201611/702782-20161114212352576-1869972276.gif)

那么64个盘子该怎么办呢?

一股脑地考虑每一步如何移动很困难，我们可以换个思路。先假设除最下面的盘子之外，我们已经成功地将上面的63个盘子移到了b柱，此时只要将最下面的盘子由a移动到c即可。

那么我们只需要：
1. 将b柱子作为辅助，把a上的63个圆盘移动到b上
2. 将a上最后一个圆盘移动到c
3. 将a作为辅助，把b上的62个圆盘移动到a上
4. 将b上的最后一个圆盘移动到c

![三根柱子从左往右依次为a,b,c](https://images2015.cnblogs.com/blog/702782/201611/702782-20161114213448920-1185627397.png)

也许你已经发现规律了，即每次都是先将其他圆盘移动到辅助柱子上，并将最底下的圆盘移到c柱子上，然后再把原先的柱子作为辅助柱子，并重复此过程。

这个过程称为递归，即定义一组基本操作，这组操作将规模小一点（或大一点）的操作当做一个整体——无需关心它的细节，只当它已经完成了——然后执行剩下的操作。而在更小或更大的规模中也依此操作，直到规模达到预定值。

在数学上，有些公式就是采用递归的方式定义的。例如阶乘和斐波那契数列（Fibonacci Sequence）

因此，递归实际上就是用自己来定义自己，自己调用自己。

#### 递归的本质

为了说明这个问题，我们举一个简单的例子:计算n的阶乘
```
f(n) = n!
```
其递归算法如下：
```c
int factorial(int n){
     if(n == 1)
          return 1;
     else
          return n * factorial(n-1);  
}
```
这段程序加载到内存的分配图如下：
![](http://mmbiz.qpic.cn/mmbiz_png/KyXfCrME6UJuiaBXeToqhXtsjY2ZsevDYOibSJWFicR3jrjeLmRlDUWnFylvxuS1wPiaDCKXdZ7IRGw4NmtWuHZRrg/0?wx_fmt=png)

由于递归是函数自身调用自身，所以程序被编译后代码段中只有一份代码。递归调用是如何进行的呢？

注意看堆栈中的栈帧啊， 每个栈帧就代表了被调用中的一个函数， 这些函数栈帧以先进后出的方式排列起来，就形成了一个栈， 栈帧的结构如下图所示：
![](http://mmbiz.qpic.cn/mmbiz_png/KyXfCrME6UJuiaBXeToqhXtsjY2ZsevDY1qRQqBrnE9J7FxdGkFMmw9A15FB2vcITJFElyOFfvZKbXrgm4Sibl1w/0?wx_fmt=png)

相信大家还记得《数据结构》（严蔚敏版）一书中提到的“工作记录”就是指函数栈帧。栈顶指针被称为“当前环境指针”。

忽略到其他内容， 只关注输入参数和返回值的话，阶乘函数factorial（4）的工作栈如下图所示：

![](http://mmbiz.qpic.cn/mmbiz_png/KyXfCrME6UJuiaBXeToqhXtsjY2ZsevDY73oicaGiczfP0WXiaMklnkZrHuU2FE9pPtJc1froaBgQf9ywPLDia7jibzg/0?wx_fmt=png)

其计算过程如下图所示：
![](http://mmbiz.qpic.cn/mmbiz_png/KyXfCrME6UJuiaBXeToqhXtsjY2ZsevDYicl0ibuoylicqca60rWpuN7gU3WUsCwIZxLbEk4nKzerXibM5ASdO2Phug/0?wx_fmt=png)

```c
factorial(l) = 1
factorial(2) = 2*factorial(l) = 2*1 = 2 
factorial(3) = 3*factorial(2) = 3*2 = 6
factorial(4) = 4*factorial(3) = 4*6 =24
```
注意， 每个递归函数必须得有个终止条件， 要不然就会发生无限递归了， 永远都出不来了。

当然针对于此递归算法，对于n的值是有限制的。因为堆栈容量是有限的，如果n值太大程序会崩掉。

该如何解决呢？
从上面的代码中可以知道`factorial(n) = n * factorial(n-1 ) `  ，这个计算式是整个程序的核心。 图中每个栈帧都需要记录下当前的n的值， 还要记录下一个函数栈帧的返回值， 然后才能运算出当前栈帧的结果。 也就是说使用多个栈帧是不可避免的。

可以使用下面的递归算法：
```c
int factorial(int n,int result){
     if(n == 1){
          return result;
     }
     else{
          return factorial(n-1,n * result);
     }
}
```
注意函数的最后一个语句， 就不是 n * factorial(n-1) 了， 而是直接调用factorial(....) 这个函数本身，  这就带来了巨大的好处。 

计算过程如下：

```c
factorial(4, l) 
= factorial(3, 4*1)  
= factorial(2, 3*4*1) 
= factorial(1, 2*3*4*1) 
= factorial(1, 24)
= 24 
```

当执行到factorial(1, 24)的时候直接就可以返回结果了。这就是妙处所在了，计算机发现这种情况，只用一个栈帧就可以搞定这些计算，无论n有多大。

![](http://mmbiz.qpic.cn/mmbiz_png/KyXfCrME6UJuiaBXeToqhXtsjY2ZsevDYD9WT8nrgce9noJ0Mkelen37MYXzQHhLecxia3SdGpJQViazJEezhLY0Q/0?wx_fmt=png)

这就是所谓的“尾递归”了， 当递归调用是函数体中最后执行的语句并且它的返回值不属于表达式一部分时， 这个递归就是尾递归。

现代的编译器就会发现这个特点， 生成优化的代码， 复用栈帧。 第一个算法中因为有个`n * factorial(n-1)` ,  虽然也是递归，但是递归的结果处于一个表达式中，还要做计算， 所以就没法复用栈帧了，只能一层一层的调用下去。
