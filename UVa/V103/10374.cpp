#include<iostream>
#include<string>
#include<map>
#include<climits>
using namespace std;

int main(){
  int runs;
  string line;
  string a,b;
  int n,m;
  
  cin >> runs;
  getline(cin,line);
  while (runs--){
	 map<string,string> person;
	 map<string,int> frec;
	 getline(cin,line);
	 cin >> n;	 getline(cin,line);
	 for (int i=0; i < n; ++i) {
		getline(cin,a);
		getline(cin,b);
		person[a] = b;
	 }
	 cin >> m;  getline(cin,line);
	 for (int i=0; i < m; ++i){
		getline(cin,a);
		if ( person.find(a) != person.end() ) frec[a]++;
	 }
	 int maxi = -INT_MAX;
	 int cnt = 0;
	 string res;
	 for (map<string,int>::iterator it = frec.begin(); it != frec.end() ; ++it){
		  if ( it->second > maxi ){
				cnt = 1; res = person[it->first]; maxi = it->second;
		  }
		  else if ( it->second == maxi ) cnt++;
	 }
	 if ( cnt > 1 ) cout << "tie" << endl;
	 else cout << res << endl;
	 if (runs) cout << endl;
  }
  
  return 0;
}