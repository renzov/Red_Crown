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
#include <list>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 505;
int N, M;
map<int,int> f;
map<int,int> f2;
pii P[2*MAXN];
map< int, list<int> > L;

int len( const pii &a, const pii &b ){
	if ( a.X == b.X ) return abs(a.Y - b.Y);
	return abs(a.X - b.X);
}

void print( bool val ){
	int left, right;
	int l;

	if ( val ) left = 2, right = N;
	else left = 1, right = N - 1;
	
	puts("YES");
	int n = 0;
	int res[505];
	fill(res, res + N + 1, -1 );
	for ( int i=left; i <= right; i+=2 ){
		l = len( P[i-1], P[i] );
		l += len( P[i], P[i+1] );
		res[ i%N ] = L[l].front();
		L[l].pop_front();
	}
	for ( int i=0; i < N; ++i ){ 
		if (i) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
}

int main(){
	int v, l;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){ 
		scanf("%d %d", &P[i].X, &P[i].Y);
		P[i+N] = P[i];
	}
	for ( int i=0; i < M; ++i ){ 
		scanf("%d", &v);
		f[v]++;
		if ( !L.count(v) ) L[v] = list<int>();
		L[v].push_back(i+1);
	}
	// first we test taking 0 as center
	for( int i=2; i <= N; i += 2 ){
		l = len( P[i-1], P[i] );
		l += len( P[i], P[i+1] );
		f2[l]++;
	}
	bool ok = true;
	for ( map<int,int>::iterator it=f2.begin(); it != f2.end() && ok; ++it ){
		ok &= (it->second <= f[it->first]);
	}
	if ( ok ) print(true);
	else {
		// Test the other possibility
		f2.clear();
		for( int i=1; i < N; i += 2 ){
			l = len( P[i-1], P[i] );
			l += len( P[i], P[i+1] );
			f2[l]++;
		}
		ok = true;
		for ( map<int,int>::iterator it=f2.begin(); it != f2.end() && ok; ++it ){
			ok &= (it->second <= f[it->first]);
		}
		if ( ok ) print(false);
		else printf("NO\n");
	}
	return 0;
}

