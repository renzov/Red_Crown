#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 10005;

int H[ 2*MAXN ];
int size;
int N;

inline int pre(const int &x){ return x >> 1; }
inline int left(const int &x){ return x << 1; }
inline int right(const int &x){ return (x << 1) | 1; }
inline bool compare(const int &a, const int &b){ return a < b; }

void bubble_up( int idx, int pos[], int d[] ){
	while ( idx > 1 && compare( d[ H[idx] ], d[ H[pre(idx)] ] ) ){
		swap( pos[ H[idx] ] , pos[ H[pre(idx)] ] );
		swap( H[idx], H[pre(idx)] );
		idx = pre(idx);
	}
}

int pop( int pos[], int d[] ){
	int idx = 1;
	int res = H[1];
	int l,r;
	pos[ H[size] ] = 1;
	H[1] = H[size];
	size--;
	while ( right(idx) <= size ){
		l = left(idx);
		r = right(idx);

		if ( !compare(d[H[l]], d[H[idx]]) && !compare(d[H[r]], d[H[idx]]) ) break;

		if ( d[ H[l] ] <= d[ H[r] ] ){
			swap( pos[ H[idx] ] , pos[ H[l] ] );
			swap( H[idx], H[l] );
			idx = l;
		}
		else {
			swap( pos[ H[idx] ], pos[ H[r] ] );
			swap( H[idx], H[r] );
			idx = r;
		}
	}
	l = left(idx);
	if ( l <= size && compare( d[ H[l] ] , d[ H[idx] ] ) ){
			swap( pos[ H[idx] ] , pos[ H[l] ] );
			swap( H[idx], H[l] );
	}
	return res;
}

void push( int u, int pos[], int d[] ){
	if ( pos[u] == -1 ){
		H[++size] = u; pos[u] = size;
	}
	bubble_up( pos[u] , pos, d );
}

void dijkstra( int s, vector<int> G[], vector<int> C[], int d[] ){
	int pos[MAXN];
	//init
	for (int i=0; i < N; ++i ){
		d[i] = INT_MAX;
		pos[i] = -1;
	}
	size = 0;
	d[s] = 0;
	push( s , pos , d );

	int u, v, w;

	while ( size ){
		u = pop( pos, d );
		for ( int i=0; i < G[u].size(); ++i ){
			v = G[u][i];
			w = d[u] + C[u][i];
			if ( d[v] > w ){
				d[v] = w; 
				push( v , pos , d );
			}
		}
	}
}


int main(){
	int runs;
	int M,K;
	int u,v,w;
	int s,t;
	vector<int> G[MAXN];
	vector<int> C[MAXN];

	vector<int> GT[MAXN];
	vector<int> CT[MAXN];

	int ds[MAXN];
	int dt[MAXN];

	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d %d %d %d", &N, &M, &K, &s, &t);
		s--,t--;

		for ( int i=0; i < N; ++i ){
			G[i].clear(); GT[i].clear();
			C[i].clear(); CT[i].clear(); 
		}

		while (M--){
			scanf("%d %d %d", &u, &v, &w);
			u--,v--;
			G[u].push_back(v); GT[v].push_back(u);
			C[u].push_back(w); CT[v].push_back(w);
		}
		dijkstra(s, G, C, ds);
		dijkstra(t, GT, CT, dt);
		int res = ds[t];
		for (int i=0; i < K; ++i){
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			if ( ds[u] != INT_MAX && dt[v] != INT_MAX ){
				res = min( res , ds[u] + w + dt[v] );
			}
			if ( ds[v] != INT_MAX && dt[u] != INT_MAX ){
				res = min( res , ds[v] + w + dt[u] );
			}
		}
		if (res == INT_MAX) puts("-1");
		else printf("%d\n",res);
	}
	return 0;
}

