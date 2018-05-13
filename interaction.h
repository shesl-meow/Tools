#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <list>
using namespace std;

list<string> makelist(int argc,char *argv[])
{
	if(argc < 3){
		cout<<"invail input number!\n";
			"the program accept at least two argument.\n";
			"have you type in adequate arguments?\n";
			"P.S. use ommit destinate file name with dash(-) sign.";
		exit(1);
	}
	list<string> ARGV;
	string temp;
	for(int i=1; i<argc; ++i)
	{
		temp = string(argv[i]);
		ARGV.push_back(temp);
	}
	return ARGV;
}

void WtsArg(list<string> &argv)
{
	int pos = 0;
	list<string>::iterator it, prev;
	for(it = argv.begin(), prev = it;
		it != argv.end(); prev = it, ++it, ++pos)
	{
		if(pos&1 == 0) continue;
		if((*it)[0] == '-' && (*it)[1] == '\0')
		{
			cout<<"omitted destinate file: "<<*prev<<endl;
			*it = *prev;
		}
		if(access(it->c_str(), F_OK) == -1)
		{
			cout<< (string)"file " + *it + (string)" seems not exist, touch it.\n";
			system( ((string)"touch " +  it->c_str()).c_str() );
			if(access(it->c_str(), F_OK) == -1)
			{
				cout<<"touch failed.";
				exit(2);
			}
		}
	}
}


list<string> WtsInput(list<string> &argv)
{
	ifstream infile(argv.front().c_str());
	if(!infile.is_open())
	{
		cout<<"can\'t open source file!\n";
			"the source file doesn\'s exit?";
		exit(2);
	}
	argv.pop_front();
	list<string> input;
	string temp;
	while( getline(infile,temp) )
		input.push_back(temp);
	infile.close();
	return input;
}

void WtsOutput(list<string> &argv,list<string> output)
{
	ofstream outfile(argv.front().c_str(),ios::out);
	if(!outfile.is_open())
	{
		cout<<"can\'s open destinate file!\n";
			"have you create it yet?";
		exit(2);
	}
	argv.pop_front();
	while( !output.empty() )
	{
		outfile<<output.front()<<endl;
		output.pop_front();
	}
	outfile.close();
}

