#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXP = 25;
const int MAXN = 101;
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int coef[MAXN][MAXP] = {0};
int N;
int X[MAXN];
int Y[MAXN];
int cnt[MAXN];
int expo[MAXN];
double PX[MAXN];
double PY[MAXN];
double PZ[MAXN]; 
double PC[MAXN];

void precalc(){
	int num; 
	for ( int i=2; i < MAXN; ++i ){
		// factorize i
		num = i;
		for ( int j=0; num > 1 && j < MAXP; ++j )
			while ( num % primes[j] == 0 )
				num /= primes[j], coef[i][j]++;

		if ( i + 1 < MAXN ){
			for ( int j=0; j < MAXP; ++j )
				coef[i + 1][j] = coef[i][j];
		}
	}
}

void fill_up( double p, double V[], const int &n ){
	V[0] = 1.0;
	for ( int i=1; i <= n; ++i ) V[i] = V[i-1]*p;
}

double get_multinomial( const int &n, const int &n1, const int &n2, const int &n3, const int &n4 ){
	for ( int i=0; i < MAXP; ++i ) expo[i] = coef[n][i];
	for ( int i=0; i < MAXP; ++i ){
		expo[i] -= coef[n1][i];
		expo[i] -= coef[n2][i];
		expo[i] -= coef[n3][i];
		expo[i] -= coef[n4][i];
	}
	double res = 1.0;
	for ( int i=0; i < MAXP; ++i ){
		while ( expo[i]-- ) res *= primes[i];
	}
	return res;
}

int main(){
	precalc();
	int S, T, D;
	int cases = 0;
	while ( scanf("%d", &N) && N ){
		fill( cnt, cnt + (N + 1), 0 );
		scanf("%d", &S);
		for ( int i=0; i < S; ++i ){ 
			scanf("%d", X + i);
			cnt[ X[i] ]++;
		}
		scanf("%d", &T);
		for ( int i=0; i < T; ++i ){ 
			scanf("%d", Y + i);
			cnt[ Y[i] ]++;
		}
		scanf("%d", &D);
		int Z = 0;	// Number of elements that are in no set
		int C = 0;	// Number of elements in the intersection of X and Y
		for ( int i=1; i <= N; ++i )
			if ( cnt[i] == 2 ) C++;
			else if ( cnt[i] == 0 ) Z++;
		int A = S - C;	// Number of elements in X but not in Y
		int B = T - C;	// Number of elements in Y but not in X
		fill_up( (double)A/N , PX, D );
		fill_up( (double)B/N , PY, D );
		fill_up( (double)Z/N , PZ, D );
		fill_up( (double)C/N , PC, D );
		double res = 0.0;
		int z, b;
		double tmp;
		// Calculate the probability of all interesting events
		for ( int a=0; 3*a <= D; ++a ){
			for ( int c=0; 2*c <= (D - 3*a); ++c ){
				b = 2*a + c;
				z = D - a - b - c;
				if ( z < 0 ) continue;
				tmp = get_multinomial( D, a, b, c, z );
				tmp *= PX[a];
				tmp *= PY[b];
				tmp *= PC[c];
				tmp *= PZ[z];
				res += tmp;
			}
		}	
		res = fabs(res);
		printf("Case %d: %.5f\n", ++cases, res);
	}
	return 0;
}
