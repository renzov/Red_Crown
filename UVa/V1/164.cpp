#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int dp[30][30];
int op[30][30];
char X[30];
char Y[30];
int n,m;

void recurse(int x,int y,int &del,int &is){
	//printf("Pos (%d,%d) ",x,y);
	if (x==0 && y==0) return;
	if (op[x][y] == 1){ recurse(x-1,y-1,del,is); }
	else if (op[x][y] == 2){
		//printf("2\n");
		recurse(x-1,y,del,is);
		printf("D%c%02d",X[x-1],x - del + is);
		del++;
	}
	else if (op[x][y] == 3){
		//printf("3\n");		
		recurse(x-1,y-1,del,is);
		printf("C%c%02d",Y[y-1],x - del + is);
	}
	else {
		//printf("4\n");
		recurse(x,y-1,del,is);
		printf("I%c%02d",Y[y-1],x+1-del+is);
		is++;
	}
}

int main(){
	int ins;
	int del;
	int change;
	char line[400];
	while (gets(line) && strcmp(line,"#")){
		X[0] = Y[0] = '\0';
		char *p = strchr(line,' ');
		*p = '\0';
		sscanf(line,"%s",X);
		*p = ' ';
		sscanf(p,"%s",Y);
		n = strlen(X);
		m = strlen(Y);

		for (int i=0; i <= n; ++i){
			dp[i][0] = i;		
			if (i != 0)			
				op[i][0] = 2; /* delete */		
		}
		for (int i=0; i <= m; ++i){
			dp[0][i] = i;
			if (i!=0)
				op[0][i] = 4; /* insert */
		}
		for (int j=1; j <= m; ++j){
			for (int i=1; i <= n; ++i){
				if (X[i-1] == Y[j-1]){
					dp[i][j] = dp[i-1][j-1];
					op[i][j] = 1;
				}
				else {
					del = dp[i-1][j] + 1;		
					ins = dp[i][j-1] + 1;			
					change = dp[i-1][j-1] + 1;
					dp[i][j] = min( del , min(ins , change) );
					if (dp[i][j] == ins){ op[i][j] = 4; }
					else if (dp[i][j] == change){ op[i][j] = 3; }
					else { op[i][j] = 2; }
				}			
			}
		}		
		int d = 0;
		int i = 0;
		recurse(n,m,d,i);
		putchar('E');
		putchar('\n');
	}
	return 0;
}
