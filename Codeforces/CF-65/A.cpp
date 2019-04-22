#include<cstdio>
#include<cstring>

int main(){	
	int N;
	char W[124];
	int len;

	scanf("%d", &N);
	while (N--){
		scanf("%s", W);
		len = strlen(W);
		if ( len < 11 ) puts(W);
		else printf("%c%d%c\n", W[0], len - 2, W[len-1]);
	}
	return 0;
}
