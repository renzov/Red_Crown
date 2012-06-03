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
int res;

bool check(int m,int u){
  for (int i=0; i < m; ++i){
	 if (G[u][sol[i]-'A']) return false;
  }
  return true;
}

void backtrack(int p){
	 if (p==n){
		sol[p] = '\0';
		printf("%c",sol[0]);
		for (int i=1; sol[i]; ++i)
			printf(" %c",sol[i]);
		putchar('\n');
		res++;
		return;
	 }
	 for (int i=0; i < n; ++i){
		if (!used[i] && check(p,vertex[i]-'A')){
		  used[i] = true;
		  sol[p] = vertex[i];
		  backtrack(p+1);
		  used[i] = false;
		}
	 }
}

int main(){
  int u,v;
  int runs;
  char line[5000];
  
  scanf("%d",&runs);
  while (getchar() != '\n');
  
  while (runs--){
	 n = 0;
	 gets(line); /* Linea en blanco */
	 gets(line);
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
			 u = line[i] - 'A';
			 i++;
			 while(!isalpha(line[i])) i++;
			 v = line[i] - 'A';
			 G[u][v] = true;
		 }
	 }
	 res = 0;
	 backtrack(0);
	 if (res == 0) puts("NO");
	 if (runs) putchar('\n');
  }
  return 0;
}