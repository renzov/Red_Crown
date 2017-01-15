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
	int x, h;
	bool out;
	event(){}
	event( int X, int H, bool t ){
		x = X, h = H, out = t;
	}
	bool operator<( const event &that ) const {
		if ( x != that.x ) return x < that.x;
		return out < that.out;
	}
};

int main(){
	vector<event> E;
	bool first = true;
	int l, r, h, x;
	while ( scanf("%d %d %d", &l, &h, &r) != EOF ){
		E.push_back( event(l, h, false) );
		E.push_back( event(r, h, true) );
	}
	sort( E.begin(), E.end() );
	multiset<int> sweep;
	sweep.insert(0);
	multiset<int>::iterator it;
	int lastX = 0;
	int H = -1;
	for ( int i=0; i < (int)E.size(); ){
		x = E[i].x;
		if ( x != lastX ){
			do {
				if ( E[i].out ){
					it = sweep.find( E[i].h );
					sweep.erase(it);
				}
				else {
					sweep.insert( E[i].h );
				}
				i++;
			}
			while ( i < (int)E.size() && E[i].x == x );
		}
		lastX = x;
		h = *sweep.rbegin();
		if ( H != h ){
			H = h;
			if ( first ) first = false;
			else putchar(' ');
			printf("%d %d", x, h);
		}
	}
	puts("");
	return 0;
}

