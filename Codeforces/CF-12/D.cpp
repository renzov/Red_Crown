#include<cstdio>
#include<climits>
#include<algorithm>
#include<set>
using namespace std;
typedef pair<int,int> point;
typedef pair<int, point> triple;
const int MAXN = 500005;

triple P[MAXN];
set<point> S;

bool dominated( const point &p ){
	set<point>::iterator it = S.upper_bound( point(p.first, INT_MAX) );	// will get the first that has first coord. greater that p.first
	return it->second > p.second; 
}

void insert( const point &p ){
	set<point>::iterator it = S.upper_bound( point(p.first, INT_MIN) );
	set<point>::iterator elim;
	if ( it->second >= p.second ) return;	// no need to insert
	if ( it->first > p.first ) it--;
	while ( it->second <= p.second ){
		elim = it--;
		S.erase(elim);
	}
	S.insert(p);
}

int main(){
	int N;
	int x, y, z;

	scanf("%d", &N);
	for ( int i=0; i < N; i++ )
		scanf("%d", &P[i].first);
	for ( int i=0; i < N; ++i )
		scanf("%d", &P[i].second.first);
	for ( int i=0; i < N; ++i )
		scanf("%d", &P[i].second.second);
	
	sort( P, P + N );
	reverse( P, P + N );

	int res = 0;
	int m;

	S.insert( point( INT_MIN, INT_MAX ) );
	S.insert( point( INT_MAX, INT_MIN ) );

	for ( int i=0; i < N;  ){
		x = P[i].first;
		int st = i;
		for ( ; i < N && P[i].first == x; ++i ){
			if ( dominated( P[i].second ) )
				res++;
		}
		
		for ( int j=st; j < i; ++j )
			insert( P[j].second );
	}
	printf("%d\n", res);
	return 0;
}
