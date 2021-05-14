#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int MAXN = 20005;
map<int,int> idx;
int N;
int T;
int par[MAXN];
int f[MAXN];

int find_set( const int &x ){
	if ( x == f[x] ) return x;
	int px = f[x];
	int rx = find_set( px );
	f[x] = rx;
	par[x] = par[px] ^ par[x];
	return rx;
}

int get_idx( const int &x ){
	int id = idx[x];
	if ( !id ){
		id = idx[x] = ++T;
		f[ id ] = id;
		par[ id ] = 0;
	}
	return id;
}

void process(){
	int M;
	int u, v, rv, ru;
	int p;
	char op[10];
	bool ok = true;

	scanf("%d", &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %s", &u, &v, op);
		if ( ok ){
			p = ( op[0] == 'e' )? 0:1;	
			if ( u <= 0 || v <= 0 || u > N || v > N || u > v ){
				ok = false;
				printf("%d\n", i);
				continue;
			}
			u--;
			u = get_idx( u );
			v = get_idx( v );
			ru = find_set( u );
			rv = find_set( v );
			if ( ru == rv ){
				if ( (par[u] ^ par[v]) != p ){
					ok = false;
					printf("%d\n", i);
					continue;
				}
			}
			else {
				f[rv] = ru;
				par[rv] = par[v] ^ par[u] ^ p;
			}
		}
	}
	if ( ok ) printf("%d\n", M);
}

int main(){
	while ( scanf("%d", &N) && N >= 0 ){
		process();
		idx.clear(); T = 0;
	}
	return 0;
}
