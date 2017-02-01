#include<cstdio>
#include<cctype>
const int SIZE = 1100/2/8+2;
char mark[SIZE] = {0};
int sieve(){
  int i,j;
  for (i=3; i*i <= 1100; i+=2){
		if ((mark[i>>4] & (1<<((i>>1)&7))) == 0){
			for (j=i*i; j <= 1100; j+= i<<1) mark[j>>4] |= (1<<((j>>1)&7)); 
		}
  }
}
int main(){
  sieve();
  char line[50];
  while (scanf("%s",line) != EOF){
		int sum = 0;
		for (int i=0; line[i]; ++i){
			 if (isupper(line[i])) sum += (line[i] - 'A' + 27);
			 else sum += (line[i]-'a'+1);
		}
		if (sum==2 || (sum%2 && (mark[sum>>4] & (1<<((sum>>1)&7))) == 0) ) puts("It is a prime word.");
		else puts("It is not a prime word.");
  }
}