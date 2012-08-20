#include<cstdio>
#include<queue>
using namespace std;
int n;
int sx,sy,ex,ey;
int d[305][305];
int dx[] = {1,2,2,1,-1,-2,-2,-1};
int dy[] = {2,1,-1,-2,2,1,-1,-2};

int bfs(){
	if ( sx == ex && sy == ey ) return 0;
	for ( int i=0; i < n; ++i ) for ( int j=0; j < n; ++j ) d[i][j] = -1;
	d[sx][sy] = 0;
	queue< pair<int,int> > q;
	q.push( make_pair(sx,sy) );
	int x,y;
	int nx,ny;
	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for ( int i=0; i < 8; ++i ){
			nx = x + dx[i]; ny = y + dy[i];
			if ( nx < 0 || ny < 0 || nx >= n || ny >= n ) continue;
			if ( d[nx][ny] == -1 ){
				d[nx][ny] = d[x][y] + 1;
				if ( nx == ex && ny == ey ) return d[nx][ny];
				q.push( make_pair(nx,ny) );
			}
		}
	}
	return -1;
}

int main(){
	int res;
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&n);
		scanf("%d %d",&sx,&sy);
		scanf("%d %d",&ex,&ey);
		res = bfs();
		printf("%d\n",res);
	}

	return 0;
}
