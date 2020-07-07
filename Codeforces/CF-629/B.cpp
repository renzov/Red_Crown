#include<cstdio>
using namespace std;

long long cnt[100005];

long long f(const int &x){
	return 1LL * x * (x - 1) / 2;
}

void process(){
	int N, K;
	scanf("%d %d", &N, &K);
	int len = N;
	while ( f(len - 1) >= K ){
		putchar('a');
		len--;
	}
	K -= f(len - 1);
	
	putchar('b'); len--; 
	while ( len > K ){
		putchar('a');
		len--;
	}
	putchar('b'); len--;
	while ( len-- ){
		putchar('a');
	}
	puts("");
}

int main(){
	
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
