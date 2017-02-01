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
#include <climits>

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

const int MAXN = 10;
const int MAXS = 15;
int N;

string join( const string &a, const string &b ){
	for ( int i=min(a.length(), b.length()); i >= 0 ; i-- ){
		if ( a.substr( a.length() - i ) == b.substr(0, i) )
			return a + b.substr(i); 
	}
	return "";
}

int main(){
	int runs;
	string S[MAXN];

	cin >> runs;
	for ( int cases=1; cases <= runs; ++cases ){
		cin >> N;
		for ( int i=0; i < N; ++i ){ 
			cin >> S[i];	
		}
		sort( S , S + N );
		string res = string(100, '?');
		string tmp;
		
		do {
			tmp = "";
			for ( int i=0; i < N; ++i ){
				tmp = join( tmp , S[i] );
			}
			if ( tmp.length() < res.length() ) res = tmp;
		} while (next_permutation( S, S + N ));
		cout << "Case " << cases << ": " << res.length() << endl;
	}
	return 0;
}

