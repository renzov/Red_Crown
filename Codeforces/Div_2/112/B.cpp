#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<climits>
#include<vector>
#include<string>
#include<set>
#include<queue>
#include<list>
#include<stack>
#include<map>
#include<algorithm>
#include<numeric>
#include<sstream>
#include<iostream>
using namespace std;

int main(){
  
  long long n;
  long long k;
  
  cin >> n >> k;
  
  long long l = 0;
  long long r = n;
  long long m;
  long long sum;
  long long pot;
  while ( (r-l) > 1 ){
	 m = ( l + r ) >> 1LL;
	 sum = 0;
	 pot = 1;
	 while ( pot <= m ){
		sum += ( m / pot );
		pot *= k;
	 }
	 if ( sum >= n ) r = m;
	 else l = m + 1;
  }
  m = l;
  sum = 0;
  pot = 1;
  while ( pot <= m ){
	 sum += ( m / pot );
	 pot *= k;
  }
  if ( sum >= n ) r = m;
  cout << r << endl;
  return 0;
}