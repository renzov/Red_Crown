#include<cstdio>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
const int MAXN = 200005;
int A[MAXN];
int nxt[MAXN];
map<int,int> last;
int best[MAXN];

int main(){

	int N, M, x;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);		
	}
	nxt[N - 1] = -1;
	last[ A[N - 1] ] = N - 1;
	for ( int i=N - 2; i >= 0; --i ){
		if ( last.find( A[i] + 1 ) == last.end() )
			nxt[ i ] = -1;
		else 
			nxt[ i ] = last[ A[i] + 1 ];
		last[ A[i] ] = i;
	}

	int res = 1;
	int st = N - 1;
	best[ N - 1 ] = 1;

	for ( int i=N - 2; i >= 0; --i ){
		if ( nxt[i] != -1 )
			best[i] = best[ nxt[i] ] + 1;
		else
			best[i] = 1;
		if ( res < best[i] ){
			res = best[i], st = i;
		}
	}

	printf("%d\n", res);
	for ( int i=0; i < res; ++i ){
		if ( i ) putchar(' ');
		printf("%d", st + 1);
		st = nxt[ st ] ;
	}
	puts("");
	return 0;
}
