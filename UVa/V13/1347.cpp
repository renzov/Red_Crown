#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

int N;
vector<int> X;
vector<int> Y;
vector< vector<double> > dp;
vector< vector<bool> > ismemo;

double D( const int &u, const int &v ){
	return sqrt( (X[u] - X[v])*(X[u] - X[v]) + (Y[u] - Y[v])*(Y[u] - Y[v]) );
}

double solve( const int &u, const int &v ){
	int nxt = max( u, v ) + 1;
	if ( nxt == N ){
		ismemo[u][v] = true;
		dp[u][v] = D( u, N - 1 ) + D(v , N - 1); 
	}
	else if ( ismemo[u][v] ){
		return dp[u][v];
	}
	else {
		ismemo[u][v] = true;
		dp[u][v] = min( solve( v, nxt ) + D(u, nxt), solve(u, nxt) + D(v, nxt) );
	}
	return dp[u][v];
}

void process(){
	X.resize(N);
	Y.resize(N);

	dp = vector< vector<double> > ( N, vector<double>(N) ); 
	ismemo = vector< vector<bool> > (N, vector<bool>(N, false) );

	for ( int i=0; i < N; ++i )
		scanf("%d %d", &X[i], &Y[i]);

	printf("%0.2f\n", solve(0, 0));
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}
