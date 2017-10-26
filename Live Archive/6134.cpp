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

int sum[5005]={0};

void preprocess(){
	int cnt[16];
	int n;

	for ( int i=1; i <= 5000; ++i ){
		n = i;
		fill( cnt, cnt + 10, 0 );
		while ( n ){
			cnt[ n%10 ]++;
			n /= 10;
		}
		bool ok = true;
		for ( int j=0; j < 10 && ok; ++j )
			ok &= ( cnt[j] <= 1 );
		if ( ok ) sum[i] = 1;
		else sum[i] = 0;
		sum[i] += sum[i-1];
	}
}


int main(){
	preprocess();
	int N, M;
	while ( scanf("%d %d", &N, &M) != EOF ){
		printf("%d\n", sum[M] - sum[N - 1]);
	}
	return 0;
}

