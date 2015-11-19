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

int N;
int res[20];

bool test( multiset<int> S ){
	multiset<int>::iterator it = S.begin();
	multiset<int>::iterator elim;
	int a0 = *it; it++;
	int a1 = *it; it++;
	int i,j;
	bool ok;
	
	for ( ; it != S.end() ; it++ ){
		if ( (a0 + a1 - *it) & 1 ) continue;
		res[0] = (a0 + a1 - *it) / 2;
		multiset<int> C = S;
		j = 1;
		ok = true;
		while ( C.size() && ok ){
			
			res[j] = *C.begin() - res[0];

			if ( res[j] < res[j-1] ) break;
			
			for ( int k=0; k < j; ++k ){
				elim = C.find(res[k] + res[j]);
				if ( elim == C.end() ){
					ok = false;
					break;	
				}
				else {
					C.erase(elim);
				}
			}

			if (ok) j++;
			
		}

		if ( j < N ) continue;

		return true;
	}

	return false;
}

int main(){
	int x;
	int M;
	while (scanf("%d",&N) == 1){
		multiset<int> S;
		M = N * (N-1) / 2;
		for ( int i=0; i < M; ++i ){
			scanf("%d", &x);
			S.insert(x);
		}
		if ( test(S) ){
			printf("%d", res[0]);
			for (int i=1; i < N; ++i)
				printf(" %d",res[i]);
				
			putchar('\n');				
		}
		else {
			puts("Impossible");
		}	
	}
	return 0;
}

