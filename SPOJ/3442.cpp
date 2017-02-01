#include<cstdio>
int a;
int gexp(int b){
  if (b==0) return 1;
  if (b%2){ return ((a%10) * gexp(b-1)%10)%10; }
  else { int tmp = gexp(b/2); return (tmp*tmp)%10; }
}
int main(){
  int runs;
  int b;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&a,&b);
	 printf("%d\n",gexp(b));
  }
  return 0; 
}