#include<cstdio>
int rev(int x){
  int r=0;
  while (x){
		r*=10;
		r+=(x%10);
		x/=10;
  }
  return r;
}
int main(){
  int a,b,runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d",&a,&b);
		printf("%d\n",rev(rev(a)+rev(b)));
  }
  return 0;
}