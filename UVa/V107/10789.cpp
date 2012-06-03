#include<cstdio>
char mark[2005] = {0};
int sieve(){
  int i,j;
  mark[0] = mark[1] = 1;
  for (i=4; i <= 2000; i+=2) mark[i] = 1;
  for (i=3; i*i <= 2000; i+=2){
		if (mark[i] == 0){
			for (j=i*i; j <= 2000; j+= i<<1) mark[j] = 1; 
		}
  }
}
int main(){
  int runs; 
  int cases = 0;
  char line[2005];
  sieve();
  scanf("%d",&runs);
  while (runs--){
	 cases++;
	 scanf("%s",line);
	 int frec[300] = {0};
	 int cnt = 0;
	 for (int i=0; line[i]; ++i) frec[ line[i] ]++;
	 printf("Case %d: ",cases);
	 for (char i='0'; i <= '9'; ++i){
		  if ( mark[ frec[i] ] == 0){ putchar(i); cnt++; }
	 }
	 for (char i='A'; i <= 'Z'; ++i){
		  if ( mark[ frec[i] ] == 0){ putchar(i); cnt++; }
	 }
	 for (char i='a'; i <= 'z'; ++i){
		  if ( mark[ frec[i] ] == 0){ putchar(i); cnt++; }
	 }
	 if (cnt == 0) printf("empty");
	 putchar('\n');
  }
  return 0;
}