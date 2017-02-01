#include<iostream>
#include<string>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

map< string , set<string> > H;

int main(){

  string s,t;

  while ( cin >> s && s != "XXXXXX" ){
		t = s;
		sort(t.begin(),t.end());
		H[t].insert(s);
  }
  
  while ( cin >> s && s != "XXXXXX" ){
		t = s;
		sort(t.begin(),t.end());
		if ( H.find(t) != H.end() ){
			 set<string>::iterator e = H[t].end();
			 for ( set<string>::iterator it = H[t].begin(); it != e ; it++)
				 cout << *it << endl;
		}
		else {
		  cout << "NOT A VALID WORD" << endl;
		}
		cout << "******" << endl;
  }

  return 0;
}