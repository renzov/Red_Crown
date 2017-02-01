#include<cstdio>
#include<algorithm>
using namespace std;

long long simulate( long long N, long long M, int x1, int x2, int y1, int y2 ){
	long long res = 0;
	//Do first move from x1
	if ( x1 ){
		res += N*M;
		x1--, N--;
		res += 2*N*M*x2;
		if ( x1 < x2 ) res -= N*M;
		x1 -= x2;
	}
	// Do first move from y2
	if ( y1 ){
		res += N*M;
		y1--, M--;
		res += 2*N*M*y2;
		if ( y1 < y2 ) res -= N*M;
		y1 -= y2;
	}
	//x2 == 0 && y2 == 0
	while ( N > 0 && M > 0 && x1 > 0 && y1 > 0 ){
		res += N*M;
		if ( N >= M )
			x1--, N--;
		else 
			y1--, M--;
	}
	if ( !N || !M ) return res;
	while ( N > 0 && x1 > 0 ){
		res += N*M;
		x1--, N--;
	}
	while ( M > 0 && y1 > 0 ){
		res += N*M;
		M--, y1--;
	}
	return res;
}

int main(){
	long long N,M;
	int x1,x2,y1,y2;
	int cases = 0;
	while ( scanf("%lld %lld", &N, &M) && N && M ){
		cases++;
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		if ( x1 < x2 ) swap( x1, x2 );
		if ( y1 < y2 ) swap( y1, y2 );
		printf("Case %d: %lld\n", cases, max( simulate(N,M,x1,x2,y1,y2), 
											  simulate(M,N,y1,y2,x1,x2) ));
	}
	return 0;
}
