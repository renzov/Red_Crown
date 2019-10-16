#include<cstdio>
#include<cctype>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 128;
const long long INF = 1e12 + 1;
int N;
int B[MAXN];
int Y[MAXN][64];
int size[MAXN];
vector<long long> cand[MAXN];

bool isvalid( int *D, const int &n, const int &b ){
	for ( int i=0; i < n; ++i )
		if ( D[i] >= b ) return false;
	return true;
}

long long eval( int *D, const int &n, const int &b ){
	long long res = 0;
	for ( int i=0; i < n; ++i ){
		res *= b;
		if ( res >= INF ) return INF;
		res += D[i];
		if ( res >= INF ) return INF;
	}
	return res;
}

long long process(){
	char S[64];
	long long r;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d %s", B + i, S);
		int &s = size[i];
		for ( s = 0; S[s] ; s++ )
			if ( isdigit(S[s])  ) Y[i][s] = S[s] - '0';
			else Y[i][s] = (S[s] - 'A') + 10;

		if ( B[i] != -1 ){
			r = eval( Y[i], size[i], B[i] ); 
			if ( r < INF ) cand[i].push_back(r);
		}
		else {
			for ( int b=2; b <= 36; ++b ){
				if ( isvalid( Y[i], size[i], b ) && (r=eval(Y[i], size[i], b)) < INF )
					cand[i].push_back( r );
			}
		}
		sort( cand[i].begin(), cand[i].end() );
	}
	// Check if there is set with no candidate solution
	for ( int i=0; i < N; ++i )
		if ( (int)cand[i].size() == 0 ) return -1;

	bool ok;
	for ( int j=0; j < cand[0].size(); ++j ){
		r = cand[0][j];
		ok = true;
		for ( int i=1; i < N && ok; ++i )
			ok &= binary_search( cand[i].begin(), cand[i].end(), r );
		if ( ok ) return r;
	}
	return -1;
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){ 
		printf("%lld\n", process());
		for ( int i=0; i < N; ++i )
			cand[i].clear();
	}
	return 0;
}
