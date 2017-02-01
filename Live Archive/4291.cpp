#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <queue>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
using namespace std;


const int MAXN = 55;

int N;
int X1[MAXN];
int Y1[MAXN];
int Z1[MAXN];
int X2[MAXN];
int Y2[MAXN];
int Z2[MAXN];

int CX[MAXN << 1];
int CY[MAXN << 1];
int CZ[MAXN << 1]; 
int sx, sy, sz;
int M[ MAXN << 1 ][MAXN << 1][MAXN << 1];
int vol, area;

void compress_coor( int V[], int &size ){
	V[size++] = -INT_MAX;
	V[size++] = INT_MAX;
	sort( V, V + size );
	size = unique( V , V + size ) - V;
}

void flood_fill(){
	int dx[] = {0, 0, 0, 0, -1, 1};
	int dy[] = {0, 0, -1, 1, 0, 0};
	int dz[] = {-1, 1, 0, 0, 0, 0};
	
	queue<int> q;
	q.push( 0 ); // X index
	q.push( 0 ); // Y index
	q.push( 0 ); // Z index
	M[0][0][0] = 0;	
	int x, y, z;
	int nx, ny, nz;

	while ( !q.empty() ){
		x = q.front(); q.pop();
		y = q.front(); q.pop();
		z = q.front(); q.pop();
		for ( int i=0; i < 6; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			nz = z + dz[i];
			if ( nx < 0 || ny < 0 || nz < 0 || 
				 nx >= sx || ny >= sy || nz >= sz || 
				 M[nx][ny][nz] != 2 ) continue;
					
			M[nx][ny][nz] = 0;					
			q.push( nx ); q.push( ny ); q.push( nz );
		}
	}

	/* Calculate area and volume */
	vol = area = 0;

	for ( int i=1; i < (sx-1); ++i )
		for ( int j=1; j < (sy-1); ++j )
			for ( int k=1; k < (sz-1); ++k ){
				if ( M[i][j][k] ) vol += (CX[i+1]-CX[i])*(CY[j+1]-CY[j])*(CZ[k+1]-CZ[k]);
				if ( (M[i][j][k] + M[i-1][j][k]) == 1) area += (CY[j+1]-CY[j])*(CZ[k+1]-CZ[k]);
				if ( (M[i][j][k] + M[i][j-1][k]) == 1 ) area += (CX[i+1]-CX[i])*(CZ[k+1]-CZ[k]);
				if ( (M[i][j][k] + M[i][j][k-1]) == 1 ) area += (CY[j+1]-CY[j])*(CX[i+1]-CX[i]);
			}
}

int main(){
	int runs;
	
	scanf("%d", &runs);
	int dx, dy, dz;
	int fz,fy,fx;
	int ty,tx,tz;
	while ( runs-- ){
		scanf("%d", &N);
		sx = sy = sz = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d %d %d %d %d %d", X1+i, Y1+i, Z1+i, &dx, &dy, &dz);
			X2[i] = X1[i] + dx;
			Y2[i] = Y1[i] + dy;
			Z2[i] = Z1[i] + dz;

			CX[sx++] = X1[i]; CX[sx++] = X2[i]; 
			CY[sy++] = Y1[i]; CY[sy++] = Y2[i]; 
			CZ[sz++] = Z1[i]; CZ[sz++] = Z2[i]; 			
		}

		compress_coor( CX , sx );
		compress_coor( CY , sy );
		compress_coor( CZ , sz );

		/* Fill the space */
		for ( int i=0; i < sx; ++i )
			for ( int j=0; j < sy; ++j )
				for ( int k=0; k < sz; ++k )
					M[i][j][k] = 2;

		/* Mark the boxes */
		for ( int i=0; i < N; ++i ){
			fx = lower_bound( CX, CX + sx, X1[i] ) - CX;
			tx = lower_bound( CX, CX + sx, X2[i] ) - CX;
			fy = lower_bound( CY, CY + sy, Y1[i] ) - CY;
			ty = lower_bound( CY, CY + sy, Y2[i] ) - CY;
			fz = lower_bound( CZ, CZ + sz, Z1[i] ) - CZ;
			tz = lower_bound( CZ, CZ + sz, Z2[i] ) - CZ;

			for ( int x=fx; x < tx; ++x )
				for ( int y=fy; y < ty; ++y )
					for ( int z=fz; z < tz; ++z )
						M[x][y][z] = 1;
		}
		/* Flood fill from outside */
		flood_fill();
		printf("%d %d\n", area, vol);
	}
	return 0;
}

