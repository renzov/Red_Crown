#include<cstdio>
#include<algorithm>
#include<set>
#include<vector>
#include<climits>
#include<queue>
using namespace std;
const int MAXN = 100005;
typedef pair<int,int> pii;

int N, M; 
vector<int> V[MAXN];
vector<pii> insertEvent[MAXN];
vector<pii> removeEvent[MAXN];
int res[MAXN];
int left[MAXN];

int f[MAXN];
set<pii> S;

void process(){
	int X, e;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &X);
		while ( X-- ){
			scanf("%d", &e);
			e--;
			V[i].push_back(e);
		}
	}

	int right = 0;
	int cntZero = M;
	int len, end, beg;
	
	for ( int i=0; i < N; ++i ){
		res[i] = INT_MAX;
		//	find the window that starts at i and covers M distinct elements
		while ( right < N && cntZero > 0 ){
			for ( int j=0; j < (int)V[right].size(); ++j ){
				e = V[right][j];
				if ( !f[e] ) cntZero--;
				f[e]++;
			}
			right++;
		}
		//	Add a new solution if found
		if ( !cntZero ){
			len = right - i;
			end = right - 1;
			beg = i;
			insertEvent[i].push_back( pii( len, beg ) );
			removeEvent[ right ].push_back( pii( len, beg ) );
		}
		//	remove the elements at V[i]
		for ( int j=0; j < (int)V[i].size(); ++j ){
			e = V[i][j];
			f[e]--;
			if ( !f[e] ) cntZero++;
		}
	}

	for ( int i=0; i < N; ++i ){
		
		for ( int j=0; j < (int)removeEvent[i].size(); ++j )
			S.erase( removeEvent[i][j] );
		for ( int j=0; j < (int)insertEvent[i].size(); ++j )
			S.insert( insertEvent[i][j] );
		
		if ( i ){
			res[i] = res[i - 1] + 1, left[i] = left[i - 1];
		}	
		if ( !S.empty() ){
			len = S.begin()->first;
			beg = S.begin()->second;
			if ( len < res[i] ){
				res[i] = len, left[i] = beg;
			}
			else if ( len == res[i] && beg < left[i] ){
				res[i] = len, left[i] = beg;	
			}
		}
	}

	for ( int i=0; i < N; ++i )
		printf("%d %d\n", left[i] + 1, left[i] + res[i]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		process();
		if ( runs ){ 
			for ( int i=0; i <= N; ++i ){ 
				V[i].clear();
				insertEvent[i].clear();
				removeEvent[i].clear();
				S.clear();
			}
		}
	}
	return 0;
}
