#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
long long D[MAXN];
long long w;
int N;

bool validzero( long long v ){
	for ( int i=0; i < N; ++i ){
		v += D[i];
		if ( v < 0 ) return false;
	}
	return true;
}


bool validw( long long v ){
	for ( int i=0; i < N; ++i ){
		v += D[i];
		if ( v > w ) return false;
	}
	return true;
}

int main(){
	
	scanf("%d %lld", &N, &w);
	for ( int i=0; i < N; ++i ) 
		scanf("%lld", D + i);
	
	long long l, r, m;
	long long L, R;

	if ( !validzero(w) ){
		puts("0");
		return 0;
	}
	else if ( validzero(0) ){
		L = 0;
	}
	else {
		l = 0, r = w;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			if ( validzero(m) )
				r = m;
			else
				l = m;
		}
		L = r;
	}
	if ( !validw(L) ){
		puts("0");
		return 0;
	}
	else if ( validw(w) ){
		R = w;
	}
	else {
		l = L;
		r = w;
		while ( r - l > 1 ){
			m = ( l + r ) >> 1;
			if ( validw(m) )
				l = m;
			else 
				r = m;
		}
		R = l;
	}
	printf("%lld\n", R - L + 1);
	return 0;
}
