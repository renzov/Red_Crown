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

const int MAXN = 100005;

vector<int> group[MAXN];
map<int,int> idx;
int nG = 0; 
int N;
int L[MAXN];
int R[MAXN];
int C[MAXN];
int V[MAXN];

int last[MAXN];
int res[MAXN];
int bres[MAXN];

int find_best( vector<int> &id, int &n, int sol[] ){
	map<int,int> b;
	map<int,int> p;
	int x;
	int prev;

	for ( int i=0; i < id.size(); ++i ){
		x = id[i];
		prev = R[x] + C[x];
		if ( L[x] == 0 && (b[ R[x] ] < V[x]) ){
			b[ R[x] ] = V[x];
			p[ R[x] ] = x;
			last[ x ] = -1;
		}
		else if ( L[x] != 0 && b[prev] != 0 && (b[ R[x] ] < V[x] + b[prev]) ){
			b[ R[x] ] = b[prev] + V[x];
			last[x] = p[ prev ];
			p[ R[x] ] = x;			
		}
	}

	if ( b[0] == 0 ) return -1;
	n = 0;
	x = p[0];
	do {
		sol[n++] = x;
		x = last[x];
	}
	while ( x >= 1 );
	reverse( sol, sol + n );
	return b[0];
}

int main(){
	int val;

	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		scanf("%d %d %d %d", V+i, C+i, L+i, R+i);
		val = L[i] + C[i] +  R[i];
		if ( !idx.count(val) ) idx[val] = nG++;
		group[ idx[val] ].push_back( i );
	}
	int best = -1;
	int bcnt = 0;
	int cnt;
	for ( int i=0; i < nG; ++i ){
		val = find_best( group[i], cnt, res );
		if ( val > best ){
			best = val;
			bcnt = cnt;
			// copy answer
			for ( int j=0; j < cnt; ++j ) bres[j] = res[j];
		}
	}
	printf("%d\n", bcnt);
	for ( int i=0; i < bcnt; ++i ){
		if (i) putchar(' ');
		printf("%d", bres[i]);
	}
	puts("");
	return 0;
}

