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

const int MAXD = 50;
const int MAXN = 100000;
vector<int> L[MAXD];

int decomp( int n ){
	int res = 0;
	while ( n > 0 ){
		res += (n%10);
		n /= 10;
	}
	return res;
}

void preprocess(){
	L[0].push_back(0);
	for ( int i=1; i <= MAXN; ++i ){
		L[ decomp(i) ].push_back( i );
	}
}

int main(){
	vector<int>::iterator it;
	int N;
	char temp[10];
	int sum;
	preprocess();
	while ( scanf("%s", temp) && temp[0] != 'E' ){
		sscanf(temp, "%d", &N);
		sum = decomp(N);
		it = lower_bound( L[sum-1].begin(), L[sum-1].end(), N );
		it--;
		printf("%d\n", *it);
	}
	return 0;
}

