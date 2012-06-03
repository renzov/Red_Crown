#include<cstdio>
#include<cstring>
int main(){

  int n;
  char s[70];

  scanf("%s",s);
  n = strlen(s);
  
  int sum = 0;
  int dig;
  int mpot = 1;
  for ( int i=n-1; i >= 0; --i ){
	 mpot = mpot % 7;
	 dig = s[i] - '0';
	 sum += (dig*mpot)%7;
	 sum %= 7;
	 mpot *= 10;
	 mpot %= 7;
  }
  printf("%d\n",sum);
  return 0;
}