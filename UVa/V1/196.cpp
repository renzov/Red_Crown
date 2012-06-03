#include<cstdio>
#include<cstring>
#include<vector>
#include<cctype>

using namespace std;

vector< vector<int> > G;
vector< bool > visited;
vector< int > value;
int R,C;

void dfs(int u){
  int v;
  visited[u] = true;
  value[u] = 0;
  for (int i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 if (!visited[v]) dfs(v);
	 value[u] += value[v];
  }
}

int getCol(char *c){
  int n = strlen(c);
  int pot = 1;
  int r = 0;
  
  while (n>0){
	r += pot*( c[n-1]-'A' + 1 );
	pot*=26;
	n--;
  }
  return r - 1;
}

void parseInput(char *def,int u){
  int p = 1;
  int n = strlen(def);
  int s;
  int fin;
  char cad[10];
  int col,row;

  //printf("inicio de parsing = %s\n",def);
  while (p < n){
	 fin = p;
	 s = 0;
	 while (isalpha(def[fin])){ 
		cad[s] = def[fin];
		s++;
		fin++;
	 }
	 cad[s] = '\0';
	 //printf("Se obtuvo row = %s\n",cad);
	 col = getCol(cad);
	 p = fin;
	 s = 0;
	 while (isdigit(def[fin]) && fin < n){ 
		cad[s] = def[fin];
		s++;
		fin++;
	 }
	 p = fin;
	 cad[s] = '\0';
	 //printf("Se obtuvo col = %s\n\n",cad);
	 sscanf(cad,"%d",&row);
	 row--;
	 G[u].push_back(row*C + col);
	 p++;
  }

}

int main(){

  int runs;
  char def[5000000];
  scanf("%d",&runs);
  while (runs--){
	 G.clear();
	 visited.clear();
	 value.clear();
	 scanf("%d %d",&C,&R);
	 G.resize( R*C );
	 visited.resize( R*C );
	 value.resize( R*C );
	 for (int i=0; i < R; ++i)
		for (int j=0; j < C; ++j){
			 scanf("%s",def);
			 if (def[0]!='='){
				visited[i*C + j] = true;
				sscanf(def,"%d",&value[i*C + j]);
			 }	
			 else {
				visited[i*C + j] = false;
				parseInput(def,i*C + j);
			 }
		}
		for (int i=0; i < R*C; ++i){
		  if (!visited[i]){
			 dfs(i);
		  }
		}
		for (int i=0; i < R; ++i){
		  printf("%d",value[i*C]);
		  for (int j=1; j < C; ++j)
			 printf(" %d",value[i*C + j]);
		  putchar('\n');
		}
  }
  return 0;
}