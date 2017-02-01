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
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 105;
int N;

int A[MAXN];
int W[MAXN];
vector<int> T[MAXN];
pii C[MAXN];

pii dfs( int u, int p ){
	pii res, tmp;
	priority_queue< pii > q;
	int v;

	for ( int i=0; i < T[u].size(); ++i ){
		v = T[u][i];
		if ( v != p ){
			tmp = dfs( v, u );
			q.push( mp( tmp.first - tmp.second, v ) );
		}
	}

	res.first = A[u];
	res.second = W[u];
	int act = A[u] - W[u];

	while ( !q.empty() ){
		tmp = q.top(); q.pop();
		v = tmp.second;
		res.second += C[v].second;
		if ( act < C[v].first ){
			res.first += (C[v].first - act);
			act = C[v].first;
		}
		act -= C[v].second;
	}
	return (C[u] = res);
}

int main(){
	int cases = 0;
	int a, m, g;
	int u, v;
	while ( scanf("%d",&N) && N ){
		cases++;
		for ( int i=0; i < N; ++i ){
			T[i].clear();
			scanf("%d %d %d", &a, &m, &g);
			A[i] = max( a , m + g );
			W[i] = m + g;
		}
		for ( int i=1; i < N; ++i ){
			scanf("%d %d", &u, &v);
			u--,v--;
			T[u].push_back(v);
			T[v].push_back(u);
		}

		int res = INT_MAX;
		pii temp;
		for ( int i=0; i < N; ++i ){
			temp = dfs(i, -1);
			if ( temp.first < res ) res = temp.first;
		}
		printf("Case %d: %d\n", cases, res);
	}
	return 0;
}

