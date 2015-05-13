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

const int MAXN = 101;

string s[MAXN];
map< vector<int> , int > dp;
vector<int> state;
int N;
int M;

void solve( int pos ){
	if ( pos == (N-1) ){
		for ( int i=0; i < s[pos].size(); ++i ){
			state[pos] = i + 1;
			int &ref = dp[state];
			ref = 0;
			for ( int j=0; j < N ; ++j ){
				state[j]--;
				ref = max( ref , dp[state] );
				state[j]++;
			}
			bool eq = true;
			for ( int j=1; j < N && eq; ++j ){
				eq = eq && ( s[0][ state[0] - 1 ] == s[j][ state[j] - 1 ] );
			}
			if ( eq ){
				for ( int j=0; j < N; ++j )
					state[j]--;
				ref = max( ref , dp[state] + 1 );
				for ( int j=0; j < N; ++j )
					state[j]++;
			}
			M = max( M , ref );
		}
	}
	else {
		for ( int i=0; i < s[pos].size(); ++i ){
			state[pos] = i + 1;
			solve( pos + 1 );
		}
	}
}

int main(){
	while ( cin >> N && N ){
		state = vector<int> (N,0);
		for ( int i=0; i < N; ++i )
			cin >> s[i];
		dp.clear();
		M = 0;
		dp[state] = 0;
		solve(0);

		cout << M << endl;
	}
	return 0;
}

