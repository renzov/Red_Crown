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

	int n;
	int k;
	int s;

	while ( scanf("%d",&k) != EOF ){
		scanf("%d",&s);
		scanf("%d",&n);
		vector<pii> a( n );
		for ( int i=0; i < n; ++i ){
			scanf("%d",&a[i].first);
			a[i].second = i;
		}
		
		sort( all(a) );

		int up = n % k;
		int down = k - up;

		int x = n / k;
		int y = ( n % k )? (x + 1):x;
		
		//printf("U = %d\tD = %d\tX = %d\tY = %d\n",up,down,x,y);

		int idx = 0;
		int sch = 0;
		int last;
		int res,pos;

		while ( sch <= s ){
			if ( up > sch )
				last = idx + y - 1;
			else
				last = idx + x - 1;
			//printf("%d -> %d - %d\n",sch,idx,last);
			if ( sch == s ){
				res = a[ idx ].first;
				pos = a[ idx ].second;
				for ( int i=idx + 1; i <= last ; ++i ){
					if ( a[i].second < pos )
						res = a[i].first , pos = a[ i ].second;
				}
			}
			idx = last + 1;
			sch++;
		}
		printf("%d\n",res);
	}

	return 0;
}

