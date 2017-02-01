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
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 105;

map<int, vector<int> > X;
map<int, vector<int> > Y;

bool sort_and_test( map<int, vector<int> > &H ){
	map<int, vector<int> >::iterator it;
	for ( it=H.begin(); it != H.end(); ++it ){
		if ( (int)it->second.size() & 1 ) return false;
		sort( it->second.begin(), it->second.end() );
	}
	return true;
}

int calc_area( map<int, vector<int> > &P ){
	int len = 0;
	int lastX = -1;
	int res = 0;
	set<int> active;
	vector<int> V;
	set<int>::iterator act, prev;
	for ( map<int, vector<int> >::iterator it=P.begin(); it != P.end(); it++ ){
		if ( len > 0 ) res += len * ( it->first - lastX );
		// insert or remove points
		V = it->second;
		for ( int i=0; i < (int)V.size(); ++i ){
			if ( active.find(V[i]) != active.end() ) active.erase( V[i] );
			else active.insert( V[i] );
		}
		// recalculate len
		act = active.begin();
		if ( act != active.end() ) prev = act++;
		len = 0;
		for ( ; act != active.end(); ){
			len += ( *act - *prev );
			act++;
			if ( act != active.end() ){ 			
				prev = act++;
			}
		}
		lastX = it->first;
	}
	return res;
}

int calc_per( map<int, vector<int> > &P ){
	int res = 0;
	vector<int> V;	
	for ( map<int, vector<int> >::iterator it=P.begin(); it != P.end(); it++ ){
		V = it->second;
		for ( int i=0; i < (int)V.size(); i += 2 ){
			res += (V[i+1] - V[i]);
		}
	}
	return res;
}

int main(){
	int N;
	int x, y;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", &x, &y);
		if ( X.find( x ) == X.end() ) X[x] = vector<int>();
		if ( Y.find( y ) == Y.end() ) Y[y] = vector<int>();
		X[x].push_back(y), Y[y].push_back(x);
	}
	bool ok = true;
	if ( !sort_and_test( X ) ) ok = false;
	if ( ok && !sort_and_test( Y ) ) ok = false;
	if ( !ok ){ 
		puts("Impossible");
		return 0;
	}
	int area = calc_area( X );
	int perY = calc_per( X );
	int perX = calc_per( Y );
	printf("%d %d\n", area, perX + perY);
	return 0;
}

