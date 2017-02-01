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
int n;
map<int,int> idx;
int M[MAX];
vector<int> G[MAX];
int S[MAX];
int C[MAX];
int B[MAX];
int res;

int dfs( int u ){
	int v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		dfs(v);
		res += abs( S[v] - C[v] );
		S[u] += S[v];
		C[u] += C[v];
	}
	C[u] += M[u];
	S[u]++;
}

int main(){
	int id;
	int m;
	while ( scanf("%d",&n) && n ){
		
		idx.clear();
		for ( int i=0; i < n; ++i ){ B[i] = false; C[i] = S[i] = 0; }

		for ( int i=0; i < n; ++i ){
			scanf("%d %d %d",&id,&M[i],&m);
			idx[ id ] = i;
			G[i].resize(m);
			for ( int j=0; j < m; ++j ){
				scanf("%d",&G[i][j]);
			}
		}
		for ( int i=0; i<n; ++i ){
			for (int j=0; j < G[i].size(); ++j){
				G[i][j] = idx[ G[i][j] ];
				B[ G[i][j] ] = true;
			}
		}
		res = 0;
		for ( int i=0; i < n; ++i ){
			if ( !B[i] ){
				dfs(i);
				break;
			}
		}
		printf("%d\n",res);
	}
	return 0;
}

