#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;

char sol[1000];
bool used[1000] = {0};
char cad[1000];
int n;

bool cmp(const char &a,const char &b){
  if (toupper(a) != toupper(b)) return toupper(a) < toupper(b);
  return a < b;
}

void backtrack(int pos){
  if (n==pos){
	 sol[pos] = '\0';
	 puts(sol);
	 return;
  }
  char pred = '*';
  for (int i=0;i < n; ++i){
		if (!used[i] && pred != cad[i]){
			 sol[pos] = cad[i];
			 used[i] = true;
			 pred = cad[i];
			 backtrack(pos+1);
			 used[i] = false;
		}
  }
}

int main(){

  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%s",cad);
		n = strlen(cad);
		sort(cad,cad+n,cmp);
		backtrack(0);
  }

  return 0;
}