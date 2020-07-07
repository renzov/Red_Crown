#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
#include<cassert>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 32;

int best[20005][20005];
queue<pii> q[2];
int W[MAXN];

int main(){
	
	int N;
	int total = 0;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", W + i);
		total += W[i];
	}
	W[N] = 0;
	int x, y, z, w;
	int nx, ny, nz;
	int res = total;
	q[0].push( pii(0, 0) );

	int act = 0, nxt = 1;
	int mx;
	
	for ( int i=0; i <= total; ++i )
		for ( int j=0; j <= total; ++j )
			best[i][j] = INT_MAX;
	best[0][0] = total;
	
	for ( int i=0; i < N; ++i ){
		w = W[i];
		while ( !q[act].empty() ){
			x = q[act].front().first, y = q[act].front().second;
			z = total - x - y;
			q[act].pop();

			nx = x + w;
			ny = y;
			nz = z - w;
			mx = max( nx, max( ny, nz ) );
			if ( best[nx][ny] > mx ){
				q[nxt].push( pii(nx, ny) );
				best[nx][ny] = mx;
				assert( nx + ny + nz == total );				
				res = min( res, mx );
			}
			
			nx = x;
			ny = y + w;
			nz = z - w;
			mx = max( nx, max( ny, nz ) );
			if ( best[nx][ny] > mx ){
				q[nxt].push( pii(nx, ny) );
				best[nx][ny] = mx;
				assert( nx + ny + nz == total );
				res = min(res, mx);
			}
		}
		swap( act, nxt );
	}
	printf("%d\n", res);
	return 0;
}

