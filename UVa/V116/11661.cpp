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

void flush(){ while (getchar() != '\n'); }

int main(){
	int L;
	int R,D;
	int M;
	char c;

	while (1){
		scanf("%d",&L);
		if (!L) break;
		flush();
		R = D = M = INT_MAX;
		for (int i=0; i < L; ++i){
			c = getchar();
			if (c == '.' || M == 0) continue;
			if (c == 'D'){ 
				D = i;
				if (R < INT_MAX && M > (D - R)) M = D - R;
			}
			else if (c == 'R'){ 
				R = i;
				if (D < INT_MAX && M > (R - D)) M = R - D;				
			}
			else {
				M = 0;
				R = D = i;
			}
		}
		printf("%d\n",M);
	}
	return 0;
}

