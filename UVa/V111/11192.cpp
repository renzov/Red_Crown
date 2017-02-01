#include<cstdio>
#include<cstring>
char s[200];

void reverse(int x,int y){
  char tmp;
  for (int i=x,j=y; i < j ; i++,--j)
	 tmp=s[i],s[i]=s[j],s[j]=tmp;
}

int main(){
  int n;
  int m;
  int g;
  while (scanf("%d",&g) && g){
		scanf("%s",s);
		m = strlen(s);
		n = m/g;
		for (int i=0; i < m; i+=n){
			 reverse(i,i+n-1);
		}
		puts(s);
  }
  return 0;
}