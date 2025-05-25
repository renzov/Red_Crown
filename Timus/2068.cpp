#include<cstdio>
using namespace std;

int main(){
	int N;
	
	scanf("%d", &N);
	
	int sum = 0;
	int a;
	for ( int i = 0; i < N; ++i ){
		scanf("%d", &a);
		a--;
		sum += a;
	}
	sum >>= 1;
	puts( !(sum & 1)? "Stannis":"Daenerys");
	return 0;
}
