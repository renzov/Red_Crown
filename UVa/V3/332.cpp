#include<cstdio>
#include<numeric>
#include<algorithm>
#include<cstring>
using namespace std;

long long pot_10(int p){
  int pot = 1;
  while (p){
	 pot*=10;
	 p--;
  }
  return pot;
}

char s[15];

bool cmp(int a,int b,int len){
  while (len--){
	 if (s[a]!=s[b]) return false;
	 a++,b++;
  }
  return true;
}

int main(){
  int j;
  int k;
  long long p;
  long long p2;
  long long num;
  long long frac;
  int cases = 0;
  long long n,d,g;
  int m;
  
  while (scanf("%d",&j) && j >= 0){
		cases++;
		scanf("%s",s);
		m = strlen(s);
		if (m <= 2){
		  printf("Case %d: 0/1\n",cases);
		  continue;
		}
		if (j == 0){
			 sscanf(s+2,"%lld",&frac);
			 n = frac;
			 d = pot_10(m - 2);
			 g = __gcd(n,d);
			 g = max(g,1LL);
			 n/=g;
			 d/=g;
			 printf("Case %d: %lld/%lld\n",cases,n,d);
		}
		else {
			 int last = m - 1;
			 int first = last - j + 1;
			 int next;
			 int len = m - 2 - j;
			 while (len >= j){
				next = first - j;
				if (cmp(first,next,j)){
					first = next;
					last = first + j - 1;
					len -= j;
				}
				else {
				  break;
				}
			 }
			 s[last + 1] = '\0';
			 k = first - 2;
			 sscanf(s+2,"%lld",&frac);
			 n = frac - frac/pot_10(j);
			 d = pot_10(j + k) - pot_10(k);
			 g = __gcd(n,d);
			 n/=g;
			 d/=g;
			 printf("Case %d: %lld/%lld\n",cases,n,d);
		}
  }
  return 0;
}