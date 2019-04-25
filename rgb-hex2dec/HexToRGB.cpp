#include<iostream>
using namespace std;

int HexToDec(char x){
	if( x<='9' && x>= '0')
		return x - '0';
	else if( x>= 'A' && x<='F')
		return x - 'A' + 10;
	else if( x>= 'a' && x<='f' )
		return x - 'a' + 10;
	else return -1;
}
int power(int b,int e){
	int res = 1;
	for(int i=0; i<e; i++)
		res *= b;
	return res;
}


int main(){
	char usr[7];
	while(cin>>usr){
		int RGB[3]={0,0,0};
		for(int i=0; i<3; i++)
			for(int j=0; j<2; j++)
				RGB[i] += HexToDec(usr[i*2+j])*power(16,1-j);
		cout<<"RGB:\t";
		for(int i=0; i<3; i++)
			cout<<RGB[i]<<" ";
		cout<<endl;
	}
	return 0;
}