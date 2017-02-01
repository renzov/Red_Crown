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
typedef pair< int , pii > piii;

const int MAXN = 1005;

bool bad[MAXN];
int f[MAXN];

void make_set(int x){ f[x] = x; }
int find_set( int x ){ return (x != f[x])? (f[x] = find_set(f[x])):x; }
void link( int x, int y ){ f[x] = y; }

int main(){
	int u,v,w;
	int n,m,p;

	while (scanf("%d %d %d", &n,&m,&p) != EOF){
		fill( bad, bad + n, false );
		for ( int i=0; i < p ; ++i ){
			scanf("%d", &u); u--;
			bad[u] = true;
		}
		vector< piii > E,F;
		
		if (n == 1){ // m == 0
			puts("0");
			continue;
		}
		else if (n == 2){
			if (m == 0) puts("impossible");
			else {  // m == 1
				scanf("%d %d %d",&u,&v,&w);
				printf("%d\n", w);
			}
			continue;
		}
		
		while (m--){
			scanf("%d %d %d", &u, &v, &w);
			u--,v--;
	 		if ( bad[u] && bad[v] ) continue;
			else if ( bad[u] || bad[v] ) F.push_back( make_pair( w , make_pair(u, v) ) );
			else E.push_back( make_pair( w , make_pair(u, v) ) );
		}
		for ( int i=0; i < n ; ++i ) make_set(i);
		int comp = n;
		int res = 0;
		sort( all(E) );
		sort( all(F) );
		for ( int i=0; i < (int)E.size(); ++i ){
			u = find_set(E[i].second.first);
			v = find_set(E[i].second.second);
			w = E[i].first;
			if ( u != v ){
				link( u , v );
				comp--;
				res += w;
			}
		}
		if ( comp != (p + 1) ){
			puts("impossible");
		}
		else {
			for ( int i=0; i < (int)F.size() && comp > 1 ; ++i ){
				u = find_set(F[i].second.first);
				v = find_set(F[i].second.second);
				w = F[i].first;
				if ( u != v ){
					link( u , v );
					comp--;
					res += w;
				}
			}
			if (comp != 1) puts("impossible");
			else printf("%d\n", res);
		}
	}
	return 0;
}

