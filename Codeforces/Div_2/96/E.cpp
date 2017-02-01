#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;

bool dp[ 150 ][ 350 ][ 60 ][ 2 ];
int res;
int m,n;
string s;

inline int abs(int x){ return x>=0? x:-x; }

void solve( int ps , int  p, int ch ,int d ){
  if ( ps == m ){
	 if ( ch == n ){
		res = max( res , abs(p-150) );
		return;
	 }
	 else return;
  }
  if ( dp[ps][p][ch][d] ) return;
  dp[ps][p][ch][d] = true;
  char c;
  for (int i=0; (i+ch) <= n ; ++i ){
	 c = s[ps];
	 if ( i & 1 ) c = (c=='T')? 'F':'T';
	 if ( c == 'F' ){
		solve( ps + 1, p + ((d==1)? 1:-1) , ch + i, d );
	 }
	 else {
		solve( ps + 1, p , ch + i , !d );
	 }
  }
}

int main(){
  cin >> s >> n;
  m = s.size();
  memset( dp , false , sizeof(dp) );
  res = -INT_MAX;
  solve( 0 , 150 , 0 , 1 );
  cout << res << endl;
  return 0;
}