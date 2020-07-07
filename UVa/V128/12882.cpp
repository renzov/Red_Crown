#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int,int> pii;
typedef pair<pii,int> piii;
const int MAXN = 50005;
int N;
int area[MAXN];
int X[2*MAXN];
int Y[2*MAXN];
int f[MAXN];
priority_queue< piii, vector<piii>, greater<piii> > Start[2*MAXN];
priority_queue< piii, vector<piii>, greater<piii> > End[2*MAXN];

struct Rect {
	pii x;
	pii y;
	Rect(){}
	Rect( const int &x1, const int &x2, const int &y1, const int &y2 ){
		x.first = x1, x.second = x2;
		y.first = y1, y.second = y2;
	}
};

Rect R[MAXN];

inline int find_set( const int &x ){ return f[x] == x? x:(f[x] = find_set( f[x] )); }
void cleanup( const int &m ){
	for ( int i=0; i < m; ++i ){
		while ( !Start[i].empty() )
			Start[i].pop();
		while ( !End[i].empty() )
			End[i].pop();
	}
}

void sweep( const int &m ){
	pii A, B;
	int idxA, idxB;
	for ( int i=0; i < m; ++i ){
		while ( !Start[i].empty() && !End[i].empty() ){
			A = Start[i].top().first, idxA = Start[i].top().second;
			B = End[i].top().first, idxB = End[i].top().second;
			if ( max( A.first, B.first ) <=  min( A.second, B.second ) ){ //intersect
				idxA = find_set( idxA );
				idxB = find_set( idxB );
				if ( idxA != idxB ){
					f[ idxA ] = idxB;
					area[ idxB ] += area[ idxA ];
				}
			}
			if ( B.second <= A.second ) End[i].pop();
			else Start[i].pop();
		}
	}
}

void process(){
	int x, y, w, h;
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", &x, &y, &w, &h);
		X[2*i] = x, X[2*i + 1] = x + w;
		Y[2*i] = y, Y[2*i + 1] = y + h;
		R[i] = Rect( x, x + w, y, y + h );
		area[i] = w * h;
	}
	sort( X, X + 2*N );
	int mx = unique( X, X + 2*N ) - X;
	sort( Y, Y + 2*N );
	int my = unique( Y, Y + 2*N ) - Y;

	for ( int i=0; i < N; ++i ){
		x = R[i].x.first;
		R[i].x.first = lower_bound( X , X + mx, x ) - X;
		x = R[i].x.second;
		R[i].x.second = lower_bound( X, X + mx, x ) - X;
		y = R[i].y.first;
		R[i].y.first = lower_bound( Y, Y + my, y ) - Y;
		y = R[i].y.second;
		R[i].y.second = lower_bound( Y, Y + my, y ) - Y;
	}
	// initialize the sets
	for ( int i=0; i < N; ++i ) f[i] = i;
	// X - axis
	for ( int i=0; i < N; ++i ){
		x = R[i].x.first;
		Start[x].push( piii(R[i].y, i) );
		x = R[i].x.second;
		End[x].push( piii(R[i].y, i) );
	}
	sweep( mx );
	cleanup( mx );
	// Y - axis
	for ( int i=0; i < N; ++i ){
		y = R[i].y.first;
		Start[y].push( piii( R[i].x, i) );
		y = R[i].y.second;
		End[y].push( piii( R[i].x, i) );
	}
	sweep( my );
	cleanup( my );

	int res = 0;
	for ( int i=0; i < N; ++i ){
		res = max( res, area[ find_set(i) ] );
	}
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}
