#include<cstdio>
int dx[]={-1,1,-2,2,-2,2,-1,1};
int dy[]={-2,-2,-1,-1,1,1,2,2};


  

int main(){

  int runs;
  int x,y,nx,ny;
  char pos[4];
  int res;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%s",pos);
	 x = pos[0] - 'a';
	 y = 8 - (pos[1] - '0');
	 res = 0;
	 for (int i=0; i<8; ++i){
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx<0||ny<0||ny>=8||nx>=8) continue;
		res++;
	 }
	 printf("%d\n",res);
  }
  return 0;
}