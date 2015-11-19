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

const int MAXN = 16390;

int P[MAXN][8];
int N;
int size[MAXN];
int R[MAXN];
int sp[MAXN];

int get_num( char *s ){
	int res = 0;
	int p = 2;
	int i;
	for ( i=0;  s[i] ; ++i ){
		if ( isdigit(s[i]) ){
			res *= 10;
			res += (s[i]-'0');
		}
		else {
			for (i++; s[i] ; ++i ){
				res *= 10;
				res += (s[i] - '0');
				p--;
			}
			break;
		}
	}
	while (p--) res *= 10;
	return res;
}

void all_comb( int idx, int a, int b, int c ){
	P[idx][0] = 0;
	P[idx][1] = a;
	P[idx][2] = b;
	P[idx][3] = c;
	P[idx][4] = a+b;
	P[idx][5] = a+c;
	P[idx][6] = b+c;
	P[idx][7] = a+b+c;
	sort( P[idx] , P[idx] + 8 );
	size[idx] = unique( P[idx] , P[idx] + 8 ) - P[idx];
}

bool test( int val ){
	int idx;
	int tmp;
	for ( int i=N-2; i >= 0 ; i-- ){
		idx = R[ i ];
		while ( sp[idx] < size[idx] && P[ idx ][ sp[idx] ] < val ){
			sp[idx]++;
		}
		if ( sp[idx] >= size[idx]  ) return false;
		tmp = P[ idx ][ sp[idx] ];
		if ( i > 0 ){
			if ( R[ i-1 ] > idx ) val = tmp + 1;
			else val = tmp;
		}
	}
	return true;
}

int main(){
	char n1[16];
	char n2[16];
	char n3[16];
	int a,b,c;
	int cases = 0;

	while ( scanf("%d",&N) && N ){
		cases++;
		for ( int i=0; i<N; ++i ){
			scanf("%s %s %s",n1,n2,n3);		
			a = get_num(n1);
			b = get_num(n2);
			c = get_num(n3);
			all_comb(i , a, b, c);
			sp[ i ] = 0;
		}
		for ( int i=0; i<N; ++i ){
			scanf("%d", R+i);
			R[i]--;
		}

		if (N == 1){
			printf("Case %d: ",cases);			
			printf("%d.%02d\n", P[0][size[0] - 1] / 100 , P[0][size[0] - 1] % 100 );
			continue;
		}

		int res = -1;
		int val;
		int idx = R[N-1];
		for ( int i=0; i < size[ idx ]; ++i ){
			if ( idx > R[N-2] ){
				val = P[idx][i];
			}
			else {
				val = P[idx][i] + 1;
			}
			if (!test( val ))
				break;
			else 
				res = P[idx][i];
		}
		printf("Case %d: ",cases);
		if ( res == -1 ) puts("No solution");
		else printf("%d.%02d\n", res / 100, res % 100 );
	}
	return 0;
}

