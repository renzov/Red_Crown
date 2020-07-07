#include<cstdio>
using namespace std;
const int MAXN = 705;

int H[MAXN][MAXN];
int V[MAXN][MAXN];

int main(){

	scanf("%d", &N);
	
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j )
			scanf("%d", H[i] + j);

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			scanf("%d", V[i] + j);


	return 0;
}
