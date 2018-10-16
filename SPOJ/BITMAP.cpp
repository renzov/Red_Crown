#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 256;

int N, M;
char B[MAXN][MAXN];
int d[MAXN][MAXN];
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

bool valid( const int &x, const int &y ){
	return x >= 0 && y >= 0 && x < N && y < M;
}

void process(){
	queue<pii> q;
	scanf("%d %d", &N, &M);
	
	for ( int i=0; i < N; ++i )
		fill( d[i], d[i] + M, -1 );
	
	for ( int i=0; i < N; ++i ){
		scanf("%s", B[i]);
		for ( int j=0; j < M; ++j )
			if ( B[i][j] == '1' ){
				d[i][j] = 0;
				q.push( pii( i, j ) );
			}			
	}
	
	int x, y, nx, ny;
	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if (  valid( nx, ny ) && d[nx][ny] == -1 ){
				d[nx][ny] = d[x][y] + 1;
				q.push( pii(nx, ny) );
			}
		}
	}
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < M; j++ ){
			if (j) putchar(' ');
			printf("%d", d[i][j]);
		}
		puts("");
	}
}

int main(){
	int runs;
	
	scanf("%d", &runs);
	while ( runs-- ){
		process();
	}
	return 0;
}
