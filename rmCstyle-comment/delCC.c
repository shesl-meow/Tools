#include <stdlib.h>
#include <stdio.h>

struct line{
	char buff[128];
	struct line* ntl;
};
void ReleaseLine(struct line *frtl)
{
	struct line *node = frtl, *prev;
	while( frtl->ntl != NULL )
	{
		while( node->ntl != NULL )
		{
			prev = node;
			node = node->ntl;
		}
		free(prev->ntl);
		prev->ntl = NULL;
	}
}

int main(int argc,char *argv[]){
	if(argc < 3){
		printf("invail input number!\n");
		printf("the program accept at least two argument.\n");
		printf("have you type in adequate arguments?");
		return -1;
	}
	FILE *in,*out;
	while(argc > 2){
		if( (in = fopen(argv[1],"r"))==NULL)
		{
			printf("can\'t open source file!\n");
			printf("the source file doesn\'s exit?");
			exit(1);
		}
		struct line *frtl = (struct line*)malloc(sizeof(struct line));
		struct line *node = frtl;
		char tmp = 'a'; int flag = 1; int pos=0;
		while(tmp != EOF)
		{
			tmp = fgetc(in);
			if(tmp == '\n')
			{
				(node->buff)[pos] = '\0';
				pos = 0;
				node->ntl = (struct line*)malloc(sizeof(struct line));
				node = node->ntl;
			}else if( flag && tmp == '/') flag = 0;
			else if( !flag && tmp == '/' )
			{
				pos = 0;
				while( tmp != '\n' && tmp != EOF )
					tmp = fgetc(in);
			}
			else if( !flag )
			{
				(node->buff)[pos] = '/'; ++pos;
				(node->buff)[pos] = tmp; ++pos;
				flag = 1;
			}else if( flag )
			{
				(node->buff)[pos] = tmp;
				++pos;
			}
			if( pos>=128 )
			{
				printf("struct line is too long!");
				exit(2);
			}
		}
		fclose(in);

		if( (out = fopen(argv[2],"w"))==NULL)
		{
			printf("can\'s open destinate file!\n");
			printf("have you create it yet?");
			exit(1);
		}
		node = frtl;
		fputs(out,node->buff);
		while( node->ntl != NULL)
		{
			node = node-> ntl;
			fputs(out,node->buff);
		}
		fclose(out);
		ReleaseLine(frtl);

		printf("%s-->%s done!\n",argv[1],argv[2]);
		argc -= 2, argv += 2;
	}
	return 0;
}