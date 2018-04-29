#include <algorithm>
#include <cstring>
#include <fstream>
#include <list>

int main(int argc,char *argv[]){
	if(argc < 3){
		printf("invail input number!\n");
		printf("the program accept at least two argument.\n");
		printf("have you type in adequate arguments?");
		return -1;
	}
	while(argc > 2){
		std::ifstream in(argv[1]);
		if(!in.is_open())
		{
			printf("can\'t open source file!\n");
			printf("the source file doesn\'s exit?");
			return -1;
		}
		std::list<std::string> ToOrder;
		std::string line;
		while(!in.eof())
		{
			getline(in,line);
			if( line.length()>0 )
				ToOrder.push_front(line);
		}
		in.close();
		//input file stirng array was above

		ToOrder.sort();
		//sort the line in original file
		ToOrder.unique();
		//remove the duplicate line in the file

		std::ofstream out(argv[2]);
		if(!out.is_open())
		{
			printf("can\'s open destinate file!\n");
			printf("have you create it yet?");
			return -1;
		}
		for(auto it=ToOrder.cbegin(); it!=ToOrder.cend(); ++it)
			out << *it << "\n";
		out.close();

		printf("%s-->%s done!\n",argv[1],argv[2]);
		argc -= 2, argv += 2;
	}
	return 0;
}
