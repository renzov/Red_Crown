#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int N,M,L;
int C[ 2005 ];
bool dp[ 2005 ][ 1005 ] = {0};
char pre[ 2005 ][ 1005 ] = {0};
vector<int> used;

void backtrack( int n , int w ){
  if ( n == 0 ) return;
  if ( pre[n][w] == 2 ){
	 backtrack(n-1,w-C[n]);
	 used.push_back(n);
  }
  else {
	 backtrack( n-1 , w );
  }
}

int main(){
  int sum;
  while ( scanf("%d %d",&M,&L) && ( M || L ) ){
	 sum = 0;
	 scanf("%d",&N);

	 for ( int i=1; i <= N; ++i ){
		scanf("%d",C+i);
		sum += C[i];
	 }
	 for ( int i=1; i <= N; ++i )
		for ( int j=0; j <= M; ++j ){
			 dp[i][j] = false;
			 pre[i][j] = 0;
		}

	 dp[0][0] = true;
	 
	 for ( int i=1; i <= N; ++i ){
		for ( int j=0; j <= M; ++j ){
		  if ( dp[i-1][j] ){
			 dp[i][j] = true;
			 pre[i][j] = 1;
		  }
		  else if ( j >= C[i] && dp[i-1][j-C[i]] ){
			 dp[i][j] = true;
			 pre[i][j] = 2;
		  }
		}
	 }
	 used.clear();
	 bool found = false;
	 for ( int j=M; j >= 0; --j ){
		if ( dp[N][j] && (sum-j) <= L ){
		  found = true;
		  backtrack( N , j );
		  break;
		}
	 }
	 if ( !found ){
		puts("Impossible to distribute");
	 }
	 else {
		printf("%d ",(int)used.size());
		for ( int i=0; i < used.size(); ++i ) printf("%d ",used[i]);
		putchar('\n');
	 }
  }
  return 0;
}