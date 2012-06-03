#include<string>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
  string s;
  string t;
  cin >> s;
  bool sign = false;
  if ( s[0] == '-' ){ t = s.substr(1); sign = true; }
  else t = s;
  int pos = t.find( '.' );
  if ( pos == string::npos ){
	 t += ".00";
  }
  else {
	 int w = t.size() - pos;
	 if ( w > 3 ){
		t = t.substr(0,pos+3);
		//cout << "sds "<< t << endl;
	 }
	 if ( w == 1 ) t+="00";
	 else if ( w == 2 ) t += "0";
  }
  string res = "";
  bool point = false;
  int c;
  for ( int i=t.size()-1; i >= 0 ; --i ){
	 if ( t[i] =='.' ){ point = true; c=0; res+="."; --i; }
	 if ( c == 3 ){ res += ","; c = 0; }
	 res += t[i];
	 if ( point ) c++;
  }
  reverse( res.begin(),res.end() );
  if ( sign ) cout << "(";
  cout << "$" << res;
  if ( sign  ) cout << ")";
  cout << endl;
  return 0;
}