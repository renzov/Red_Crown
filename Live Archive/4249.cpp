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

double A[] = {9.23076, 1.84523, 56.0211, 4.99087, 0.188807, 15.9803, 0.11193};
double B[] = {26.7, 75, 1.5, 42.5, 210, 3.8, 254};
double C[] = {1.835, 1.348, 1.05, 1.81, 1.41, 1.04, 1.88};
bool T[] = {false, true, true, false, true, true, false};

int main(){
	int runs;
	scanf("%d", &runs);
	
	while ( runs-- ){
		double P;
		long long res = 0;
		for ( int i=0; i < 7; ++i ){
			scanf("%lf", &P);
			if ( T[i] ){
				res += (long long) floor ( A[i] * pow ( P - B[i], C[i] ) );
			}
			else {
				res += (long long) floor ( A[i] * pow ( B[i] - P, C[i] ) );			
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}

