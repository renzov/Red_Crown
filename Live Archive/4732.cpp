#include<cstdio>
#include<map>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii, int> piii;

const int MAXN = 5000;
const int MAXM = 500000;

int f[MAXN];
int val[MAXN];
int sign[MAXN];
piii E[MAXN];
map<int,int> inv;
map<int,int> frec;

int find_set( const int &x ){
	if ( x == f[x] ) return x;
	int px = f[x];
	f[x] = find_set( px );
	sign[ x ] ^= sign[ px ];
	return f[x];
}

void process(){
	int N, M;
	int u, v, w;
	int pu, pv;

	scanf("%d %d", &N, &M);
	// Init the sets
	for ( int i=0; i  < N; ++i ) f[i] = i, sign[i] = 0;
	for ( int i=0; i < M; ++i ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		if ( u > v ) swap(u, v);
		E[i] = piii( pii(u, v), w );
	}
	sort( E , E + M );
	// First insert the information about the distance with the center
	int i;
	bool ok = true; // is there a solution?
	int cnt;
	
	for ( i=0 ; ok && i < M && E[i].first.first == 0 ; ++i ){
		v = E[i].first.second;
		w = E[i].second;
		val[v] = w;
		cnt = frec[w];
		if ( cnt == 0 ){ // It already exists
			frec[w]++;
		}
		else if ( cnt == 1 ) {
			u = inv[w];
			frec[w]++;
			pu = find_set( u );
			pv = find_set( v );
			// it is guaranteed that pu != pv, otherwise there would be 3 vertices with the same distance
			f[ pv ] = pu;
			sign[ pv ] = sign[u] ^ sign[v] ^ 1; // invert the sign
		}
		else {
			ok = false; // Three or more vertices at the same distance is impossible
		}
	}
	// process the rest of the information
	for ( ; ok && i < M; ++i ){
		u = E[i].first.first;
		v = E[i].first.second;
		w = E[i].second;
		if ( val[u] + val[v] == w ){ // u and v must be in different sides
			pu = find_set(u);
			pv = find_set(v);
			if ( pu != pv ){ // join the sets
				f[ pv ] = pu;
				sign[ pv ] = sign[u] ^ sign[v] ^ 1; // invert the sign in the subtree rooted by pv 
			}
			else if ( (sign[u] ^ sign[v]) != 1 ) {
				ok = false; // impossible
			}
		}
		else if ( abs(val[u] - val[v]) == w ){ // u and v must be in the same side
			pu = find_set(u);
			pv = find_set(v);
			if ( pu != pv ){
				f[pv] = pu;
				sign[ pv ] = sign[ u ] ^ sign[ v ];
			}
			else if ( (sign[u] ^ sign[v]) != 0 ) {
				ok = false;
			}
		}
		else {	// impossible
			ok = false;
		}
	}
	// compress every path
	for ( int i=0; i < N; ++i ) find_set(i);
	// Print the solution
	printf("%d\n", N);
	if ( !ok ) puts("impossible");
	else {
		for ( int i=0; i < N; ++i ){
			if (i) putchar(' ');
			if ( sign[i] ) printf("-%d", val[i]);
			else printf("%d", val[i]);
		}
		puts("");	
	}
	// Clean memory for next testcase
	inv.clear();
	frec.clear();
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
