#include<cstdio>
using namespace std;

int main(){
	char S[10];
	scanf("%s", S);
	if ( S[2] == S[3] && S[4] == S[5] )
		puts("Yes");
	else
		puts("No");
	return 0;
}
