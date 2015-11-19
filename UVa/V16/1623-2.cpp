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
const int MAXN = 1000005;

int rain[ MAXN ]; 
int p[ MAXN ];
int last[ MAXN ];
int lst[ MAXN ];
int res[ MAXN ];

inline int find(int x){ return (x == p[x])? x:(p[x] = find(p[x])); }

int main(){
	int runs;
	int N,M;
	bool ok;
	int size;
	int pos;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		fill( last + 1 , last + N + 1, 0 );
		p[0] = 1;
		p[M+1] = M+1;
		for ( int i=1; i <= M; ++i ){
			res[i] = 0;
			scanf("%d", rain + i);
			if (rain[i]) p[i] = i+1;
			else p[i] = i;
		}
		ok = true;
		size = 0;
		for ( int i=1; i <= M && ok; ++i ){
			if ( rain[i] ){
				pos = find( last[ rain[i] ] );
				if ( pos > i ) ok = false;
				else {
					last[ rain[i] ] = i;
					res[ pos ] = rain[i];
					p[ pos ] = pos + 1;
				}
			}
			else {
				lst[size++] = i;
			}
		}
		if (!ok) puts("NO");
		else {
			puts("YES");
			if ( size ){
				printf("%d", res[ lst[0] ]);
				for (int i=1; i < size; ++i) 
					printf(" %d", res[ lst[i] ]);
				putchar('\n');
			}
		}
	}
	return 0;
}

