#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> vi;

const int MAXN = 1001;
const int MOD = 1000000007;

int N;
long long ways[MAXN + 5][MAXN + 5];
int indeg[ MAXN + 5 ];
int size[ MAXN + 5 ];
vi T[MAXN + 5];

long long solve( int u ){
	if ( T[u].size() == 0 ){ 
		size[u] = 1;
		return 1LL;
	}
	int v;
	long long last, val;
	int Sv, S = 0;
	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		val = solve( v );
		Sv = size[v];
		if ( S == 0 ){
			S += Sv;
			last = val;
		}
		else {
			last = ( last * ( ( val * ways[Sv + S][Sv] ) % MOD ) ) % MOD;
			S += Sv;
		}
	}
	size[u] = S + 1;
	return last; 
}

int main(){
	int runs;
	int u, v;
	ways[0][0] = 1;
	for ( int i=1; i < MAXN; ++i ){
		ways[i][0] = ways[i][i] = 1;
		for ( int j=1; j < i; ++j )
			ways[i][j] = ( ways[i-1][j] + ways[i-1][j-1] ) % MOD;
	}
	scanf("%d", &runs);
	for ( int cases = 1; cases <= runs; ++cases ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			T[i].clear();
			size[i] = indeg[i] = 0;
		}
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			T[u].push_back(v);
			indeg[v]++;
		}
		for ( int i=0; i < N; ++i )
			if ( !indeg[i] ){
				u = i;
				break;
			}

		printf("Case %d: %lld\n", cases, solve(u));
	}
	return 0;
}

