#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN = 2005;

char result[MAXN];

bool check( const int &wins ){
	int A = 0, B = 0;
	int cntA = 0, cntB = 0;

	for ( int i = 0; result[i]; ++i ){
		if ( result[i] == 'A' )
			A++;
		else 
			B++;
		if ( A >= wins ){
			cntA++, A = 0, B = 0;
		}
		else if ( B >= wins ){
			cntB++, A = 0, B = 0;
		}
	}
	return cntA > cntB;
}

int main(){
	int N;

	scanf("%s", result );
	N = strlen( result );

	vector<int> ans;
	for ( int i = 1; i <= N; ++i )
		if ( check( i ) )
			ans.push_back(i);

	printf("%d\n", (int)ans.size());
	if ( !ans.empty() ){
		printf("%d", ans[0]);
		for ( int i = 1; i < (int)ans.size(); ++i )
			printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}
