#include<cstdio>
#include<cstring>
#include<climits>
int memo[500][500];
int S[500];

inline int L(int a,int b){ return ( a == 0 )? S[b] : ( S[b] - S[a-1] ); }
inline int max(int a,int b){ return a>=b? a:b; }

int solve(int a,int b){
  if ( a == b ) return 0;
  if ( memo[a][b] != -1 ) return memo[a][b];
  int res = INT_MAX;
  int tmp;
  for ( int c=a; c < b; ++c){
	 tmp = solve( a , c ) + solve( c+1 , b ) + max( L(a,c) , L(c+1,b) );
	 if ( tmp < res ) res = tmp;
  }
  memo[a][b] = res;
  return res;
}

int main(){
  int C[500];
  int n;
  double f;
  int res;
  int a,b;
  int ca,cb;
  while ( scanf("%d %lf",&n,&f) && n ){
	 for (int i=0; i < n; ++i){
		scanf("%d",C+i);
	 }
	 S[0] = C[0];
	 for (int i=1; i < (n<<1); ++i) S[i] = S[i-1] + C[i%n];
	 memset(memo,-1,sizeof(memo));
	 res = INT_MAX;
	 if ( n == 1 ){ //Special Case
		printf("0.00\n");
		continue;
	 }
	 /* Iterate over all partitions */
	 for (int i=0; i < n; ++i){
		for (int j=i; j < n; ++j){
		  if ( (j - i + 1) < n ){
			 a = solve( i , j );
			 ca = L(i,j);
			 if ( j == (n-1) ){
				b = solve( 0 , i-1 );
				cb = L(0,i-1);
			 }
			 else if ( i==0 ){ 
				b = solve(j+1,n-1);
				cb = L(j+1,n-1);
			 }
			 else {
				b = solve( j + 1, n + i - 1 );
				cb = L( j + 1, n + i - 1 );
			 }
			 if ( (a + b + max(ca,cb)) <= res ) res = a + b + max(ca,cb);
		  }
		}
	 }
	 printf("%0.2lf\n",f*res);
  }
  return 0;
}