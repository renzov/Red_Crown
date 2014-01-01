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

const int MAX = 25;

int X[MAX];
int Y[MAX];
int S[MAX];
bool T[MAX];
int P[MAX];

int main(){
	int t;
	int N,M;
	while ( scanf("%d %d",&N,&M) && N ){
	
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d",X+i,Y+i,&t);
			if ( t > 0 ) S[i] = t, T[i] = false;
			else S[i] = -t , T[i] = true;
		}
		
		for ( int i=0; i < N; ++i ) P[i] = i;

		int res = 0;
		bool ok;	
		do {
			ok = true;
			for (int i=0; i < M && ok; ++i){
				if ( T[i] ){
					ok &= (abs(P[ X[i] ] - P[ Y[i] ]) >= S[i]);
				}
				else {
					ok &= (abs(P[ X[i] ] - P[ Y[i] ]) <= S[i]);
				}
			}
			if (ok) res++;
		}
		while ( next_permutation( P , P + N ) );
		printf("%d\n",res);
	}
	
	return 0;
}

