#include<cstdio>
#include<algorithm>
#include<cmath>
#include<deque>
using namespace std;
const int MAXN = 100005;
const double EPS = 1e-6;
int N, L;
char B[MAXN];
int A[MAXN];
double S[MAXN];
double mini[MAXN];
deque<double> val;
deque<int> idx;

double cmp( const double &a, const double &b ){
	if ( fabs( a - b ) < EPS ) return 0;
	return a < b? -1:1;
}

int binsearch( const double &s ){
	if ( val.empty() || cmp( s, val.front() ) < 0 ) return -1;
	if ( cmp( s, val.back() ) >= 0 ) return idx.back();
	int l = 0;
	int r = (int)val.size() - 1;
	int m;
	while ( r - l > 1 ){
		m = (l + r) >> 1;
		if ( cmp( s, val[m] ) >= 0 ) l = m;
		else r = m;
	}
	return idx[l];
}

void print_ans( const double &X ){
	for ( int i=1; i <= N; ++i ){
		S[i] = S[i - 1];
		S[i] += ( A[i] - X );
	}
	val.push_back( 0 ), idx.push_back( 0 );
	int bestR = N, bestL = 0;
	for ( int i=L; i <= N; ++i ){
		// Search for best idx
		int l = binsearch( S[i] );
		if ( l >= 0  ){
			if ( i - l < bestR - bestL ){
				bestL = l, bestR = i;
			}
			else if ( ((i - l) == (bestR - bestL)) && bestL > l ){
				bestL = l, bestR = i;
			}
		}
		while ( !val.empty() && cmp( S[i + 1 - L], val.back() ) <= 0 )
			val.pop_back(), idx.pop_back();
		val.push_back( S[i + 1 - L] ), idx.push_back( i + 1 - L );
	}
	printf("%d %d\n", bestL + 1, bestR);
}

bool possible( const double &X ){
	mini[0] = S[0] = 0;
	for ( int i=1; i <= N; ++i ){
		S[i] = S[i - 1];
		S[i] += ( A[i] - X );
		mini[i] = min( mini[i - 1], S[i] );
	}
	for ( int i=L; i <= N; ++i ){
		if ( cmp(S[i], mini[i - L]) >= 0 ) 
			return true;
	}
	return false;
}

void process(){
	scanf("%d %d", &N, &L);
	scanf("%s", B);
	for ( int i=1; i <= N; ++i )
		A[i] = B[i - 1] - '0';
	
	double l = 0;
	double r = 1.01;
	double m;
	
	for ( int i=0; i < 30; ++i ){
		m = ( l + r ) / 2;
		if ( possible( m ) ){
			l = m;
		}
		else { 
			r = m;
		}
	}
	print_ans( l );
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		// clean memory	
		while ( !idx.empty() ) idx.pop_back();
		while ( !val.empty() ) val.pop_back();
	}
	return 0;
}
