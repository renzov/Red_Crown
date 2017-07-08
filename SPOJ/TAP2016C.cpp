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

const int MAXN = 50005;

int N, M;
vector<int> G[MAXN];
int indeg[MAXN];
int idx[MAXN];

bool blocked[MAXN];
bool freed[MAXN];

int main(){
	int u, v;
	int res;
	while ( scanf("%d %d", &N, &M) != EOF ){
		for ( int i=0; i < N; ++i ){
			G[i].clear();
			indeg[i] = 0;
			blocked[i] = true;
			freed[i] = false;
		}
		// Read the DAG		
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			indeg[v]++;
			G[u].push_back(v);
		}
		// Read the order
		for ( int i=0; i < N; ++i ){ scanf("%d", idx + i); idx[i]--; }
		// initialize free
		for ( int i=0; i < N; ++i )
			if ( indeg[ i ] == 0 ) freed[ i ] = true;
		// Process the vertices
		queue<int> q;
		res = 0;
		for ( int i=0; i < N; ++i ){
			u = idx[i];
			blocked[u] = false;
			if ( freed[u] ){
				q.push( u );
				while ( !q.empty() ){
					res++;
					u = q.front();
					q.pop();
					for ( int j=0; j < (int)G[u].size(); ++j ){
						v = G[u][j];
						indeg[v]--;
						if ( indeg[v] == 0 ) freed[v] = true;
						if ( !blocked[v] && freed[v] ) q.push(v);
					}
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}

