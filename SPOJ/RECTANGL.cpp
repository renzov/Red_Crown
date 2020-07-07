#include<cstdio>
#include<cmath>
#include<chrono>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int MAXN = 250005;

int X[MAXN], Y[MAXN];
int mapX[MAXN], mapY[MAXN];
int A, B;
vector<int> P[MAXN];
int in[MAXN];
int ord[MAXN];

inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x){
  char c=nc(),b=1;
  for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
  for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

bool cmp2( const int &i, const int &j ){
	return ( X[i] != X[j] )? ( X[i] < X[j] ):( Y[i] < Y[j] );
}

bool cmp( const int &i, const int &j ){
	return (int)P[i].size() < (int)P[j].size();
}

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

unordered_map<long long, int, custom_hash> safe_map;

int main(){
	int N;
	safe_map.reserve(16777216);
	safe_map.max_load_factor(0.25);	
	read(N);
	for ( int i=0; i < N; ++i ){
		read( X[i] ), read( Y[i] );
		mapX[i] = X[i], mapY[i] = Y[i];	
		ord[i] = i;
	}
	// Compress coordinates
	sort( mapX, mapX + N ); 
	A = unique( mapX, mapX + N ) - mapX;
	sort( mapY, mapY + N );
	B = unique( mapY, mapY + N ) - mapY;
	for ( int i=0; i < N; ++i ){
		X[i] = lower_bound( mapX, mapX + A, X[i] ) - mapX;
		Y[i] = lower_bound( mapY, mapY + B, Y[i] ) - mapY;
		// Put points by bucket	
		P[ X[i] ].push_back( Y[i] );
	}
	for ( int i=0; i < A; ++i )
		sort( P[i].begin(), P[i].end() );
	// Find answer
	long long res = 0;
	int x1, x2, y, cnt;
	int sq = (int) sqrt( (double)N );
	int low, high;
	for ( int k = 0; k < A; ++k ){
		if ( P[k].size() > sq ){
			// mark points in bucket
			for ( int i=0; i < (int)P[k].size(); ++i ){
				y = P[k][i];
				in[y] = 1;
			}
			// Compare to previous buckets
			for ( int j=0; j < k; ++j ){
				cnt = 0;
				for ( int i=0; i < (int)P[j].size(); ++i ){
					y = P[j][i];
					cnt += in[y];
				}
				res += (1LL * ( cnt - 1 ) * cnt) >> 1; 
			}
			// Undo the marking
			for ( int i=0; i < P[k].size(); ++i ){
				y = P[k][i];
				in[y] = 0;
			}
		}
		else {
			for ( int i=1; i < (int)P[k].size(); ++i )	
				for ( int j=0; j < i; ++j ){
					high = P[k][i];
					low = P[k][j];
					//Map[((long long)high<<32)+low]++;
					safe_map[ ((long long)high << 31) + low ]++;
				}
		}
	}
	//for (int i=1;i<=Map.inum;i++)
    // 	res += (long long)Map.v[i]*(Map.v[i]-1)/2;
	for (auto &entry : safe_map){
     	cnt = entry.second;
		res += (1LL * ( cnt - 1 ) * cnt) >> 1; 
	}
	printf("%lld\n", res);
	return 0;
}
