#include<cstdio>
int main(){
  int n;
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		int row = 0;
		int sum = row;
		while ((sum + (row + 1)) < n){ row++; sum += row; }
		bool inc;
		int x,y;
		if (row % 2){
			 x = 1;
			 y = row + 1;
			 inc = true;
		}
		else {
			 x = row + 1;
			 y = 1;
			 inc = false;
		}
		sum++;
		while (sum < n){
			if (inc) x++,y--;
			else x--,y++;
			sum++;
		}
		printf("TERM %d IS %d/%d\n",n,x,y);
  }
  
  return 0;
}