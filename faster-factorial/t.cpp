#include <iostream>
#include "factorial.h"
using namespace std;

int main()
{
	while(1){
		int a=0;
		cout<<"please enter a integer. a=?";
		cin>>a;
		if(a<=0) break;
		cout<<"\nsr factorial of a is:"<<SR::Fact(a)<<endl;
		cout<<"bs factorial of a is:"<<BS::Fact(a)<<endl;
	}
	return 0;
}
