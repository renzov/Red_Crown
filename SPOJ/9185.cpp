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
const int MAXR = 105;
const int MAXN = 10005;

int R,C,N;
int dx[] = {1,0,-1,0};
int dy[] = {0,-1,0,1};
char M[MAXR][MAXR];
int idx[MAXR][MAXR];
vector<pii> G[MAXN][4];
stack<pii> S;
int n;
int num[MAXN][4];
int low[MAXN][4];
bool in[MAXN][4];
int nc;
int comp[MAXN][4];
pii rep[MAXN];
int val[MAXN];
int T[MAXR][MAXR][4];

void dfs( int u , int k ){
	low[u][k] = num[u][k] = n++;
	in[u][k] = true;
	S.push( mp( u , k ) );
	int v,j;
	for ( int i=0; i < G[u][k].size(); ++i ){
		v = G[u][k][i].first;
		j = G[u][k][i].second;
		if ( num[v][j] == -1 ){
			dfs(v,j);
			low[u][k] = min( low[u][k] , low[v][j] );
		}
		else if ( in[v][j] ){
			low[u][k] = min( low[u][k] , num[v][j] );
		}
	}

	if ( low[u][k] == num[u][k] ){
		do {
			v = S.top().first;
			j = S.top().second;
			S.pop(); in[v][j] = false;
			comp[v][j] = nc;
		}
		while ( u != v || k != j );
		rep[nc++] = mp( u , k );
	}
}

bool two_sat(){
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < 4; ++j ){
			num[i][j] = -1;
			in[i][j] = false;
		}

	while ( !S.empty() ) S.pop();
	
	n = 0;
	nc = 0;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < 4; ++j )
			if ( num[i][j] == -1 )
				dfs(i,j);

	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < 4; ++j ){
			if ( comp[i][j] == comp[i][(j+2)%4] ){
				return false;
			}
		}
	}

	fill( val , val + nc , -1 );
	int u,k,j;
	for ( int i=0; i < nc; ++i ){
		if ( val[i] == -1 ){
			val[i] = 1;
			u = rep[i].first; k = rep[i].second;
			j = (k + 2) % 4;
			val[ comp[u][j] ] = 0;
		}
	}
	return true;
}

char get_res( int u ){
	if ( val[ comp[u][0] ] ){
		return val[ comp[u][1] ]? '3' : '2';
	}
	else {
		return val[ comp[u][1] ]? '4' : '1';
	}
}

void add( int u , int k ){
	int j = (k + 2)%4;
	G[u][j].push_back( mp( u , k ) );
}

void add( int u , int k , int v , int j ){
	int l = (k + 2)%4;
	int m = (j + 2)%4;
	G[u][l].push_back( mp(v,j) );
	G[v][m].push_back( mp(u,k) );
}

void error(const char *s ){
	//puts(s);
	while(1);
}

int main(){
	
	scanf("%d %d",&R,&C);
	
	N = 0;

	for ( int i=0; i < R; ++i ){
		scanf("%s",M[i]);
		for ( int j=0; j < C; ++j )
			if ( M[i][j] == 'T' ){
				idx[i][j] = N++;
			}
	}

	for ( int i=0; i < R; ++i ){
		//<--
		T[i][0][2] = -1;
		for ( int j=1; j < C; ++j ){
			if ( M[i][j] == '#' ) T[i][j][2] = -1;
			else if ( M[i][j - 1] == 'T' ) T[i][j][2] = idx[i][j-1];
			else T[i][j][2] = T[i][j-1][2];
		}
		//-->
		T[i][C - 1][0] = -1;
		for ( int j = C - 2; j >= 0 ; j-- ){
			if ( M[i][j] == '#' ) T[i][j][0] = -1;
			else if ( M[i][j+1] == 'T' ) T[i][j][0] = idx[i][j+1];
			else T[i][j][0] = T[i][j+1][0];
		}
	}
	for ( int j=0; j < C; ++j ){
		// ^
		T[0][j][1] = -1;
		for ( int i=1; i < R; ++i ){
			if ( M[i][j] == '#' ) T[i][j][1] = -1;
			else if ( M[i-1][j] == 'T' ) T[i][j][1] = idx[i-1][j];
			else T[i][j][1] = T[i-1][j][1];
		}
		// v
		T[R-1][j][3] = -1;
		for ( int i=R-2; i >= 0; --i ){
			if ( M[i][j] == '#' ) T[i][j][3] = -1;
			else if ( M[i+1][j] == 'T' ) T[i][j][3] = idx[i+1][j];
			else T[i][j][3] = T[i+1][j][3];
		}
	}

	int cnt;
	pii pos[2];
	for ( int i=0; i < R; ++i ){
		for ( int j=0; j < C; ++j ){
			if ( M[i][j] == 'T' ){
				for ( int k=0; k < 4; ++k )
					if ( T[i][j][k] >= 0 ) add( idx[i][j] , (k + 2)%4 );
			}
			else if ( M[i][j] == 'n' ){
				cnt = 0;
				if ( T[i][j][0] > -1 && T[i][j][2] == -1 ){
					pos[cnt++] = mp( T[i][j][0] , 2 );
				}
				else if ( T[i][j][0] == -1 && T[i][j][2] > -1 ){
					pos[cnt++] = mp( T[i][j][2] , 0 );
				}
				if ( T[i][j][1] > -1 && T[i][j][3] == -1 ){
					pos[cnt++] = mp( T[i][j][1] , 3 );
				}
				else if ( T[i][j][1] == -1 && T[i][j][3] > -1 ){
					pos[cnt++] = mp( T[i][j][3] , 1 );
				}
				if ( cnt == 2 ) add( pos[0].first , pos[0].second , pos[1].first , pos[1].second  );
				else if ( cnt == 1 ) add( pos[0].first , pos[0].second );
				else { printf("(%d , %d) ",i,j); error("uncovered position"); }
			}
		}
	}

	if ( two_sat() ){	
		for ( int i=0; i < R; ++i ){
			for ( int j=0; j < C; ++j ){
				if ( M[i][j] != 'T' ) putchar(M[i][j]);
				else putchar( get_res( idx[i][j] ) );
			}
			puts("");
		}
	}
	else {
		error("Not satisfiable");
	}
	return 0;
}

