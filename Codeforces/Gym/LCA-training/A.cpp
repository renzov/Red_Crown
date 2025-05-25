#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
int L[MAXN];
int P[MAXN];

int lca( int a, int b ){
	if ( L[a] > L[b] )
		swap(a, b);
	
	while ( L[b] > L[a] ) 
		b = P[b];

	while ( a != b ){
		a = P[a];
		b = P[b];
	}
	return a;
}

int main(){
	int Q;
	int a, b;
	char op[5];

	L[0] = 0; 	
	P[0] = -1;

	freopen ("lca.in", "r", stdin);
	freopen ("lca.out", "w", stdout);

	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%s %d %d", op, &a, &b);
		a--, b--;
		if ( op[0] == 'A' ){
			L[b] = L[a] + 1;
			P[b] = a; 
		}
		else {
			printf("%d\n", lca(a, b) + 1 );
		}
	}
	return 0;
}
