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
#include <climits>

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
const int MAXD = 205;
int H, L;
int M[MAXD][MAXD];
bool vis[MAXD][MAXD]={0};
int frec[ MAXD * MAXD ] = {0};

int dx[]={1, 0, -1, 0};
int dy[]={0, -1, 0, 1};

int flood( int x, int y ){
	vis[x][y] = true;
	int nx, ny;
	int res = 1;
	for ( int k=0; k < 4; ++k ){
		nx = x + dx[k];
		ny = y + dy[k];
		if ( nx < 0 || ny < 0 || nx >= H || ny >= L )
			continue;
		if ( M[nx][ny] == M[x][y] && !vis[nx][ny] ){
			res += flood( nx, ny );
		}
	}
	return res;
}

int main(){
	int val;
	int res = INT_MAX;
	scanf("%d %d", &H, &L );
	for ( int i=0; i < H; ++i )
		for ( int j=0; j < L; ++j )
			scanf("%d", &M[i][j]);
	for ( int i=0; i < H; ++i )
		for ( int j=0; j < L; ++j )
			if ( !vis[i][j] ){
				val = flood( i , j );
				if ( frec[ M[i][j] ] == 0 || 
				     frec[ M[i][j] ] > val ){
					 	frec[ M[i][j] ] = val;
					res = min( res, val );
				}
			}
	printf("%d\n", res);
	return 0;
}

