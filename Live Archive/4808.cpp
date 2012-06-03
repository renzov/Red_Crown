#include<cstdio>

int p[]={1,10,100,1000,10000,100000,1000000,10000000,100000000};

void get_digits(int c,long long *C){
  int i,j;
  bool flag = false;
  for (i=0; i < 10; ++i) C[i] = 0;
  for (i=0; i < 9; ++i) if ( p[i] == c ){ flag = true; break; }
  long long left = 0;
  int dig;
  long long right = 0;
  i = 0;
  if ( c < 10 ){
	 for (j = 1; j <= c; ++j){
		C[ j ] = 1;
	 }
	 return;
  }
  while ( c ){
	 if ( c < 10 ){ //leftmost
		dig = c % 10;
		for (j = 1; j < 10; ++j){
		  if ( j < dig ){
			 C[ j ] += p[i];
		  }
		  else if ( j == dig ){
			 C[ j ] += (left + 1);
		  }
		}
	 }
	 else if ( i == 0 ){ //rightmost
		dig = c % 10;
		right = c / 10;
		for (j = 0; j < 10; ++j){
		  if ( j == 0 ){
			 C[j] += ( right * p[i] );
		  }
		  else if ( j < dig ){
			 C[ j ] += ( right + 1 )*p[i];
		  }
		  else if ( j == dig ){
			 C[ j ] += (( right + 1 )*p[i] );
		  }
		  else {
			 C[ j ] += ( right )*p[i];
		  }
		}
	 }
	 else {
		dig = c % 10;
		right = c / 10;
		for (j = 0; j < 10; ++j){
		  if ( j < dig ){
			 if (j==0) C[ j ] += ( right )*p[i];
			 else C[ j ] += ( right + 1 )*p[i];
		  }
		  else if ( j == dig ){
			 if (j==0) C[ j ] += (( right - 1)*p[i] + left + 1);
			 else C[ j ] += (( right )*p[i] + left + 1);
		  }
		  else {
			 C[ j ] += ( right )*p[i];
		  }
		}
	 }
	 left = dig*p[i] + left;
	 c /= 10;
	 i++;
  }
}

int main(){
  long long A[15];
  long long B[15];
  int a;
  int b;
  int i;
  while ( scanf("%d %d",&a,&b) && a ){
	 a--;
	 get_digits(a,A);
	 get_digits(b,B);
	 printf("%lld",B[0]-A[0]);
	 for (i=1; i < 10; ++i) printf(" %lld",B[i]-A[i]);
	 putchar('\n');
  }
  return 0;
}