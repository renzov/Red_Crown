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

const int MAXN = 10005;
int N;
vector<int> T[MAXN];
int color[MAXN][2];
int c;

void dfs( int u, int p ){
	if ( p == -1 ) color[u][0] = c++;
	else color[u][0] = color[p][1];
	
	if ( (int)T[u].size() == 1 ){
		if ( p==-1 ) color[u][1] = c++;
		else color[u][1] = color[p][0];
	}
	else {
		color[u][1] = c++;
	}
	
	int v;
	for ( int i=0; i < (int)T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			dfs( v, u );
		}
	}
}

int main(){
	int u, v;
	while ( scanf("%d", &N) != EOF ){
		for ( int i=0; i < N; ++i ){
			T[i].clear();
		}
		for ( int i=1; i<N; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			T[u].push_back(v);
			T[v].push_back(u);
		}
		c = 0;
		for ( int i=0; i < N; ++i ){
			if ( (int)T[i].size() == 1 ){
				dfs( i , -1 );
				break;
			}
		}
		for ( int i=0; i < N; ++i ){
			printf("%d %d\n", color[i][0], color[i][1]);
		}
	}
	return 0;
}

