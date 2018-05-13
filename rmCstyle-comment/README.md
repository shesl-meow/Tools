# README

1. safe, complex and clumsy c++

2. dangerous(i have set protection as far as i can) and swift c 

**usage of program**:

## you should

You are working in the directory where delCC file is:

>$ ls
> raw.txt  dest.txt  delCC  delCC.cpp delCC.c

assuming that there is a file named "raw.txt" contain c-style comment which is what you want to remove.eg:

```c++
// i am a c-style comment
int main()
{
	return 0;
} 
```

Then type in the following command in *command line*:

>$ ./delCC raw.txt dest.txt

There will be codes without comments in dest.cpp which is a file *alread exit*.eg:

```c++
int main(){
	return 0;
}
```

## you can also

If you don't want another file store the result, type in the dash(-) represent the ommit destinate file name.

That is to say:

>$ ./delCC sourceFile.txt -

is equivalent to:

>$ ./delCC soueceFile.txt sourceFile.txt


**as for c program, it doesn't ommit option.**