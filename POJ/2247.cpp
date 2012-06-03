#include<cstdio>
#include<set>
#include<cstring>
using namespace std;
long long res[ 5844 ];
int main(){
  set<long long> s;
  s.insert(1);
  for (int i=1; i <= 5842; ++i){
	 res[i] = *s.begin();
	 s.erase( s.begin() );
	 s.insert( res[i]*2 ); s.insert( res[i]*3 );
	 s.insert( res[i]*5 ); s.insert( res[i]*7 ); 
  }
  int n;
  int term;
  char st[5];
  while (scanf("%d",&n) && n){
	 term = (n/10)%10;
	 if (n%10 == 1 && term != 1) strcpy(st,"st");
	 else if (n%10 == 2 && term != 1) strcpy(st,"nd");
	 else if (n%10 == 3 && term != 1) strcpy(st,"rd");
	 else strcpy(st,"th");
	 printf("The %d%s humble number is %lld.\n",n,st,res[n]);
  }
}