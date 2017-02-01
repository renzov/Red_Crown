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

int main(){
	
	double u,v,t,a,s;
	int type;
	int runs = 0;

	while ( scanf("%d",&type) && type ){
		runs++;
		printf("Case %d: ",runs);
		if ( type == 1 ){
			scanf("%lf %lf %lf",&u,&v,&t);
			a = (v - u) / t;
			s = u * t + .5*a*t*t;
			printf("%.3lf %.3lf\n",s,a);
		}
		else if ( type == 2 ){
			scanf("%lf %lf %lf",&u,&v,&a);
			t = (v - u) / a;
			s = u * t + .5 * a * t * t;
			printf("%.3lf %.3lf\n",s,t);
		}
		else if ( type == 3 ){
			scanf("%lf %lf %lf",&u,&a,&s);
			v = sqrt( u*u + 2*a*s );
			t = ( v - u ) / a;
			printf("%.3lf %.3lf\n",v,t);
		}
		else {
			scanf("%lf %lf %lf",&v,&a,&s);
			u = sqrt ( v*v - 2*a*s );
			t = ( v - u ) / a;
			printf("%.3lf %.3lf\n",u,t);
		}
	}
	return 0;
}

