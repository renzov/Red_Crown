#include<cstdio>
#include<set>
#include<map>
using namespace std;
typedef pair<int,int> pii;
set<pii> active;
map<int,int> W;

int query( const int &idx ){
	if ( active.size() == 1 ) return 1;
	
	int w = W[idx];
	int res = 0;
	active.erase( pii( w, idx ) );
	set<pii>::iterator it = active.begin();
	
	int sum = 0;

	if ( it->first <= w ){
		res++;
		sum += it->first;
		it++;
		while ( it != active.end() && (it->first + sum) <= w ){
			res++;
			sum += it->first;
			it = active.lower_bound( pii( sum, -1 ) );
		}
	}
	sum += w;
	res++;
	it = active.lower_bound( pii(sum, -1) );
	while ( it != active.end() ){
		res++;
		sum += it->first;
		it = active.lower_bound( pii( sum, -1 ) );
	}
	active.insert( pii( w, idx ) );
	return res;
}

int main(){

	int N, Q;
	int w, idx;

	scanf("%d %d", &N, &Q);
	
	for ( int i=0; i < N; ++i ){
		scanf("%d", &w);
		W[ i + 1 ] = w;
		active.insert( pii( w, i + 1 ) );
	}
	
	char op;
	while ( Q-- ){
		scanf(" %c", &op);
		if ( op == '?' ){
			scanf("%d", &idx);
			printf("%d\n", query( idx ) );
		}
		else if ( op == '-' ){
			scanf("%d", &idx );
			active.erase( pii( W[idx], idx ) );
			W.erase( idx );
		}
		else {
			scanf("%d %d", &w, &idx);
			W[ idx ] = w;
			active.insert( pii( w, idx ) );
		}
	}
	return 0;
}
