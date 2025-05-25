#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN = 1005;

typedef pair<int,int> pii;
typedef pair<pii, pii> node;

int N, M;
int T[MAXN][MAXN];
int d[MAXN][MAXN][3][4];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

inline bool in( const int &x, const int &y ){
	return x < N && y < M && x > -1 && y > -1;
}

bool valid( const int &x, const int &y, const int &s ){
	if ( !T[x][y] ) return false;
	if ( T[x][y] == 3 ) return s == 1;
	return true;
}

int state( const int &x, const int &y, const int &s ){
	if ( T[x][y] == 2 ) return 1;
	if ( T[x][y] == 4 ) return 2;
	if ( s == 2 ) return 0;
	return s;
}

int bfs(){
	queue<node> Q;
	for ( int i = 0; i < 4; ++i ){
		d[0][0][0][i] = 0;
		Q.push( node( pii(0, 0), pii(0, i) ) );
	}
	
	int x, y, s, l;
	int nx, ny, ns;

	while ( !Q.empty() ){
		x = Q.front().first.first;
		y = Q.front().first.second;
		s = Q.front().second.first;
		l = Q.front().second.second;
		Q.pop();

		if ( x == N - 1 && y == M - 1 ) return d[x][y][s][l];

		if ( s == 2 ){	// sliding
			nx = x + dx[l];
			ny = y + dy[l];
			if ( in( nx, ny ) && valid( nx, ny, s ) ){
				ns = state( nx, ny, s );
				if ( d[nx][ny][ns][l] == -1 ){
					d[nx][ny][ns][l] = d[x][y][s][l] + 1;
					Q.push( node( pii( nx , ny ), pii( ns, l ) ) );
				}
				continue;
			}
		}
		
		for ( int i = 0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( !in( nx, ny ) || !valid( nx, ny, s ) ) continue;
			ns = state( nx, ny, s );		
			if ( d[nx][ny][ns][i] == -1 ){
				d[nx][ny][ns][i] = d[x][y][s][l] + 1;
				Q.push( node( pii( nx , ny ), pii( ns, i ) ) );
			}
		}
	}
	return -1;
}

int main(){
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);

	scanf("%d %d", &N, &M);
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < M; ++j ){
			scanf("%d", T[i] + j );
			
			for( int s = 0; s < 3; ++s )
				for ( int l = 0; l < 4; ++l )
					d[i][j][s][l] = -1;
		}
	printf("%d\n", bfs() );
	return 0;
}
