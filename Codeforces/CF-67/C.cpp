#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXD = 100000;
int d[MAXD];
int M;

void gen_div( const int &A, const int &B ){
	int x, y;
	for ( long long i=1; i*i <= A; ++i ){
		if ( A % i == 0 ){
			x = (int) i;
			y = (int) (A/i);
			if ( B % x == 0 ) d[M++] = x;
			if ( x != y && B % y == 0 ) d[M++] = y;
		}
	}
	sort(d, d + M);
}

int main(){
	int A, B;
	int N;
	int l , r;
	int pos;

	scanf("%d %d", &A, &B);
	gen_div(A, B);
	scanf("%d", &N);
	while ( N-- ){
		scanf("%d %d", &l, &r);
		pos = upper_bound( d, d + M, r ) - d;
		pos--;
		if ( d[pos] >= l ) printf("%d\n", d[pos]);
		else puts("-1");
	}	
	return 0;
}
