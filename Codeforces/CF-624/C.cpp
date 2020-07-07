#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 200005;
char S[MAXN];
int P[MAXN];
int res[32];

void process(){
	int N, M;
	scanf("%d %d", &N, &M);
	fill( res, res + 27, 0 );
	scanf("%s", S);
	for ( int i=0; i < M; ++i )
		scanf("%d", P + i);
	sort(P, P + M);
	
	int lb = 0;
	int idx;
	for ( int i=1; i < N; ++i ){
		while ( lb < M && P[lb] < i ) lb++;
		idx = S[i - 1] - 'a';
		res[idx] += (M - lb);
	}
	for ( int i=0; i < N; ++i ){
		idx = S[i] - 'a';
		res[idx]++;
	}
	for (int i=0;i < 26; ++i){
		if (i) putchar(' '); 
		printf("%d", res[i]);
	}
	puts("");
}

int main(){
	int T;
	scanf("%d", &T);
	while ( T-- ) process();

	return 0;
}
