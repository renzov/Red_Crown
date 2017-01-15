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
	int N;
	string s;
	while ( cin >> N ){
		map<string, int> H1, H2;
		for ( int i=0; i < N; ++i ){
			cin >> s;
			H1[s]++;
		}
		for ( int i=0; i < N; ++i ){
			cin >> s;
			H2[s]++;
		}
		map<string,int>::iterator it;
		int res = 0;
		for ( it=H1.begin(); it != H1.end(); it++ ){
			res += min( it->second, H2[it->first] );
		}
		cout << res << endl;
	}
	return 0;
}

