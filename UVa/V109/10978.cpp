#include<queue>
#include<map>
#include<iostream>
#include<string>
using namespace std;

int main(){
  
  int n,m;
  string card;
  string name;
  string r[60];

  while (cin >> n && n){
	 queue<int> q;
	 for (int i=0; i < n; ++i) q.push(i);
	 for (int i=0; i < n; ++i){
		  cin >> card >> name;
		  m = name.size();
		  for (int j=0; j < m-1; ++j){
			 q.push( q.front() ); q.pop();
		  }
		  r[ q.front() ] = card;
		  q.pop();
	 }
	 for (int i=0; i < n; ++i){
		  if (i > 0) cout << " ";
		  cout << r[i];
	 }
	 cout << endl;
  }

  return 0;
}