#include<cstdio>
using namespace std;
int F[3];
int main(){
	int x;
	int N;

	scanf("%d", &N);
	while ( N-- ){
		for ( int i=0; i < 3; ++i ){
			scanf("%d", &x);
			F[i] += x;
		}
	}
	puts( (F[0] == 0 && F[1] == 0 && F[2] == 0)? "YES":"NO");
	return 0;
}
