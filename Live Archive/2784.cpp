#include<cstdio>
#include<cstring>
#include<climits>
int dp[1<<11][8][8];
int w[8];
int s[12][8];
int n;

int solve( int first , int last , int state ){
  if ( state == ((1<<n) - 1) ) return first == last ? w[last]:INT_MAX;
  if (dp[state][first][last] != -1) return dp[state][first][last];
  int i,j;
  int tmp,next;
  int best = INT_MAX;
  for (i=0; i < n; ++i){
	 if ( !((state >> i) & 1) ){
		for (j=0; j < 8; ++j){
		  if ( s[i][j] == last ){
			 next = s[i][(j+4)%8];
			 tmp = solve( first , next , state | (1<<i) );
			 if (tmp < INT_MAX && tmp + w[next] < best){
				best = tmp + w[last];
			 }
		  }
		}
	 }
  }
  return dp[state][first][last] = best;
}

int main(){
  int i,j;
  char t[12];
  int res,tmp;
  while (scanf("%d",&n) && n){
	 for (i=0; i < 8; ++i) scanf("%d",w+i);
	 for (i=0; i < n; ++i){
		 scanf("%s",t);
		 for (j=0; t[j] ;++j) 
			 s[i][j] = t[j] - 'A';
	 }
	 res = INT_MAX;
	 memset(dp,-1,sizeof(dp));
	 for (i=0; i < n; ++i){
		for (j=0; j < 8; ++j){
		  tmp = solve( s[i][j] , s[i][(j+4)%8] , 1<<i );
		  if (tmp < res) res = tmp;
		}
	 }
	 if (res < INT_MAX) printf("%d\n",res);
	 else puts("impossible");
  }
  return 0;
}