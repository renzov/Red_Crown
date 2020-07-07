#include<cstdio>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 10005;


int N, M;
int C[MAXN];
vector<int> G[MAXN];
set<int> S[MAXN];
bool in[10*MAXN];

void clean(){
	for ( int i=0; i < N; ++i ){
		G[i].clear();
		S[i].clear();
	}
	fill( in, in + 10*MAXN, false );
}

void process(){
	for ( int i=0; i < N; ++i )
		scanf("%d", C + i);
	
	int u, v, w, g;
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	// Begin the search
	int res = 0;
	queue< pii > q;
	for ( int i=0; i < N; ++i ){
		S[i].insert( C[i] );
		q.push( pii( i, C[i] ) );
		if ( !in[ C[i] ] ){
			in[ C[i] ] = true;
			res++;
		}
	}
	while ( !q.empty() ){
		u = q.front().first;
		w = q.front().second;
		q.pop();

		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			g = __gcd( w, C[v] );
			if ( S[v].find(g) != S[v].end() ) continue;
			if ( !in[ g ] ){
				in[ g ] = true;
				res++;
			}
			S[v].insert(g);
			q.push( pii(v, g) );
		}
	}
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d %d", &N, &M) == 2 ){
		process();
		clean();
	}
	return 0;
}
