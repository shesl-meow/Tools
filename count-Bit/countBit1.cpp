#include <iostream>
using namespace std;

template <class T>
unsigned int NumBit1(T ip)
{
	unsigned int res = 0;
	while(ip){
		res++;
		ip = ip&(ip-1);
	}
	return res;
}

unsigned int ch2int(char*ip)
{
	unsigned int res = 0;
	for(int pos=0; ip[pos]!='\0'; pos++)
	{
		res *= 10;
		res += ip[pos] - '0';
	}
	return res;
}

int main(int argv,char*argc[]){
	if( argv<2 ) cout<<"Invalid input number!";
	else{
		auto tmp = ch2int(argc[1]);
		cout<<"Number of bit 1 in your input:"<<NumBit1(tmp)<<endl;
	}
	return 0;
}
