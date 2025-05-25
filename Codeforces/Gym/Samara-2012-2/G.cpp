#include<cstdio>
#include<queue>
using namespace std;
const int MAXN = 200005;

char S[MAXN];
int frec[26];
bool ok[MAXN];


int main(){

	scanf("%s", S);
	int N, c;
	for ( N = 0; S[N] ; ++N ){
		c = S[N] - 'a';
		frec[c]++;
		ok[N] = frec[c] <= 1; 
	}

	if ( N > 26 ){
		puts("IMPOSSIBLE");
	}
	else {
		queue<char> Q;
		for ( int i = 0; i < 26; ++i )
			if ( !frec[i] )
				Q.push( (char)(i + 'a') );
		for ( int i = 0; i < N; ++i ){
			if ( !ok[i] ){
				S[i] = Q.front();
				Q.pop();
			}
		}
		puts(S);
	}
	return 0;
}

