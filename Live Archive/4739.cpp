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

const int MAXN = 256;

int N;
bool D[MAXN][MAXN];
vector<int> G[MAXN];
vector<int> I[MAXN];

void init(){
	for ( int i=0; i < N; ++i ){
		G[i].clear();
		I[i].clear();
		fill( D[i] , D[i] + N , false );
		
		G[i].push_back(i);
		I[i].push_back(i);
		D[i][i] = true;
	}
}

int main(){

	int T;	
	int cases = 0;
	int u,v,a,b;
	int res;

	while ( scanf("%d %d", &N, &T) && N && T ){
		cases++;
		res = 0;
		init();
		for ( int i=0; i < T; ++i ){
			scanf("%d %d", &u, &v);
			u--,v--;
			if ( D[v][u] ) res++;
			else {
				for ( int i=0; i < (int)I[u].size(); ++i ){
					a = I[u][i];
					if ( !D[a][v] ){
						for ( int j=0; j < (int)G[v].size(); ++j ){
							b = G[v][j];
							if ( !D[a][b] ){
								D[a][b] = true;
								G[a].push_back(b);
								I[b].push_back(a);
							}
						}
					}
				}
			}
		}
		printf("%d. %d\n", cases, res);
	}
	return 0;
}
