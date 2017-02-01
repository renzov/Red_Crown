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
	int a,b,c,d,L,res;
	int mod;
	while ( scanf("%d %d %d %d %d",&a,&b,&c,&d,&L) & (a || b || c || d || L) ){
		res = 0;
		for (int x=0; x <= L; ++x){
			mod = ((a*x*x)%d + (b*x)%d + c%d)%d;
			if ( !mod ) res++;
		}
		printf("%d\n",res);
	}
	return 0;
}

