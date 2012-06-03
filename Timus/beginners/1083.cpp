#include<cstdio>
#include<cstring>
int main(){
  char s[25];
  int n;
  int k;

  scanf("%d",&n);
  scanf("%s",s);
  k = strlen(s);

  int res = 1;

  while (n > 0){
	 res *= n;
	 n -= k;
  }
  printf("%d\n",res);
  return 0;
}