#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int best;
int n;

void dfs( char *s , int last , int l ){
  int i;
  bool b = false;
  int p;
  int nb = 0;
  for (i=0;  i<n; ++i){
	 if ( s[i] == 2 ) p = i;
	 else if ( s[i] ){
		if ( !b ){ b = true; nb++; }
	 }
	 else {
		if ( b ){ b = false; }
	 }
  }
  if ( nb <= 1 ){
	 best = l;
	 return;
  }
  if ( (l + 1) >= best ) return;
  if ( (p + 1) < n && ( p + 1 ) != last ){
	 swap( s[p] , s[p+1] );
	 dfs( s , p , l + 1 );
	 swap( s[p] , s[p+1] );
  }
  if ( p > 0 && ( p - 1 ) != last ){
	 swap( s[p] , s[p-1] );
	 dfs( s , p , l + 1 );
	 swap( s[p] , s[p-1] );
  }
  if ( (p + 2) < n && ( p + 2 ) != last ){
	 swap( s[p] , s[p+2] );
	 s[p] = !s[p];
	 dfs( s , p , l + 1 );
	 swap( s[p] , s[p+2] );
	 s[p+2] = !s[p+2];
  }
  if ( p > 1 && ( p - 2 ) != last){
	 swap( s[p] , s[p-2] );
	 s[p] = !s[p];
	 dfs( s , p , l + 1 );
	 swap( s[p] , s[p-2] );
	 s[p-2] = !s[p-2];
  }
}

int main(){
  int runs = 0;
  char s[105];
  int i;
  while ( scanf("%s",s) && s[0] != '-' ){
	 runs++;
	 n = strlen(s);
	 for ( i = 0; i < n; ++i ){
		if ( s[i] == 'B' ) s[i] = 1;
		else if ( s[i] == 'W' ) s[i] = 0;
		else s[i] = 2;
	 }
	 best = 10;
	 printf("%d. ",runs);
	 dfs( s , -1 , 0 );
	 if ( best == 10 ) printf("-1\n");
	 else printf("%d\n",best);
  }

  return 0;
}