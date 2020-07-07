#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 1024;
char S[MAXN];
char T[MAXN];
bool G[30][30];

void process(){
	scanf("%s %s", S, T);
	int M;
	int u, v;
	char a, b;
	scanf("%d", &M);
	
	for ( int i=0; i < 26; ++i ){
		fill( G[i], G[i] + 26, false );
		G[i][i] = true;
	}
	
	while ( M-- ){
		scanf(" %c->%c", &a, &b);
		u = a - 'a', v = b - 'a';
		G[u][v] = true; 
	}

	for ( int k=0; k < 26; ++k )
		for ( int i=0; i < 26; ++i )
			for ( int j=0; j < 26; ++j )
				G[i][j] |= ( G[i][k] & G[k][j] );

	bool res = (strlen(S) == strlen(T));
	for ( int i=0; S[i] && res; ++i ){
		u = S[i] - 'a', v = T[i] - 'a';
		res &= G[u][v];
	}
	puts(res? "YES":"NO");
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
