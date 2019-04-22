#include<cstdio>

char X[10];

int main(){
	int N;
	int res = 0;
	scanf("%d", &N);
	
	while (N--){
		scanf("%s", X);
		if ( X[0] == '+' || X[2] == '+' )
			res++;
		else 
			res--;
	}
	printf("%d\n", res);
	return 0;
}
