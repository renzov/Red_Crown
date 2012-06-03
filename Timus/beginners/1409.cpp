#include<cstdio>
int main(){
  int a,b;
  int n;

  scanf("%d %d",&a,&b);
  n = a+b-1;
  printf("%d %d\n",n-a,n-b);
  return 0;
}