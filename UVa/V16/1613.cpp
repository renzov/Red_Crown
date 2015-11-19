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
const int MAXN = 9999;

int N,M;
vector<int> G[MAXN];
int color[MAXN];

void dfs( int u ){
	int v;
	int tmp[ (int)G[u].size() + 1 ];
	int s = 0;

	color[u] = -2;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( color[v] == -1 ){
			dfs( v );
			tmp[s++] = color[v];
		}
		else if (color[v] > -1){
			tmp[s++] = color[v];
		}
	}

	if (s == 0){
		color[u] = 0;
		return;
	}

	sort(tmp, tmp + s);
	int last = 0;
	for ( int i=0; ; ++i ){
		if ( last >= s || tmp[last] != i ){
			color[u] = i; break;
		}
		while ( last < s && tmp[last] == i ) last++;
	}
}

int main(){
	int Mdeg,mdeg;
	int k,root;
	int cases = 0;
	int u,v;

	while ( scanf("%d %d",&N,&M) != EOF ){
		
		if (cases) puts("");
		cases++;

		for ( int i=0; i < N; ++i ){
			G[i].clear();
			color[i] = -1;
		}
		while ( M-- ){
			scanf("%d %d",&u,&v);
			u--,v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Mdeg = 0;
		mdeg = N;
		for ( int i=0; i < N; ++i ){
			if ( (int)G[i].size() > Mdeg ) Mdeg = (int) G[i].size();
			if ( (int)G[i].size() < mdeg ){ mdeg = (int) G[i].size(); root = i; }
		}
		if ( Mdeg & 1 ) k = Mdeg;
		else k = Mdeg + 1;

		dfs( root );

		printf("%d\n",k);
		for ( int i=0; i < N ; ++i ) printf("%d\n",color[i] + 1);
	}
	return 0;
}

