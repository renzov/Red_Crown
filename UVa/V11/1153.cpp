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

const int MAXN = 800005;
pair<int,int> J[MAXN];

int main(){

	int N;
	int runs;
	
	scanf("%d",&runs);

	while (runs--){
		priority_queue< int > q;
		scanf("%d",&N);
		for ( int i=0; i < N; ++i )
			scanf("%d %d",&J[i].second, &J[i].first);
		sort(J,J+N);
		int T = 0;
		for ( int i=0; i < N ; ++i ){
			if ( (T + J[i].second) > J[i].first ){
				if ( !q.empty() && q.top() > J[i].second ){
					T = T - q.top() + J[i].second;
					q.pop();
					q.push( J[i].second );
				}
			}
			else {
				q.push( J[i].second );
				T += J[i].second;
			}
		}
		printf("%d\n",(int) q.size());
		if (runs){ 
			puts("");
		}
	}
	return 0;
}

