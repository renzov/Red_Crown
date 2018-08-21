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
#include <cassert>

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
const int MAXN = 1000010;
int N, K;
int A[MAXN];
deque<int> val;
deque<int> pos;

void insert( const int &v, const int &p ){
	while ( !val.empty() && val.back() >= v ) 
		val.pop_back(), pos.pop_back();
	val.push_back(v), pos.push_back(p);
}

void solve(const int &mul){
	for ( int i=1; i < K; ++i ) insert( A[i]*mul , i );
	for ( int i = K; i <= N; ++i ){
		insert( A[i]*mul, i );
		while ( i - pos.front() >= K ) pos.pop_front(), val.pop_front();
		if ( i > K ) putchar(' ');
		printf("%d", val.front()*mul);
	}
	puts("");
}

int main(){	
	while ( scanf("%d %d", &N, &K) == 2 ) {
		for ( int i=1; i <= N; ++i ) scanf("%d", A+i);
		solve(1);
		solve(-1);
		val.clear(), pos.clear();
	}
	return 0;
}

