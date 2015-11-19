#include <cstdio>
#include <cstring>
char num[1000005];

int numdig(int x){
	int res = 0;
	while (x){
		res++;
		x /= 10;
	}
	return res;
}

int main(){
	while (1){
		scanf("%s",num);
		if (strcmp(num,"END") == 0) break;

		if (strcmp(num,"1") == 0){
			puts("1");
			continue;
		}
		int res = 2;
		int x1,x2;
		x1 = strlen(num);
		while (x1 > 1){
			x2 = numdig(x1);
			res++;
			x1 = x2;
		}
		printf("%d\n", res);
	}
	return 0;
}