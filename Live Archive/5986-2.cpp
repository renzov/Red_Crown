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

int a[100];

int main(){
	int runs;
	int N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ) scanf("%d", a+i);
		sort(a, a+N);
		int minSum;
		int sum = 0;
		int delta = 0;
		for ( int i=1; i <= N; ++i ){
			minSum = i*(i-1)/2;
			sum += a[i-1];			
			if ( sum < minSum ){ 
				delta += (minSum - sum);
				sum = minSum;
			}
		}
		printf("%d\n", delta + sum - N*(N-1)/2);
	}
	return 0;
}

