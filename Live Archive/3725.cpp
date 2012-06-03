#include<cstdio>
#include<climits>
const int MAX = 12; 
#define forn(i,n) for( int i=0; i < (int)(n) ; ++i )
int G[12][12];
bool used[12] = {0};
int n;
int best;
inline int min( int a , int b ){ return a<=b? a : b; }

void backtrack( int u , int sum , int m ){
  if ( m == n ){
	 sum += G[u][0];
	 if ( sum < best ) best = sum;
	 return;
  }
  for ( int v=1; v <= n; ++v ){
	 if ( !used[v] && ( ( sum + G[u][v] ) < best )  ){
		used[v] = true;
		backtrack( v , sum + G[u][v] , m + 1 );
		used[v] = false;
	 }
  }
}

int main(){
  while ( scanf("%d",&n) && n ){
	 forn( i , n + 1 )
		forn( j , n + 1  )
		  scanf("%d",&G[i][j]);
	 forn(k,n+1)
		forn(i,n+1)
		  forn(j,n+1)
			 G[i][j] = min( G[i][j] , G[i][k] + G[k][j] );
	 best = INT_MAX;
	 backtrack( 0 , 0 , 0 );
	 printf("%d\n",best);
  }
  return 0;
}