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
const int MAX = 20;
int sum;
int s[ MAX ];
int v[ MAX ];
int n;
int mid;
int size;
int type;
int sol[MAX];
int p[MAX];
queue<int> q[3];

void parse( string &line ){
	int sgn = 1;
	string c;
	sum = n = 0;
	stringstream in(line);
	while ( in >> c ){
		if ( c == "+" )
			sgn = 1;
		else if ( c == "-" )
			sgn = -1;
		else if ( c == "=" )
			sgn = 1, mid = n;
		else {
			sscanf(c.c_str(),"%d",v + n);
			s[n] = sgn;
			sum += v[n];
			n++;
		}
	}

	while ( q[0].size() ) q[0].pop();
	while ( q[2].size() ) q[2].pop();

	//Changing sign of terms after =
	for ( int i=mid; i < n ; i++ )
		s[i] *= -1;
	//Counting number of positive signs
	int cnt = 0;
	for ( int  i=0; i < n ; ++i ){
		if ( s[i] > 0 ) cnt++;
		q[ s[i] + 1 ].push( i );
	}
		
	if ( cnt <= (n - cnt) ){
		size = cnt;
		type = 1;
	}
	else {
		size = n - cnt;
		type = -1;
	}
}

bool backtrack( int pos , int cnt , int val ){
	if ( cnt >= size )
		return val == 0;
	
	if ( pos < 0 ) return false;

	int last = v[pos] + 1;//init value 
	
	for ( int i=pos; i >= 0 ; --i ){
		if ( p[i] < val ) return false;
		if ( val < v[i] || last == v[i] ) continue;
		sol[ cnt ] = i;
		last = v[i];
		if ( backtrack( i - 1 , cnt + 1 , val - v[i] ) )
			return true;
	}
	return false;
}

int main(){
	string line;
	int res[MAX];
	bool used[MAX];

	while ( getline( cin , line ) ){

		parse(line);

		if ( sum & 1 ){ puts("no solution"); continue; }
		
		sort( v , v + n );
		p[0] = v[0];
		used[0] = false;
		for ( int i=1; i < n ; i++ ){
			p[i] = p[i-1] + v[i];
			used[i] = false;
		}

		if ( backtrack( n - 1 , 0 , sum >> 1 ) ){

			int idx;
			for ( int i=0; i < size; ++i ){
				idx = q[ type + 1 ].front();
				q[type + 1].pop();
				res[ idx ] = v[ sol[i] ];
				used[ sol[i] ] = true;
			}
			
			for ( int i=0; i < n; ++i )
				if ( !used[i] ){
					idx = q[1 - type].front();
					q[1 - type].pop();
					res[idx] = v[i];
				}

			for ( int i=mid ; i<n ; ++i )
				s[i] *= -1;

			for ( int i=0; i < n; ++i ){
				if ( i > 0 ){
					if (i==mid) printf(" = ");
					else if ( s[i] > 0 ) printf(" + ");
					else printf(" - ");
				}
				printf("%d",res[i]);
			}
			puts("");
		}
		else {
			puts("no solution");
		}

	}

	return 0;
}

