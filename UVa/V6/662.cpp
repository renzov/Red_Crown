#include<cstdio>
#include<climits>

int n,k;
int d[205];
int S[205][205];
int dp[205][35];
int pre[205][35];
int up[205];
int p[35][2];
int depot[35];

void get_sol( int pos , int dep , int right ){
  depot[ dep - 1 ] = pos;
  if ( dep == 1 ){
	 p[dep-1][0] = 0;
	 p[dep-1][1] = right;
	 return;
  }
  int prev = pre[pos][dep];
  int cut;
  for ( int i=prev; i <= pos; ++i ){
	 if ( (d[i] - d[prev]) > (d[pos]-d[i]) ){
		cut = i - 1;
		break;
	 }
  }
  p[dep-1][0] = cut + 1;
  p[dep-1][1] = right;
  get_sol( prev , dep - 1 , cut );
}

void precalc(){
  for ( int i=0; i < n; ++i )
	 for ( int j=i+1; j < n; ++j ){
		S[i][j] = 0;
		for ( int t=i+1; t < j; ++t ){
		  if ( (d[t] - d[i]) <= (d[j] - d[t]) ) S[i][j] += (d[t] - d[i]);
		  else S[i][j] += (d[j] - d[t]);
		}
	}
  
  for ( int i=0; i < n; ++i ){
	 up[i] = 0;
	 for ( int j = i+1; j < n; ++j )
		up[i] += ( d[j] - d[i] );
  }
}

int main(){
  int cases = 0;
  while ( scanf("%d %d",&n,&k) && n ){

	 cases++;

	 for (int i=0; i < n; ++i) scanf("%d",d+i);

	 precalc();

	 for ( int i=0; i < n; ++i ){
		dp[i][1] = 0;
		for ( int j=0; j < i; ++j )
		  dp[i][1] += (d[i] - d[j]);
	 }

	 for ( int j=2; j <= k; ++j ){
		for ( int i=j-1; i < n; ++i ){
		  dp[i][j] = INT_MAX;
		  for ( int t=j-2; t < i; ++t ){
			 if ( dp[i][j] > ( dp[t][j-1] + S[t][i] ) ){
				dp[i][j] = dp[t][j-1] + S[t][i];
				pre[i][j] = t;
			 }
		  }
		}
	 }

	 int last;
	 int best = INT_MAX;

	 for ( int i=k-1; i < n; ++i ){
		if ( best > (dp[i][k] + up[i]) ){
		  best = dp[i][k] + up[i];
		  last = i;
		}
	 }

	 get_sol( last , k , n-1 );
	 printf("Chain %d\n",cases);
	 for ( int i=0; i < k; ++i ){
		if ( p[i][0] < p[i][1] ){
		  printf("Depot %d at restaurant %d serves restaurants ",i+1,depot[i]+1);
		  printf("%d to %d\n",p[i][0] + 1,p[i][1] + 1);
		}
		else {
		  printf("Depot %d at restaurant %d serves restaurant ",i+1,depot[i]+1);
		  printf("%d\n",p[i][0] + 1);
		}
	 }
	 printf("Total distance sum = %d\n\n",best);
  }
  return 0;
}