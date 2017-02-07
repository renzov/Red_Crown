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

const int MAX = 31622;
bool np[MAX] = {0};
int p[MAX], sz;
int res[MAX];
int div[MAX];
void sieve(){
	sz = 0;
	p[sz++] = 2;
	for ( int i=4; i <= MAX; i+=2 ) np[i] = true, div[i] = 2;
	for ( int i=3; i <= MAX; i+=2 ){
		if ( !np[i] ){
			res[i] = 1;
			p[sz++] = i;
			for ( int j=i*i; j <= MAX; j += (i<<1) ){
				np[j] = true;
				div[j] = i;
			}
		}
		else {
			res[i] = div[i]*res[ i / div[i] ] + (i / div[i]);
		}
	}
}

int main(){
	sieve();
	int runs;
	int N;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
	}
	return 0;
}

