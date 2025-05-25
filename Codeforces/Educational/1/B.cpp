#include<cstdio>
using namespace std;
const int MAXN = 10005;

char S[MAXN];
char C[MAXN];

int main(){
	int Q;
	int l, r, k;
	int len;

	scanf("%s", S);
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d %d", &l, &r, &k);
		l--, r--;
		len = r - l + 1;
		k = k % len;
		if ( k ){
			for ( int from = l, to = l + k; from <= r; ++from ){
				C[to - l] = S[from];
				to++;
				if ( to > r ) to = l;
			}
			for ( int i = l;  i <= r; ++i )
				S[i] = C[i - l];
		}
	}
	puts(S);
	return 0;
}
