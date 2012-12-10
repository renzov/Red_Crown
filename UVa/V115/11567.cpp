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

	long long S;
	int res;
	while ( scanf("%lld",&S) != EOF ){
		if ( S <= 1 ) printf("%d\n",(int)S);
		else {
			res = 1;
			while ( S > 1 ){
				if ( S & 1 ){
					if ( (S==3) || ( ((S + 1) >> 1) & 1 ) )
						S--;
					else
						S++;
				}
				else {
					S >>= 1;
				}
				res++;
			}
			printf("%d\n",res);
		}
	
	}

	return 0;
}

