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

struct task{
	int left,right,;
	int span;
	task(){}
	task(int L,int R, int S){ left = L; right = R; span = S; }
	bool operator>( const task &t ) const {
		return left > t.left;
	}
};

int main(){

	int n,m;
	int l,r,s;
	while ( scanf("%d %d",&n,&m) && ( m || n ) ){
		
		priority_queue< task , vector<task> , greater<task> > q;
		
		for ( int i=0; i < n; ++i ){
			scanf("%d %d",&l,&r);
			q.push( task(l,r,-1) );
		}
		for (int i=0; i < m; ++i){
			scanf("%d %d %d",&l,&r,&s);
			q.push( task(l,r,s) );
		}
		int left = 0;
		bool ok = true;
		task t;
		while ( !q.empty() && ok && left <= 1000000 ){
			t = q.top(); q.pop();
			if ( t.left < left ) ok = false;
			else {
				left = t.right;
				if ( t.span > -1 ){
					q.push( task( t.left + t.span , t.right + t.span, t.span ) );
				}
			}
		}
		if ( ok ) puts("NO CONFLICT");
		else puts("CONFLICT");
	}
	return 0;
}

