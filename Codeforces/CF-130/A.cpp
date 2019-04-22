#include<cstdio>
#include<cstring>
using namespace std;

char w[256];

int main(){
	int n;
	scanf("%s", w);
	n = strlen(w);
	for ( int i=0; i < n - 2; i++ ){
		if (w[i] == 'W' && w[i+1]=='U' && w[i+2] == 'B'){
			w[i] = ' ';
			w[i+1] = ' ';
			w[i+2] = ' ';
		}
	}	
	char *str = strtok(w, " ");
	bool first = true;
	while ( str != NULL ){
		if (!first) putchar(' ');
		printf("%s", str);
		str = strtok(NULL, " ");
		first = false;
	} 
	puts("");
	return 0;
}
