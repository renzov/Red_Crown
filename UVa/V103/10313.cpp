#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<algorithm>
using namespace std;

long long nw[ 301 ][ 301 ];

long long solve(int n,int c){
  if (n == 0) return (c>=0);
  if ( c == 0) return (n==0);
  if (n < 0) return 0;
  if ( c < 0 ) return 0;
  
  if (nw[n][c] != -1) return nw[n][c];

  nw[n][c] = solve(n-c,c) + solve(n,c-1);

  return nw[n][c];
  
}

int main(){

  memset(nw,-1,sizeof(nw));

  string line;
  int n,l1,l2;
  int cnt;

  while (getline(cin,line)){
	 stringstream in(line);
	 cnt = 1;
	 in >> n;
	 if (in >> l1){
		cnt++;
		if (in >> l2){
		  cnt++;
		}
	 }
	 if (cnt==1){
		  cout << solve(n,n) << "\n";
	 }
	 else if (cnt == 2){
		  cout<< solve(n,min(l1,n)) << "\n";
	 }
	 else {
		  cout << solve(n,min(n,l2)) - solve(n,min(n,l1-1)) << "\n";
	 }
  }

  return 0;
}