# README

**usage**:

You are working in the directory where delCC file is:

>$ ls
> raw.txt  dest.txt  delCC  delCC.cpp

assuming that there is a file named "raw.cpp" contain c-style comment which is what you want to remove.eg:

>// i am a c-style comment
>int main(){
>return 0;
>} 

Then type in the following command in *command line*:

>$ ./delCC raw.cpp dest.cpp

There will be codes without comments in dest.cpp which is a file *alread exit*.eg:

> int main(){
> return 0;
> }
