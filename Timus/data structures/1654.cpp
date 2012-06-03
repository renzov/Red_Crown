#include<cstdio>
char stack[200005];
int main(){
	char c;
   int st = 0;
	while (1){
		c=getchar();
		if (c == '\n' || c== EOF) break;
		if (st==0) stack[st++] = c;
		else if ( stack[st-1] == c ) st--;
		else stack[st++] = c;
	}
	stack[st] = '\0';
	puts(stack);
	return 0;
}