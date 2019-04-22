#include<cstdio>
#include<cstring>
using namespace std;

char s[256];
int f[32];

int main(){
	int cnt = 0;
	scanf("%s", s);
	for ( int i=0; s[i] ; ++i ){
		if ( f[s[i] - 'a'] == 0 )
			cnt++;
		f[ s[i] - 'a']++;
	}
	puts(cnt & 1? "IGNORE HIM!":"CHAT WITH HER!");
	return 0;
}
