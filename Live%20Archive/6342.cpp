#include<cstdio>
#include<cstring>
using namespace std;
const int MAXS = 15;

int main(){
	char s[MAXS];
	int runs, N;
	bool ok;
	scanf("%d", &runs);
	while (runs--){
		scanf("%s", s);
		N = strlen(s);
		ok = true;
		for ( int i=0, j=N-1; ok && i < j ; i++,j-- )
			ok = (s[i] == s[j]);
		if (ok) puts("YES");
		else puts("NO");
	}
	return 0;
}
