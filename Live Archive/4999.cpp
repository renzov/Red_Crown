#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <vector>
#include <cmath>
#include <unordered_map>


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

const int INF = 10000000; 
const int SHIFT = 3;
const int ELEM = ( 1 << SHIFT ) - 1;
const int MASKBITS = ( 1 << (SHIFT*8) ) - 1; 
int cost[10][10];
char board[10][10];
char sol[10][10];
unordered_map<int,int> dp[10][10];

int solve( int x, int y, int mask ){
	if ( x == 8 ){	//We have processed all rows
		int c;
		while ( mask > 0 ){
			c = mask & ELEM;
			if ( c > 1 ) return INF;
			mask >>= SHIFT;
		}
		return 0;
	}
	if ( y == 8 ) return solve(x+1, 0, mask); // All the column
	if ( dp[x][y].find( mask ) != dp[x][y].end() ) return dp[x][y][mask];
	int res = INF;
	// get the state
	int tmpMask = mask;
	int largest = 0;
	int comp[10];
	for ( int i=7; i >= 0; i-- ){
		comp[i] = tmpMask & ELEM;
		tmpMask >>= SHIFT;
		if ( comp[i] > largest ) largest = comp[i];
	}
	// Cuting early
	if ( largest < 2 ){
		res = 0;
	}
	int above = comp[0];
	int left = (y==0)? 0:comp[7];
	int nextMask;
	if ( above == 0 && left == 0 ){
		nextMask = ( (mask << SHIFT) | (largest+1) ) & MASKBITS;
		res = min(res, solve(x, y+1, nextMask) + cost[x][y]);
	}
	else if ( (above==0) ^ (left==0) ){
		nextMask = ( (mask<<SHIFT) | (max(left, above)) ) & MASKBITS;
		res = min(res, solve(x, y+1, nextMask) + cost[x][y] + 1);
	}
	else if ( above != left ){ //There is always an acyclic optimal soltion
		int a = min(left, above);
		int b = max(left, above);
		int c;
		nextMask = 0;
		for (int i=1; i < 8; ++i){
			if ( comp[i] == b ) c = a;
			else if ( comp[i] > b && a != b ) c = comp[i] - 1;
			else c = comp[i];
			nextMask = ( (nextMask<<SHIFT) | (c) ) & MASKBITS;
		}
		nextMask = ( (nextMask<<SHIFT) | (a) ) & MASKBITS;
		res = min(res, solve(x, y+1, nextMask) + cost[x][y] + 2);
	}
	bool canCut = true;
	if ( comp[0] > 0 ){
		canCut = false;
		for ( int i=1; i < 8; ++i ){
			if ( comp[i] == comp[0] ){ 
				canCut = true;
				break;
			}
		}
	}
	if ( canCut ){
		nextMask = (mask<<SHIFT) & MASKBITS;
		res = min(res, solve(x, y+1, nextMask));
	}
	dp[x][y][mask] = res;
	return res;
}

int main(){
	int L, W;
	int runs;
	int cnt;
	scanf("%d", &runs);
	for ( int cases = 1; cases <= runs; ++cases ){
		cnt = 0;
		scanf("%d %d", &L, &W);
		for ( int i=0; i < 8; ++i ){
			scanf("%s", board[i]);
			for ( int j=0; j < 8; ++j ){
				dp[i][j].clear();
				switch ( board[i][j] ){
					case '.' : cost[i][j] = L; break;
					case 'W' : cost[i][j] = W; break; 
					default :  cost[i][j] = -INF; 
							   cnt++;
							   break;  // Generator or house
				}
			}
		}
		printf("Case %d: %d\n", cases, solve(0,0,0) + cnt*INF );
	}
	return 0;
}
