#include<cstdio>
#include<cmath>
using namespace std;
const int MAXD = 1024;

long long V;
int D;
int N;
int S[MAXD][2] = {0};


int main(){
	int p, a, b;
	int wA = 0, wB = 0;

	scanf("%d %d", &N, &D);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d", &p, &a, &b);
		S[p][0] += a, S[p][1] += b;
		V += a;
		V += b;
	}
	
	int total , w;
	for ( int i=1; i <= D; ++i ){
		total = S[i][0] + S[i][1];
		if ( S[i][0] > S[i][1] ){
			w =  S[i][0] - (total >> 1) - 1;
			wA += w, wB += S[i][1];
			printf("A %d %d\n", w, S[i][1]);
		}
		else {
			w = S[i][1] - (total >> 1) - 1;
			wA += S[i][0], wB += w;
			printf("B %d %d\n", S[i][0], w );
		}
	}
	printf("%.8f\n", fabs( (double)wA - (double)wB )/V);
	return 0;
}
