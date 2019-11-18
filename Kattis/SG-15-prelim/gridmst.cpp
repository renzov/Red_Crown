#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<set>
#include<queue>
#include<vector>
using namespace std;
const int MAXN = 1024;
const int MAXP = 100005;
typedef pair<int,int> point;
typedef pair<int, point> piii;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
point P[MAXP];
int f[MAXP];
int G[MAXN][MAXN];
int d[MAXN][MAXN];
int color[MAXN][MAXN];
int N;
int M;
queue< point > q;

int dist( const int &i, const int &j ){
	return abs( P[i].first - P[j].first ) + abs( P[i].second - P[j].second );
}

inline int find_set( const int &x ){ return x == f[x]? x:( f[x] = find_set(f[x]) ); }

int main(){
	M = 0;

	int x, y;
	int Mx = 0, My = 0 , mx = 1000, my = 1000;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &x, &y);
		Mx = max( Mx, x ), mx = min( mx, x );
		My = max( My, y ), my = min( my, y );
		if ( !G[x][y] ){
			P[++M] = point(x, y);
			d[x][y] = 1;
			color[x][y] = M;
			q.push( P[M] );
		}
	}

	int nx, ny;
	int a, b, w;
	set< point > edges;
	while ( !q.empty() ){
		x = q.front().first, y = q.front().second;
		q.pop();
		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i], ny = y + dy[i];
			if ( nx < mx || ny < my || nx > Mx || ny > My ) continue;
			if ( !d[nx][ny] ){
				color[nx][ny] = color[x][y];
				d[nx][ny] = d[x][y] + 1;
				q.push( point(nx, ny) );
			}
			else if ( color[x][y] != color[nx][ny] ) {
				a = min( color[x][y] , color[nx][ny] );
				b = max( color[x][y] , color[nx][ny] );
				edges.insert( point( a, b ) );
			}
		}
	}

	vector<piii> E;
	for ( set<point>::iterator it=edges.begin(); it != edges.end(); ++it ){
		a = it->first, b = it->second;
		E.push_back( piii( dist( a, b ) , *it ) );
	}

	sort( E.begin(), E.end() );
	long long res = 0;
	int cmp = M;
	// Initialize the sets
	for ( int i=1; i <= M; ++i ) f[i] = i;

	for ( int i=0; i < ( int )E.size() && cmp > 1; ++i ){
		a = E[i].second.first, b = E[i].second.second;
		w = E[i].first;
		a = find_set(a), b = find_set(b);
		if ( a != b ){
			f[a] = b;
			res += w;
			cmp--;
		}
	}
	printf("%lld\n", res);
	return 0;
}
