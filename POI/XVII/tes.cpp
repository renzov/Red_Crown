#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;
set<pii> S;

int main(){
	int a;
	int M, N, K;
	
	scanf("%d", &M);
	for ( int i=0; i < M; ++i ){
		scanf("%d", &a);
		S.insert( pii(a, i) );
	}
	scanf("%d", &N);
	while ( N-- ){
		scanf("%d", &K);
		int last = -1;
		bool ok = true;
		set<pii>::iterator it;
		while ( K-- ){
			scanf("%d", &a);
			if ( ok ){
				it = S.lower_bound( pii(a, last + 1) );
				if ( it == S.end() || it->second <= last || it->first != a ) ok = false;
				else last = it->second;
			}
		}
		if ( ok ) puts("TAK");
		else puts("NIE");
	}
	return 0;
}
