/* Can suppose key <= 100 */

#include <cstdio>
using namespace std;

const int MAXP = 1024;
int div[MAXP + 5] = {0}; 
int phi[MAXP + 5];

void sieve(){
	for ( int i=2; i <= MAXP ; i++ ){
		if ( !div[i] ){
			phi[ i ] = i-1;
			for ( int j=i*i ; j <= MAXP;  j += i ){
				div[ j ] = i;
			}
		}
		else {
			if ( (i / div[i]) % div[i] ){
				phi[ i ] = phi[ i / div[i] ] * ( div[ i ] - 1 ); 
			}
			else {
				phi[ i ] = phi[ i / div[i] ] * div[ i ];
			}
		}
	}
}

void decompose( int num, int v[] , int s ){
	for ( int i=s-1; i >= 0; --i ){
		v[i] = num % 100;
		num /= 100;
	}
}

long long big_mod( long long x, int p, int m ){
	if ( p == 0 ) return 1;
	if ( p == 1 ) return x;
	if ( p&1 ) return ( big_mod( x , p-1 , m ) * x ) % m;
	long long res = big_mod( x , p >> 1 , m );
	return ( res * res ) % m;
}

int solve(int key[], int r[]){
	long long N = key[0] * key[1] * key[2] * key[3];
	long long Ni[5];
	long long inv[5];

	for ( int i=0; i < 4; ++i ) Ni[i] = N / key[i];
	for ( int i=0; i < 4; ++i ) inv[i] = big_mod( Ni[i] , phi[ key[i] ] - 1 , key[i] );

	long long res = 0;
	
	for ( int i=0; i < 4; ++i ){
		res += Ni[ i ] * inv[ i ] * r[i];
		res %= N;
	}
	return (int) res;
}

int main(){
	sieve();
	int runs;
	int N;
	int key[5];
	int A;
	int X;
	int r[5], d[5];
	char stmt[300];
	int size;

	scanf("%d", &runs);
	while ( runs-- ){
		size = 0;
		scanf("%d", &N);
		
		for ( int i=0; i < 4; ++i ) scanf("%d", key + i );

		for ( int i=0; i < N; ++i ){
			scanf("%d", &A);
			decompose( A , r , 4 );
			X = solve( key, r );
			decompose( X , d , 3 );
			for ( int i=0; i < 3; ++i ){
				if ( d[i] <= 26 ){
					stmt[ size++ ] = (char)( 'A' + d[i] - 1 );
				}
				else {
					stmt[ size++ ] = ' ';
				}
			}
		}
		while ( size > 0 && stmt[size - 1] == ' ' ) size--;
		stmt[size] = '\0';
		puts( stmt );
	}
	return 0;
}

