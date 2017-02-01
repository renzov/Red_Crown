#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
typedef pair<int,int> card;
const int MAXN = 30;
card A[MAXN];
card B[MAXN];
bool G[MAXN][MAXN];
int n;
int hole[MAXN];
bool visited[MAXN];

card get_card( char *s ){
	card c;
	if ( isdigit(s[0]) ){
		c.first = s[0] - '0';	
	}
	else {
		switch ( s[0] ){
			case 'A': c.first = 14; break;
			case 'T': c.first = 10; break;
			case 'J': c.first = 11; break;
			case 'Q': c.first = 12; break;
			case 'K': c.first = 13; break;
		}
	}
	switch ( s[1] ){
		case 'C': c.second = 0; break;
		case 'D': c.second = 1; break;
		case 'S': c.second = 2; break;
		case 'H': c.second = 3; break;
	}
	return c;
}

bool alternate( int u ){
	if ( visited[u] ) return false;
	visited[u] = true;
	for ( int v=0; v < n; ++v ){
		if ( G[u][v] && ( hole[v]<0 || alternate( hole[v] ) ) ){
			hole[ v ] = u;
			return true;
		}
	}
	return false;
}

int process(){
	int cnt = 0;	
	for ( int i=0; i < n; ++i ){
		fill( visited , visited + n , false );
		if ( alternate(i) ) cnt++;
	}
	return cnt;	
}

void read_input(){
	char s[5];
	scanf("%d",&n);
	for ( int i=0; i < n; ++i ){
		scanf("%s",s);
		B[i] = get_card(s);
		
	}
	for ( int i=0; i < n; ++i ){
		scanf("%s",s);
		A[i] = get_card(s);
	}
}

void init(){
	for ( int i=0; i < n; ++i )
		for ( int j=0; j < n; ++j ){
			if ( A[i] > B[j] )
				G[i][j] = true;
			else 
				G[i][j] = false;
		}
	fill( hole , hole + n, -1 );
}

int main(){
	int runs;
	int res;
	scanf("%d",&runs);
	while ( runs-- ){
		read_input();
		init();
		res = process();
		printf("%d\n",res);
	}
	return 0;
}
