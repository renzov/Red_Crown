#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN = 1000005;

char A[MAXN];
char B[MAXN];
int p[MAXN];
int N;
int M;

void prefix_function(){
	p[0] = 0;
	for ( int i = 1; i <= M; ++i ){
		int j = p[i - 1];
		while ( j > 0 && B[j] != B[i] )
			j = p[j - 1];
		if ( B[j] == B[i] ) 
			j++;
		p[i] = j;
	}
}

void process(){
	scanf("%s %s", A, B);
	N = strlen(A);
	M = strlen(B);
	prefix_function();
	vector<int> ans;
	// use the prefix function calculated previously
	int cnt = 0;
	for ( int i = 0; i < N; ++i ){
		int j = cnt;
		while ( j > 0 && B[j] != A[i] )
			j = p[j - 1];
		if ( B[j] == A[i] ) 
			j++;
		cnt = j;
		if ( cnt == M ) ans.push_back( i - M + 2 );
	}
	// Print the solution
	if ( ans.empty() ) puts("Not Found");
	else {
		printf("%d\n%d", (int)ans.size(), ans[0]);
		for ( int i = 1; i < (int)ans.size(); ++i )
			printf(" %d", ans[i]);
		puts("");
	}
}

int main(){
	int runs;
	scanf("%d", &runs);

	while ( runs-- ){
		process();
		if ( runs ) puts("");
	}

	return 0;
}
