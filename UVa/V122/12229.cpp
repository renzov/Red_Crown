#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN = 2048;
int N, M;
vector<int> G[3][MAXN];
int indeg[3][MAXN];
int res[3][MAXN];

inline int left( const int &x ){ return x; }
inline int right( const int &x ){ return x + N; }

bool topsort( vector<int> Adj[], int deg[], int pos[] ){
	queue<int> q;

	for ( int i=0; i < 2*N; ++i ){
		if ( deg[i] == 0 ) q.push(i);
	}

	int u, v;
	int p = 0;

	while ( !q.empty() ){
		u = q.front();
		q.pop();
		pos[ u ] = p++;
		for ( int i=0; i < (int)Adj[u].size(); ++i ){
			v = Adj[u][i];
			deg[v]--;
			if ( deg[v] == 0 ) q.push( v );
		}
	}
	if ( p != 2*N ) return false;
	return true;
}

void clear(){
	for ( int j=0; j < 3; ++j ){
		for ( int i=0; i < 2*N; ++i ){	
			G[j][i].clear();
			indeg[j][i] = 0;
		}
	}
}

void add_arc( const int &dim, const int &u, const int &v ){
	G[ dim ][ u ].push_back( v );
	indeg[ dim ][ v ]++;
}

void process(){
	char op;
	int u, v;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < 3; ++j )
			add_arc( j, left(i), right(i) );

	while ( M-- ){
		scanf(" %c %d %d", &op, &u, &v);
		u--, v--;
		if ( op == 'I' ){
			for ( int j=0; j < 3; ++j ){
				add_arc( j, left(u), right(v) );
				add_arc( j, left(v), right(u) );
			}
		}
		else {
			add_arc( (int)(op - 'X'), right(u), left(v) );
		}
	}

	bool ok = true;
	for ( int j=0; j < 3 && ok; ++j ){
		ok &= topsort( G[j], indeg[j], res[j] );
	}
	if ( !ok ) puts("IMPOSSIBLE");
	else {
		puts("POSSIBLE");
		for ( int i=0; i < N; ++i ){
			printf("%d %d %d %d %d %d\n", res[0][ left(i) ], res[1][ left(i) ], res[2][ left(i) ],
										  res[0][ right(i) ], res[1][ right(i) ], res[2][ right(i) ] );
		}
	}
}

int main(){
	int runs = 0;
	while ( scanf("%d %d", &N, &M) && ( N || M ) ){
		printf("Case %d: ", ++runs);
		process();
		puts("");
		clear();
	}
	return 0;
}
