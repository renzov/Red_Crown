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

struct event {
	int t;
	double x,y,r;
	event(){}
	event( double X, double R, int T ){
		x = X, r = R, t = T;
	}
	event( double X , double Y , double R ){
		x = X, y = Y, r = R;
	}
	bool operator<(const event &that) const {
		return x < that.x;
	}
};

vector<event> E;

int main(){

	int runs;
	double x1,x2,y1,y2;
	double r;
	int n;
	scanf("%d",&runs);

	while ( runs-- ){
		E.clear();
		scanf("%d",&n);

		for ( int i=0; i<n; ++i ){
			
			scanf("%lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&r);
			if ( x1 <= x2 ){
				E.push_back( event( x1, r , 0 ) );
				E.push_back( event( x2, r , 1 ) );
			}
			else {
				E.push_back( event( x1, r , 1 ) );
				E.push_back( event( x2, r , 0 ) );
			}
		}

		sort(all(E));
		
		vector< event > q;
		x1 = 0;
		double p = 1.0;
		for ( int i=0; i < E.size(); ++i ){
			x2 = E[i].x;
			q.push_back( event( x1 , x2 , p ) );
			x1 = x2;
			if ( E[i].t ) p /= E[i].r;
			else p *= E[i].r; 
		}
		q.push_back( event( x1 , x2 , p ) );
		printf("%d\n",(int)q.size());
		for ( int i=0; i < q.size(); ++i ){
		
			if ( i==0 ){
				printf("-inf %0.3lf %0.3lf\n",q[i].y,q[i].r);
			}
			else if ( i == (q.size() - 1) ){
				printf("%0.3lf +inf %0.3lf\n",q[i].x,q[i].r);
			}
			else {
				printf("%0.3lf %0.3lf %0.3lf\n",q[i].x,q[i].y,q[i].r);				
			}
		}
		if ( runs ) puts("");
	}

	return 0;
}

