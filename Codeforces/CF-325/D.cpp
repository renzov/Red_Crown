#include<cstdio>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, long long> pil; 
typedef pair<pii, pil> piv;

const int MAXN = 32;
int X[MAXN], Y[MAXN], Z[MAXN];

int slX, slY, slZ;
int srX, srY, srZ;
int N;

vector<piv> L, R;

void gen_all( const int &l, const int &r, const int &x, const int &y, const int &z, const long long &mask, vector<piv> &V ){
	if ( l == r ){
		V.push_back( piv( pii( x - y, x - z ), pil( -x, mask ) ) );
		return ;
	}
	gen_all( l + 1, r, x - X[l], y, z, mask, V );
	gen_all( l + 1, r, x, y - Y[l], z, mask | (1LL << (l * 2)),  V );
	gen_all( l + 1, r, x, y, z - Z[l], mask | (1LL << (l * 2 + 1)), V );
}

int main(){

	scanf("%d", &N);
	
	int n = N >> 1;

	for ( int i = 0; i < N; ++i ){
		scanf("%d %d %d", X + i, Y + i, Z + i );
		if ( i < n ){
			slX += X[i], slY += Y[i], slZ += Z[i];
		}
		else {
			srX += X[i], srY += Y[i], srZ += Z[i];
		}
	}
	
	gen_all( 0, n, slX, slY, slZ, 0LL, L );
	gen_all( n, N, srX, srY, srZ, 0LL, R );

	sort( L.begin(), L.end() );

	int base = INT_MAX;
	long long bitV;
	vector<piv>::iterator lp;

	for ( int i = 0; i < (int)R.size(); ++i ){
		int dy = -R[i].first.first;
		int dz = -R[i].first.second;
		lp = lower_bound( L.begin(), L.end(), piv( pii( dy, dz ), pil( INT_MIN, 0LL ) ) );
		if ( lp != L.end() && lp->first.first == dy && lp->first.second == dz ){
			if ( base > ( lp->second.first + R[i].second.first ) ){
				base = lp->second.first + R[i].second.first;
				bitV = lp->second.second | R[i].second.second;
			}
		}
	}
	int opt;
	if ( base != INT_MAX ){
		for ( int i = 0; i < N; ++i ){
			opt = bitV & 3;	// two lowest bits
			if ( opt == 0 ) puts("MW");
			else if ( opt == 1 ) puts("LW");
			else puts("LM");
			bitV >>= 2;
		}
	}
	else {
		puts("Impossible");
	}
	return 0;
}
