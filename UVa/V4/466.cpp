#include<cstdio>
#include<cctype>
int n;
char p[15][15];
char s[15][15];
char t[15][15];

bool no_move(){
  for (int i=0; i < n; ++i)
	 for (int j=0; j < n; ++j)
		if (p[i][j] != s[i][j]) return false;
  return true;
}

void rotate_90(){
	 for (int i=0; i < n; ++i){
		  for (int j=0; j < n; ++j)
				t[j][n-i-1] = p[i][j];
	 }
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  p[i][j] = t[i][j];
}

void rotate_90_rev(){
	 for (int i=0; i < n; ++i){
		  for (int j=0; j < n; ++j)
				t[n-j-1][i] = p[i][j];
	 }
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  p[i][j] = t[i][j];
}

void vertical(){
  for (int i=0; i < n; ++i){
		for (int j=0; j < n; ++j)
		  t[n-i-1][j] = p[i][j];
  }
  for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  p[i][j] = t[i][j];
}

int main(){
  int runs = 0;
  
  while (scanf("%d",&n) != EOF){
	 runs++;
	 for (int i=0; i < n; ++i){
		  scanf("%s",p[i]);
		  scanf("%s",s[i]);
		  for (int j=0; j < n; ++j){
			 s[i][j] = toupper(s[i][j]);
			 p[i][j] = toupper(p[i][j]);
		  }
	 }
	 if ( no_move() ){
		printf("Pattern %d was preserved.\n",runs);
		continue;
	 }
	 bool found = false;
	 for (int i=90; i < 360 && !found; i+=90){
		  rotate_90();
		  if (no_move()){ printf("Pattern %d was rotated %d degrees.\n",runs,i); found = true; }
 	 }
	 if (!found){
		rotate_90();
		vertical();
		if ( no_move() ){
		  printf("Pattern %d was reflected vertically.\n",runs);
		  found = true;
		}
		for (int i=270; i > 0 && !found; i-=90){
		  rotate_90_rev();
		  if (no_move()){ printf("Pattern %d was reflected vertically and rotated %d degrees.\n",runs,i); found = true; }
 	   }
		if (!found) printf("Pattern %d was improperly transformed.\n",runs);
	 }
  }
  return 0;
}