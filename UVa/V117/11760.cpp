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
const int MAX = 10005;

bool col[MAX];
bool row[MAX];

int dx[] = {0,0,-1,0,1};
int dy[] = {0,1,0,-1,0};

int main(){
	int x,y,nx,ny;
	int R,C,N;
	int runs = 0;
	while ( scanf("%d %d %d",&R,&C,&N) && N ){
		runs++;
		fill( row, row + R , false );
		fill( col , col + C , false );
		for ( int i=0; i < N ; ++i ){
			scanf("%d %d",&x,&y);
			row[x] = true;
			col[y] = true;
		}
		scanf("%d %d",&x,&y);
		bool ok = true;
		for ( int i=0; i < 5 && ok; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( nx < 0 || ny < 0 || nx >= R || ny >= C ) continue;
			ok = row[nx] || col[ny];
		}
		
		printf("Case %d: ",runs);
		if ( ok ) puts("Party time! Let's find a restaurant!");
		else puts("Escaped again! More 2D grid problems!");
	}
	return 0;
}

