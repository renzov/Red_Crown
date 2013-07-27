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

char X[505];
char Y[505];

int memo[505][2][505][2];
bool calc[505][2][505][2];

int solve( int i , bool openX , int j, bool openY ){
	
	if ( calc[i][openX][j][openY] ) return memo[i][openX][j][openY];
	
	calc[i][openX][j][openY] = true;
	
	int punish;
	int &ret = memo[i][openX][j][openY];

	if ( i == 0 ){
		punish = (openX)? 0:4;
		if ( j == 0 ) ret = 0;
		else ret = -(j + punish);
		return ret;
	}
	if ( j == 0 ){
		punish = (openY)? 0:4;
		if ( i == 0 ) ret = 0;
		else ret = -(i + punish);
		return ret;
	}
	
	ret = solve( i - 1 , false, j - 1, false ) + (X[i-1] == Y[j-1]? 2:-1); 

	punish = (openX)? 1:5;

	ret = max( ret , solve( i , true , j - 1 , false ) - punish );
	
	punish = (openY)? 1:5;

	ret = max( ret , solve( i - 1 , false , j , true ) - punish );
	
	return ret;
}

int main(){

	int runs;
	int n,m;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%s",X);
		scanf("%s",Y);
		n = strlen(X);
		m = strlen(Y);
		memset( calc , false , sizeof(calc) );
		printf("%d\n", solve(n,false,m,false) );
	}
	return 0;
}

