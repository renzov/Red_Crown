#include<cstdio>
#include<cstring>

char M[105][105];
int dx[]={ 1,1,0,-1,-1,-1,0,1};
int dy[]={0,-1,-1,-1, 0, 1, 1, 1};
char w[105];
int n;
int l;
int nx,ny;

bool match(int y,int x,int z){
	 for (int i=0; i < l; ++i){
		  if (M[y][x] != w[i]) return false;
		  if (i==(l-1)){
			 ny = y;
			 nx = x;
		  }
		  x += dx[z];
		  y += dy[z];
		  if (i < (l-1) && (x<0 || x >= n || y<0 || y>=n)) return false;
	 }
	 return true;
}

int main(){
  bool found;
  
  scanf("%d",&n);
  for (int i=0; i < n; ++i){
		scanf("%s",M[i]);
  }
  while (1){
	 scanf("%s",w);
	 if (w[0]=='0') break;
	 found = false;
	 l = strlen(w);
	 for (int i=0; i < n && !found; ++i)
		for (int j=0; j < n && !found; ++j)
		  for (int k=0; k < 8 && !found; ++k){
				if (w[0]==M[i][j] && match(i,j,k)){
					 found = true;
					 printf("%d,%d %d,%d\n",i+1,j+1,1 + ny,nx + 1);
				}
		  }
	 if (!found) puts("Not found");
  }

  return 0;
}