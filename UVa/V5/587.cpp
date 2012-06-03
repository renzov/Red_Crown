#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
const double diag = 1.0/sqrt(2.0);
char line[500];
double dx[]={1,diag,0,-diag,-1,-diag,0,diag};
double dy[]={0,diag,1,diag,0,-diag,-1,-diag};

int get_dir( char *s ){
  if ( s[0] == 'N' ){
	 if ( s[1] == 'W' ) return 3;
	 else if ( s[1] == 'E' ) return 1;
	 else return 2;
  }
  else if ( s[0] == 'S' ){
	 if ( s[1] == 'W' ) return 5;
	 else if ( s[1] == 'E' ) return 7;
	 else return 6;
  }
  else if ( s[0] == 'W' ){
	 return 4;
  }
  else {
	 return 0;
  }
}

int main(){
  double x,y;
  int len;
  int idx;
  char s[5];
  char *ptr;
  int runs = 0;
  while ( scanf("%s",line) && strcmp(line,"END") ){
	 runs++;
	 x = y = 0;
	 ptr = strtok( line , ",." );
	 while ( ptr != NULL ){
		sscanf(ptr,"%d%s",&len,s);
		idx = get_dir( s );
		x += len*dx[idx]; y += len*dy[idx];
		ptr = strtok(NULL,",.");
	 }
	 printf("Map #%d\n",runs);
	 printf("The treasure is located at (%0.3lf,%0.3lf).\n",x,y);
	 printf("The distance to the treasure is %0.3lf.\n",hypot(x,y));
	 puts("");
  }
  return 0;
}