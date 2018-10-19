#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> event;

const int MAXN = 256;
int X[MAXN];
int Y[MAXN];
int W[MAXN];
int D[MAXN];
int H[MAXN];
bool vis[MAXN];
event E[2*MAXN];
int ord[MAXN];
set< pii > S;
int N;

bool cmp( const int &i, const int &j ){
	return pii( X[i], Y[i] ) < pii( X[j], Y[j] );
}

int main(){
	int cases = 0;
	while ( scanf("%d", &N) && N ){
		for ( int i=0; i < N; ++i ){
			scanf("%d %d %d %d %d", X + i, Y + i, W + i, D + i, H + i);
			E[2*i] = event( X[i] , pii (1, i) );
			E[2*i + 1] = event( X[i] + W[i] , pii(0, i) );
			vis[i] = false;
		}
		sort( E, E + 2*N );
		int x, idx;
		int lastH;
		set<pii>::iterator it;
		for ( int i=0; i < 2*N;  ){
			// Check the visible buildings
			if ( !S.empty() ){
				lastH = -1;
				for ( it = S.begin(); it != S.end(); it++ ){
					if ( H[ it->second ] > lastH ){
						lastH = H[ it->second ];
						vis[it->second] = true;
					}
				}
			}
			x = E[i].first;
			while ( i < 2*N && E[i].first == x ){
				idx = E[i].second.second;
				if ( E[i].second.first == 1 ){
					S.insert( pii( Y[idx], idx ) );
				}
				else {
					S.erase( pii( Y[idx], idx ) );
				}
				i++;
			}
		}
		if ( cases ) puts("");
		printf("For map #%d, the visible buildings are numbered as follows:\n", ++cases);
		int M = 0;
		for ( int i=0; i < N; ++i )
			if ( vis[i] ) ord[M++] = i;
		sort( ord, ord + M, cmp );
		for ( int i=0; i < M; ++i ){
			if ( i ) putchar(' ');
			printf("%d", ord[i] + 1); 
		}
		puts("");	
	}
	return 0;
}
