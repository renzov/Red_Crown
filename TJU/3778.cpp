#include<cstdio>
int main(){
  char c;
  int e;
  int max = 0;
  int size = 0;
  
  while (scanf(" %c",&c) != EOF){
	 if (c == 'n'){
		scanf("%d",&e);
		size++;
		if (e*e > max) max = e*e;
	 }
	 else {
		size--;
		if (size == 0) max = 0;
	 }
  }
  printf("%d\n",max);
  return 0;
}