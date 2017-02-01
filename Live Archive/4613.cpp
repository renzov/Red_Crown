#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int INF = 1000000000;
int dp[205][205][2];

int main(){

  int runs;
  int n,a,b;
  char c;
  int ta[205];
  int tb[205];
  int A[205];
  int B[205];
  int ls,ns;
  int le,ne;
  scanf("%d",&runs);
  while ( runs-- ){
		scanf("%d",&n);
		a = b = 0;
		for ( int i=0; i < n; ++i ){
		  scanf(" %c",&c);
		  if ( c == 'A' ){
			 scanf("%d %d",A+a,ta+a);
			 a++;
		  }
		  else {
			 scanf("%d %d",B+b,tb+b);
			 b++;
		  }
		}

		for ( int i=0; i <= a; ++i )
		  for ( int j=0; j <= b; ++j )
			 dp[i][j][0] = dp[i][j][1] = INF;

		dp[0][0][0] = dp[0][0][1] = 0;
		for ( int i=0; i <= a; ++i ){
		  for ( int j=0; j <= b; ++j ){
			 //last = 0
			 le = dp[i][j][0] - 10;
			 ls = le;
			 for ( int k=i; k < a ; ++k ){
				ns = max( ls + 10 , A[k] );
				ne = max( le + 10 , ns + ta[k] );
				dp[k+1][j][1] = min( dp[k+1][j][1] , ne );
				le = ne;
				ls = ns;
			 }
			 le = dp[i][j][1] - 10;
			 ls = le;
			 for ( int k=j; k < b ; ++k ){
				ns = max( ls + 10 , B[k] );
				ne = max( le + 10 , ns + tb[k] );
				dp[i][k+1][0] = min( dp[i][k+1][0] , ne );
				ls = ns;
				le = ne;
			 }
		  }
		}
		printf("%d\n",min( dp[a][b][0] , dp[a][b][1] ));
  }

  return 0;
}