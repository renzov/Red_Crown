#include<cstdio>
#include<algorithm>
#include<climits>
#include<vector>
#include<set>
using namespace std;
const int MAXN = 100005;

int num;
bool invalid[MAXN];
int dfsnum[MAXN];
int dfsord[MAXN];	
int cycles[MAXN];	// Number of fundamental cycles that contain each vertex
vector<int> G[MAXN];
multiset<int> S[MAXN];
int f[MAXN];

int N;
int M;

inline int find_set( const int &x ){ return x == f[x]? x:(f[x] = find_set( f[x] )); }

void merge( const int &u, const int &v ){
	for ( multiset<int>::iterator it = S[v].begin(); it != S[v].end(); it++ )
		S[u].insert( *it );
}

void dfs( const int &u, const int &p ){
	dfsnum[u] = num;
	dfsord[num++] = u;
	int v;
	int last = find_set(u);
	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( v == p ) continue;
		if ( dfsnum[v] == -1 ){
			dfs( v, u );		
			v = find_set(v);
			if ( S[last].size() >= S[v].size() ){
				merge( last, v ); 
				f[v] = last;
			}
			else {
				merge( v, last );
				f[last] = v;
				last = v;
			}
		}
		else if ( dfsnum[v] < dfsnum[u] ){	// start of a back edge
			S[last].insert(v);
		}
	}
	cycles[u] = (int)S[last].size();
	//printf("cycles[%d]: %d\n", u, cycles[u]);	
	S[last].erase( u );
}

bool find_cycle( const int &u, const int &p ){
	int v;
	dfsnum[u] = num++;
	bool found = false;
	for ( int i=0; i < (int)G[u].size() && !found; ++i ){
		v = G[u][i];
		if ( invalid[v] || v == p ) continue;
		if ( dfsnum[v] == -1 ){
			found |= find_cycle( v, u );
		}
		else {
			found = true;
		}
	}
	return found;
}

bool check( const int &u ){
	invalid[u] = true;
	fill( dfsnum, dfsnum + N, -1 );
	num = 0;
	for ( int i=0; i < N; ++i )
		if ( !invalid[i] && dfsnum[i] == -1 && find_cycle(i, -1) ){
			invalid[u] = false;
			return false;
		}
	invalid[u] = false;
	return true;
}

void process(){
	int u, v;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	fill( dfsnum, dfsnum + N, -1 );
	num = 0;
	int cmp = 0;	// number of components
	
	for ( int i=0; i < N; ++i ) f[i] = i;
	
	for ( int i=0; i < N; ++i )
		if ( dfsnum[i] == -1 ){
			dfs( i , -1 );
			cmp++;	
		}

	int res = INT_MAX;
	int total_cycles = M - N + cmp;
	if ( total_cycles == 1 ){
		for ( int i=0; i < N; ++i ){
			if ( total_cycles == cycles[i] ){
				res = i + 1;
				break;
			}
		}
	}
	else if ( total_cycles > 1 ){
		int first = -1;
		int last = -1;
		for ( int i=0; i < N; ++i ){	// Iterate over the vertices in dfs order
			u = dfsord[i];
			if ( cycles[u] == total_cycles ){
				if ( first == -1 ) first = u;
				last = u;
			}
		}
		
		if ( first != -1 && check( first ) ) 
			res = first + 1;
		if ( last != -1 && last != first && check( last ) )
			res = min(res, last + 1);
	}
	if ( res == INT_MAX ) res = -1;
	printf("%d\n", res);
	// Clean up the memory
	for ( int i=0; i < N; ++i ){
		G[i].clear();
		S[i].clear();
	}
}


int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
