#include<cstdio>
#include<set>
#include<queue>
using namespace std;
const long long B = 1e18;

long long f[21];
set<long long> sols;

void backtrack(){
	queue<long long> Q;
	
	sols.insert( 1LL );
	Q.push(1LL);

	long long nxt;
	long long n;

	while ( !Q.empty() ){
		n = Q.front();
		Q.pop();
	
		for ( int i = 2; i < 20; ++i )
			if ( n <= B / f[i] ){
				nxt = n * f[i];
				if ( !sols.count(nxt) ){
					sols.insert(nxt);
					Q.push(nxt);
				}
			}
	}
}

int main(){
	f[0] = 1;
	for ( int i = 1; i < 20; ++i )
		f[i] = f[i - 1] * i;
	
	backtrack();
	int N;
	long long a;
	scanf("%d", &N);
	while ( N-- ){
		scanf("%lld", &a);
		puts( sols.count(a)? "YES":"NO");
	}
	return 0;
}
