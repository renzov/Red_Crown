#include<cstdio>
#include<vector>
using namespace std;

const int MAXN = 100005;
int V[MAXN];
vector<int> G[MAXN];

void process(){
	int u, v;
	int N, M;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back(v), G[v].push_back(u);
	}
	if ( (M & 1) ){
		u = -1;
		for ( int i=0; i < N; ++i ){
			if ( ( (int)G[i].size() ) & 1 ){
				u = i;
				break;
			}
		}
		if ( u != -1 ){	// odd-degree vertex exists
			puts("2");
			V[u] = 2;
			for ( int i=0; i < N; ++i )
				if ( i != u ) V[i] = 1;
		}
		else {	// every vertex has even degree
			puts("3");
			for ( int i=0; i < N; ++i ){	// Take any nonzero degree vertex
				if ( (int)G[i].size() ){
					u = i;
					break;
				}
			}
			v = G[u][0];	// Take any neighbor (odd degree in G - u)
			V[u] = 3, V[v] = 2;
			for ( int i=0; i < N; ++i )
				if ( i != u && i != v )
					V[i] = 1;
		}
		printf("%d", V[0]);
		for ( int i=1; i < N; ++i ) 
			printf(" %d", V[i]);
		puts("");
	}
	else {
		puts("1");
		printf("1");
		for ( int i=1; i < N; ++i )
			printf(" 1");
		puts("");
	}
	// clean memory
	for ( int i=0; i < N; ++i ) G[i].clear();
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
