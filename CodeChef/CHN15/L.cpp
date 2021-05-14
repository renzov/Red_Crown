#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 100005;

vector<int> T[MAXN];
int deg[MAXN];
int f[MAXN];
int cnt[MAXN];
int maxL[MAXN];
int N;

void clear(){
	for ( int i=0; i < N; ++i )
		T[i].clear();
}

void process(){
	int Q;
	int u, v;

	scanf("%d %d", &N, &Q);
	fill( deg, deg + N, 0 );
	fill( f, f + N, -1 );
	fill( maxL, maxL + N, -1 );

	for ( int i=1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		T[u].push_back(v);
		T[v].push_back(u);
		deg[u]++, deg[v]++;
	}
	// Labelling the vertices
	deque<int> dq;
	for ( int i=0; i < N; ++i ){
		if ( deg[i] == 1 ){
			dq.push_back( i );
			deg[i]--;
			f[i] = 1;
		}
	}
	
	while ( !dq.empty() ){
		u = dq.front();
		dq.pop_front();
		for ( int i=0; i < (int)T[u].size(); ++i ){
			v = T[u][i];
			if ( f[v] == -1 ){
				deg[v]--;
				if ( f[u] > maxL[v] ){
					maxL[v] = f[u], cnt[v] = 1;
				}
				else if ( f[u] == maxL[v] ){
					cnt[v]++;
				}
				if ( deg[v] == 1 ){
					deg[v]--;
					f[v] = maxL[v];
					if ( cnt[v] > 1 ) f[v]++;
					if ( f[v] == f[u] ){ 
						dq.push_front( v );
					}
					else {
						dq.push_back( v );
					}
				}
			}
		}
	}
	for ( int i=0; i < N; ++i ) printf("f[%d] = %d\n", i+1, f[i]);
	// Process the queries
	while ( Q-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
	}
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		clear();
	}
	return 0;
}
