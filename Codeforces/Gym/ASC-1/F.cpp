#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
const long double EPS = 1e-8;
const int MAXN = 350;

long double X[MAXN];
long double Y[MAXN];
long double R[MAXN];
int N;

vector<int> G[MAXN];
int dfsnum[MAXN];
int low[MAXN];
int num = 0;
stack<int> S;
bool inStack[MAXN];

int compare( const long double &x, const long double &y ){
	if ( fabsl( x - y ) < EPS ) return 0;
	return ( x < y )? -1:1;
}

inline long double sq( const long double &x ){
	return x * x;
}

long double dist( const int &i, const int &j ){
	long double dx = X[i] - X[j];
	long double dy = Y[i] - Y[j];
	return sqrtl(dx * dx + dy * dy);
}

bool barrier( const int &i, const int &j ){
	return compare( dist( i , j ), R[i] + R[j] ) < 0;
}

void dfs( const int &u ){
	dfsnum[u] = low[u] = num++;
	S.push( u );
	inStack[u] = true;

	int v;
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			dfs( v );
			low[u] = min( low[u], low[v] );
		}
		else if ( inStack[v] ){
			low[u] = min( low[u], dfsnum[v] );
		}  
	}

	if ( low[u] == dfsnum[u] ){
		do {
			v = S.top();
			S.pop();
			inStack[v] = false;
		}
		while ( v != u );
	}
}

int dir( const int &i, const int &j ){
	long double area2 = X[i] * ( Y[j] - Y[i] ) - Y[i] * ( X[j] - X[i] );
	return compare( area2, 0 );
}

int main(){
	freopen("out.in", "r", stdin);
	freopen("out.out", "w", stdout);

	scanf("%d", &N);
	// read the input
	for ( int i=0; i < N; ++i )
		scanf("%Lf %Lf %Lf", X + i, Y + i, R + i );
	scanf("%Lf %Lf %Lf", X + N, Y + N, R + N );
	// translate the origin to the point (X[N], Y[N])
	for ( int i=0; i < N; ++i ){
		X[i] -= X[N];
		Y[i] -= Y[N];
		R[i] += R[N];	// increase the circunference
	}
	// create the digraph
	for ( int i=0; i < N; ++i )
		for ( int j=i + 1; j < N; ++j ){
			if ( barrier( i, j ) ){		// circle cannot cross through i and j
				int d = dir( i , j );
				if ( d <= 0 ) G[j].push_back( i );
				if ( d >= 0 ) G[i].push_back( j );
			}
		}
	// check if the digraph has a directed cycle
	fill( dfsnum, dfsnum + N, -1 );
	for ( int i=0; i < N; ++i )
		if ( dfsnum[i] == -1 )
			dfs( i );
	//
	bool hasCycle = false;
	for ( int i=0; i < N; ++i ){
		if ( low[i] < dfsnum[i] )
			hasCycle = true;
	}
	// print answer
	puts( hasCycle? "NO":"YES");
	return 0;
}
