#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 200005;
char S[MAXN];
int N;
bool can( const int &w ){
	int beg = 0;
	int last; 
	while ( beg < N ){
		last = -1;
		for ( int i=beg + 1; i <= min(N + 1, beg + w); ++i ){
			if ( S[i] == 'R' ) last = i;
		}
		if ( last == -1 ) return false;
		beg = last;
	}
	return true;
}

void process(){
	scanf("%s", &S[1]);
	N = strlen( &S[1] );
	S[0] = 'R';
	S[N + 1] = 'R';
	int l = 0;
	int r = N + 1;
	int m;
	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( can(m) ) r = m;
		else l = m;
	}
	printf("%d\n", r);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
