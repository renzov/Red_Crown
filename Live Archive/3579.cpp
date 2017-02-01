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

const int MAXN = 505;

int main(){

	int N;
	int r[MAXN];
	int a[MAXN];
	bool used[MAXN];
	int cnt;

	while ( scanf("%d",&N) && N ){
		for ( int i=0; i < N; ++i ){
			scanf("%d",a+i);
			used[i] = false;
		}
		for ( int i=0; i < N; ++i ){
			cnt = 0;
			for ( int j=0; j < N; ++j ){
				if ( !used[j] ){ 
					if ( cnt == a[i] ){
						r[j] = i + 1;
						used[j] = true;
						break;
					}
					else {
						cnt++;	
					}
				}
			}
		}
		for ( int i=0; i < N; ++i ){
			if (i) putchar(',');
			printf("%d",r[i]);
		}
		puts("");
	}
	return 0;
}

