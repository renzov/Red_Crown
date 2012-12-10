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

long long F[100];
string B[25];

void init(){
	B[0] = "0";
	B[1] = "1";
	F[0] = 1;
	F[1] = 1;
	int i=2;
	while ( (F[i] = F[i-1] + F[i-2]) < (1LL << 31) ){
		i++;
	}
	for ( int i=2; i <= 20; ++i )
		B[i] = B[i-2] + B[i-1];
}

int main(){
	init();
	cout << B[20] << endl;
	return 0;
}

