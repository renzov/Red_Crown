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
typedef vector<int64> poly;

const int MAXN = 104;

char s[MAXN];
int cur;
poly X;

poly mult ( poly A, poly B ){
	poly C( A.size() + B.size() - 1, 0 );
	for ( int i=0; i < A.size(); ++i )
		for ( int j=0; j < B.size(); ++j )
			C[i+j] += A[i]*B[j];
	return C;
}

poly add( poly A, poly B ){
	poly C( max( A.size(), B.size() ) , 0 );
	for ( int i=0; i < A.size(); ++i ) C[i] += A[i];
	for ( int i=0; i < B.size(); ++i ) C[i] += B[i];
	return C;
}

poly subst( poly A, poly B ){
	poly C( max( A.size(), B.size() ) , 0 );
	for ( int i=0; i < A.size(); ++i ) C[i] += A[i];
	for ( int i=0; i < B.size(); ++i ) C[i] -= B[i];
	return C;
}

poly parse(){
	if ( s[cur] == 'x' ){ 
		cur++;
		return X;
	}
	char op = s[cur];
	cur++;
	poly left = parse();
	poly right = parse();

	if ( op == 'M' ) return mult( left , right );
	else return subst( add(left, right) , mult(left, right) );
}

int main(){
	int runs;
	scanf("%d", &runs);

	X.push_back(0); X.push_back(1);

	while ( runs-- ){
		scanf("%s", s);
		cur = 0;
		poly P = parse();
		long double res = 1.0;
		for ( int i=0; i < P.size(); ++i )
			res -= (long double) P[i] / (long double) (i+1);
		printf("%.6Lf\n", res);
	}
	return 0;
}

/*
	Another way to get the result

		long double res = 0.0;
		long double temp;
		for ( int i = 1; i < P.size() ; ++i  ){
			temp = (long double)P[i] / (long double) (i+1);
			temp *= i;
			res += temp;
		}

*/

