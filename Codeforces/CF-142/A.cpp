#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1024;
pair<int,int> W[MAXN];

int main(){
	bool ok = true;
	int S, N;

	scanf("%d %d", &S, &N);
	for ( int i=0; i < N; ++i ) scanf("%d %d", &W[i].first, &W[i].second);
	sort(W, W + N);
	for ( int i=0; i < N && ok; ++i ){
		if (S <= W[i].first)
			ok = false;
		S += W[i].second; 
	}
	puts(ok? "YES":"NO");
	return 0;
}
