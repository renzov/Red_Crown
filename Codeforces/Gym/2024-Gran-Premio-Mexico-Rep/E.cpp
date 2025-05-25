#include<cstdio>
#include<climits>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 100005;
const long long MOD = 1000000007LL;
vector<int> G[MAXN];
vector<int> W[MAXN];

int d[MAXN];
int cnt[MAXN];
int val[MAXN];

long long fact[MAXN];
long long inv[MAXN];

long long gcd ( const long long &a, const long long &b) {
    return b ? gcd (b, a % b) : a;
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long binom( const int &n, const int &k ){
	if ( n < k ) return 0;
	return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}

void dijkstra( const int &N ){
	fill( d, d + N, INT_MAX );
	d[0] = 0;
	priority_queue< pii, vector<pii>, greater<pii> > Q;
	Q.push( pii(0, 0) );

	int u, v, w, nw;
	while ( !Q.empty() ){
		u = Q.top().second;
		w = Q.top().first;
		Q.pop();
		if ( d[u] < w ) continue;
		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			nw = w + W[u][i];
			if ( d[v] > nw ){
				d[v] = nw;
				Q.push( pii( nw, v ) );
			}
		}
	}
}

long long inverse( const long long &a ){
	return binpow( a, MOD - 2 );
}

void precomp( const int &N ){
	fact[0] = 1;
	inv[0] = 1;
	for ( int i = 1; i <= N; ++i ){
		fact[i] = fact[i - 1] * i % MOD;
		inv[i] = inv[i - 1] * inverse( i ) % MOD; 
	}
}

int main(){
	int N, M, K;
	int u, v, w;

	scanf("%d %d %d", &N, &M, &K);
	for ( int i = 0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(v);
		G[v].push_back(u);
		W[u].push_back(w);
		W[v].push_back(w);
	}
	dijkstra(N);
	precomp(N);
	sort( d, d + N ); 
	int last = -1;
	int m = 0;
	for ( int i = 0; i < N; ++i ){
		if ( last == d[i] ){
			cnt[m - 1]++;
		}
		else {
			val[m] = d[i];
			cnt[m++] = 1;
		}
		last = d[i];
	}

	long long res, num = 0, den, q;
	int n = N - 1;
	for ( int i = 1; i < m; ++i ){
		q = binom( n, K ); 
		if ( i < (m - 1) ){
			q = (MOD + q - binom( n - cnt[i], K ) ) % MOD;
		}
		num += ( q * val[i] % MOD );
		num %= MOD;
		n -= cnt[i];
	}
	den = binom( N - 1, K );
	long long g = gcd( num, den );
	num /= g, den /= g;
	res = num * inverse( den ) % MOD;
	printf("%lld\n", res );
	return 0;
}
