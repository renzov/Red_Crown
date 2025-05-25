#include<cstdio>
using namespace std;

const int MAXN = 100005;
char S[MAXN];

int main(){
	int N;

	scanf("%d %s", &N, S);
	
	int res = 0;
	char x, y;
	for ( int i = 1; i < N; ++i ){
		x = S[i - 1], y = S[i];
		if ( x == ':' && y == '(' ) res--;
		else if ( x == ':' && y == ')' ) res++;
		else if ( y == ':' && x == '(' ) res++;
		else if ( y == ':' && x == ')' ) res--;
	}
	if ( !res ) puts("BORED");
	else puts(res > 0? "HAPPY":"SAD");
	return 0;
}
