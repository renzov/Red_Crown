#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int N;
int to[2][2][2];
int nxt[1 << 20];
int pos[1 << 20];

int pack( int b[] ){
	int res = 0;
	for ( int i = 0; i < N; ++i ){
		res <<= 1;
		if ( b[i] ) res |= 1; 
	}
	return res;
}

void unpack( const int &mask, int b[] ){
	for ( int i = 0; i < N; ++i )
		b[i] = (mask >> i) & 1;
	reverse(b, b + N);
}

void gen_graph(){
	int B[20];
	int NB[20];

	for ( int mask = 0; mask < (1 << N); ++mask ){
		unpack( mask, B );
		int l = N - 2;
		int r = 1;
		for ( int i = 0; i < N; ++i ){
			NB[i] = to[ B[l] ][ B[i] ][ B[r] ];
			l++, r++;
			l %= N;
			r %= N;
		}
		nxt[mask] = pack( NB );
	}
}

int solve( const int &u, const int &p, const int &l ){
	pos[u] = p;
	if ( !l ) return u;
	int v = nxt[u];
	if ( pos[v] == -1 ) return solve( v, p + 1, l - 1 );
	int len = pos[u] - pos[v] + 1;
	// we got to v
	int left = (l - 1) % len;
	while ( left-- )
		v = nxt[v];
	return v;
}

void print_lexicographic( char S[] ){
	char best[20];
	char aux[20];
	copy( S, S + N, best );
	best[N] = '\0';
	for ( int i = 1; i < N; ++i ){
		copy( S + i, S + (i + N), aux );
		aux[N] = '\0';
		if ( strcmp( best, aux ) > 0 )
			strcpy( best, aux );
	}
	puts(best);
}

void process(){
	char op[5];
	int bits[5];
	int B[20];
	char S[40];

	scanf("%s", S);		
	for ( int i = 0; i < N; ++i ) B[i] = S[i] - 'a';
	int start = pack(B);

	for ( int i = 0; i < 8; ++i ){
		scanf("%s", op);
		for ( int j = 0; j < 4; ++j )
			bits[j] = op[j] - 'a';
		to[ bits[0] ][ bits[1] ][ bits[2] ] = bits[3];
	}
	int L;
	scanf("%d", &L);
	gen_graph();
	for ( int i = 0; i < (1 << N); ++i ) pos[i] = -1;
	int ends = solve( start, 0, L );
	unpack( ends, B );
	for ( int i = 0; i < N; ++i ){
		S[i] = (char)('a' + B[i]);
		S[i + N] = S[i]; 
	}
	print_lexicographic(S);
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}
