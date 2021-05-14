#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> edge;
const int MAXN = 2600;

int f[MAXN];

inline int find_set( const int &x ){ return ( x == f[x] )? x:( f[x] = find_set( f[x] ) ); }
inline void union_set( const int &x, const int &y ){ f[y] = x; }

vector<edge> E;

int main(){
	int N;
	int u, v, w;

	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		f[i] = i;	// Init
		for ( int j=1; j <= N; ++j ){
			scanf("%d", &w);
			if ( i < j )
				E.push_back( edge( w, pii(i, j) ) );
		}
	}

	sort( E.begin(), E.end() );
	for ( int i=0; i < (int)E.size(); ++i ){
		u = E[i].second.first, v = E[i].second.second;
		if ( find_set(u) != find_set(v) ){
			printf("%d %d\n", u, v);
			union_set( find_set(u), find_set(v) );
		}
	}
	return 0;
}
