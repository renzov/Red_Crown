#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 128;
char S[MAXN];

int main(){
	int N;
	char last;
	scanf("%d %s", &N, S);
	last = 'a';
	int res = 0;
	int cnt = 0;
	for ( int i=0; i < N; ++i ){
		if ( S[i] == 'x' ){
			cnt++;
		}
		else {
			if ( cnt >= 3 ) res += ( cnt - 2 );
			cnt = 0;
		}
		last = S[i];
	}
	if ( cnt >= 3 ) res += (cnt - 2);
	printf("%d\n", res);
	return 0;
}
