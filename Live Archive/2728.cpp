#include<cstdio>
#include<climits>

int times[55];
int start[55][55];
int end[55][55];
int dp[55][255];

inline int min(int a,int b){ return a<=b? a:b; }

int main(){
  int N;
  int T;
  int M1;
  int M2;
  int runs = 0;
  
  while (scanf("%d",&N) && N){
	 runs++;
	 
	 scanf("%d",&T);
	 for (int i=0; i < N-1; ++i) scanf("%d",times+i);
	 
	 scanf("%d",&M1);
	 
	 for (int i=0; i < 	M1; ++i) scanf("%d",&start[i][0]);
	 
	 for (int i=0; i < M1; ++i){
		for (int j=1; j < N; ++j){
		  start[i][j] = start[i][j-1] + times[j-1];
		}
	 }
	 
	 scanf("%d",&M2);
	 
	 for (int i=0; i < M2; ++i) scanf("%d",&end[i][N-1]);
	 
	 for (int i=0; i < M2; ++i){
		for (int j=N-2; j >= 0; --j){
		  end[i][j] = end[i][j+1] + times[j];
		}
	 }
	 /* Initialize the dp */
	 for (int i=0; i < N; ++i)
		for (int j=0; j <= T; ++j)
		  dp[i][j] = INT_MAX;
	 dp[0][0] = 0;
	 for (int j=0; j < T; ++j){
		for (int i=0; i < N; ++i){
		  if ( dp[i][j] < INT_MAX ){ /* Can reach state */
			 dp[i][j+1] = min( dp[i][j] + 1, dp[i][j+1] ); /* Can always stay */
			 if (i < N-1){ /* Go forward */
				for (int k=0; k < M1; ++k){
					 if ( start[k][i] == j && start[k][i+1] <= T ){
						 dp[i+1][ start[k][i+1] ] = min( dp[i][j] , dp[i+1][ start[k][i+1] ] );
					 }
				}
			 }
			 if ( i > 0 ){ /* Go Backward */
				for (int k=0; k < M2; ++k){
					 if ( end[k][i] == j && end[k][i-1] <= T ){
						 dp[i-1][ end[k][i-1] ] = min( dp[i][j] , dp[i-1][ end[k][i-1] ] );
					 }
				}
			 }
		  }
		}
	 }
	 printf("Case Number %d: ",runs);
	 if ( dp[N-1][T] >= INT_MAX ) puts("impossible");
	 else printf("%d\n",dp[N-1][T]);
  }
  return 0;
}