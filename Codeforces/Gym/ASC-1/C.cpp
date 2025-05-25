#include<cstdio>
#include<cstdlib>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 500005;

vector<int> T[MAXN];
int f[2][MAXN];			// f[cover][u] = max. matching of subtree T[u] s.t. u is already covered
int matched[2][MAXN];
bool res[MAXN];

void get_sol( const int &u, const int &cov ){	
	int v;

	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != matched[cov][u] )
			get_sol( v, 0 );
		else {
			res[ v ] = true;
			get_sol( v, 1 );
		}
	}
}

void solve( const int &u ){
	if ( (int)T[u].size() == 0 ){	// u is leaf
		f[0][u] = f[1][u] = 0;
		return;
	}
	// Initialize
	f[0][u] = f[1][u] = 0; 
	
	int v;
	int best = INT_MIN;	// best difference
	int idx = -1;

	for ( int i = 0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		solve( v );
		f[1][u] += f[0][v];
		if ( best < (f[1][v] - f[0][v]) ){
			best = f[1][v] - f[0][v];
			idx = v;
		}
	}

	f[0][u] = f[1][u];
	if ( best >= 0 ){
		f[0][u] = f[1][u] + best + 1;
		matched[0][u] = idx;
	}

}

int main(){
	freopen("grant.in", "r", stdin);
	freopen("grant.out", "w", stdout);

	int N;
	int u;

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d", &u);
		u--;
		T[u].push_back( i );
	}
	
	fill( matched[0], matched[0] + N, -1 );
	fill( matched[1], matched[1] + N, -1 );
	solve(0);

	printf("%d\n", f[0][0] * 1000);	
	get_sol(0, 0);

	bool first = true;
	for ( int i=0; i < N; ++i ){
		if ( res[i] ){
			if ( !first ) putchar(' ');
			printf("%d", i + 1);
			first = false;
		}
	}
	puts("");
	return 0;
}
