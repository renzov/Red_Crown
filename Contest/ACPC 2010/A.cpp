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
#include <list>
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

void shift( list<int> &L ){
	int tmp = L.front();
	L.pop_front();
	L.push_back(tmp);
}

void lswap(list<int> &L){
	int tmp1 = L.front(); L.pop_front();
	int tmp2 = L.front(); L.pop_front();
	L.push_front( tmp1 );
	L.push_front( tmp2 );
}

int main(){

	int n;
	int elem;
	int a[500];
	list<int>::iterator it;
	while ( scanf("%d",&n) & (n > 0) ){
		list<int> L;
		for (int i=1; i <= n; ++i){ 
			scanf("%d",a+i); L.push_back(i);
		}
		if ( n == 1 ) puts("");
		else {
			while ( *L.begin() != a[1] ){
				shift(L);
				putchar('2');
			}
			//puts("Llego");
			shift(L); putchar('2');
			for ( int i=2; i <= n; ++i ){
				while ( L.front() != a[i] ){
					shift(L);
					putchar('2');
				}
				it = L.begin(); it++;
				while ( *it != a[1] ){
					lswap(L); putchar('1');
					shift(L); putchar('2');
					it = L.begin(); it++;
				}
				for ( int j=1; j < i; ++j ){
					lswap(L); putchar('1');
					shift(L); putchar('2');
				}
				shift(L); putchar('2');
			}
			puts("");
			
		}
	}

	return 0;
}

