#include<cstdio>
#include<vector>
#include<chrono>
#include<unordered_map>
using namespace std; 
const int MAXN = 50005;
typedef pair<int,int> pii;
int dx[128];
int dy[128];
int M;

int N;
int X[MAXN];
int Y[MAXN];
int color[MAXN];
vector<int> G[MAXN];
int cnt[2];

// Structure for hashing
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<long long, int, custom_hash> P;


void clean(){
	P.clear();
	for ( int i=0; i < N; ++i )
		G[i].clear();
}

bool isNear( const int &X1, const int &Y1 ){
	return ( X1 * X1 + Y1 * Y1 ) <= 25;
}

void findPoints(){
	M = 0;
	for ( int i=-5; i <= 5; ++i )
		for ( int j=-5; j <= 5; ++j ){
			if ( i == 0 && j == 0 ) continue;
			if ( isNear(i , j) ){
				dx[M] = i, dy[M] = j; 
				M++;
			}
		}
}

void dfs( const int &u, const int &f, const int &c ){
	color[u] = c;
	cnt[c]++;
	int v;
	for ( int i=0; i < (int) G[u].size(); ++i ){
		v = G[u][i];
		if ( v == f ) continue;
		if ( color[v] == -1 ){
			dfs( v, u, c ^ 1 );
		}
	}
}

void process(){
	long long H;
	for ( int i=1; i <= N; ++i ){
		scanf("%d %d", X + i, Y + i);
		H = ( (long long)X[i] << 31 ) + Y[i];
		P[ H ] = i;
		// initialize
		color[i] = -1;
	}	
	int x, y;
	long long nx, ny;
	int idx;
	for ( int i=0; i < N; ++i ){
		x = X[i], y = Y[i];
		for ( int j=0; j < M; ++j ){
			nx = x + dx[j], ny = y + dy[j];
			H = (nx << 31) + ny;
			if ( P.find(H) != P.end() )
				G[i].push_back( P[H] );
		}
	}

	int res = 0;
	for ( int i=0; i < N; ++i ){
		if ( color[i] == -1 ){
			cnt[0] = cnt[1] = 0;
			dfs( i, -1, 0 );
			res += min( cnt[0], cnt[1] );
		}
	}
	printf("%d\n", res);
}

int main(){
	findPoints();
	while ( scanf("%d", &N) == 1 ){
		process();
		clean();	
	}
	return 0;
}
