#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

char rev(char x){
  char res = 0;
  for (int i=0; i < 8; ++i){
	 res <<= 1;
	 res |= ( x >> i ) & 1;
  }
  return res;
}

int main(){
  char s[250];
  gets(s);
  unsigned char r,b,x;
  for (int i=0; s[i] ; ++i){
	 r = rev(s[i]);
	 if (i > 0) b = rev(s[i-1]);
	 else b = 0;
	 if ( b < r ){ x = 256 - r + b; }
	 else x = (b - r)%256;
	 cout << (int)x << endl;
  }
  return 0;
}