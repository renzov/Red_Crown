#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
const int MAXN = 200005;
const int SQRT = 450;
vector<int> S[SQRT];
int V[MAXN] = {0};

int main(){
	int N, Q;
	int t;
	int a, b, c, d;

	scanf("%d %d", &N, &Q);
	int sq = (int)sqrt( (double)N ) + 1; 

	for ( int i=1; i <= sq; ++i )
		S[i] = vector<int>( i, 0 );

	while ( Q-- ){
		scanf("%d", &t);
		if ( t == 1 ){
			scanf("%d %d %d", &a, &b, &c);
			if (  b <= sq ) S[b][a] += c;
			else {
				if ( a == 0 ) a = b;
				for ( int i=a; i <= N; i += b )
					V[i] += c;
			}
		}
		else {
			scanf("%d", &d);
			t = V[d];
			for ( int i=1; i <= sq; ++i )
				t += S[i][ d%i ];
			printf("%d\n", t);
		}
	}
	return 0;
}
