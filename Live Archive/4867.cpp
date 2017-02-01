#include<cstdio>
int n,m;
int H[1005][1005] = {0};

inline int sum( int a , int b , int c, int d ){ return H[c][d] - H[c][b-1] - H[a-1][d] + H[a-1][b-1]; }
inline int min( int a,int b ){ return a <= b? a:b; }
bool possible( int k ){
  for ( int i=1; i <= (n-k+1); ++i ){
	 for ( int j=1; j <= (m-k+1); ++j ){
		if ( sum( i , j , i + k - 1 , j + k - 1 ) == (k*k) ) return true;
	 }
  }
  return false;
}

int main(){
  int c;
  while ( scanf("%d %d",&n,&m) && n && m ){
	 for ( int i=1; i <= n; ++i ){
		for ( int j=1; j <= m; ++j ){
		  scanf("%d",&c);
		  H[i][j] = c + H[i-1][j] + H[i][j-1] - H[i-1][j-1];
		}
	 }
	 if ( H[n][m] == 0 ){
		printf("0\n");
	 }
	 else {
		int r = min( n , m );
		int l = 1;
		int mid;
		while ( (r-l) > 1 ){
		  mid = ( l + r ) >> 1;
		  if ( possible( mid ) ){
			 l = mid;
		  }
		  else {
			 r = mid;
		  }
		}
		if ( possible( r ) ) l = r;
		printf("%d\n",l);
	 }
  }
  return 0;
}