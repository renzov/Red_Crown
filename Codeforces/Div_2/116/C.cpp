#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;
char s[100005];
int main(){
	scanf("%s",s);
	int i=0;
	int res = 0;
	int a=0;
	int b=0;
	//while ( s[i] && isupper(s[i]) ) i++;
	for ( int j=i; s[j] ; j++ ){
		if ( isupper( s[j] ) ) a++;
		if ( islower( s[j] ) ) b++;
	}
	printf("%d %d\n",a,b);
	res = min( a , b );
	printf("%d\n",res);
	return 0;
}
