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

int N;
int indeg[MAXN];
int nxt[MAXN];
bool lowered[MAXN] = {0};

bool dfs( const int &u ){
	indeg[u] = 0;	
	if ( indeg[ nxt[u] ] ) return dfs( nxt[u] ) | lowered[u];
	return lowered[u];
}

int main(){
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", nxt + i);
		nxt[i]--;
		indeg[ nxt[i] ]++;
	}

	int leaves = 0;
	queue<int> q;
	for ( int i=0; i < N; ++i ) 
		if ( indeg[i] == 0 ) q.push(i), leaves++;
	int nonCycle = 0;
	int u, v;

	int formerCycles = 0;
	while ( !q.empty() ){
		nonCycle++;
		u = q.front(); q.pop();
		v = nxt[u];
		indeg[v]--;
		lowered[v] = true;
		if ( indeg[v] == 0 ) q.push(v);
	}
	int numCycles = 0;
	for ( int i=0; i < N; ++i ){
		if ( indeg[i] > 0 ){ 
			if ( !dfs( i ) ){ 
				formerCycles++;
			}
			numCycles++;
		}
	}
	int mini = leaves + formerCycles;
	int maxi = nonCycle + numCycles;
	printf("%d %d\n", mini, maxi);
	return 0;
}
//**  REMEMBER ALL YOUR WAs, the way wrong case analysis lead to failure  **//

