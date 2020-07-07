#include<cstdio>
#include<cctype>
using namespace std;
const int MAXN = 1000005;
char S[MAXN];

void process(){
	int prefcnt[3] = {1, 0, 0};
	int d;
	int sum = 0;
	long long res = 0;
	for ( int i=0; S[i]; ++i ){
		if ( isdigit( S[i] ) ){
			d = S[i] - '0';
			sum += d;
			sum %= 3;
			res += prefcnt[ sum ];
			prefcnt[ sum ]++;
		}
		else {
			prefcnt[1] = prefcnt[2] = 0;
			prefcnt[0] = 1;
			sum = 0;
		}
	}
	printf("%lld\n", res);

}


int main(){
	while ( scanf("%s", S) != EOF )
		process();
	return 0;
}
