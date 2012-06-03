#include<cstdio>
bool pred[205][10002];
bool dp[205][10002];
bool sel[205];
int w[205];

void backtrack( int p , int l ){
  if (p<1 || l <= 0) return;
  if (pred[p][l]){
	 sel[p] = true;
	 backtrack( p-1 , l - w[p] );
  }
  else {
	 backtrack( p-1 , l );
  }
}

int main(){

  int runs;
  int m;
  int n;
  int s;
  int t;
  bool change;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&m);
		m *= 100;
		for (int i=0; i <= m; ++i){ dp[0][i] = false; pred[0][i] = false; }
		dp[0][0] = true;
		s = 0;
		n = 0;
		while ( scanf("%d",w+n+1) && w[n+1] ){
		  for (int i=0; i <= m; ++i){ dp[n+1][i] = dp[n][i]; pred[n+1][i] = false; }
		  change = false;
		  for (int j=0; j <= (m - w[n+1]); ++j){
			 if ( dp[n][j] && (s - j) <= m){
				dp[n+1][j+w[n+1]] = true;
				pred[n+1][j+w[n+1]] = true;
				change = true;
			 }
		  }
		  if (!change){
			 while (scanf("%d",&t) && t);
			 break;
		  }
		  s += w[n+1];
		  n++;
		}
		for (int i=0; i <= n; ++i) sel[i] = false;
		for (int i=m; i >= 0; --i){
		  if (pred[n][i]){
			 backtrack( n , i );
			 break;
		  }
		}
		printf("%d\n",n);
		for (int i=1; i <= n; ++i)
		  if ( sel[i] ) puts("port");
		  else puts("starboard");
		if (runs) putchar('\n');
  }

  return 0;
}