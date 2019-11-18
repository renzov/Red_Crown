#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

#define X first
#define Y second

typedef pair<int,int> event;
typedef pair<long long, long long> point;
const int MAXK = 10005;

int S;
int K;
int W;
point O;
point base;
bool in[4*MAXK];
point P[4*MAXK];
event E[4*MAXK];

long long area2( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y); 
}

bool left( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y) > 0LL; 
}

struct Compare {
	static point ref;
	bool operator()( const int &a, const int &b ){
		return area2( P[a], P[a + 1], ref ) < area2( P[b], P[b + 1], ref );
	}
};
point Compare::ref;

set<int,Compare> Seg;
set<int,Compare>::iterator pointer[4*MAXK];

bool intersect( const point &A, const point &B, const point &C, const point &D ){
	// Returns true if segment AB intersects CD
	return 	( left(A, B, C) xor left(A, B, D) ) and 
			( left(C, D, A) xor left(C, D, B) );
}


bool cmp( const event &a, const event &b ){
	int i = a.first, j = b.first;
	bool sideA = area2( O, base, P[i] ) >= 0;
	bool sideB = area2( O, base, P[j] ) >= 0;
	if ( sideA != sideB ) return sideA;
	return area2( O, P[i], P[j] ) >= 0LL;
}

int sweep( const int &M ){
	int res = 0;
	int idx;
	int minS;
	for ( int i=0; i < M; ++i ){
		Compare::ref = P[ E[i].first ];
		switch (E[i].second) {
			case -1:	idx = E[i].first;
						if ( idx & 1 ) idx--;
						if ( in[idx] ){
							Seg.erase( pointer[idx] );
							pointer[idx] = Seg.end();
							in[idx] = false;
						}
						break;

			case 1:		idx = E[i].first;
						if ( idx & 1 ) idx--;
						in[idx] = true;
						pointer[idx] = Seg.insert( idx ).first;
						break;

			case 0:		// Query
						if ( Seg.empty() ){
							res++;
						}
						else {
							idx = E[i].first;
							minS = *Seg.begin();
							if ( !intersect( O, P[idx], P[minS], P[minS + 1] ) )
								res++;
						}
						break;
		}
	}
	return res;
}


void process(){
	int M;

	for ( int i=2*W; i < (2*W+K); ++i )
		scanf("%lld %lld", &P[i].X, &P[i].Y);
	for ( int i=0; i < 2*W; ++i )
		scanf("%lld %lld", &P[i].X, &P[i].Y);

	for ( int i=2*W; i < (2*W + S); ++i ){
		M = 0;
		O = P[i];
		base = point( O.X + 1, O.Y );
		// Kid events
		for ( int j=2*W; j < (2*W + K); ++j )
			if ( j != i ){ 
				E[M++] = event( j , 0 );
			}

		// Order points in a segment according to the angle formed with O
		for ( int j=0; j < 2*W; j += 2 ){
			if ( !left( O, P[j] , P[j + 1] ) )
				swap( P[j], P[j + 1] );
		}
		// Wall events
		for ( int j=0; j < 2*W; j += 2 ){
				E[M++] = event( j , 1 );
				E[M++] = event( j + 1, -1 );
		}
		// sort by angle arround i-th kid
		sort( E, E + M, cmp );
		fill( in, in + 2*W, false );
		Seg.clear();
		for ( int j=0; j < 2*W; ++j ) 
			pointer[j] = Seg.end();
		sweep( M );
		printf("%d\n", sweep(M));
	}
}

int main(){
	while ( scanf("%d %d %d", &S, &K, &W) == 3 )
		process();
	return 0;
}
