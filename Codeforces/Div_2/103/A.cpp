#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0; i < (int)(n); ++i )
int a[150];

int main(){
  int n;
  int pmax,pmin;
  cin >> n;
  int maxi = -1;
  int mini = 200;
  forn(i,n){ 
	 cin >> a[i]; 
	 if ( a[i] > maxi ){ maxi = a[i]; pmax = i; }
	 if ( a[i] <= mini ){ mini = a[i]; pmin = i; }
  }
  int res;
  if ( pmin > pmax ){
	 res = (n-1) - pmin + pmax;
  }
  else {
	 res = (n-1) - pmin + pmax - 1;
  }
  cout << res << endl;
  return 0;
}