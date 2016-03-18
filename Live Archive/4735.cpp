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
const int MAXN = 1000000;

int lastp[MAXN + 10] = {0};
void sieve(){
	for ( int i=4; i < MAXN; i+= 2 ) lastp[i] = 2;
	for ( int i=3; i < 1000; i += 2 ){
		if (!lastp[i]){
			for ( int j=i*i; j < MAXN; j += (i<<1) )
				lastp[j] = i;
		}
	}
}

int main(){

	sieve();
	int A, B;
	int cases = 0;
	int res;
	while ( scanf("%d %d", &A, &B) && A && B ){
		cases++;
		map<int,int> pot;
		set<int> p;
		// factor A
		while ( lastp[A] ){
			p.insert(lastp[A]);
			pot[ lastp[A] ]++;
			A /= lastp[A];
		}
		if ( A > 1 ){
			p.insert(A);
			pot[ A ]++;
		}
		// factor B
		while ( lastp[B] ){
			p.insert( lastp[B] );
			pot[ lastp[B] ]--;
			B /= lastp[B];
		}
		if ( B > 1 ){
			p.insert(B);
			pot[B]--;
		}
		res = 0;
		for ( map<int,int>::iterator it = pot.begin(); it != pot.end(); ++it ){
			res += abs( it->second );
		}
		printf("%d. %d:%d\n", cases, (int)p.size(), res );
	}
	return 0;
}

