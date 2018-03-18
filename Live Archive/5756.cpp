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
typedef pair< pii, int > piii;
const int MAXN = 100005;
int C[ MAXN ];
set<piii> S;
set<pii> cost;

void insert( int a, int b, int c, int idx ){
	//printf("insert %d: %d %d %d\n", idx, a, b, c);
	set<piii>::iterator it;
	// search for the first element that have first coord greater than a
	it = S.upper_bound( piii( pii( a, INT_MAX ), idx ) );
	if ( it != S.end() && it->first.second >= b ){ 
		//printf("outdated by first rule\n");
		return; //new element is outdated
	}
	if ( it == S.begin() ){ // we can insert element
		//printf("insert the element - 1r\n");
		S.insert( piii( pii(a,b), idx ) );
		cost.insert( pii(c, idx) );	
	}
	else { // we have to remove the elements we dominate
		set<piii>::iterator prev = it;
		prev--;
		while ( a == prev->first.first && prev->first.second < b || a > prev->first.first && prev->first.second <= b ){
			//printf("prev (%d, %d)\n", prev->first.first, prev->first.second);		
			it = prev;
			prev--;
			cost.erase( pii( C[it->second] , it->second ) );
			S.erase(it);
		}
		if ( a == prev->first.first && b < prev->first.second  ) return; // newly element is outdated
		if ( a == prev->first.first && b == prev->first.second ){ // special case, we can only insert if cost is lower
			if ( C[ prev->second ] > c ){ // erase the element that is equal but higher price
				cost.erase( pii( C[prev->second], prev->second ) );
				S.erase( prev );
				S.insert( piii( pii(a,b), idx ) );
				cost.insert( pii(c, idx) );	
			}
		}
		else { // we are sure that a > prev->first.first and b > prev->first.second
			S.insert( piii( pii(a,b), idx ) );
			cost.insert( pii(c, idx) );			
		}
	}
}

int toint( char *c ){
	int res = 0;
	int cnt = 0;
	bool point = false;
	for ( int i=0; c[i]; ++i ){
		if (point) cnt++;
		if ( isdigit(c[i]) ) res *= 10, res += (c[i] - '0');
		else point = true;
	}
	while ( cnt < 6 ) res *= 10, cnt++;
	return res;
}

int main(){
	char op;
	int runs;
	int a, b, c;
	char x[30];
	int N;
	bool first;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		// insert dummy element in S and cost
		S.insert( piii( pii(-1, INT_MAX) , -1 ) ); cost.insert( pii( INT_MAX , -1 ) );
		first = true;
		for ( int i=1; i <= N; ++i ){
			scanf(" %c", &op);
			if ( op == 'P' ){
				scanf("%d %s %d", &a, &x, &c);
				b = toint(x);
				C[i] = c;
				insert( a, b, c, i );
			}
			else {
				if ( !first ) putchar(' ');
				else first = false;
				printf("%d", cost.begin()->second);
			}
		}
		puts("");
		S.clear();
		cost.clear();
	}
	return 0;
}

