#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<cassert>
using namespace std;
const int MAXN = 200005;
char B[ MAXN ][ 6 ];
int size;
char op[ 25 ];
int main(){
	int N,M,K;
	deque<int> Q;
	stack<int> S;
	scanf("%d %d %d", &N, &M, &K);
	size = 0; 
	for ( int i=0; i<N; ++i ){
		scanf("%s", B[size]);
		Q.push_front( size );
		size++;
	}
	for ( int i=0; i < (N-K); ++i ){
		S.push( Q.front() );
		Q.pop_front();
	}
	bool rev = false;
	while ( M-- ){
		scanf("%s", op);
		if ( op[0] == 'R' ){
			if ( !Q.empty() ) rev ^= true; 
		}
		else {
			//parsear
            memset(B[size],0,sizeof(B[size]));			
			for ( int i=4; op[i] != ')' ; ++i ){
				B[size][i-4] = op[i];
			}
			if ( K==0 ){
				S.push( size );
			}
			else {
				if ( ((int)Q.size()) >= K ){
					if ( rev ){
						S.push( Q.back() );
						Q.pop_back();
					}
					else {
						S.push( Q.front() );
						Q.pop_front();
					}
				}
				//push index
				if ( rev ){
					Q.push_front( size );
				}
				else {
					Q.push_back( size );
				}
			}
			size++;
		}
	}
	if ( rev ){
		while ( !Q.empty() ){
			printf("%s\n", B[ Q.front() ]);
			Q.pop_front();
		}
	}
	else {
		while ( !Q.empty() ){
			printf("%s\n", B[ Q.back() ]);
			Q.pop_back();
		}
	}
	while ( !S.empty() ){
		printf("%s\n", B[ S.top() ]);
		S.pop();
	}
	return 0;
}
