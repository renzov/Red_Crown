#include<cstdio>
#include<cmath>
using namespace std;
const int SQRT = 31623;

void process(){
	int X, K;

	scanf("%d %d", &X, &K);
	int sq = sqrt(1.0*X);
	int e = 0;
	
	while ( !(X&1) ){
		X >>= 1;
		e++;
	}

	for ( int i=3; i <= sq; i += 2 ){
		if ( X % i == 0 ) X /= i, e++;
	} 
	if ( X > 1 ) e++;
	puts((e >= K)? "1":"0");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
