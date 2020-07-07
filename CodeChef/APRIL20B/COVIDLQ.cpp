#include<cstdio>
using namespace std;

void process(){
	bool ok = true;
	int last = -20;
	int A;
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", &A);
		if ( A == 1 ){
			ok &= (( i - last ) >= 6);
			last = i;
		}
	}
	puts( ok? "YES":"NO");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
