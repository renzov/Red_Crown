#include<cstdio>
#include<cstring>
using namespace std;

int main(){
	char prev[3];
	char act[3];
	int N;
	int res = 1;

	scanf("%d", &N);
	scanf("%s", prev); N--;

	while ( N-- ){
		scanf("%s", act);
		if ( act[0] == prev[1] ){
			res++;
		}
		strcpy(prev, act);
	}
	printf("%d\n", res);
}
