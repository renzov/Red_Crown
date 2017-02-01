#include<cstdio>
#include<algorithm>
using namespace std;

int a[100005];
int ord[100005];
int res[100005];

bool cmp( const int &x, const int &y ){
	return a[x] < a[y];
}

int main(){
	long long sum;
	int N;

	while (scanf("%d",&N) != EOF){
		sum = 0;		
		for ( int i=0; i < N ; ++i ){
			scanf("%d", a+i);
			sum += a[i];
			ord[i] = i;		
		}
		if (sum & 1){
			puts("No");
			continue;
		}
		puts("Yes");
		sort(ord,ord + N);
		sum >>= 1;
		for ( int i=N-1; i >= 0 ; --i ){
			if ( sum >= a[ ord[i] ] ){
				sum -= a[ ord[i] ];
				res[ ord[i] ] = 1;
			}
			else {
				res[ ord[i] ] = -1;
			}
		}
		printf("%d",res[0]);
		for ( int i=1; i < N ; ++i){
			printf(" %d",res[i]);
		}
		puts("");
	}
	return 0;
}
