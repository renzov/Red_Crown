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

const int MAXN = 100005; 

bool inS[MAXN] = {0};
deque<int> S;

int main(){
	int N;
	int u;

	scanf("%d", &N);
	
	while ( N-- ){
		scanf("%d", &u);
		if ( inS[u] ){
			while ( S.back() != u ){
				inS[ S.back() ] = false;
				S.pop_back();
			}
			S.pop_back();
		}
		S.push_back(u);
		inS[u] = true;
	}
	while ( !S.empty() ){
		u = S.front();
		S.pop_front();
		printf("%d", u);
		if ( !S.empty() ) putchar(' ');
	}
	puts("");
	return 0;
}

