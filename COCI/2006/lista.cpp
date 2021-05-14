#include<cstdio>
#include<list>
#include<algorithm>
using namespace std;
const int MAXN = 500005;

list<int> L;
list<int>::iterator pos[MAXN];
int A[MAXN];
int best[MAXN];
int idx[MAXN];
int P[MAXN];
int B[MAXN];

int LIS( const int &N ){
	int M = 1;
	int pt;
	
	P[0] = -1;
	best[0] = A[0];
	idx[0] = 0;
	for ( int i=1; i < N; ++i ){
		pt = upper_bound( best, best + M, A[i] ) - best;
		P[i] = idx[ pt - 1 ];
		if ( pt == M ){
			idx[M] = i;
			best[M++] = A[i];				
		}
		else if ( best[pt] > A[i] ){
			idx[pt] = i;
			best[pt] = A[i];
		}
	}
	int i = idx[ M - 1 ];
	int j = 0;
	while ( i >= 0 ){
		B[j] = A[i];
		i = P[i];
		j++;
	}
	reverse( B, B + M );
	return M;
}

int main(){
	int x, y;
	char op;
	int N, M;
	list<int>::iterator it;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i )
		pos[i] = L.insert(L.end(), i);
	
	for ( int i=0; i < M; ++i ){
		scanf(" %c %d %d", &op, &x, &y);
		x--, y--;
		if ( op == 'A' ){
			L.erase( pos[x] );
			pos[x] = L.insert( pos[y], x );
		}
		else { 
			L.erase( pos[x] );
			it = pos[y];
			pos[x] = L.insert( ++it, x );
		}
	}
	int i=0;
	for ( it=L.begin(); it != L.end(); ++it, ++i ){
		A[i] = *it;
	}
	// Find the lis of A
	int K = LIS(N);
	int last = N;
	printf("%d\n", N - K);
	// print the moves;
	for ( int i=N - 1, j = K - 1; i >= 0; --i ){
		if ( j < 0 ){ 
			printf("A %d %d\n", i + 1, last + 1);
		}
		else if ( i == B[j]  ) j--;
		else {
			printf("B %d %d\n", i + 1, B[j] + 1);
		}
		last = i;		
	}
	return 0;
}
