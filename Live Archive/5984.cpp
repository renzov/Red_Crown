#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

int area2( const point &A, const point &B, const point &C ){
	return (B.X - A.X)*(C.Y - A.Y) - (C.X - A.X)*(B.Y - A.Y); 
}

int dist2( const point &A, const point &B ){
	return (A.X - B.X)*(A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y);
}

struct fig {
	char t;
	int r;
	point P[5];
	bool inside( const point &p ){
		if ( t == 'T' ){
			for ( int i=0; i < 3; ++i ) 
				if ( area2( P[i], P[i+1], p ) < 0 ) return false;
			return true;
		}
		else if ( t == 'S' ){
			for ( int i=0; i < 4; ++i ) 
				if ( area2( P[i], P[i+1], p ) < 0 ) return false;
			return true;
		}
		// its circle
		return dist2( P[0] , p ) <= r*r;
	}
};

fig F[55];

int main(){
	int runs;
	int N;
	int l;
	int Xmin, Xmax, Ymin, Ymax;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		Xmin = Ymin = INT_MAX;
		Xmax = Ymax = -INT_MAX;
		for ( int i=0; i < N; ++i ){
			scanf(" %c", &F[i].t);
			// Reading the figures and calculating the bounds
			switch ( F[i].t ){
				case 'T':	for ( int j=0; j < 3; ++j ){
								scanf("%d %d", &F[i].P[j].X, &F[i].P[j].Y);
								if ( Xmin > F[i].P[j].X ) Xmin = F[i].P[j].X;
								if ( Xmax < F[i].P[j].X ) Xmax = F[i].P[j].X;
								if ( Ymin > F[i].P[j].Y ) Ymin = F[i].P[j].Y;
								if ( Ymax < F[i].P[j].Y ) Ymax = F[i].P[j].Y;
							}
							if ( area2( F[i].P[0], F[i].P[1], F[i].P[2] ) < 0 ){
								swap( F[i].P[1], F[i].P[2] );
							}
							F[i].P[3] = F[i].P[0];
							break;
				case 'C':	scanf("%d %d %d", &F[i].P[0].X, &F[i].P[0].Y, &F[i].r);
							l = F[i].r;
							F[i].P[1] = point( F[i].P[0].X + l, F[i].P[0].Y );
							F[i].P[2] = point( F[i].P[0].X, F[i].P[0].Y + l);
							F[i].P[3] = point( F[i].P[0].X - l, F[i].P[0].Y);
							F[i].P[4] = point( F[i].P[0].X, F[i].P[0].Y - l);
							for ( int j=1; j < 5; ++j ){
								if ( Xmin > F[i].P[j].X ) Xmin = F[i].P[j].X;
								if ( Xmax < F[i].P[j].X ) Xmax = F[i].P[j].X;
								if ( Ymin > F[i].P[j].Y ) Ymin = F[i].P[j].Y;
								if ( Ymax < F[i].P[j].Y ) Ymax = F[i].P[j].Y;
							}
							break;
				case 'S':	scanf("%d %d %d", &F[i].P[0].X, &F[i].P[0].Y, &l);
							F[i].P[1] = point( F[i].P[0].X + l, F[i].P[0].Y );
							F[i].P[2] = point( F[i].P[0].X + l, F[i].P[0].Y + l);
							F[i].P[3] = point( F[i].P[0].X, F[i].P[0].Y + l);
							for ( int j=0; j < 4; ++j ){
								if ( Xmin > F[i].P[j].X ) Xmin = F[i].P[j].X;
								if ( Xmax < F[i].P[j].X ) Xmax = F[i].P[j].X;
								if ( Ymin > F[i].P[j].Y ) Ymin = F[i].P[j].Y;
								if ( Ymax < F[i].P[j].Y ) Ymax = F[i].P[j].Y;
							}
							F[i].P[4] = F[i].P[0];
							break;
			}
		}
		int res = 0;
		bool in;
		point p;
		for ( int x = Xmin; x <= Xmax; ++x )
			for ( int y=Ymin; y <= Ymax; ++y ){
				in = false;
				p.X = x, p.Y = y;
				for ( int i=0; i < N && !in; ++i ){
					if ( F[i].inside( p ) ) in = true;
				}
				if ( in ) res++;
			}
		printf("%d\n", res);
	}
	return 0;
}

