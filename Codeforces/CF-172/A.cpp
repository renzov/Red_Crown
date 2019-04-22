#include<cstdio>
#include<cctype>

char S[1024];

int main(){
	scanf("%s", S);
	S[0] = toupper(S[0]);
	puts(S);
}
