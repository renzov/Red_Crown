#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;

const int MAXN = 250005;
point P[MAXN];
int ord[MAXN];
int l, b, e, dir;
int N;
char C1,C2;
bool cmp( const int &i, const int &j ){
	return P[i] < P[j];
}

void sweep(){
	int l1, b1, e1;
	for ( int i=0; i < (N-1); ++i ){
		point &A = P[ord[i]];
		point &B = P[ord[i+1]];
		if ( A.X == B.X && abs(ord[i] - ord[i+1]) > 1 ){
			l1 = B.Y - A.Y; 
			b1 = min(ord[i+1], ord[i]); 
			e1 = max(ord[i], ord[i+1]);
			if ( l1 < l ){
				l = l1, b = b1, e = e1, dir = ( b == ord[i] )? C1:C2;
			}
			else if ( l1 == l && b1 < b ){
				b = b1, e = e1, dir = ( b == ord[i] )? C1:C2;				
			}
			else if ( l1 == l &&  b1 == b &&  e1 > e ){
				e = e1, dir = ( b == ord[i] )? C1:C2;					
			}
		}
	}
}

int main(){
	int runs;
	char d;
	int curX, curY;
	P[0] = point(0,0);
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		curX = curY = 0;
		P[0].X = P[0].Y = 0;
		ord[0] = 0;
		for ( int i=1; i <= N ; ++i ){
			ord[i] = i;
			scanf(" %c", &d);
			switch (d){
				case 'N' : P[i].X = curX, P[i].Y = ++curY; break;
				case 'S' : P[i].X = curX, P[i].Y = --curY; break;
				case 'E' : P[i].Y = curY, P[i].X = ++curX; break;
				case 'W' : P[i].Y = curY, P[i].X = --curX; break;
			}
		}
		N++;
		l = INT_MAX;
		C1 = 'N', C2 = 'S';
		sort( ord, ord + N , cmp );
		sweep();
		for ( int i=0; i < N; ++i ) swap( P[i].X, P[i].Y );
		C1 = 'E', C2 = 'W';
		sort( ord, ord + N, cmp);
		sweep();
		printf("%d %d %d %c\n", l, b, e, dir);
		if ( runs ) puts("");
	}
	return 0;
}
