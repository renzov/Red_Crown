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
	int a[50];
	int runs;
	int n,p,q;
	scanf("%d",&runs);
	for ( int k=1; k <= runs; ++k ){
		scanf("%d %d %d",&n,&p,&q);
		for ( int i=0; i < n; ++i ){
			scanf("%d",a+i);
		}
		sort(a,a+n);
		int sum = 0;
		int res = 0;
		for ( int i=0; i < n && i < p; ++i ){
			if ( (sum + a[i]) <= q ){
				sum += a[i];
				res++;
			}
			else break;
		}
		printf("Case %d: %d\n",k,res);
	}
	return 0;
}

