#include<cstdio>
#include<vector>
#include<climits>
using namespace std;
const int INF = 100000000;
int N, M;

int dist( const vector<int> &A, const vector<int> &B ){
	int res = 0;
	bool found = false; 
	for ( int j=0; j < M; ++j ){
		if ( A[j] != -1 && B[j] != -1 ){
			res += (A[j] - B[j])*(A[j] - B[j]);
			found = true;
		}
	}
	if ( !found ) return INF - 1;
	return res;
}

int main(){
	int Q;
	int c, g;

	scanf("%d %d", &N, &M);
	vector< vector<int> > C( N, vector<int>(M, -1) );

	for ( int i=0; i < N; ++i ){
		scanf("%d", &Q);
		while ( Q-- ){
			scanf("%d %d", &c, &g);
			c--;
			C[ i ][ c ] = g;
		}
	}

	for ( int i=0; i < N; ++i ){
		int id = -1;
		int best = INF;
		int D;
		for ( int j=0; j < N; ++j ){
			if ( i == j ) continue;
			D = dist( C[i], C[j] );
			if ( D < best ){
				best = D, id = j;
			}
		}
		int res = -1;
		best = -1;
		for ( int j=0; j < M; ++j ){
			if ( C[id][j] != -1 && C[i][j] == -1 && C[id][j] > best ){
				best = C[id][j], res = j;
			}
		}
		if ( res == -1 ) printf("%d\n", res);
		else printf("%d\n", res + 1);
	}
	return 0;
}
