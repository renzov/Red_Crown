#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
const int MAXN = 128;

vector<int> ord;
vector<int> T[MAXN];
bool in[MAXN];
int par[MAXN];	
int f[MAXN][2];
int choose[MAXN][2];
int dp[MAXN];
/*
	f[u][used] = min size of dominating set in T_u ( subtree rooted at u ) 
				 if the vertex u is needs to bo covered (0 or 1)
*/
void topsort( const int &u, const int &p ){
	int v;

	par[u] = p;
	for ( int i = 0; i < (int) T[u].size(); ++i ){
		v = T[u][i];
		if ( v == p ) continue;
		topsort( v, u );
	}
	ord.push_back(u);
}

void get_solution( const int &u, const int &type ){
	int v;

	if ( type == 0 ){
		if ( choose[u][0] == u ){
			get_solution( u, 1 );
		}
		else {
			for ( int i = 0; i < (int)T[u].size(); ++i ){
				v = T[u][i];
				if ( v == par[u] ) continue;
				get_solution( v, 2 );
			}
		}
	}
	else if ( type == 1 ){
		in[u] = true;
		for ( int i = 0; i < (int)T[u].size(); ++i ){
			v = T[u][i];
			if ( v == par[u] ) continue;
			get_solution( v, 0 );
		}
	}
	else {
		if ( choose[u][1] == u ){
			get_solution( u, 1 );
		}
		else {
			for ( int i = 0; i < (int)T[u].size(); ++i ){
				v = T[u][i];
				if ( v == par[u] ) continue;
				if ( v == choose[u][1] )	
					get_solution( v, 1 );
				else
					get_solution( v, 2 );
			}
		}
	}
}

void solve( const int &u ){
	int v, Y;
	int sum1 = 0; 
	int sum2 = 0;
	int minDiff = 5000;	// represents infinity
	int vertex = -1;

	if ( (int)T[u].size() == 1 && u != 0 ){	// u is a leaf different from root
		dp[u] = f[u][1] = 1;
		choose[u][1] = u;
		f[u][0] = 0;
		choose[u][0] = -1;
	}
	else {
		for ( int i = 0; i < (int)T[u].size(); ++i ){
			v = T[u][i];
			if ( v == par[u] ) continue;
			sum1 += f[v][0];
			sum2 += dp[v];
			if ( minDiff > ( f[v][1] - dp[v] ) ){
				minDiff = f[v][1] - dp[v];
				vertex = v;
			} 
		}
		f[u][1] = 1 + sum1;
		// calculate f[u][0]
		if ( f[u][1] <= sum2 ){
			f[u][0] = f[u][1];
			choose[u][0] = u;
		}
		else {
			f[u][0] = sum2;
			choose[u][0] = -1;
		}
		// calculate dp[u]
		if ( f[u][1] <= ( sum2 + minDiff ) ){
			dp[u] = f[u][1];
			choose[u][1] = u;
		}
		else {
			dp[u] = sum2 + minDiff;
			choose[u][1] = vertex;
		}
	}
}


int main(){
	int N;
	int u, v;

	freopen("input.txt", "r", stdin );
	freopen("output.txt", "w", stdout );

	scanf("%d", &N);
	for ( int i = 1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
	}	
	// process the vertices in topological order -- root is vetex 0
	topsort( 0, -1 );
	for ( int i = 0; i < N; ++i )
		solve( ord[i] );
	// print solution -- root is vertex 0
	get_solution( 0, 2 );
	for ( int i = 0; i < N; ++i ){
		if (i) putchar(' ');
		putchar( in[i]? '1':'0' );
	}
	puts("");
	return 0;
}
