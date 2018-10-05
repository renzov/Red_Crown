#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 1024;
typedef pair<int,int> pii;


int X[MAXN], Y[MAXN];
pii E[MAXN * MAXN];
int p[MAXN];

inline int dist2(const int &i, const int &j){
	return (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]);
}

int find_set(const int &x){
	return ( x == p[x] )? x:(p[x] = find_set(p[x]));
}

int main(){
	int N;
	int M;

	while ( scanf("%d", &N) && N ){
		M = 0;
		for ( int i=0; i < N; ++i )
			scanf("%d %d", X + i, Y + i);
	
		for ( int i=0; i < N; ++i )
			for ( int j=i+1; j < N; ++j ){
				E[ M++ ] = pii( dist2(i,j) , i*N + j );
			}

		double res = 0.0;
		sort( E , E + M );
		
		int u, v, w;
		int ncomp = N;
		for ( int i=0; i < N; ++i ) p[i] = i;

		for ( int i=0; i < M && ncomp > 1; ++i ){
			u = E[i].second / N;
			v = E[i].second % N;
			w = E[i].first;
			u = find_set(u);
			v = find_set(v);
			if ( u != v ){
				res += sqrt(w);
				p[u] = v;
				ncomp--;
			}
		}
		printf("%.2f\n", res);
	}
	return 0;
}

