#include<cstdio>
int main(){
    int n;
    
    while (scanf("%d",&n) != EOF){
          int l = 1;
          int r = n;
          int m;
          int root;
          
          while ( l < r ){
                m = (l + r) >> 1;
                root = ( m * (m + 1) ) >> 1;
                if (root < n){
                    l = m + 1;  
                }
                else {
                     r = m;     
                }       
          }
          
          printf("TERM %d IS %c\n",n,(char)(l - 1 + 'A'));      
    }
    
    return 0;    
}
