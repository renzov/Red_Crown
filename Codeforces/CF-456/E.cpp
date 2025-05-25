#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXVAL = 1000000000000000000LL;

vector<int> P[2];
vector<long long> multL;
vector<long long> multR;

void gen_multiples( const int &idx, vector<int> &p, long long num, long long bound, vector<long long> &S ){
	if ( idx == (int)p.size() ){
		S.push_back( num );
		return;
	}
	while ( bound > 0 ){
		gen_multiples( idx + 1, p, num, bound, S );
		num *= p[idx];
		bound /= p[idx];
	}
}

long long cnt_leq( const long long &X ){
	int idx = 0;
	long long ans = 0LL;
	
	for ( int i = 0; i < multL.size(); ++i ){
		while ( idx < multR.size() && multR[idx] <= X / multL[i] )
			idx++;
		ans += idx;
	}
	return ans;
}

int main(){
	int N;
	int v;
	long long K;

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &v );
		P[i & 1].push_back(v);
	}
	scanf("%lld", &K);

	gen_multiples( 0, P[0], 1LL, MAXVAL, multL );
	gen_multiples( 0, P[1], 1LL, MAXVAL, multR );

	sort( multL.begin(), multL.end() );
	reverse( multL.begin(), multL.end() );
	sort( multR.begin(), multR.end() );

	long long l = 0;
	long long r = MAXVAL;
	long long m;

	while ( r - l > 1 ){
		m = (l + r) >> 1;
		if ( cnt_leq( m ) >= K )
			r = m;
		else 
			l = m;

	}
	printf("%lld\n", r);
	return 0;
}
