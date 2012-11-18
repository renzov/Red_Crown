#include<cstdio>
#include<cstring>
#include<climits>
int X[15];
int Y[15];
int n;
int dp[13][1<<13];
int d[15][15];

inline int abs( int x ){ return x < 0? -x:x; }
inline int min(int x,int y){ return x<=y? x:y; }
inline int D( int i ,int j ){ return abs(X[i] - X[j]) + abs(Y[i] - Y[j]); }

int solve( int u , int mask ){
	if ( mask == ((1<<n) - 1) ){
		return d[u][0];
	}
	if ( dp[u][mask] != -1 ) return dp[u][mask];
	int mini = dp[u][mask] = INT_MAX;
	int tmp;
	for ( int v = 1; v < n; ++v ){
		if ( !((mask>>v)&1) ){
			tmp = solve( v , mask | (1<<v) );
			mini = min( mini , tmp + d[u][v] );
		}
	}
	return (dp[u][mask] = mini);
}

void read_input(){
	int a,b;
	scanf("%d %d",&a,&b);
	scanf("%d %d",X,Y);
	scanf("%d",&n);
	for ( int i=1; i <= n ; ++i ) scanf("%d %d",X+i,Y+i);
	n++;
	for ( int i=0; i < (n-1); ++i )
		for ( int j=i+1; j < n; ++j )
			d[i][j] = d[j][i] = D(i,j);
}

int main(){
	int runs;
	int res;
	int i,j;
	scanf("%d",&runs);
	while (runs--){
		read_input();
		for (i=0; i < n; ++i)
			for (j=0; j < (1<<n); ++j)
				dp[i][j] = -1;
		printf("The shortest path has length %d\n",solve(0,1));
	}
	return 0;
}
