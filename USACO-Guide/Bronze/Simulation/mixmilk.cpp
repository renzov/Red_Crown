#include<cstdio>
#include<algorithm>
using namespace std;

long long C[4];
long long M[4];

int main(){
	freopen ("mixmilk.in","r", stdin);
	freopen ("mixmilk.out","w", stdout);

	for ( int i=0; i < 3; ++i )
		scanf("%lld %lld", C + i, M + i);

	int act;
	int nxt;
	long long eps;

	for ( int i=0; i < 100; ++i ){
		act = i % 3;
		nxt = (i + 1) % 3;

		eps = min(  C[nxt] - M[nxt] , M[act] );
		M[act] -= eps;
		M[nxt] += eps;
	}

	for ( int i=0; i < 3; ++i )
		printf("%lld\n", M[i]);
	return 0;
}
