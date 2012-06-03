#include<cstdio>
#include<cstring>
int main(){
  char s[100];
  int n;
  int p;
  int m;
  int l;
  while (scanf("%s",s) && s[0] !='.' ){
	  scanf("%d",&n);
	  l = strlen(s);
	  for (int i=0; s[i]; ++i){
		  for (int j=0; j < n; ++j){
			 for (int k=0; k < l; ++k){
				  putchar(s[(i+k)%l]);
			 }
		  }
		  putchar('\n');
	  }
  }
  return 0;
}