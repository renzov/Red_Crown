#include<cstdio>

char h[] = "hello";

int main(){

	char w[128];	
	int pos = 0;
	scanf("%s", w);
	
	for ( int i=0; w[i] && pos < 5; ++i )
		if ( w[i] == h[pos] )
			pos++;
	
	puts(pos == 5? "YES":"NO");
	return 0;
}
