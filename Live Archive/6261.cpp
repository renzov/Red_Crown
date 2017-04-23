#include<cstdio>
#include<algorithm>
#include<climits>
#include<set>
#include<map>
using namespace std;

typedef pair< int, pair<int,int> > event;


const int MAXN = 200005;
int N, K;

int X[MAXN];
int Y[MAXN];
int C[MAXN];
int TX[MAXN];
int TC[MAXN];
int t[444444];
set<int> S[MAXN];
event E[MAXN];

void add(int x, int v) { for(int i=x;i<=N;i+=i&-i) t[i] += v; }
int sum(int a) { 
	int ans=0;
	for(int i=a;i;i-=i&-i) ans += t[i];
	return ans; 
}
int sum(int a, int b) { 
	if(a>b) return 0;
	return sum(b) - sum(a-1); 
}

int main(){
	int runs;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &K);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d %d", X+i, Y+i, C+i);
			TX[ i ] = X[i], TC[i] = C[i];
		}
		sort( TX, TX + N );
		sort( TC, TC + N );
		
		int M = unique( TX, TX + N ) - TX;
		int c = unique( TC, TC + N ) - TC;
		// remap the X coord and C.
		for ( int i=0; i < N; ++i ){ 
			X[i] = lower_bound( TX, TX + M, X[i] ) - TX;
			X[i]++;
			C[i] = lower_bound( TC, TC + c, C[i] ) - TC; 
			E[i].first = Y[i], E[i].second.first = X[i], E[i].second.second = C[i];
		}
		M++;
		// dummy entries in set
		for ( int i=0; i < c; ++i ) S[i].insert(0), S[i].insert(M); 

		sort( E, E + N );
		
		for(int i=1; i <= M;i++) t[i] = 0;

		int res = 0;
		int a, b;
		event e;
		set<int>::iterator it, prev;
		for ( int i=0; i < N; ){
			int j = i;
			while ( j < N && E[i].first == E[j].first ){
				// process
				e = E[j];
				it = S[e.second.second].lower_bound( e.second.first );
				if ( *it != e.second.first ){ 
					b = *it - 1; // Consider before b
					it--;
					a = *it + 1;	// a < X[idx]
					if ( a <= b ) res = max( res , sum( a, b ) );
				}
				j++;
			}
			// update
			for ( int k=i; k < j; ++k ){
				e = E[k];
				add( e.second.first, 1 );
				S[ e.second.second ].insert( e.second.first );
			}
			i = j;
		}
		
		for ( int i=0; i < c; ++i ){
			for ( it = S[i].begin(), prev=it++; it != S[i].end(); ++it ){
				if ( (*prev + 1) <= (*it - 1) ) res = max( res, sum( *prev + 1, *it - 1 ) );
				prev = it;
			}
		}
		printf("%d\n", res);
		if ( runs ){
			for ( int i=0; i < c; ++i ) S[i].clear();
		}
	}
	return 0;
}
