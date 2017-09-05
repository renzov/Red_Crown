#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXR = 500;

int R, C;
char M[MAXR][MAXR];
int d[MAXR][MAXR];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

bool isvalid( const int &x, const int &y ){
	return x >= 0 && x < R && y >= 0 && y < C && M[x][y] != '#'; 
}

bool isborder( const int &x, const int &y ){
	return x == 0 || x == (R-1) || y == 0 || y == (C-1);
}

int main(){
	scanf("%d %d", &R, &C);
	
	for ( int i=0; i < R; ++i ){
		scanf("%s", M[i]);
		fill( d[i], d[i] + C, INT_MAX );
	}

	int sx, sy;
	scanf("%d %d", &sx, &sy);
	sx--, sy--;

	d[sx][sy] = 1;
	deque< pii > q;
	q.push_back( pii(sx, sy) );	

	int x, y, nx, ny;

	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop_front();

		if ( M[x][y] == 'D' && isborder(x,y) ){
			printf("%d\n", d[x][y]);
			break;
		}

		for ( int i=0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( !isvalid( nx, ny ) ) continue;
			if ( M[nx][ny] == 'c' ){
				if ( d[nx][ny] > d[x][y] + 1 ){
					d[nx][ny] = d[x][y] + 1;
					q.push_back( pii( nx, ny ) );
				}
			}
			else {
				if ( d[nx][ny] > d[x][y] ){
					d[nx][ny] = d[x][y];
					q.push_front( pii( nx, ny ) );
				}
			}
		}
	}

	return 0;
}
