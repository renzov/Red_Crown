#include<cstdio>
using namespace std;

const int MAXN = 10005;
int timestamp[MAXN] = {0};

int main(){
	int N, R;
	int idx;
	int t = 0;

	while ( scanf("%d %d", &N, &R) == 2 ){
		t++;
		for ( int i = 0; i < R; ++i ){
			scanf("%d", &idx);
			timestamp[idx] = t;
		}
		bool first = true;
		for ( int i = 1; i <= N; ++i )
			if ( timestamp[i] < t ){
				if ( first ) first = false;
				printf("%d ", i);
			}

		if ( first ) putchar('*');
		puts("");
	}
	return 0;
}
