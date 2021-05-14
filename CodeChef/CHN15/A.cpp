#include<cstdio>
#include<algorithm>
using namespace std;

bool test( const int &E, const int &M, const int &H, const int &K ){
	int e = min( E - K, (K + 1)/2 );
	int m = min( M - K, (K + 1)/2 );
	int h = min( H, (K + 1)/2 );
	return (e + m + h) >= K;
}

void process(){
	int E, M, H;
	scanf("%d %d %d", &E, &M, &H);
	
	int l = 0;		// always possible
	int r = M + 1; // impossible
	int m;

	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( test(E, M, H, m) )
			l = m;
		else 
			r = m;
	}
	printf("%d\n", l);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
