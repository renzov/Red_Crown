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

const int MAXN = 100005;
int ord[MAXN];
int day[MAXN];
int cow[MAXN];
int eps[MAXN];

bool cmp( const int &i, const int &j ){
	return day[i] < day[j];
}

map< int, int > cnt;
map< int, int > val;
set< int > active;

int main(){
	freopen ("measurement.out","w",stdout);
	freopen ("measurement.in","r",stdin);		
	int N; 
	int d, c, diff;
	int G;

	scanf("%d %d", &N, &G);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d", day + i, cow + i, eps + i);
		ord[i] = i;
	}
	sort( ord, ord + N, cmp );

	// Initially you have 10^9 cows, all with value G
	cnt[ G ] = 1000000000;
	active.insert(G);
	int best = G;
	
	int newBest;
	int res = 0;
	int lastVal, newVal;
	int idx;
	int prevcnt;
	bool wasTop;
	bool isTop;

	for ( int i=0; i < N; ++i ){
		// get the number of cows that attain the maxima
		prevcnt = cnt[best];
		// get the id of the operation
		idx = ord[i];
		// look if you have not seen that cow previously
		if ( val.find( cow[idx] ) == val.end() ){
			val[ cow[ idx ] ] = G;
		}
		
		lastVal = val[ cow[idx] ];
		newVal = lastVal + eps[idx];
		wasTop = lastVal == best;
		// apply the changes to the count of cows of a certain value, and the value 
		// of cow being inspected
		val[ cow[idx] ] = newVal;
		cnt[newVal]++, cnt[lastVal]--;
		// Look if you do not have cows with previous value
		if ( cnt[lastVal] == 0 ) active.erase( lastVal );
		if ( active.find(newVal) == active.end() ) active.insert(newVal);
		// look if you have a new maxima
		if ( newVal > best ){
			newBest = newVal;
		}
		else if ( active.find(best) == active.end() ){ // or the previous maximum is no longer
			newBest = *active.rbegin();
		}
		else { // remains the same
			newBest = best;
		}
		isTop = newVal == newBest;
		// look if you need to change the chart
		if ( wasTop ){ 
			if ( !isTop || cnt[newBest] != prevcnt ) res++;
		}
		else if ( isTop ){
			res++;
		}
		best = newBest;
	}
	printf("%d\n", res);

	return 0;
}

