#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define X first
#define Y second
const long double EPS = 1e-10;
typedef pair<long double, long double> point;
typedef pair<point, int> item;

int sign( const long double &x ){
	return (x > EPS) - (x < -EPS);
}

int cmp( const point &A, const point &B ){
	int sy = sign( B.Y - A.Y );
	if ( sy != 0 ) return sy;
	return sign( B.X - A.X );
}

bool cmp2( const item &A, const item &B ){
	int c = cmp( A.first , B.first );
	if ( c != 0 ) return c < 0;
	return A.second > B.second;
}

bool operator<( const point &A, const point &B ){
	if ( fabs(A.X - B.X) < EPS ) return fabs(A.Y - B.Y) > EPS && A.Y < B.Y;
	return A.X < B.X;
}

point operator+( const point &A, const point &B ){
	return point( A.X + B.X , A.Y + B.Y );
}

point operator-( const point &A, const point &B ){
	return point( A.X - B.X, A.Y - B.Y ); 
}

long double operator*(const point &A, const point &B){
	return A.X * B.X + A.Y * B.Y;
}

long double operator^( const point &A, const point &B ){
	return A.X * B.Y - B.X * A.Y;
}

long double dist( const point &A, const point &B ){
	return sqrtl( (A.X - B.X)*(A.X - B.X) + (A.Y - B.Y)*(A.Y - B.Y) );
}

point ort( const point &A ){
	return point( -A.Y, A.X );
}

struct Line{
	point N;	// N = (A, B) in equation AX + BY + C = 0
	point O;
	long double C;

	Line( const point &D, const point &P1 ){
		N = D, O = P1;
		C = -(D * P1);
	}
	
	point intersection( const Line &L ){
		long double den = N ^ L.N;
		long double x = ( point( -C, N.Y ) ^ point( -L.C, L.N.Y ) ) / den;
		long double y = ( point( N.X, -C ) ^ point( L.N.X, -L.C ) ) / den;
		return point( x, y );
	}

	bool belongs( const point &A ){
		return fabs( (N * A) + C ) < EPS;	// point belongs to line
	}
};

vector<point> read_polygon(const int &N){
	vector<point> P(N);
	for ( int i = 0; i < N; ++i )
		cin >> P[i].X >> P[i].Y;
	// Find the lowest left point
	int idx = 0;
	for ( int i = 1; i < N; ++i )
		if ( P[i] < P[idx] ) idx = i;
	// make the lowest left point the beginning of the polygon
	rotate( P.begin(), P.begin() + idx, P.end() );
	P.push_back(P[0]);
	// Remove 180 degree angles
	vector<point> S;
	S.push_back( P[0] );
	S.push_back( P[1] );
	int s = 2;
	for ( int i = 2; i <= N; ++i ){
		while ( (int)S.size() > 1 && fabs( (P[i] - S[s - 1]) ^ (S[s - 1] - S[s - 2]) ) < EPS ){
			s--;
			S.pop_back();
		}
		S.push_back( P[i] );
		s++;
	}
	S.pop_back();
	s--;
	// Check if polygon is ccw - otherwise reverse
	if ( sign( (S[1] - S[0]) ^ (S[2] - S[1]) ) < 0 )
		reverse( S.begin(), S.end() );
	return S;
}

int main(){
	int N, M;

	cin >> N >> M;
	vector<point> P = read_polygon(N);
	N = P.size();

	point A, B, D;
	int prev, act, nxt;
	int si, sj, sk;
 
 	cout << setprecision(11) << fixed;
	while ( M-- ){
		cin >> A.X >> A.Y >> B.X >> B.Y;
		if ( cmp(A, B) > 0 ) 
			swap(A,B);
		// a ray comes from +inf with direction D
		D = B - A;
		Line L( ort(D), A );
		vector< item > R;		
		// First, find proper intersections of line segments and line
		for ( act = 0; act < N; ++act ){
			nxt = (act + 1) % N;
			si = sign( D ^ (P[act] - A) );
			sj = sign( D ^ (P[nxt] - A) );
			if ( si * sj == -1 ){
				Line L2( ort(P[nxt] - P[act]), P[act] );
				R.push_back( item( L.intersection(L2), si ) );
			}
		}
		// Check vertices of polygon intersecting with line
		prev = N - 1;
		for ( act = 0 ; act < N; ++act ){
			nxt = (act + 1) % N;
			if ( L.belongs( P[act] ) ){
				si = sign( D ^ (P[prev] - A) );
				sj = sign( D ^ (P[nxt] - A) );
				if ( si * sj == -1 ){
					R.push_back( item( P[act], si ) );
				}
				else if ( si == 0 ){
					sk = -sign( D * (P[act] - P[prev]) );
					R.push_back( item( P[act], sk ) );
				}
				else if ( sj == 0 ){
					sk = sign( D * (P[nxt] - P[act]) );
					R.push_back( item( P[act], sk ) );
				}
			}
			prev = act;
		}
		sort( R.begin(), R.end(), cmp2 );
		int wn = -1;
		long double res = 0.0;
		for ( int i = 0; i < (int)R.size(); ++i ){
			if ( wn >= 0 ) res += dist( R[i - 1].first, R[i].first );	
			wn = R[i].second;
		}
		cout << res << endl;
	}
	return 0;
}
