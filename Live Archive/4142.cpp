#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN = 10005;

typedef pair<int,int> pii;
typedef pair<int, pii> event;

char name[MAXN][32];
event E[3*MAXN];
int res[MAXN];

void process(){
	int N, M, Q;
	int l, r, p;
	int type;
	int idx;

	scanf("%d", &N);
	M = 0;
	for ( int i=0; i < N; ++i ){
		scanf("%s %d %d", name[i], &l, &r);
		E[M++] = event( l, pii(-1, i) );
		E[M++] = event( r, pii(1, i ) );
	}
	scanf("%d", &Q);
	for ( int i=0; i < Q; ++i ){
		scanf("%d", &p);
		E[M++] = event( p, pii(0, i) );
	}
	sort( E, E + M );
	
	set<int> active;
	for ( int i=0; i < M; ++i ){
		p = E[i].first, type = E[i].second.first, idx = E[i].second.second;
		switch (type){
			case 0:
					if ( active.empty() || active.size() > 1 )
						res[idx] = -1;
					else 
						res[idx] = *active.begin();
					break;
			case 1:
					active.erase( idx );
					break;
			case -1:
					active.insert( idx );
					break;
		}
	}
	for ( int i=0; i < Q; ++i )
		if ( res[i] < 0 ) puts("UNDETERMINED");
		else puts(name[ res[i] ]);
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){ 
		process();
		if ( runs ) puts("");
	}
	return 0;
}
