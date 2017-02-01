#include<cstdio>
#include<cctype>
int main(){
  char line[10];
  puts("Ready");
  while (1){
		gets(line);
		if (line[0] == ' ' && line[1] == ' ') break;
		if ( (tolower(line[0])== 'b' && tolower(line[1]) == 'd') || 
			  (tolower(line[0])== 'd' && tolower(line[1]) == 'b') ||
			  (tolower(line[0])== 'q' && tolower(line[1]) == 'p') ||
			  (tolower(line[0])== 'p' && tolower(line[1]) == 'q')
			 ) 
		  puts("Mirrored pair");
		else 
		  puts("Ordinary pair");
  }
  return 0;
}