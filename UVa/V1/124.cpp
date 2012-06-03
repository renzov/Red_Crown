#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;

bool G[30][30];
bool used[30];
int n;
char vertex[30];
char sol[30];

bool check(int m,int u){
  for (int i=0; i < m; ++i){
	 if (G[u][sol[i]-'a']) return false;
  }
  return true;
}

void backtrack(int p){
	 if (p==n){
		sol[p] = '\0';
		puts(sol);
		return;
	 }
	 for (int i=0; i < n; ++i){
		if (!used[i] && check(p,vertex[i]-'a')){
		  used[i] = true;
		  sol[p] = vertex[i];
		  backtrack(p+1);
		  used[i] = false;
		}
	 }
}

int main(){
  int u,v;
  int cases = 0;
  char line[500];
  
  while (gets(line)){
	 cases++;
	 n = 0;
	 for (int i=0; line[i] ; ++i)
		if (isalpha(line[i])){
		  vertex[ n++ ] = line[i];
 		}
	 sort(vertex,vertex+n);
	 gets(line);
	 memset(G,false,sizeof(G));
	 memset(used,false,sizeof(used));
	 for (int i=0; line[i]; ++i){
		 if (isalpha(line[i])){
			 u = line[i] - 'a';
			 i++;
			 while(!isalpha(line[i])) i++;
			 v = line[i] - 'a';
			 G[u][v] = true;
		 }
	 }
	 if (cases > 1) putchar('\n');
	 backtrack(0);
  }
  return 0;
}