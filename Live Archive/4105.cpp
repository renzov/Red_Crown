#include<cstdio>
#include<cstring>

char T[505][505];
char dp[505][505];

int main(){
  
  int runs;
  int s,t;
  char str[5];
  int i,j;
  bool found;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&s,&t);
	 for (j=1; j <= s; ++j) T[0][j] = 1;
	 for (i=1; i <= t; ++i){
		for (j=1; j <= s; ++j){
		  scanf("%s",str);
		  if (str[0] != 'u') T[i][j] = str[0];
		  else {
			 if ( T[i-1][j] != 'r' && T[i-1][j] != 's' ) T[i][j] = T[i-1][j];
			 else if (T[i-1][j] == 's') T[i][j] = 0;
			 else T[i][j] = 1;
		  }
 		}
	 }
	 
	 memset(dp,0,sizeof(dp));
	 found = false;
	 
	 for (i=0; i <= t; ++i) T[i][s+1] = 1;
	 for (i=0; i <= t; ++i) dp[i][0] = 1;
	 
	 for (i=1; i <= t && !found; ++i){
		for (j=1; j <= (s+1) && !found; ++j){
		  if ( T[i][j] == 1 ){
				dp[i][j] |= dp[i-1][j-1];
				dp[i][j] |= dp[i-1][j];
				if ( j != (s+1) ) dp[i][j] |= dp[i-1][j+1];
				else if ( dp[i][j] ){
				  printf("%d\n",i-1);
				  found = true;
				}
		  }
		}
	 }
	 if ( !found && dp[t][s] ) printf("%d\n",t);
	 else if (!found) puts("-1");
  }
  
  return 0;
}