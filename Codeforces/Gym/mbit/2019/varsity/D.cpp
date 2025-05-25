#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
const int MAXN = 128;
typedef pair<int,int> state;

int N, M;
vector<int> G[MAXN];
vector<int> W[MAXN];
int D[MAXN][MAXN];
int P[MAXN];
int A, B, C;

int main(){

	scanf("%d %d %d", &N, &M, &C);		
	scanf("%d %d", &A, &B);
	A--, B--;

	for ( int i=0; i < N; ++i )
		scanf("%d", P + i);

	int u, v, w, f, c;
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back( v ); W[u].push_back( w );
		G[v].push_back( u ); W[v].push_back( w );
	}

	// Initialize distance 
	for ( int i=0; i < N; ++i )
		for ( int j=0; j <= C; ++j )
			D[i][j] = INT_MAX;
	
	D[A][0] = 0;
	
	queue<state> q;
	q.push( state(A, 0) );
	while ( !q.empty() ){
		u = q.front().first;
		f = q.front().second;
		q.pop();

		if ( u == B ){
			printf("%d\n", D[u][f]);
			break;
		}
		// Try every possible transition
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			c = W[u][i];
			if ( f >= c && ( D[v][f - c] == INT_MAX ) ){
				D[v][f - c] = D[u][f] + 1;
				q.push( state( v, f - c ) );
			}
		}
		// Or refuel
		w = min( f + P[u], C);
		if (  D[u][w] == INT_MAX ){
			D[u][w] = D[u][f] + 1;
			q.push( state( u, w ) );			
		}
	}
	return 0;
}
