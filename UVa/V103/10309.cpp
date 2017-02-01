#include<cstdio>
#include<cstring>
char name[ 300 ];
char M[10][10];

void apply(char tmp[10][10],int mask,int &p){
  for (int j=0; j < 10; ++j){
		if ((mask >> j) & 1){
		  if (j > 0){ 
				tmp[0][j-1] = (tmp[0][j-1] == '#')? 'O':'#';
		  }
		  if ((j + 1) < 10){
				tmp[0][j+1] = (tmp[0][j+1] == '#')? 'O':'#';
		  }
		  tmp[1][j] = (tmp[1][j] == '#')? 'O':'#';
		  tmp[0][j] = (tmp[0][j] == '#')? 'O':'#';
		  p++;
		}
  }
}

int main(){

  char tmp[10][10];
  int best;
  int res;
  bool ok;
  
  while (scanf("%s",name) && strcmp(name,"end")){

		for (int i=0; i < 10; ++i)
		  scanf("%s",M[i]);

		best = 105;

		for (int k=0; k < 1024; ++k){
			 
			 for (int j=0; j < 10; ++j)
				strcpy(tmp[j],M[j]);
			 
			 res = 0;
				
			 apply(tmp,k,res);
			
			 ok = true;
			 
			 for (int i=1; i < 10 && res < best; ++i)
				for (int j=0; j < 10 && res < best; ++j){
				  if (tmp[i-1][j] == 'O' ){
					 if (j > 0){ 
						 tmp[i][j-1] = (tmp[i][j-1] == '#')? 'O':'#';
					 }
					 if ((j + 1) < 10){
						 tmp[i][j+1] = (tmp[i][j+1] == '#')? 'O':'#';
					 }
					 if ((i+1) < 10){
						 tmp[i+1][j] = (tmp[i+1][j] == '#')? 'O':'#';
					 }
					 tmp[i][j] = (tmp[i][j] == '#')? 'O':'#';
					 tmp[i-1][j] = '#';
					 res++;
				  }
				}
			 for (int i=0;(res < best) && (i < 10) && ok; ++i)
				if (tmp[0][i] != '#' || tmp[9][i] != '#') ok = false;
			 if (ok && res < best){
				best = res;
			 }
		}
		printf("%s %d\n",name,(best <= 100)? best:-1);
  }

  return 0;

}