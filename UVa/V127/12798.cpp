#include<cstdio>
using namespace std;

void process(const int &N, const int &M){
	int ans = 0;
	int X;
	bool ok;

	for ( int i = 0; i < N; ++i ){
		ok = true;
		for ( int j = 0; j < M; ++j ){
			scanf("%d", &X);
			ok &= ( X > 0 ); 
		}
		if ( ok ) ans++;
	}
	printf("%d\n", ans);
}

int main(){
	int N, M;

	while (	scanf("%d %d", &N, &M) == 2 )
		process(N, M);
	return 0;
}
