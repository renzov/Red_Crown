#include<cstdio>
#include<climits>

char M[105][28];
int dp[105][28];
int next[105][28];

int main(){
  int i,j;
  int x,y,k;
  int runs = 0;
  int R,C;
  int ss;
  while ( scanf("%d %d",&R,&C) && R ){
	 runs++;
	 for (i=0; i < R; ++i){
		scanf("%s",M[i]);
	 }
	 for (i=0; i < R; ++i){
		for (j=0; j < C; ++j){
		  dp[i][j] = INT_MAX;
		  next[i][j] = -1;
		}
	 }
	 scanf("%d %d",&x,&y);
	 x--,y-=2;
	 for (i=0; i < C; ++i){
		if ( M[y][i] == 'O' ){
		  dp[y][i] = 0;
		}
	 }
	 for (i=y-1; i >= x; i--){
		 for (j=0; j < C; ++j){
			 if ( M[i][j] == 'O'){
				for (k=0; k < C; ++k){
				  if ( M[i+1][k] == 'O' && dp[i+1][k] < INT_MAX){
						ss = k != j;
						if ( dp[i][j] > ( dp[i+1][k] + ss ) ){
						  dp[i][j] = dp[i+1][k] + ss;
						  next[i][j] = k;
						}
				  }
				}
			 }
		 }
	 }
	 int mini = INT_MAX;
	 int start;
	 for (i=0; i<C; ++i){
		if ( dp[x][i] < mini ){ mini = dp[x][i]; start = i; }
	 }
	 if (runs > 1) putchar('\n');
	 printf("Case %d:\n\n",runs);
	 if ( mini == INT_MAX ) puts("Not available");
	 else {
		int act = start;
		int len = 1;
		int s = x;
		for (i=x; i <= y; ++i){
		  if ( next[i][act] == act ) len++;
		  else {
			 printf("%c: %d-%d\n",(char)(act+'A'),s+1,s+1+len);
			 act = next[i][act]; len = 1;
			 s = i+1;
		  }
		}
		//printf("%c: %d-%d\n",act+'A',s,s+l);
	 }
  }
  return 0;
}