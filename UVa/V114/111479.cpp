#include<cstdio>

bool valid( long long a , long long b, long long c ){
  return ((a+b)>c) && ((b+c)>a) && ((a+c)>b);
}

int main(){
  long long a,b,c;
  scanf("%d",&runs);
  for ( int i=1; i<=runs; ++i ){
	 scanf("%lld %lld %lld",&a,&b,&c);
	 printf("Case %d: ",i);
	 if ( !valid(a,b,c) ) printf("Invalid\n");
	 else {
		if ( a == b && b == c ){
		  printf("Equilateral\n");
		}
		else {
		  if ( a==b || b==c || a==c ){
			 printf("Isosceles\n");
		  }
		  else printf("Scalene\n");
		}
	 }
  }
  return 0;
}