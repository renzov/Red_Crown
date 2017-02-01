#include<cstdio>
using namespace std;

int main(){
	int runs;
	char s[100];
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%s", s);
		bool ok = true;
		for ( int i=0; s[i] && ok; ++i )
			if ( s[i] == 'D' ) ok = false;
		if (ok) puts("Possible");
		else puts("You shall not pass!");
	}
	return 0;
}
