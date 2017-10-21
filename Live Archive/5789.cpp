#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
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
list<int>::iterator pos[MAXN];
list<int> soldiers;

int main(){
	int S, B;
	int L, R;
	list<int>::iterator it, elim;

	while ( scanf("%d %d", &S, &B) && S ){
		soldiers.clear(); // clear memory
		for ( int i=1; i <= S; ++i ){
			pos[i] = soldiers.insert( soldiers.end() , i );
		}
		for ( int i=0; i < B; ++i ){
			scanf("%d %d", &L, &R);
			it = pos[L];
			while ( *it <= R && it != soldiers.end() ){
				elim = it;
				it = soldiers.erase(elim);
			}
			elim = it;
			if ( it == soldiers.begin() ){
				printf("* ");
			}
			else {
				elim--;
				printf("%d ", *elim);
			}
			if ( it == soldiers.end() ){
				printf("*\n");
			}
			else {
				printf("%d\n", *it);
			}
		}
		puts("-");
	}
	return 0;
}

