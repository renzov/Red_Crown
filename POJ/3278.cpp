#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 200000;
int d[MAXN + 5];
int q[MAXN + 5];
int qf, qt;

int main(){
	int s, t, u;
	scanf("%d %d", &s, &t);

	qt = qf = 0;
	fill( d, d + MAXN + 1, -1 );
	d[s] = 0;
	q[ qt++ ] = s;	
	
	while ( qf < qt && d[t] == -1 ){
		u = q[ qf++ ];
		if ( u + 1 <= MAXN && d[u + 1] == -1 ){
			d[u + 1] = d[u] + 1;
			q[ qt++ ] = u + 1;
		}
		if ( u > 0 && d[u - 1] == -1 ){
			d[u - 1] = d[u] + 1;
			q[ qt++ ] = u - 1;
		}
		if ( (u<<1) <= MAXN  && d[u<<1] == -1  ){
			d[u<<1] = d[u] + 1;
			q[ qt++ ] = u << 1; 
		}
	}
	printf("%d\n", d[t]);
	return 0;
}

