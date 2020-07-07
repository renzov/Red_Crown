/* ACCEPTED in acmicpc.net - Live Archive is down at the moment (03/03/2020) */
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXT = 128;
const int MAXP = 16;
const double INF = 10e12;
const double EPS = 1e-6;
const int BASE = 20;
double X[MAXT*MAXT]; 
int T, P;
int A[MAXT];
int B[MAXT];
int S[MAXT];
int M;

void process(){
	char s[12];
	int attemps;

	for ( int i=0; i < T; ++i ){
		S[i] = A[i] = B[i] = 0;
		for ( int j=0; j < P; ++j ){
			scanf("%d/%s", &attemps, s);
			//printf("at: %d - %s\n", attemps, s);
			if ( isdigit(s[0]) ){
				S[i]++;
				A[i] += ( attemps - 1 );				
				B[i] += atoi( s );
			}
		}	
	}

	M = 0;
	int low = 1;
	int up = INT_MAX;
	int x;
	for ( int i=0; i < T; ++i )
		for ( int j=0; j < i; ++j ){
			if ( A[i] == A[j] || S[i] != S[j] ) continue;	// parallel lines
			if ( BASE*A[i] + B[i] == BASE*A[j] + B[j] )
				low = up = BASE;
			else {
				if ( (B[j] - B[i]) % ( A[i] - A[j] ) == 0 ){
					x = ( B[j] - B[i] ) / ( A[i] - A[j] );
					if ( x < BASE ) low = max( low , x + 1 );
					else up = min( up, x - 1 );
				}
				else {
					x = ( B[j] - B[i] ) / ( A[i] - A[j] );
					if ( x < BASE ) low = max( low, x + 1 );
					else up = min( up, x );
				}
			}
		}
	
	printf("%d ", low);
	if ( up == INT_MAX )
		puts("*");
	else
		printf("%d\n", up);
}

int main(){
	while ( scanf("%d %d", &T, &P) && T && P )
		process();
	return 0;
}
