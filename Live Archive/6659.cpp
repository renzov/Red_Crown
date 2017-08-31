#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXL = 1005;
char S[MAXL];
bool f[30];
int main(){
	int runs;
	int cases = 0;
	int idx;
	int odd;
	int N;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%s", S);
		N = strlen(S);
		int res = 0;
		for ( int i=0; i < N; ++i ){
			// We do sliding window to count how many
			// substrings are dromicpalin
			// A string is dromicpalin if the in the frequence of the 
			// letters of the string there is at most one with odd frequence
			fill( f, f + 26, false );
			odd = 0;			
			for ( int j = i; j < N; ++j ){
				idx = S[j] - 'a';
				if ( f[idx] ){
					odd--;
					f[idx] = false;
				}
				else {
					odd++;
					f[idx] = true;
				}
				if ( odd <= 1 ) res++;
			}
		}
		printf("Case %d: %d\n", ++cases, res);
	}	
	return 0;
}
