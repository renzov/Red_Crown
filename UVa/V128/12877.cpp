#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 16;

int N, M;
int W[MAXN][MAXN];
int size[MAXN];
bool nozero[26];
int res;
int val[26];
bool used[10];

void solve( const int &r, const int &c, const int &sum, const int &carry ){
	if ( c >= M ){ 
		if ( carry == 0 ){
			res++;
		}
		return; 
	}
	int d, x;
	if ( r == (N - 1) ){
		d = (sum + carry) % 10;
		x = W[r][c];
		if ( val[x] == -1 ){
			if ( used[d] ) return;	// invalid
			if ( d == 0 && nozero[x] ) return; // invalid
			val[x] = d, used[d] = true;
			solve( 0, c + 1, 0, (carry + sum)/10 );
			val[x] = -1, used[d] = false;
		}
		else if ( val[x] == d ){
			solve( 0, c + 1, 0, (carry + sum)/10 );
		}
	}
	else {
		if ( size[r] <= c ){
			solve( r + 1, c, sum, carry );
		}
		else {
			x = W[r][c];
			if ( val[x] != -1 ){
				solve( r + 1, c, sum + val[x], carry );
			}
			else {
				// try to use zero
				if ( !used[0] && !nozero[x] ){
					used[0] = true, val[x] = 0;
					solve( r + 1, c, sum, carry );
					used[0] = false, val[x] = -1;
				}
				for ( int i=1; i <= 9; ++i ){
					if ( used[i] ) continue;
					val[x] = i, used[i] = true;
					solve( r + 1, c, sum + i, carry );
					val[x] = -1, used[i] = false;
				}
			}
		}
	}
}

void process(){
	char s[16];
	fill( size, size + N, 0 );
	fill( nozero, nozero + 26, false );
	fill( val, val + 26, -1 );
	fill( used, used + 26, false );
	for ( int i=0; i < N; ++i ){
		scanf("%s", s);
		for ( int j=0; s[j]; ++j ){
			W[i][j] = s[j] - 'A';
			size[i]++;
		}
	}
	for ( int i=0; i < N; ++i ){
		nozero[ W[i][0] ] = true;
		reverse( W[i], W[i] + size[i] );	
	}
	M = size[ N - 1 ];
	res = 0;
	solve( 0 , 0, 0, 0);
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}
