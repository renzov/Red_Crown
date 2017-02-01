#include<cstdio>
#include<numeric>
#include<map>
#include<cstdlib>
#include<cstring>
using namespace std;
struct point {
   int x,y;
};

int gcd(int a,int b){
	while (b > 0){
		a = a % b;
		a ^= b;
		b ^= a;
		a ^= b;
	}
	return a;
}

int main(){
    
    int n = 0;
    map< pair<int,int> , int > H;
    int tmp;
    int best;
    int B;
    point p[1000];
    int runs;
	 char line[1000];

	 scanf("%d",&runs);
	 while (getchar() != '\n');
	 gets(line);
	 while (runs--){
		n = 0;
		while (1){
			if (!gets(line)) break;
			if (strlen(line) == 0) break;
			sscanf(line,"%d %d",&p[n].x,&p[n].y);          
			n++;      
    	}
    	int u,v,g;
    	B = 0;
    	for (int i=0; i < n; ++i){
        /* Tomamos el punto i como base */
        H.clear();
        best = 1;
        for (int j=0; j < n; ++j){
            if (i!=j){
               u = abs( p[j].x - p[i].x );                
               v = abs( p[j].y - p[i].y );
               g = gcd(u,v);
               if (g){
                  u/=g;
                  v/=g;
               }
               tmp = ++H[ make_pair(u,v) ];
               if (tmp > best) best = tmp;
            }    
        }
        if ((best + 1) > B) B = best + 1;    
    	}
    	printf("%d\n",B);
		if (runs) putchar('\n');
	 }	
   return 0;    
}
