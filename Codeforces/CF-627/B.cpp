#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 5005;
int first[MAXN];
int last[MAXN];

void process(){
	int x, N;
	scanf("%d", &N);
	for ( int i=1; i <= N; ++i )
		first[i] = last[i] = 0;
	
	for ( int i=1; i <= N; ++i ){
		scanf("%d", &x);
		if ( !first[x] ) first[x] = i;
		last[x] = i;
	}
	bool found = false;
	for ( int i=1; !found && i <= N; ++i )
		if ( last[i] - first[i] >= 2 ) found = true;
	puts(found? "YES":"NO");
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
