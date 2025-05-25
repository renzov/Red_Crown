#include<cstdio>
#include<algorithm>
using namespace std;
int P[20];
int f[20];

int count_peaks( const int &N ){
	int res = 0;
	bool ok;
	for ( int i = 0; i < N; ++i ){
		ok = true;
		for ( int j = 0; ok && j < i; ++j )
			if ( P[j] > P[i] )
				ok = false;
			if ( ok ) res++;
	}
	return res;
}

int main(){
	int N;
	scanf("%d", &N);
	for ( int i = 0; i < N; ++i )
		P[i] = i;
	do {
		int cnt = count_peaks(N);
		f[cnt]++;
	}
	while (next_permutation(P, P + N));
	for ( int i = 0; i <= N; ++i )
		printf("%d ", f[i]);
	puts("");
	return 0;
}
