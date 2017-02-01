#include<cstdio>
#include<cstring>

char line[100];
int p;
int n;

char get_next(){
  if (p >= n) return -1;
  return line[p++];
}

void unget(){
  if (p > 0) p--;
  else puts("Error");
}

bool isSlump(){
  char c = get_next();
  if (c != 'D' && c != 'E') return false;
  c = get_next();
  if (c != 'F') return false; /* Enforcing at least one 'F' */
  while ( ( c = get_next() ) == 'F');
  if (c == -1) return false; /* Not enough */
  if (c == 'G') return true;
  unget();
  return isSlump();
}

bool isSlimp(){
	 char c = get_next();
	 if (c != 'A') return false;
	 c = get_next();
	 if (c == -1) return false;
	 if (c == 'H') return true;
	 if (c == 'B'){
		  return isSlimp() && (get_next() == 'C');
	 }
	 unget();
	 return isSlump() && (get_next() == 'C');
}

bool isSlurpy(){
  return isSlimp() && isSlump() && (get_next() == -1);
}

int main(){
  
  int runs;
  scanf("%d",&runs);
  puts("SLURPYS OUTPUT");
  while (runs--){
	 scanf("%s",line);
	 n = strlen(line);
	 p = 0;
	 if (isSlurpy()) puts("YES");
	 else puts("NO");
  }
  puts("END OF OUTPUT");
  return 0;
}