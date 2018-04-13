#include <fstream>

int main(int argc,char *argv[]){
	if(argc != 3) return -1;
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	if(!in.is_open() || !out.is_open())
	{
		printf("can't open file!");
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
			while( ((next = in.get()) != '\n'))
				if(!in.eof()) break;
			out.put('\n');
		}
	}
	in.close();
	out.close();
	return 0;
}