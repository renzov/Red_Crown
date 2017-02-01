#include<cstdio>
#include<cstring>
#include<cstdlib>

char line[10000];
bool dp[32][32][6002];
int a[35];
int s[35];
bool used[6002];
int res;
int n;

void solve( int p , int cnt , int sum ){
  if ( dp[p][cnt][sum + 3000] ) return;
  dp[p][cnt][sum + 3000] = true;
  if ( p == n ){
	 if ( !used[sum + 3000] ){ res++; used[ sum + 3000 ] = true; }
	 return;
  }
  sum = sum + a[p]*s[p]*(( cnt & 1 )?  -1:1); 
  if ( s[p] < 0 ) solve( p+1 , cnt + 1 , sum );
  if ( cnt > 0 ) solve( p+1 , cnt - 1 , sum );
  solve( p+1 , cnt, sum );
}

int main(){
  char *ptr;
  int sig;
  while (gets(line)){
	 ptr = strtok(line," ");
	 sig = 1;
	 n = 0;
	 res = 0;
	 while ( ptr ){
		s[n] = sig;
		a[n++] = atoi(ptr);
		ptr = strtok(NULL," ");
		if ( ptr == NULL ) break;
		if ( *ptr == '-' ) sig = -1;
		else sig = 1;
		ptr = strtok(NULL," ");
	 }
	 memset(dp,false,sizeof(dp));
	 memset(used,false,sizeof(used));
	 solve( 0 , 0 , 0 );
	 printf("%d\n",res);
  }
  return 0;
}


