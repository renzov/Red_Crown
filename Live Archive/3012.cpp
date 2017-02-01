#include<cstdio>
inline int abs(int x){
  return (x < 0)? -x:x;
}
int print(int num,int s){
  for (int i=0; i < s; ++i) putchar(' ');
  printf("%d\n",num);
}
int gcd(int a,int b){
  return  (!b)? a:gcd(b,a%b);
}

int len(int x){
  int res = 0;
  while (x){
		res++;
		x/=10;
  }
  return res;
}

int main(){
  int n;
  int sum;
  int a;
  int runs=0;
  while (scanf("%d",&n) && n){
	 sum = 0;
	 runs++;
	 for (int i=0; i < n; ++i){
		scanf("%d",&a);
		sum += a;
	 }
	 printf("Case %d:\n",runs);
	 if ( (abs(sum) % n)== 0){
		if (sum < 0){ printf("- "); }
		printf("%d\n",abs(sum)/n);
	 }
	 else {
		  bool neg = sum < 0;
		  a = 0;
		  if (neg) sum *= -1;
		  if ( sum > n ){
				a = sum/n;
				sum %= n;
		  }
		  int g = gcd(sum,n);
		  sum /= g;
		  n /= g;
		  int l1 = len(sum);
		  int l2 = len(n);
		  int space = 0;
		  if (neg) space+=2;
		  if (a) space += len(a);
		  print(sum,space + l2 - l1);
		  if (neg) printf("- ");
		  if (a) printf("%d",a);
		  for (int i=0; i<l2; ++i) putchar('-');
		  putchar('\n');
		  print(n,space);
	 }
  }

  return 0;
}