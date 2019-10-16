#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 100005;
char S[MAXN];
vector<int> P[26];

int main(){
	int N;

	scanf("%s", S);
	N = strlen( S );
	for ( int i=0; i < N; ++i )
		P[ S[i]-'a' ].push_back( i );
	
	for ( int i=0; i < 26; ++i )
		P[i].push_back(N);

	int res = 0;
	int act, nxt;
	int idx;
	for ( int i=0; i < 26; ++i ){
		for ( int j=0; j < (int)P[i].size() - 1; ++j ){
			act = P[i][j], nxt = P[i][j + 1];
			for ( int k=0; k < 26; ++k )
				if ( k != i )
					if ( *lower_bound( P[k].begin(), P[k].end(), act + 1 ) < nxt ) 
						res++;		
		}
	}
	printf("%d\n", res);
	return 0;
}
