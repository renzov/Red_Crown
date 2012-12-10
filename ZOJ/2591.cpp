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
#include <bitset>
#include <climits>

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
const int MAXY = 2009 - 1870;

int n,m;

int dp[MAXY][ 5 ][ 6 ];
int pred[MAXY][5][6];

vector<int> I[MAXY][5];
vector<int> M[5][5];

struct film {
	char name[128];
	int year;
	int type;
};

film F[ 2005 ];

void init(){
	for ( int i=0; i<MAXY; ++i )
		for ( int j=0; j < 5; ++j )
			I[ i ][ j ].clear();
	memset( dp , 0 , sizeof(dp) );
}

void read_name( char *s ){
	while ( getchar() != '\"' );
	s[ 0 ] = '\"';
	int p = 1;
	while ( (s[p++] = getchar()) != '\"' );
	s[p] = '\0';
}	

int main(){
	int runs;
	
	for ( int i=1; i < (1<<5); ++i ){
		for ( int j=0; j < 5; ++j ){
			for ( int k=0; k < 5; ++k ){
				if ( k != j && ( i & (1<<j) ) && ( i & (1<<k) ) )
					M[j][k].push_back( i );
			}
		}
	}	

	for (int i=0; i < 5; ++i )
		M[i][i].push_back( 1 << i );

	scanf("%d",&runs);
	while ( runs-- ){
		init();
		scanf("%d",&n);
		for ( int i=0; i < n; ++i ){
			read_name(F[i].name);	
			scanf("%d %d",&F[i].year,&F[i].type);
			F[ i ].type--;
			F[ i ].year -= 1869;
			I[ F[i].year ][ F[i].type ].push_back(i);
		}
		
		int by,bc,bl;
		int prev;
		int mask,sum,ch;
		int maxi = -1;

		for ( int y=1; y < MAXY; ++y ){
			for ( int i = 0; i < 5 ; ++i ){
				for ( int j=0; j < 5; ++j ){
				
					for (int idx = 0; idx < M[j][i].size(); ++idx){
						mask = M[j][i][idx];
						sum = 0; ch = -1;
						for ( int k=0; k < 5; ++k ){
							if ( (mask >> k) & 1 ){ sum += I[y][k].size(); ch++; }
						}

						for ( int l=0; (l + ch) <= 5; ++l ){
							prev = dp[ y - 1 ][ j ][ l ];
							if (dp[ y ][ i ][ l + ch ] < (prev + sum) ){
								dp[ y ][ i ][ l +  ch ] = prev + sum;
								pred[ y ][ i ][ l + ch ] = mask ^ ( j << 5 );
								if ( dp[ y ][ i ][ l +  ch ] > maxi ){ by = y, bc = i, bl = l + ch; maxi = dp[ y ][ i ][ l +  ch ]; }
							}
						}
					}
				
				}
			}
		}
		
		vector<int> res;
		int pc;
		
		while ( dp[by][bc][bl] ){
			mask = 31 & pred[ by ][ bc ][ bl ];
			pc =  pred[ by ][ bc ][ bl ] >> 5;
			
			res.insert( res.end() , I[ by ][ bc ].begin() ,  I[ by ][ bc ].end() );
			for ( int i=4 ; i >= 0  ; --i ){
				if ( i != bc && i != pc && ( (mask >> i) & 1 ) ){
					res.insert( res.end() , I[ by ][ i ].begin() ,  I[ by ][ i ].end() );
					bl--;
				}
			}
			if ( bc != pc ){
				res.insert( res.end() , I[ by ][ pc ].begin() ,  I[ by ][ pc ].end() );
				bl--;
			}
			bc = pc;
			by--;
		}
		printf("%d\n",(int)res.size());
		while ( !res.empty() ){
			puts(F[ res.back() ].name);
			res.pop_back();
		}
		if ( runs ) puts("");
	}
	return 0;
}
