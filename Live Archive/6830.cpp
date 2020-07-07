#include<cstdio>
using namespace std;
const int MAXN = 625;
int V[MAXN][MAXN];

void process(){
	for ( int i=0; i < R; ++i )
		for ( int j=0; j < C; ++j )
			scanf("%d", V[i] + j);
}

int main(){
	while ( scanf("%d %d %d", &R, &C, &N) == 3 ){
		process();
		clean();
	}
	return 0;
}
