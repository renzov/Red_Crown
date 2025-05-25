#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 128;

bool in[100005];

int main(){
	int N, X;
	int val;

	in[0] = true;
	vector<int> seen;
	vector<int> nseen;
	seen.push_back(0);

	scanf("%d", &N);
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &X );
		for ( int j = 0; j < (int)seen.size(); ++j ){
			val = seen[j] + X;
			if ( !in[ val ] ){
				in[ val ] = true;
				nseen.push_back( val );
			}
		}
		while ( !nseen.empty() ){
			seen.push_back( nseen.back() );
			nseen.pop_back();
		}
	}

	printf("%d\n", (int)seen.size() - 1);
	sort( seen.begin(), seen.end() );
	printf("%d", seen[1]);
	for ( int i = 2; i < (int)seen.size(); ++i )
		printf(" %d", seen[i]);
	puts("");
	return 0;
}
