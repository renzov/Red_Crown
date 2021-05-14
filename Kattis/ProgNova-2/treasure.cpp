#include<cstdio>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 55;
typedef pair<int, int> pii;
typedef pair< pii, pii > node;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int N, M, K;
char G[MAXN][MAXN];
int W[MAXN][MAXN];
int sx, sy;
int ex, ey;
pii d[MAXN][MAXN];

inline bool isvalid( const int &x, const int &y ){
	return x < N && y < M && x >= 0 && y >= 0 && K >= W[x][y];
}

int dijkstra(){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			d[i][j].first = INT_MAX, d[i][j].second = INT_MAX;

	priority_queue< node, vector<node>, greater<node> > q;
	q.push( node( pii(1, 0), pii(sx, sy) ) );
	d[ sx ][ sy ] = pii( 1, 0 );
	
	int x, y, nx, ny;
	pii w, nw;
	pii pos;
	while ( !q.empty() ){
		pos = q.top().second;
		w = q.top().first;
		q.pop();

		x = pos.first, y = pos.second;

		if ( w > d[x][y] ) continue;

		if ( x == ex && y == ey ) return d[ex][ey].first;

		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];

			if ( !isvalid( nx, ny ) ) continue;
			if ( w.second + W[nx][ny] <= K ){
				nw = pii( w.first, w.second + W[nx][ny] );
			}
			else {
				nw = pii( w.first + 1, W[nx][ny] );
			}

			if ( d[nx][ny] > nw ){
				d[nx][ny] = nw;
				q.push( node( nw, pii( nx, ny ) ) );
			}

		}
	}
	return -1;
}

int main(){
	scanf("%d %d %d", &N, &M, &K);
	for ( int i=0; i < N; ++i ){
		scanf("%s", G[i]);
		for ( int j=0; j < M; ++j ){
			if ( G[i][j] == 'S' ){
				sx = i, sy = j;
				G[i][j] = '.';
			}
			else if ( G[i][j] == 'G' ){
				ex = i, ey = j;
				G[i][j] = '.';
			}

			switch ( G[i][j] ){
				case '.': W[i][j] = 1; break;
				case 'F': W[i][j] = 2; break;
				case 'M': W[i][j] = 3; break;
				case '#': W[i][j] = INT_MAX; break; 
			}

		}
	}

	printf("%d\n", dijkstra());

	return 0;
}
