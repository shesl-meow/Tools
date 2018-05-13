#pragma once

#define factorial Fact

//Split Recursive algorithm
namespace SR
{
	static const unsigned int b[]={
		0x2,0xC,0xF0,0xFF00,0xFFFF0000,0xFFFFFFFF00000000};
	static const unsigned int S[]={1,2,4,8,16,32};
	static unsigned int log2n(unsigned int v,const int n=4)
	//计算log2n，向下取整
	{
		register unsigned int r = 0;
		for(int i=n; i>=0; --i)
			if(v&b[i])
			{
				v >>= S[i];
				r |= S[i];
			}
		return r;
	}
	
	static int cnt;		//记录当前乘到的奇数位置
	static inline long long Product(const int& n)
	//计算区间(cnt,cnt+2*n]的奇数积，并将cnt迭代到cnt+2*n
	{
		if(n<1) return 1;
		if(n==1) return cnt += 2;
		int m = n/2;
		return Product(n-m)*Product(m);
	}
	int Fact(int n)
	{
		if(n < 0) return 0;
		if(n < 2) return 1;
		cnt = -1;			//初始化乘到的奇数为1
		int h = 0;			//当次循环中，因子2的个数
		int shift = 0;		//n的阶乘中，因子2的个数
		long long prdt = 1;	//记录(1,shift]中的奇数积
		long long res = 1;	//阶乘结果
		
		for(int i=log2n(unsigned(n)); i>=0; --i)
		//引论：一个n位二进制数x(n:1)，它的阶乘中因子2的个数为：
		// x(n:2)+x(n:3)+...x(n:n-1)+x(n:n)
		//以此进行循环计算。
		//第i此循环中h的含义为：所有阶乘数字中因子含有2^(n-i)的数字个数
		{
			shift += h;
			h = n >> i;				//h= n!中，含有因子2^(n-i)的数字个数
			int len = (h>>2)+(h&1);	//本次循环与前一次循环h的半差值，即增长长度的一半
			if(len > 0)				//如果这个差值大于1
			{
				prdt *= Product(len);
				res *= prdt;
			}
		}

		return res << shift;
	}
}

//binary split algorithm
namespace BS{
	static int nminussumofbits(int v)
	//二进制数x(n:1)函数返回：x(n:2)+x(n:3)+...x(n:n-1)+x(n:n)
	{
		long w = (long)v;
		w -= (0xaaaaaaaa & w) >> 1;
		w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
		w = w + (w >> 4) & 0x0f0f0f0f;
		w += w >> 8;
		w += w >> 16;
		return v - (int)(w & 0xff);
	}
	static long long partProduct(int n, int m)
	//二分法计算[n,m]中奇数积
	{
		if (m <= (n + 1)) return (long long) n;
		if (m == (n + 2)) return (long long) n * m; 
		int k =  n + m >> 1 | 1;
		return partProduct(n, k) * partProduct(k + 2, m);
	}
	static void loop(int n, long long& p, long long& r)
	{
		if (n <= 2) return;
		loop(n / 2, p, r);
		p = p * partProduct(n / 2 + 1 | 1,n - 1 | 1);
		r = r * p;
	}
	long long Fact(int n)
	{
		long long p = 1, r = 1;
		loop(n, p, r);
		return r << nminussumofbits(n);
	}
}
