#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 500005;
const int NLOG = 20;

int L[MAXN];
int P[NLOG][MAXN];

int lca( int a, int b ){
	if ( L[a] > L[b] )
		swap(a, b);
	
	for ( int i = NLOG - 1; i >= 0; --i )
		if ( (L[b] - L[a]) >= (1 << i) )
			b = P[i][b];

	if ( a == b ) return a;

	for ( int i = NLOG - 1; i >= 0; --i ){
		if ( P[i][a] != -1 && P[i][a] != P[i][b] )
			a = P[i][a], b = P[i][b];
	}
	return P[0][a];
}

int main(){
	int Q;
	int a, b;
	char op[5];

	L[0] = 0; 	
	for ( int i = 0; i < NLOG; ++i )
		P[i][0] = -1;
	
	freopen ("lca.in", "r", stdin);
	freopen ("lca.out", "w", stdout);

	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%s %d %d", op, &a, &b);
		a--, b--;
		if ( op[0] == 'A' ){
			L[b] = L[a] + 1;
			P[0][b] = a;
			for ( int i = 1; i < NLOG; ++i ){
				P[i][b] = P[i - 1][ P[i - 1][b] ];
			}
		}
		else {
			printf("%d\n", lca(a, b) + 1 );
		}
	}
	return 0;
}

