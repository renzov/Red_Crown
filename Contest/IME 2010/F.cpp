#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
int main(){
	char s[200];
	long long res;
	int runs,p,n,k;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%s",s);
		p = 0;
		n = strlen(s);
		while ( isdigit( s[p] ) ) p++;
		k = n - p;
		s[p] = '\0';
		n = atoi(s);
		res = 1;
		while ( n > 0 ){
			res *= n;
			n -= k;
		}
		printf("%lld\n",res);
	}

	return 0;
}
