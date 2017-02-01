#include <queue>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
#include <climits>
#include <cstring>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef pair< int , pii > pti;
const int MAXN = 105;
const int MAXL = 55;

char word[MAXN][MAXL];
vector<int> pre[MAXN][MAXL];
int sz[MAXN];
int N;
int d[MAXN][MAXL];

void precalc(){
	bool ok;
	int pi, pk;
	for ( int i=0; i < N; ++i ){
		for ( int j=sz[i]-1; j >= 0; --j ){
			pre[i][j].clear();
			for ( int k=0; k < N; ++k ){
				if ( k != i || j != 0 ){
					ok = true;
					pi = j, pk = 0;
					while ( pi < sz[i] && pk < sz[k] && ok ){
						ok &= (word[i][pi] == word[k][pk]);
						pk++, pi++;
					}
					if ( ok ) pre[i][j].push_back(k);
				}
			}
		}
	}
}

int main(){

	while ( scanf("%d", &N) && N ){
		for ( int i=0; i < N; ++i ){
			scanf("%s", word[i]);
			sz[i] = strlen(word[i]);
		}
		if ( N == 1 ){
			puts("-1");
			continue;
		}
		precalc();
		int off;
		priority_queue< pti, vector<pti>, greater<pti> > q;
		for ( int i=0; i < N; ++i ){
			fill( d[i], d[i] + MAXL, INT_MAX );
		}
		// init dijsktra
		for ( int i=0; i < N; ++i ){
			d[i][0] = sz[i];
			q.push( pti( sz[i] , pii( i , 0 ) ) );
		}
		// continue dijkstra
		int res = -1;
		int u, v, w, idx, len, nd;
		while ( !q.empty() ){
			w = q.top().first;
			u = q.top().second.first;
			idx = q.top().second.second;
			q.pop();
			if ( w != d[u][idx] ) continue;
			if ( idx == sz[u] ){
				res = w;
				break;
			}
			for ( int i=0; i < pre[u][idx].size(); ++i ){
				v = pre[u][idx][i];
				len = min( sz[v] , sz[u] - idx );
				if ( len == sz[v] ){
					if ( d[u][idx + len] > w ){
						q.push( pti( w , pii( u , idx + len ) ) );
						d[u][idx + len] = w;
					}
				}
				else {
					nd = w + sz[v] - len;
					if ( nd < d[v][len] ){
						q.push( pti( nd, pii( v , len ) ) );
						d[v][len] = nd;
					}
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

