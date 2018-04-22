# README

**faster algorithm for calculating log base 2**

## Refrences:
* <a href=https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog>Bit Twidding Hacks</a>
* <a href=https://www.fluentcpp.com/2017/10/27/function-aliases-cpp/>Function aliases in c++</a> 

## Function Included

* log2n: 接受两个传参的函数，第一个参数为无符号整数，第二个指定整数的位数（传入4表示32位数，5表示64位数，默认为64位）

* log2n_32：32位无符号整数，以二为底的对数

* log2n_64：64位无符号整数，以二为底的对数

* log2n_ubr32：32位无符号整数，以二为底的对数。计算机处理分支指令较慢时应用此函数更快。

* log2n_ubr64：64位无符号整数，以二为底的对数。计算机处理分支指令较慢时应用此函数更快。

* log2n_32p2：32位无符号整数，以二为底的对数，只可用于求2幂次数的对数。

* log2n_64p2：64位无符号整数，以二为底的对数，只可用于求2幂次数的对数。 