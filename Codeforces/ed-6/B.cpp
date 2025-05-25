#include<cstdio>
using namespace std;

int cnt[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

int main(){

	int a, b;
	int res = 0;
	scanf("%d %d", &a, &b);

	while ( a <= b ){
		int tmp = a;
		while ( tmp ){
			res += cnt[ tmp % 10 ];
			tmp /= 10;
		}
		a++;
	}
	printf("%d\n", res);
	return 0;
}
