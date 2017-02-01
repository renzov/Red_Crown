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
typedef pair< int , int > edge;

const int MAXN = 100005;
const int MAXM = 600005;
int N, M;
vector<int> G[MAXN];
edge E[MAXM];
bool used[MAXM] = {0};
int odd[MAXN];
vector<int> T;

void tour( int u ){
	int e, v;
	while ( !G[u].empty() ){
		if ( !used[ G[u].back() ] ){
			e = G[u].back();
			v = ( E[e].first == u )? E[e].second:E[e].first;
			used[e] = true;
			G[u].pop_back();
			tour(v);
		}
		else {
			G[u].pop_back();
		}
	}
	T.push_back( u );
}

int main(){
	int u , v;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d", &u, &v);
		u--, v--;
		E[i] = edge( u , v );
		G[u].push_back(i);
		G[v].push_back(i);
	}
	int o = 0;
	for ( int i=0; i < N; ++i )
		if ( (int)G[i].size()&1 ) odd[o++] = i;
	// o must be even
	for ( int i=0; i < o; i+=2 ){
		u = odd[i], v = odd[i+1];
		E[ M ] = edge( u, v );
		G[u].push_back(M);
		G[v].push_back(M);
		M++;
	}
	if ( M & 1 ){
		E[M] = edge( 0, 0 );
		G[0].push_back( M );
		M++;
	}
	tour( 0 );
	printf("%d\n", M);
	for ( int i=1; (i+1) < (int)T.size(); i += 2 ){ 
		printf("%d %d\n", T[i]+1, T[i-1]+1);
		printf("%d %d\n", T[i]+1, T[i+1]+1);
	}
	return 0;
}

