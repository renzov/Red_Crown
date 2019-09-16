#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
typedef pair<int,int> sample;
deque<sample> minQ;
deque<sample> maxQ;

inline int get_val( deque<sample> &Q ){
	return Q.front().first;
}

void remove( deque<sample> &Q, const int &pos ){
	while ( Q.front().second <= pos )
		Q.pop_front();
}

void insert( deque<sample> &Q, const sample &S ){
	while ( !Q.empty() && Q.back().first >= S.first )
		Q.pop_back();
	Q.push_back( S );
}

int main(){	
	int N, M, C, a;
	int cnt = 0; 
	scanf("%d %d %d", &N, &M, &C);
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &a);
		if ( i > M ){
			remove( minQ ,  i - M );
			remove( maxQ , i - M  );
		}
		insert( minQ, sample( a , i ) );
		insert( maxQ, sample( -a , i ) );
		if ( i >= M ){
			if ( -get_val( maxQ ) - get_val( minQ ) <= C ){
				printf("%d\n", i - M + 1);
				cnt++;
			}
		}
	}
	if ( !cnt ) puts("NONE");
	fclose(stdout);
	return 0;
}
