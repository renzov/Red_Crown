#include<cstdio>
using namespace std;

int main(){
	int N;
	int X;
	int m2;
	int m3;

	scanf("%d", &N);
	while ( N-- ){
		scanf("%d", &X);
		m2 = X % 2;
		m3 = X % 3;
		if ( (m2 + m3) && !(m2 * m3) )
			puts("YES");
		else 
			puts("NO");
	}
	return 0;
}
