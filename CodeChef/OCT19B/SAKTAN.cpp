#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int X[MAXN];
int Y[MAXN];

void process(){
	int Q, N, M;
	scanf("%d %d %d", &N, &M, &Q);
	int x, y;
	while ( Q-- ){
		scanf("%d %d", &x, &y);
		X[x]++, Y[y]++;
	}
	int even = 0, odd = 0;
	for ( int i=1; i <= M; ++i ){
		if ( Y[i] & 1 ) odd++;
		else even++;
		Y[i] = 0;
	}
	
	long long res = 0;
	for ( int i=1; i <= N; ++i ){
		if ( X[i] & 1 ) res += even;
		else res += odd;
		X[i] = 0;
	}
	printf("%lld\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
	}
	return 0;
}
