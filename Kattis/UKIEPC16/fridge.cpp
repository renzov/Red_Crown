#include<cstdio>
using namespace std;
char s[1024];
int f[10] = {0};

int main(){
	scanf("%s", s);
	for ( int i=0; s[i] ; ++i ) f[ s[i] - '0']++;
	int minf = 3000;
	int mind;
	int flag = 0;

	for ( int i=1; i < 10; ++i ){
		if ( minf > f[i] ){
			minf = f[i];
			mind = i;
		}
		if ( f[i] > 0 && !flag ){
			flag = i;
		}
	}
	
	if ( f[0] < minf ){
		printf("%d", mind);
		for ( int i=0; i <= f[0]; ++i ) putchar('0');
		puts("");
	}
	else {
		for ( int i=0; i <= minf; ++i ) printf("%d", mind);
		puts("");
	}
	return 0;
}
