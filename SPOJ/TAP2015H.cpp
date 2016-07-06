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
	int frec[10] = {0,0,0,0,0,0,0,0,0,0};
	int N, res;
	int temp, M;

	while ( scanf("%d", &N) != EOF ){
		res = 0;
		while ( N ){
			temp = N;
			frec[0] = 0;
			while ( temp ){
				frec[temp % 10]++;
				temp /= 10;
			}
			M = 0;
			for ( int i=1; i < 10; ++i ){
				while ( frec[i] ){
					M *= 10;
					M += i;
					frec[i]--;
				}
			}
			N -= M;
			res++;
		}
		printf("%d\n", res);
	}
	return 0;
}
