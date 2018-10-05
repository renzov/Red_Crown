#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int pot[] = {1, 10, 100, 1000, 10000, 100000, 1000000 };

int inv( int x ){
	int res = 0;
	while ( x > 0 ){
		res *= 10;
		res += (x % 10);
		x /= 10;
	}
	return res;
}

int main(){
	int n;
	char N[20];
	char P[20];

	while ( scanf("%s", N) && strcmp(N, "0") != 0 ){
		n = strlen(N);
		if ( n == 1 ){
			puts("0");
			continue;
		}
		int num = atoi( N );
		int m = n >> 1;
		strncpy( P, N, m );
		P[m] = '\0'; 		
		int A = atoi(P);
		reverse( P , P + m );
		int B = atoi( P );
		if ( n & 1 ){
			int mid = N[m] - '0';
			bool ok = false;
			int val;
			for ( int i=mid; i < 10 && !ok; ++i ){
				val = A*pot[m+1] + i*pot[m] + B;
				if ( val >= num ){
					ok = true;
					printf("%d\n", val - num);
				}
			}
			if ( !ok ){
				sprintf( P, "%0*d", m , A + 1);
				reverse( P, P + m );
				B = atoi(P);
				val = (A + 1)*pot[m+1] + B;
				printf("%d\n", val - num);
			}
		}
		else {
			if ( A * pot[m] + B >= num ){
				printf("%d\n", A*pot[m] + B - num);
			}
			else {
				sprintf( P, "%0*d", m , A + 1);
				reverse( P, P + m );
				B = atoi(P);
				printf("%d\n", (A + 1)*pot[m] + B - num);
			}
		}
	}
	return 0;
}

