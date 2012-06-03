#include<cstdio>
#include<string>
#include<set>
#include<queue>
#include<map>
#include<cstring>
#include<cctype>
#include<iostream>
using namespace std;

int T[605][27];
string L[ 605 ];
char links[ 27 ];
long long dp[ 105 ][ 605 ];
int n;
int m;

long long solve( int left , int p ){
  if ( left < 0 ) return 0;
  if ( left == 0 ) return 1;
  if ( dp[left][ p ] != -1 ) return dp[left][p];
  long long res = 0;
  for ( int i=0; i< m; ++i ){
	 if ( T[p][i] >= 0 )
		res += solve( left - 1 , T[p][i] );
  }
  dp[left][p] = res;
  return res;
}

void to_up( char *s ){
  for (int i=0; s[i] ; ++i) s[i] = toupper(s[i]);
}

int main(){
  char st[ 15 ];
  bool chs[ 27 ];
  int t;
  string f;
  string tmp;
  int x,y,z;

  while ( scanf("%d %d %d",&x,&y,&z) && x ){
	 map< string , int > H;
	 memset( chs , false, sizeof(chs) );
	 t = m = n = 0;
	 for (int i=0; i < z; ++i){
		scanf("%s",st);
		to_up(st);
		if ( H.find( st ) == H.end() ){
		  H[ st ] = n;
		  L[n++] = st; 
		  for (int j=0; st[j] ; ++j) chs[ st[j] - 'A' ] = true;
		}
	 }
	 if ( n ){ t = strlen( st ); t--; }
	 for ( char c='A' ; c <= 'Z' ; ++c ) if ( chs[ c - 'A' ] ) links[m++] = c;
	 // Init of transitions
	 for ( int i=0; i<n; ++i )
		for (int j=0; j<m; ++j) 
		  T[i][j] = -1;
	 // Transitions
	 for ( int i=0;  i<n; ++i ){
		strcpy(st, L[i].substr( 1 ).c_str() );
		for ( int j=0 ; j < m ; ++j ){
			st[t] = links[j];
			st[t+1] = '\0';
			if ( H.find( st ) != H.end() ) T[i][j] = H[st];
		}
	 }
	 for (int i=0; i <= y; ++i) 
		for (int j=0; j < n; ++j)
			 dp[i][j] = -1;
	 long long res = 0;
	 for ( int i=0; i < n; ++i ){
		res += solve( y - L[i].size() , i );
	 }
	 printf("%lld\n",res);
  }
  return 0;
}

