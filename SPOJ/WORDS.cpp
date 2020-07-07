#include<cstdio>
#include<cassert>
#include<bitset>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 128;
const int MAXS = 256;
const int BASE = 26;
const int MAXH = 11881378;

int N, L;
char W[MAXN][MAXS];
char RW[MAXN][MAXS];
int P[MAXN][8];
int S[MAXN][8];
int pot[6];
bool vis[MAXN];
bitset<MAXH> in;

void allsubstr( const int &i ){
	int v = P[i][L - 1];
	assert( v < (int)in.size() );
	in.set( v );
	for ( int j=L; W[i][j]; ++j ){
		v = v % pot[L - 1];
		v *= BASE;
		v += (W[i][j] - 'a');	
		assert( v < (int)in.size() );
		in.set(v);
	}
}

int main(){
	int n;
	scanf("%d %d", &N, &L);
	assert( N < MAXN );
	assert( L < 6 && L > 0 );
	pot[0] = 1;
	for ( int i=1; i <= L; ++i ) pot[i] = pot[i-1] * BASE;

	for ( int i=0; i < N; ++i ){
		scanf("%s", W[i]);
		for ( n=0; W[i][n]; ++n )
			RW[i][n] = W[i][n];
		RW[i][n] = '\0';
		reverse( RW[i], RW[i] + n );
	}
	for ( int i=0; i < N; ++i ){
		// All the prefixes of size <= L
		P[i][0] = W[i][0] - 'a';
		for (int j=1; j < L; ++j )
			P[i][j] = P[i][j-1]*BASE + (W[i][j] - 'a');
		// All the suffixes of size <= L
		S[i][0] = RW[i][0] - 'a';
		for ( int j=1; j < L; ++j )
			S[i][j] = S[i][j-1] + (RW[i][j] - 'a') * pot[j];
	}

	int A, B;
	int a, b;
	int v;	
	queue<int> q;
	q.push(0);
	vis[0] = true;
	while ( !q.empty() ){
		int i = q.front();
		q.pop();
		allsubstr( i );
		for ( int j=1; j < N; ++j ){
			// We test every possible match
			for ( int k=0; k < L - 1; ++k ){
				if ( S[i][k] == P[j][k] ){	// They match
					if ( !vis[j] ){
						q.push(j);
						vis[j] = true;
					}
					a = L - 2;	
					b = k + 1;	
					while ( a > k && b < L ){	
						A = S[i][a] / pot[k + 1];
						B = P[j][b];
						v = A * pot[b + 1] + B;
						assert( v < (int)in.size() );
						in.set( v );
						a--, b++;
					}
				} 
			}
		}
	}
	printf("%d\n", (int)in.count());
	return 0;
}
