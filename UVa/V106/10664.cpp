#include<cstdio>
#include<cstring>
#include<cstdlib>

bool dp[2][200];
int v[25];

int main(){
  char line[5000];
  int runs;
  int n;
  int S;
  int act,next;
  char *ptr;
  gets(line);
  sscanf(line,"%d",&runs);
  while (runs--){
	 gets(line);
	 ptr = strtok(line," ");
	 n = 0;
	 S = 0;
	 while (ptr != NULL){
		v[n] = atoi(ptr);
		S += v[n];
		n++;
		ptr = strtok(NULL," ");
	 }
	 if (S & 1){
		puts("NO");
	 }
	 else {
		S >>= 1;
		bool ok = false; 
		for (int i=0; i <= S; ++i) dp[0][i] = dp[1][i] = false;
		act = 0; next = 1;
		dp[0][0] = true;
		for (int i=0; i < n; ++i){
		  for (int j=0; j <= S; ++j){
			 if ( dp[act][j] ){ 
				dp[next][j] = true;
				if ( (j + v[i]) <= S ) dp[next][j + v[i]] = true;
			 }
		  }
		  if ( dp[next][S] ){ ok = true; break; }
		  act = 1 - act;
		  next = 1 - next; 
		}
		if (ok) puts("YES");
		else puts("NO");
	 }
  }
  return 0;
}
