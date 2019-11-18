#include<cstdio>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
int f[MAXN];
pii E[MAXN];
int N, M;

int get_answer(){
	int left = M;
	int l, r = 0;
	int t;
	int res = INT_MAX;
	for ( l=0; l < N; ++l ){
		if ( left > 0 ){
			while ( r < N && left ){
				t = E[r].second;
				f[t]++;
				if ( f[t] == 1 ) left--;
				r++;
			}
			if ( left ) return res;
		}
		res = min( res , E[r - 1].first - E[l].first );
		t = E[l].second;
		f[t]--;
		if ( f[t] == 0 ) left++;
	}
	return res;
}

void process(){
	int x;
	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &x);
		E[i] = pii( x, i%M );
	}
	sort( E, E + N );
	printf("%d\n", get_answer());
	// clean up memory
	fill( f, f + M, 0 );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
