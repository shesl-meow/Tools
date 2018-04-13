#include <fstream>

int main(int argc,char *argv[]){
	if(argc != 3) return -1;
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	if(!in.is_open())
	{
		printf("can't open source file!\n
				the source file doesn's exit?");
		return -1;
	}
	if(!out.is_open())
	{
		printf("can's open destinate file!\n
				have you create it yet?");
		return -1;
	}

	char cur,next;
	while(!in.eof())
	{
		in.get(cur);
		if(cur != '/')
			out.put(cur);
		else if((next = in.get()) != '/')
			out<<cur<<next;
		else{
			out.put('\n');
			while( ((next = in.get()) != '\n'))
				if(!in.eof()) break;
		}
	}
	in.close();
	out.close();
	return 0;
}
