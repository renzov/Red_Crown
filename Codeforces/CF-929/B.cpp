#include<cstdio>
using namespace std;

void process(){
	int N;
	int res = 0, a;
	int cnt[3] = {0, 0, 0};

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		cnt[a % 3]++;
		res += a;
		res %= 3;
	}
	if ( res == 0 ) puts("0");
	else if ( res == 2 ) puts("1");
	else puts( ( cnt[1] )? "1":"2" );
}

int main(){
	int t;
	scanf("%d", &t);
	while ( t-- )
		process();
	return 0;
}
