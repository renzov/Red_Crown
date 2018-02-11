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
int out[MAXN];
int indeg[MAXN] = {0};

int main(){
	freopen ("shuffle.out","w",stdout);
	freopen ("shuffle.in","r",stdin);	
	int N;
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", out + i);
		indeg[ out[i] ]++;
	}
	queue< int > q;
	for ( int i=1; i <= N; ++i )
		if ( indeg[i] == 0 ) q.push(i);

	int res = N;
	int u, v;
	while ( !q.empty() ){
		u = q.front();
		q.pop();
		res--;
		v = out[u];
		indeg[ v ]--;
		if ( indeg[v] == 0 )
			q.push( v );
	}
	printf("%d\n", res);
	return 0;
}

