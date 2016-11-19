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

string tour;
bool M[300][300];

int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

bool get_bounds( int col, int &l, int &r ){
	l = 1000;
	r = -1;
	for ( int i=0; i < 300; ++i )
		if ( M[i][col] ){
			l = min( l, i );
			r = max( r, i );
		}
	return ( l <= r );
}

int main(){
	int runs;
	cin >> runs;
	cout << runs << endl;
	while ( runs-- ){
		cin >> tour;
		for ( int i=0; i < 300; ++i ) for ( int j=0; j < 300; ++j ) M[i][j] = false;
		int x = 150, y = 0;
		int dir = 0;
		M[x][y] = true;
		for ( int i=0; i < tour.size(); ++i ){
			switch ( tour[i] ){
				case 'R': dir = (dir + 1) % 4;
						  break;
				case 'L': dir = (dir + 3) % 4;
						  break;
				case 'B': dir = (dir + 2) % 4;
						  break; 
			}
			x = x + dx[dir];
			y = y + dy[dir];
			M[x][y] = true;
		}
		// Get the grid bound
		int ry, ly = 0;
		int lx = 1000, rx = -1;
		int t1, t2;
		for ( ry=1; get_bounds( ry, t1, t2 ); ++ry  ){
			lx = min( lx, t1 );
			rx = max( rx, t2 );
		}
		lx--, rx++;
		cout << rx - lx + 1 << ' ' << ry - ly + 1 << endl;
		for ( int i=lx; i <= rx; ++i ){
			for ( int j=ly; j <= ry; ++j ){
				cout << (M[i][j]? '.':'#');
			}
			cout << endl;
		}
	}
	return 0;
}

