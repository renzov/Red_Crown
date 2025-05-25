#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int N, B, M;
int res;
vector<piii> O;
vector<int> cap;

void backtrack( const int &idx, const int &ans ){
	if ( idx == M ){
		res = max( res, ans );
		return;
	}
	// check if we can use apply the order
	int p = O[idx].first;
	int s = O[idx].second.first;
	int t = O[idx].second.second;

	bool ok = true;
	for ( int i = s; ok && i < t; ++i )
		if ( cap[i] + p > N ) ok = false;
	
	if ( ok ){
		for ( int i = s; i < t; ++i ) cap[i] += p;
		backtrack( idx + 1, ans + (t - s)*p );
		for ( int i = s; i < t; ++i ) cap[i] -= p;
	}
	// do not use the order
	backtrack( idx + 1, ans );
}

void process(){
	O.clear();
	cap.clear();
	int from, to, pass;
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d", &from, &to, &pass);
		O.push_back( piii( pass, pii( from, to ) ) );
	}
	cap.resize( B + 1 );
	fill( cap.begin(), cap.end(), 0 );
	res = INT_MIN;
	backtrack( 0, 0 );
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d %d %d", &N, &B, &M) && ( N || B || M ) )
		process();
	return 0;
}
