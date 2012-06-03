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

char w[1000005];
int s[1000005] = {0};

int main(){
  int k,n;
  scanf("%d",&k);
  scanf("%s",&w[1]);
 
  for ( n=1; w[n] ; ++n ){
	 s[ n ] = s[ n-1 ];
	 if ( w[n] == '1' ) s[n]++;
  }
  long long more=0,less=0;
  int l=1, r=1;
  
  for ( l = 1, r = 1;  l < n  ;  ++l ){
	 while ( r < n && (s[r] - s[l-1]) <= k ){ 
		r++;
	 }
	 if ( r < n ){
		more += (n - r);
	 }
	 else break;
  }
  for ( l = 1 , r = 1; l < n; ++l ){
	 while ( r < l ) r++;
	 while ( r < n && (s[r] - s[l-1]) < k ){
		r++;
	 }
	 if ( r < n ){
		less += ( n - r );
	 }
	 else break;
  }
  cout << less - more << endl;
  
  return 0;
}