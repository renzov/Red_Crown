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
typedef pair< double , int > event;

const int MAXE = 200005;
event E[MAXE];

int main(){
	int N, m, M;
	double w, u, v, t1, t2;
	char dir;
	double p, l, res;
	int cnt;
	while ( scanf("%d %lf %lf %lf %lf %lf", &N, &w, &u, &v, &t1, &t2) != EOF ){
		M = 0;	// Num of events 
		E[M++] = event(t1, 0);
		E[M++] = event(t2, 0);		
		for ( int i=0; i < N; ++i ){
			scanf(" %c %d", &dir, &m);
			for ( int j=0; j < m; ++j ){
				scanf("%lf %lf", &l, &p);
				if ( dir == 'W' ) p = -p;	// mirroring
				E[M++] = event( -p/u - (i+1)*w/v , 1 );
				E[M++] = event( (-p + l)/u - i*w/v, -1 );
			}
		}
		sort( E, E + M );
		cnt = 0; // Num of active intervals
		res = 0.0; 
		for ( int i=0; (i+1) < M; ++i ){
			cnt += E[i].second;
			if ( E[i].first < t1 ) continue;
			if ( E[i+1].first > t2 ) continue;
			if ( cnt == 0 ){
				res = max( res , E[i+1].first - E[i].first );
			}
		}
		printf("%f\n", res);
	}
	return 0;
}
