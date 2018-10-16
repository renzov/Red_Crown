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
#include <climits>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int main(){
	int N, L;
	int runs;
	int x, y;
	int resMax;
	int resMin;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &L, &N);
		resMax = -INT_MAX;
		resMin = -INT_MAX;
		while ( N-- ){
		 	scanf("%d", &x);
			y = L - x;
			if ( x < y ) swap( x, y ); // x >= y
			resMax = max( x , resMax );
			resMin = max( y , resMin );
		}
		printf("%d %d\n", resMin, resMax);
	}
	return 0;
}

