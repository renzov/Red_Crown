#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>
int C[105];
int M[105];
int dp[1<<16][2];
int Mask;
int end;
int s;
int add(int a,int b){
  int t = a + b;
  for (int i=0; i < s; ++i){
	 if ( ( (t >> (i<<1)) & 3 ) == 3 ) t ^= ( 1 << (i<<1) );  
  }
  return t;
}

int main(){
  char line[2000];
  int n,m;
  char *ptr;
  int v;
  int c;
  int t,ct;
  while ( scanf("%d %d %d",&s,&m,&n) && s){
	 while (getchar() != '\n');
	 Mask = 0;
	 ct = 0;
	 for (int i=1; i <= s; ++i){
		Mask |= 1 << (( i-1 )<<1);
	 }
	 end = Mask << 1;
	 int start = 0;
	 for (int i=0; i < m; ++i){
		gets(line);
		ptr = strtok(line," ");
		c = atoi(ptr);
		ct += c;
		t = 0;
		ptr = strtok(NULL," ");
		while (ptr != NULL){
		  v = atoi(ptr);
		  t |= 1 << (( v-1 )<<1);
		  ptr = strtok(NULL," ");
		}
		start = add(start,t);
	 }

	 for (int i=0; i < n; ++i){
		gets(line);
		ptr = strtok(line," ");
		C[i] = atoi(ptr);
		M[i] = 0;
		ptr = strtok(NULL," ");
		while (ptr != NULL){
		  v = atoi(ptr);
		  M[i] |= 1 << (( v-1 )<<1);
		  ptr = strtok(NULL," ");
		}
	 }
	 bool act = false;
	 bool next = true;
	 if ( start == end ){
		printf("%d\n",ct);
		continue;
	 }
	 for (int i=0; i < (1 << (s<<1)); ++i) dp[i][0] = dp[i][1] = INT_MAX;
	 dp[start][act] = ct;
	 for (int i=0; i < n; ++i){
		  for (int j=0; j < (1 << (s<<1)); ++j){
			 if (dp[j][act] < INT_MAX){
				if ( dp[j][next] > dp[j][act] ) dp[j][next] = dp[j][act];
				t = add( j , M[i] );
				if ( dp[t][next] > (dp[j][act] + C[i]) )
					dp[t][next] = dp[j][act] + C[i];
			 }
		  }
		  act = !act;
		  next = !next;
	 }
	 printf("%d\n",dp[end][act]);
  }
  return 0;
}