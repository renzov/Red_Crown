#include<iostream>
#include<string>
#include<map>
#include<sstream>
#include<cctype>
#include<cmath>
#include<cstdio>
using namespace std;
bool rem[300] = {0};

void remove_sep(string &s){
  for (int i=0; i < s.size(); ++i){
		if ( rem[s[i]] ) s[i] = ' ';
		else s[i] = toupper(s[i]);
  }
}

int main(){
  int wc;
  string line;
  string w;
  getline(cin,line);
  rem[','] = true;
  rem['.'] = true;
  rem[':'] = true;
  rem[';'] = true;
  rem['!'] = true;
  rem['?'] = true;
  rem['\"'] = true;
  rem['('] = true; 
  rem[')'] = true;
  rem[(char)EOF] = true;
  rem[' '] = true;
  rem['\t'] = true;
  rem['\n'] = true;
  rem['\0'] = true;
  while ( line != "****END_OF_INPUT****" ){
		map<string,int> cnt;
		wc = 0;
		while ( line != "****END_OF_TEXT****" ){
		  remove_sep(line);
		  stringstream in(line);
		  while ( in >> w ){
			 wc++;
			 cnt[w]++;
		  }
		  getline(cin,line);
		}
		if (wc == 0) {
		  printf("%d %.1lf %.0lf\n",0,0.0,0.0);
		  getline(cin,line);
		  continue;
		}
		double Etotal = log10( wc*1.0 );
		double ET = 0.0;
		double ER;  
		for (map<string,int>::iterator it = cnt.begin(); it != cnt.end() ; it++){
			 ET += it->second*( Etotal - log10( it->second*1.0 ) );
		}
		ET /= wc;
		ER = (ET*100.0)/Etotal;
		ET = floor(ET*10 + 0.5)/10;
		ER = floor(ER);
		printf("%d %.1lf %.0lf\n",wc,ET,ER);
		getline(cin,line);
  }

  return 0;
}