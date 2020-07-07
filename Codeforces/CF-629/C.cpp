#include<cstdio>
using namespace std;

const int MAXN = 100005;	
char X[MAXN];
char res[2][MAXN];

void process(){
	int N;
	scanf("%d", &N);
	scanf("%s", X);

	int gre = -1;
	
	for ( int i=0; i < N; ++i ){
		if ( X[i] == '2' ){
			if ( gre == -1 ){
				res[0][i] = res[1][i] = '1';
			}
			else{
				res[gre][i] = '0';
				res[1-gre][i] = '2';
			}
		}
		else if ( X[i] == '1' ){
			if ( gre == -1 ){
				res[0][i] = '1';
				res[1][i] = '0';
				gre = 0;
			}
			else {
				res[gre][i] = '0';
				res[1 - gre][i] = '1';					
			}
		}
		else {
			res[0][i] = res[1][i] = '0';
		}
	}
	for ( int j=0; j < 2; ++j ){
		for ( int i=0; i < N; ++i )
			putchar( res[j][i] );	
		puts("");
	}

}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
