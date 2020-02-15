#include<cstdio>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

const int MAXN = 50005;

int N;
int X1[MAXN];
int X2[MAXN];
int Y1[MAXN];
int Y2[MAXN];
int ord[MAXN];
int f[MAXN];
long long len[MAXN];

inline int find_set( const int &x ){ return x == f[x]? x:( f[x] = find_set( f[x] ) ); }

inline bool cmp( const int &i, const int &j ){
	return ( X1[i] != X1[j] )? (X1[i] < X1[j]):(Y1[i] < Y1[j]); 
} 

void join_rectangles(){
	
}

void process(){
	int w, h;
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", X1+i, Y1+i, &w, &h);
		X2[i] = X1[i] + w;
		Y2[i] = Y1[i] + h;
		ord[i] = i;	// for sorting
		f[i] = i;	// for union-find
	}
	// Join the rectangles by X
	sort( ord, ord + N, cmp );
	join_rectangles();
	// Join the rectangles by Y
	for ( int i=0; i < N; ++i ){
		swap( X1[i], Y1[i] );
		swap( X2[i], Y2[i] );
	}
	sort( ord, ord + N, cmp );
	join_rectangles();
	for ( int i=0; i < N; ++i )
		len[ find_set(i) ] += (X2[i] - X1[i])*(Y2[i] - Y1[i]);
	printf("%lld\n", *max_element( len, len + N ));
	// clean the data structures
	for ( int i=0; i < N; ++i )
		len[i] = 0LL;
}

int main(){
	while ( scanf("%d", &N) == 1 ) process();
	return 0;
}
