#include<cstdio>
#include<set>
#include<vector>
using namespace std;

const int MAXN = 50005;
const int B = 500;

bool online[MAXN];
set<int> G[MAXN];
bool vis[MAXN];
int cnt[MAXN];

// Buffer of operations
int X[MAXB];
int Y[MAXB];
int size = 0;
void apply_op( const int &idx ){
	int u, v;
	u = X[idx];
	v = Y[idx];

	if ( u == N ){	// turn online
		online[ v ] = true;
	}
	else if ( u == -N ){	// turn offline
		online[ v ] = false;
	}
	else if ( X[idx] <= 0 && Y[idx] <= 0  ){
		u = -u;
		v = -v;
		G[u].erase(v), G[v].erase(u);
	}
	else {
		G[u].insert(v), G[v].insert(u);
	}
}

void dfs( const int &u, const int &p ){
	int v;
	set<int>::iterator it;
	cnt[u] = 0;

	for ( it = G[u].begin(); it != G[u].end(); ++it ){
		v = *it;
		if ( online[v] ) cnt[u]++;
		if ( v == p ) continue;
		if ( !vis[v] ) 
			dfs( v, u );
	}
}

void rebuild(){
	for ( int i = 0; i < size; ++i ) 
		apply_op(i)
	size = 0;

	fill( vis, vis + N, false );
	for ( int i = 0; i < N; ++i )
		if ( !vis[i] )
			dfs( i, -1 );
}


int main(){
	int N, M, Q, O;
	int u, v;
	int res;
	char op;

	// Read input
	scanf("%d %d %d %d", &N, &M, &Q, &O);
	
	while ( O-- ){
		scanf("%d", &u);
		u--;
		online[u] = true;
	}
	
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].insert( v );
		G[v].insert( u );
	}
	// Start to process queries
	rebuild();
	
	while ( Q-- ){
		scanf(" %c", &op);
		if ( op == 'O' ){
			X[size] = N;
			scanf("%d", Y + size );
			Y[size]--;
			size++;
		}
		else if ( op == 'F' ){
			X[size] = -N;
			scanf("%d", Y + size );
			Y[size]--;
			size++;
		}
		else if ( op == 'A' ){
			scanf("%d %d", X + size, Y + size);
			X[size]--, Y[size]--;
			size++;
		}
		else if ( op == 'D' ){
			scanf("%d %d", X + size, Y + size);
			X[size]--, Y[size]--;
			X[size] *= -1, Y[size] *= -1; 
			size++;
		}
		else {
			scanf("%d", &u);
			u--;
			res = cnt[u];
			for ( int i = 0; i < size; ++i )
				res += get_op( u, i );
			printf("%d\n", res);
		}
		if ( size >= B ) rebuild();
	}
	return 0;
}
