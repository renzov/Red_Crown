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

string res[16];

int f( string &s ){
	int si = ( int )s.size() - 2;
	for ( int i=0; i < 16; ++i ){
		if ( si == (int)res[i].size() ){
			return i;
		}
	}
	return -1;
}

int main(){

	res[0] = "";
	res[1] = "{}";
	for ( int i=2; i < 16; ++i ){
		res[i] = res[i-1] + ",{" + res[i-1] + "}"; 
	}
	
	int runs;
	int x;
	string a,b;

	cin >> runs;
	while ( runs-- ){
		cin >> a >> b;
		x = f(a) + f(b);
		cout << "{" << res[x] << "}" << endl;
	}
	return 0;
}

