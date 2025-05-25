#include<cstdio>
using namespace std;

void process(){
	int N, K;

	scanf("%d %d", &N, &K);
	int f = N - K + 1;
	int odds = K / 2;
	if ( (K & 1) && (f & 1) )
		odds++;
	puts( odds & 1? "NO":"YES" );
}

int main(){
	int t;

	scanf("%d", &t);
	while ( t-- )
		process();
	return 0;
}
