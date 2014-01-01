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
#include <numeric>
#include <list>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
typedef pair< double , double > pdd;

const double EPS = 1e-8;

bool intersect( pdd &a , pdd &b ){
	return ( (a.second + EPS) > b.first );
}

void merge( list<pdd> &I ){

	I.sort();

	list<pdd>::iterator d = I.begin();
	list<pdd>::iterator b = d++;
	list<pdd>::iterator tmp;

	while ( b != I.end() ){
		
		while ( d != I.end() && intersect( *b , *d ) ){
				b->second = max(d->second,b->second);
				tmp = d;
				d++;
				I.erase( tmp );
		}
		b++; d++;
	}
}

int main(){
	
	int runs;
	double X;
	int N;
	double f[10];
	double M;
	pdd losser;
	scanf("%d",&runs);

	while ( runs-- ){
		M = -1;
		scanf("%lf %d",&X,&N);

		list<pdd> inter; 
		
		for ( int i=0; i < N; ++i ){
			scanf("%lf",f+i);
			if ( M < f[i] ) M = f[i];
			inter.push_back( make_pair( 1.0  , 1.0 / f[i] ) );
		}
		losser.second = 0.0;

		while ( losser.second < X ){
			merge( inter );
			losser.first = inter.front().second;
			losser.second = losser.first / M;

			inter.pop_front();

			if ( inter.size() ){
				losser.second = min( losser.second , inter.front().first );
			}

			for ( int i=0;  i<N; ++i )
				inter.push_back( make_pair( losser.first / f[i] , losser.second / f[i] ) );

		}
		if ( X < losser.first ) puts("Nils");
		else puts("Mikael");
	}
	return 0;
}

