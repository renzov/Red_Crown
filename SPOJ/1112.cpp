#include<cstdio>
int main(){
  int x,y;
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d",&x,&y);
		if (x==y){
			 if (x%2) printf("%d\n",2*x-1);
			 else printf("%d\n",2*x);
		}
		else if (x == (y+2)){
			 if (x % 2)
				printf("%d\n",2*y + 1);
			 else 
				printf("%d\n",2*y + 2);
		}
		else puts("No Number");
  }

  return 0;
}