#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN = 20005;
map<int,int> V[5];
int ord[MAXN];
int N;

bool cmp( const int &i, const int &j ){
	int frec = 0;
	for ( int k=0; k < 5; ++k )
		frec += ( V[k][i] < V[k][j] );
	return frec > 2;
}

int main(){
	int idx;
	scanf("%d", &N);
	for ( int i=0; i < 5; ++i )
		for ( int j=0; j < N; ++j ){
			scanf("%d", &idx);
			V[i][ idx ] = j;
			ord[j] = idx;
		}

	sort( ord, ord + N, cmp );
	for ( int i=0; i < N; ++i ) printf("%d\n", ord[i]);
	return 0;
}
