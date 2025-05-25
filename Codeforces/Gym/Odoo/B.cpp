#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 1024;

char S[MAXN];
char P[5] = "ODOO";

void process(){
	scanf("%s", S);
	
	int N = strlen(S);
	int cost;
	
	int res = 4 * N;

	for ( int i=0; i + 4 <= N; ++i ){
		cost = 0;
		for ( int j = 0; j < 4; ++j )
			if ( S[i + j] != P[j] )
				cost++;
		res = min( res, cost + N - 4 );
	}
	printf("%d\n", res );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
