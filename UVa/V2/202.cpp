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

void process( long long x, long long y ){
	printf("%lld/%lld = ",x,y);
	set< long long > num;
	map< long long , int > pos;
	char s[1000];
	sprintf(s,"%lld",x / y );
	x %= y;
	string sol = "";
	printf("%s.",s);
	while ( 1 ){
		if ( !x  ){
			printf("%s(0)\n",sol.c_str());
			printf("   1 = number of digits in repeating cycle\n");
			break;
		}
		x *= 10;
		if ( num.find(x) == num.end() ){
			num.insert(x);
			pos[ x ] = sol.size();
			sol += (char)((x/y) + '0');
			x %= y;
		}
		else {
			int p = pos[x];
			for ( int i=0; i < 50 && i < sol.size(); ++i ){
				if ( i==p ) putchar('(');
				putchar( sol[i] );
			}
			if ( sol.size() > 50 ){
				puts("...)");
			}
			else {
				puts(")");
			}
			printf("   %d = number of digits in repeating cycle\n",(int)sol.size() - p);
			break;
		}
	}
}

int main(){
	long long a,b;
	while ( scanf("%lld %lld",&a,&b) != EOF ){
		process(a,b);
		puts("");
	}

	return 0;
}

