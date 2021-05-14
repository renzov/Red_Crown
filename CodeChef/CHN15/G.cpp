#include<cstdio>
using namespace std;
const int MAXN = 505;
char S[MAXN];

void process(){
	scanf("%s", S);
	int res = 0;
	for ( int i=0; S[i]; ++i ){
		res <<= 1;;
		res %= 3;
		if ( S[i] == 'R' ){
			res++;
			res %= 3;
		}
	}
	puts( res == 0? "Animesh":"Malvika" );
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
