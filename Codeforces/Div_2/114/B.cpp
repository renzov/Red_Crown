#include<cstdio>
#include<iostream>
#include<cstring>
#include<cctype>
#include<string>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<list>
#include<climits>
#include<sstream>
using namespace std;
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )

bool espec( string &s ){
  forn(i,s.size()){
	 if ( !isspace( s[i] ) ){
		return s[i]=='#';
	 }
  }
  return false;
}

int main(){
  bool first = true;
  bool last = true;;
  string line;
  string lastS;
  string acc = "";
  while ( getline( cin,line ) ){
	 lastS = line;
	 if ( espec( line ) ){
		cout << acc;
		if ( !first ) cout << endl;
		cout << line << endl;
		acc = ""; first = true;
		last = true;
	 }
	 else {
		stringstream in(line);
		string w;
		while ( in >> w ){
		  acc += w;
		}
		last = false;
		first = false;
	 }
  }
  if ( acc != "" ) cout << acc << endl;
  else if ( lastS == "" ) cout << endl;
  return 0;
}