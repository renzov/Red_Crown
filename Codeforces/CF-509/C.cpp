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

const int MAXN = 200005;
int A[MAXN];
int ord[MAXN];
int res[MAXN];

bool cmp( const int &i, const int &j ){
	return A[i] < A[j];
}

priority_queue < pii, vector<pii>, greater<pii> > q;

int main(){
	int N, M, d;
	scanf("%d %d %d", &N, &M, &d);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A+i);
		ord[i] = i;
	}
	sort( ord, ord + N, cmp );
	int idx;
	int r;
	int col = 0;
	for ( int i=0; i < N; ++i ){
		idx = ord[i];
		r = A[ idx ];
		if ( q.empty() ){
			col++;
			q.push( pii( min(r + d, M) , col ) );
			res[idx] = col;
		}
		else {
			pii t = q.top();
			if ( r > t.first ){
				q.pop();
				q.push( pii( min(r + d, M), t.second ) );
				res[idx] = t.second;
			}
			else {
				col++;
				q.push( pii( min(r + d, M ) , col ) );
				res[idx] = col;
			}
		}
	}
	printf("%d\n", col);
	for( int i=0; i < N; ++i ){
		if ( i ) putchar(' ');
		printf("%d", res[i]);
	}
	puts("");
	return 0;
}

