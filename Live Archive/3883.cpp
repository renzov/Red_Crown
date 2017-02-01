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
#include <bitset>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXL = 1299709;
const int MAXP = 100015;

bool np[MAXL + 5];
int P[MAXP];
int N;

void sieve(){
	N = 0;
	P[N++] = 2;
	for ( int i=3; i < 1141; i += 2 ){
		if (!np[i]){
			P[N++] = i;
			for ( int j=i*i; j <= MAXL; j += (i<<1) )
				np[j] = true;	
		}
	}
	for ( int i=1141; i <= MAXL; i += 2 ){
		if ( !np[i] )
			P[N++] = i;
	}
}

int main(){
	sieve();
	int K;
	int idx;
	while ( scanf("%d", &K) && K ){
		if ( K==1 ) puts("1");
		else if ( K==2 ) puts("0");
		else if ( (K&1) && !np[K]) printf("0\n");
		else {
			idx = lower_bound( P , P + N , K ) - P;
			printf("%d\n", P[idx] - P[idx - 1] );
		}
	}
	return 0;
}

