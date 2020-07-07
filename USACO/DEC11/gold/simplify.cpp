#include<cstdio>
#include<set>
#include<algorithm>
using namespace std; 
typedef pair<int,int> pii;
typedef pair<int, pii> edge;
const int MAXN = 40004;
const int MAXE = 100005;
const int MOD = 1000000007;

int f[MAXN];
edge E[MAXE];
inline int find_set( const int &x ){ return x == f[x]? x:( f[x] = find_set(f[x]) ); }

int main(){
	int N, M;
	int u, v, w;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		E[i] = edge( w, pii(u, v) );
	}

	sort( E, E + M );
	for ( int i=0; i < N; ++i )
		f[i] = i;

	int active;
	int merges;
	int diff;
	long long mst = 0;
	long long res = 1;
	
	for ( int i=0, j; i < M; ){
		w = E[i].first;
		j = i;
		active = 0;
		set<pii> join;
		while ( j < M && w == E[j].first ){
			u = E[j].second.first, v = E[j].second.second;
			u = find_set(u), v = find_set(v);
			if ( u > v ) swap(u, v);
			if ( u != v ){
				active++;
				join.insert( pii(u, v) );
			}
			j++;
		}
		merges = 0;
		while ( i < j ){
			u = E[i].second.first, v = E[i].second.second;
			u = find_set(u), v = find_set(v);
			if ( u != v ){
				f[u] = v;
				merges++;
				mst += w;
			}
			i++;
		}
		if ( active == 3  ){
			if ( merges == 1 ) res *= 3;
			else if ( merges == 2 && join.size() == 3 ) res *= 3;	// merges 
			else if ( merges == 2 ) res *= 2;
		}
		else if ( active == 2 && merges == 1 ){
			res *= 2;
		}
		res %= MOD;
	}
	printf("%lld %lld\n", mst, res);
	return 0;
}
