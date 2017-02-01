#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 105;

int N,M;
int n,m;

int G[MAXN][MAXN];
int X[MAXN];
int Y[MAXN];
int D[MAXN];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};

void init(){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < M; ++j )
			G[i][j] = -1;
}

bool move( int id ){
	int nx = X[id] + dx[ D[id] ];
	int ny = Y[id] + dy[ D[id] ];
	if ( nx < 0 || ny < 0 || nx >= M || ny >= N ){
		printf("Robot %d crashes into the wall\n",id + 1);
		return false;
	}
	if ( G[ny][nx] != -1 ){
		printf("Robot %d crashes into robot %d\n",id + 1,G[ ny ][ nx ] + 1);
		return false;
	}
	G[ Y[id] ][ X[id] ] = -1;
	G[ ny ][ nx ] = id;
	X[id] = nx;
	Y[id] = ny;
	return true;
}

int getdir( char c ){
	switch (c){
		case 'E': return 0;
		case 'N': return 1;
		case 'W': return 2;
		case 'S': return 3;
	}
}

int main(){

	char c;
	int runs;
	int rep;
	int id;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d %d",&M,&N);
		scanf("%d %d",&n,&m);
		init();

		for ( int i=0; i < n; ++i ){
			scanf("%d %d %c",X+i,Y+i,&c);
			Y[i] = N - Y[i];
			X[i]--;
			G[ Y[i] ][ X[i] ] = i;
			D[i] = getdir(c);
		}

		bool ok = true;
		for ( int i=0; i < m; ++i ){
			scanf("%d %c %d",&id,&c,&rep);
			id--;
			for ( int j=0; ok && j < rep; ++j ){
				switch (c){
					case 'L': D[id] = (D[id] + 1)%4; break;
					case 'R': D[id] = (D[id] + 3)%4; break;
					case 'F': ok = move( id  ); break;
				}
			}
		}
		if (ok) puts("OK");
	}
	return 0;
}
