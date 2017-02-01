#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string line;
char sc[15][15];

int main(){
	string tmp;
	int n;
	int p;
	bool over;
	int r,c;
	int cases = 0;
	while (cin >> n && n){
		cases++;
		getline(cin,tmp);
		line = "";
		for (int i=0; i < n; ++i){
			getline(cin,tmp);
			line += tmp;
		}
		/* inicializacion */
		r = c = 0;
		over = true;
		p = 0;
		for (int i=0; i < 10; ++i) for (int j=0; j < 10; ++j) sc[i][j] = ' ';
		/* */
		while (p < line.size()){
			if (line[p] == '^'){
				/* control */
				p++;
				if (isdigit(line[p])){
					r = line[p]-'0';
					c = line[p+1]-'0';
					p++;
				}
				else if (line[p]=='^'){
					if (over){ sc[r][c] = line[p]; }
					else {
						for (int i=9; i > c ;--i) sc[r][i] = sc[r][i-1]; 
						sc[r][c] = line[p]; 
					}
					if (c < 9) c++;
				}
				else {
					switch( line[p] ){
						case 'b' : c = 0; break;
						case 'c' : for (int i=0; i < 10; ++i) for (int j=0; j < 10; ++j) sc[i][j] = ' '; break;
						case 'd' : if (r < 9) r++; break;
						case 'e' : for (int i=c; i < 9; ++i) sc[r][i] = sc[r][i+1];
								   sc[r][9] = ' ';
								   break;
						case 'h' : r = c = 0; break;
						case 'i' : over = false; break;
						case 'l' : if (c > 0) c--; break;
						case 'o' : over = true; break;
						case 'r' : if (c < 9) c++; break;
						case 'u' : if (r > 0) r--; break;
					}
				}
			}
			else {
				if (over){ sc[r][c] = line[p]; }
				else { 
					for (int i=9; i > c ;--i) sc[r][i] = sc[r][i-1]; 
					sc[r][c] = line[p]; 
				}
				if (c < 9) c++;
			}
			
			p++;
		
		}
		printf("Case %d\n",cases);
		putchar('+');
		for (int i=0; i < 10; ++i) putchar('-');
		putchar('+');
		putchar('\n');
		for (int i=0; i < 10; ++i){
			putchar('|');
			for (int j=0; j < 10; ++j) putchar(sc[i][j]);
			putchar('|');
			putchar('\n');
		}
		putchar('+');
		for (int i=0; i < 10; ++i) putchar('-');
		putchar('+');
		putchar('\n');
	}

	return 0;
}