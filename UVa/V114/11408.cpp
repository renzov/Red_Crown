#include<cstdio>
#include<cstring>
const int MAXN = 5000000;
int p[5000002];
int s[5000002] = {0};

int fact( int x ){
  int sum = 0;
  int last = -2;
  while ( p[x] != -1 ){
	 if ( last != p[x]){
		sum += p[x]; last = p[x];
	 }
	 x /= p[x];
  }
  if ( last != x ) sum += x;
  return sum;
}

int sieve(){
  int i,j;
  memset(p,-1,sizeof(p));
  for ( i = 4; i <= MAXN; i+=2 ) p[i] = 2;
  for ( i = 3; (i*i) < MAXN; i+=2 ){
	 if ( p[i] == -1 ){
		for ( j = (i*i) ; j < MAXN ; j += (2*i) )
		  p[j] = i;
	 }
  }
  for ( i = 2; i <= MAXN; ++i ){
	 s[i] = s[i-1];
	 if ( p[ fact(i) ] == -1 )
		  s[i]++;
  }
}

int main(){
  sieve();
  int a,b,t;
  while ( scanf("%d",&a) && (a>1) ){
	 scanf("%d",&b);
	 if ( a > b ){ t = a; a = b; b = t; }
	 printf("%d\n",s[b] - s[a-1]);
  }
}