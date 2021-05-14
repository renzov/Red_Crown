#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 128;
char S[MAXN];
int cnt[2];

void process(){
	scanf("%s", S);
	cnt[0] = cnt[1] = 0;
	for ( int i=0; S[i]; ++i )
		cnt[ S[i] - 'a' ]++;
	printf("%d\n", min( cnt[0], cnt[1] ));
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
