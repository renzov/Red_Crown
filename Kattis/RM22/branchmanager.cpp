#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 200005;

vector<int> T[MAXN];

int num = 0;
int L[MAXN], R[MAXN];

void dfs( const int &u ){
	L[u] = R[u] = ++num;
	
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		dfs( v );
		R[u] = R[v];
	}
} 

inline bool in( const int &r, const int &u ){	// r is an ancestor of u
	return L[r] <= L[u] && L[u] <= R[r];
}

int main(){
		
	int N, Q;
	int u, v;
	
	scanf("%d %d", &N, &Q);
	for ( int i = 1; i < N; ++i ){
		scanf("%d %d", &u, &v);
		T[u].push_back( v );
	}
	for ( int i = 0; i < N; ++i )
		sort( T[i].begin(), T[i].end() );

	dfs( 1 );

	int cur = -1;
	int ans = 0;
	while ( Q-- ){
		scanf("%d", &u);
		if ( cur == -1 || cur == u ) cur = u;
		else if ( L[cur] > L[u] && !in( u, cur ) ){
			break;
		}
		else if ( L[cur] < L[u] ){	
			cur = u;
		}
		ans++;
	}
	printf("%d\n", ans );
	return 0;
}
