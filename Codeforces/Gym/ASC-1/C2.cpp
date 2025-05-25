#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 500005;

bool matched[MAXN];
int p[MAXN];
vector<int> res;

int main(){
	freopen("grant.in", "r", stdin);
	freopen("grant.out", "w", stdout);

	int N;

	scanf("%d", &N);
	for ( int i=1; i < N; ++i ){
		scanf("%d", p + i);
		p[i]--;
	}
	
	int ans = 0;
	for ( int i=N-1; i > 0; --i ){
		if ( !matched[i] && !matched[ p[i] ] ){
			matched[i] = true;
			matched[ p[i] ] = true;
			ans++;
			res.push_back( i );
		}
	}
	
	reverse( res.begin(), res.end() );
	bool first = true;

	printf("%d\n", ans * 1000);
	for ( int i=0; i < (int)res.size(); ++i ){
		if ( !first ) putchar(' ');
		printf("%d", res[i] + 1);
		first = false;
	}
	puts("");
	return 0;
}

