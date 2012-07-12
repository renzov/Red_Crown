#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int main(){
	int n;
	int digit;
	double r;
	while ( scanf("%d",&n) != EOF ){
		digit = floor( n * log(2) + 1 );
		r = exp( (digit - n)*log(2) + digit * log(5) );
		printf("%4.3lf %d\n",r,digit);
	}
	return 0;
}
