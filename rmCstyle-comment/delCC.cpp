#include <fstream>

int main(int argc,char *argv[]){
	if(argc < 3){
		printf("invail input number!\n");
		printf("the program accept at least two argument.\n");
		printf("have you type in adequate arguments?");
		return -1;
	}
	while(argc > 2){
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);
		if(!in.is_open())
		{
			printf("can\'t open source file!\n");
			printf("the source file doesn\'s exit?");
			return -1;
		}
		if(!out.is_open())
		{
			printf("can\'s open destinate file!\n");
			printf("have you create it yet?");
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
					if(in.eof()) break;
			}
		}
		in.close();
		out.close();

		printf("%s-->%s done!\n",argv[1],argv[2]);
		argc -= 2, argv += 2;
	}
	return 0;
}
