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
	int N,T;
	int x,sum;
	int i,res;

	while (scanf("%d %d",&N,&T) != EOF){
		sum = 0;
		for (i=0; i < N && sum <= T; ++i){
			scanf("%d",&x);
			sum += x;
		}
		if (sum > T) res = i-1;
		else res = i;
		printf("%d\n",res);
		for ( ; i<N ; ++i ) scanf("%d",&x);
	}
	return 0;
}

