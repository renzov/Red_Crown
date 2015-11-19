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

void fast_mult( int A[][2], int p, int R[][2] ){
	if (p > 1){
		int T[2][2];		
		if (p&1){
			fast_mult( A , p - 1 , T );
			R[0][0] = (A[0][0] * T[0][0] + A[0][1] * T[1][0])%10;
			R[0][1] = (A[0][0] * T[0][1] + A[0][1] * T[1][1])%10;
			R[1][0] = (A[1][0] * T[0][0] + A[1][1] * T[1][0])%10;
			R[1][1] = (A[1][0] * T[0][1] + A[1][1] * T[1][1])%10;
		}
		else {
			fast_mult( A , p >> 1, T );
			R[0][0] = (T[0][0] * T[0][0] + T[0][1] * T[1][0])%10;
			R[0][1] = (T[0][0] * T[0][1] + T[0][1] * T[1][1])%10;
			R[1][0] = (T[1][0] * T[0][0] + T[1][1] * T[1][0])%10;
			R[1][1] = (T[1][0] * T[0][1] + T[1][1] * T[1][1])%10;
		}
	}
	else {
		R[0][0] = A[0][0]; R[0][1] = A[0][1];
		R[1][0] = A[1][0]; R[1][1] = A[1][1];
	}
}

int main(){
	int N;
	int A[2][2] = { {1, 1}, {1, 0} };
	int R[2][2];

	scanf("%d",&N);
	
	if (N == 1) puts("1");
	else if (N == 2) puts("2");
	else {
		fast_mult(A, N-2, R);
		printf("%d\n", (2*R[0][0] + R[0][1])%10 );
	}
	return 0;
}

