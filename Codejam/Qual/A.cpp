#include<string>
#include<iostream>
#include<sstream>
#include<cctype>
using namespace std;
char H[256];

void init(){
  H['a'] = 'y'; H['b'] = 'h';
  H['c'] = 'e'; H['d'] = 's'; H['e'] = 'o'; H['f'] = 'c';
  H['g'] = 'v'; H['h'] = 'x'; H['i'] = 'd'; H['j'] = 'u';
  H['k'] = 'i'; H['l'] = 'g'; H['m'] = 'l'; H['n'] = 'b';
  H['o'] = 'k'; H['p'] = 'r'; H['q'] = 'z'; H['r'] = 't';
  H['s'] = 'n'; H['t'] = 'w'; H['u'] = 'j'; H['v'] = 'p';
  H['w'] = 'f'; H['x'] = 'm'; H['y'] = 'a'; H['z'] = 'q';
}

int main(){
  init();
  int runs;
  cin >> runs;
  string s,w;
  getline(cin,s);
  for ( int k=1; k <= runs; ++k ){
	 getline(cin,s);
	 w = s;
	 for ( int i=0; i < s.size(); ++i ){
		if ( isalpha(s[i]) ) w[i] = H[s[i]];
	 }
	 cout << "Case #" << k << ": " << w << endl;
  }
  return 0;
}