#include<cstdio>
using namespace std; 

int main(){	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	int a;
	int S;

	scanf("%d", &N);
	
	S = 0 ;
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		a--;
		S += a;
	}
	puts( S & 1? "Constantine":"Mike" );
	return 0;
}
