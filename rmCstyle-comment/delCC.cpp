#include "../inter.h"

int main(int argc,char *argv[]){
	list<string> ARGV = makelist(argc,argv);
	WtsArg(ARGV);
	string source,dest;

	while(!ARGV.empty()){
		source = ARGV.front();
		list<string> input = WtsInput(ARGV);
		string temp; bool flag =true;
		for(list<string>::iterator jt = input.begin(); jt != input.end(); ++jt)
		{
			int pos = 0;
			for(string::iterator it = jt->begin(); it != jt->end(); ++it, ++pos)
			{
				if( flag && *it == '/') flag = false;
				else if( !flag && *it == '/' )
				{
					*jt = jt->substr(0,pos-1);
					break;
				}
				else if( !flag ) flag = true;
			}
		}
		dest = ARGV.front();
		WtsOutput(ARGV,input);
		cout<<source<<"-->"<<dest<<" trans done!"<<endl;
	}
	return 0;
}
