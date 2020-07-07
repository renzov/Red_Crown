#include<cstdio>
#include<climits>
#include<vector>
using namespace std;
const int MAXN = 128;
int N, M;
int S[MAXN];
int D[MAXN];
int C[MAXN];

vector<int> B[MAXN];
vector<int> E[MAXN];
bool act[MAXN] = {0};

int sch[MAXN];

int main(){

	scanf("%d %d", &N, &M);
	for ( int i=1; i <= M; ++i ){
		scanf("%d %d %d", S+i, D+i, C+i);
		B[ S[i] ].push_back( i );
		E[ D[i] ].push_back( i );
		sch[ D[i] ] = M + 1;
	}
	int best;
	int idx;
	int ok = true;
	for ( int i=1; i <= N && ok; ++i ){
		// new active task
		for ( int j=0; j < (int)B[i].size(); ++j ){
			act[ B[i][j] ] = true;
		}
		
		if ( sch[ i ] == 0 ){
			int best = -1, width = INT_MAX;
			int len;
			for ( int j=1; j <= M; ++j ){
				if ( act[j] && C[j] > 0 ){ // active task
					len = D[j] - i - C[j];
					if ( len < width ){
						width = len, best = j;
					}
				}
			}
			if ( best != -1 ){
				C[best]--;
				sch[i] = best;
			}
		}
		// Test removed tasks
		for ( int j=0; j < E[i].size(); ++j ){
			idx = E[i][j];
			if ( C[idx] > 0 ) ok = false;
			act[ idx ] = false;
		}
	
	}
	if ( !ok ) puts("-1");
	else {
		for ( int i=1; i <= N; ++i ){
			if ( i > 1 ) putchar(' ');
			printf("%d", sch[i]);
		}
		puts("");
	}
	return 0;
}
