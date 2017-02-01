#include<iostream>
#include<string>
#include<set>
#include<sstream>
#include<cctype>
using namespace std;
int n,m;

string add(string x,string c){
  if ( ( x.size() + c.size() ) <= m ) return (x+c);
  return x.substr(0,m-c.size()) + c;
}

string normalize(string s){
	 string res = "";
	 for (int i=0; i <s.size(); ++i){
		if (isalpha(s[i])) res += tolower(s[i]);
	 }
	 return res;
}

int main(){
  int cases = 0;
  string line,a,b,r;
  while ( cin >> n >> m && n ){
	 cases++;
	 cout << "Case " << cases << endl;
	 set<string> S;
	 getline(cin,line);
	 for (int i=0; i < n; ++i){
		getline(cin,line);
		stringstream in(line);
		in >> a;
		while ( in >> b );
		a = normalize(a);
		b = normalize(b);
		r = a[0];
		for ( int j=0; r.size() < m && j<b.size() ; ++j )
		  r+=b[j];
		if ( S.find( r ) == S.end() ){
		  cout << r << endl;
		}
		else {
		  string tmp,f;
		  bool found = false;
		  for (char j='1'; j <= '9' && !found; ++j ){
			 f = "";
			 f += j;
			 tmp = add(r,f);
			 if ( S.find(tmp) == S.end() ){
				found = true;
				r = tmp;
			 }
		  }
		  for (char j='1'; j <= '9' && !found; ++j){
			 for (char k='0'; k <= '9' && !found; ++k){
				f = "";
				f += j;
				f += k;
				tmp = add(r,f);
				if ( S.find(tmp) == S.end() ){
				  found = true;
				  r = tmp;
				}
			 }
		  }
		  cout << r << endl;
		}
		S.insert(r);
	 }
  }
  return 0;
}