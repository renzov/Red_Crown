#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAXN = 20005;
int N, Q;

int f[MAXN];
int XOR[MAXN];
char line[128];

void read_query( int &type, int v[] ){
	char ch[8]; 
	scanf("%s", ch);
	if ( ch[0] == 'Q' ){
		type = 3;
		scanf("%d", &v[0]);
		for ( int i=1; i <= v[0]; ++i )
			scanf("%d", v + i );
	}
	else {
		gets(line);
		if ( sscanf(line, "%d %d %d", v, v+1, v+2) == 2 ){
			type = 1;
		}
		else {
			type = 2;
		}
	}
}

int find_set( const int &x ){
	if ( x == f[x] ) return x;
	int px = f[x];
	f[x] = find_set( px );
	XOR[x] ^= XOR[ px ];
	return f[x];
}

void process(){
	for ( int i=0; i <= N; ++i ) f[i] = i, XOR[i] = 0;
	bool ok = true;
	int type;
	int val[32];
	int u, pu, v, pv;
	int x, k;
	int res; 
	int p[32];
	int facts = 0;
	while ( Q-- ){
		read_query( type , val );
		if ( ok ){
			if ( type == 1 ){
				facts++;
				u = N;
				v = val[ 0 ];
				x = val[ 1 ];
				pu = find_set( u );
				pv = find_set( v );
				if ( pu != pv ){
					f[pv] = pu;
					XOR[pv] = XOR[v] ^ XOR[u] ^ x;
				}
				else if ( (XOR[u] ^ XOR[v]) != x ){
					ok = false;
					printf("The first %d facts are conflicting.\n", facts);
				}
			}
			else if ( type == 2 ){
				facts++;
				u = val[0];
				v = val[1];
				x = val[2];
				//printf("u = %d - v = %d - x = %d\n", u, v, x);
				pu = find_set( u );
				pv = find_set( v );
				//printf("pu = %d - pv = %d - Xu = %d - Xv = %d -- %d\n\n", pu, pv, XOR[u], XOR[v], XOR[u] ^ XOR[v]);
				if ( pu != pv ){
					if ( pv == find_set(N) ){
						swap( pv, pu );
						swap( u, v );
					}
					f[pv] = pu;
					XOR[pv] = XOR[v] ^ XOR[u] ^ x;
				}
				else if ( (XOR[u] ^ XOR[v]) != x ) {
					ok = false;
					printf("The first %d facts are conflicting.\n", facts);
				}
			}
			else {
				k = val[0];
				res = 0;
				for ( int i=1; i <= k; ++i ){
					p[i - 1] = find_set( val[i] );
					res ^= XOR[ val[i]  ];
				}
				sort( p, p + k );
				int last = -1;
				int cnt = 0;
				bool pos = true;
				// count if every parent (not zero) appears an even number of times
				for ( int i=0; i < k && pos; ++i ){
					if ( last != p[i] ){
						if ( (cnt & 1) && last != find_set(N) ) pos = false;
						last = p[i];
						cnt = 1;
					}
					else {
						cnt++;
					}
				}
				if ( (cnt & 1) && last != find_set(N) ) pos = false;
				if (pos) printf("%d\n", res);
				else puts("I don't know.");
			}
		}
	}
}

int main(){
	int runs = 0;
	while ( scanf("%d %d", &N, &Q) && N ){	
		runs++;
		printf("Case %d:\n", runs);
		process();
		puts("");
	}
	return 0;
}
