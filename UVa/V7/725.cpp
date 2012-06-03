#include<cstdio>

int main(){
    
    int n;
    int used[12] = {0};
    int num;
    int den;
    bool ok;
    bool sol;
    int cases = 0;
    while (scanf("%d",&n) && n){
          cases++;
          if (cases > 1) putchar('\n');
          sol = false;
          used[0] = used[1] = used[2] = used[3] = used[4] = used[5] = used[6] = used[7] = used[8] = used[9] = 0;
          for (int i=0; i < 10; ++i){
              if (!used[i]){
                 used[i]++;
                 for (int j=0; j < 10; ++j){
                     if (!used[j]){
                        used[j]++;
                        for (int k=0; k < 10; ++k){
                            if (!used[k]){
                               used[k]++;
                               for (int l=0; l < 10; ++l){
                                   if (!used[l]){
                                      used[l]++;
                                      for (int m=0; m < 10; ++m){
                                          if (!used[m]){
                                             used[m]++;
                                             num = i*10000 + j*1000 + k*100 + l*10 + m;
                                             if (num % n == 0){
                                                den = num / n;
                                                ok = true;
                                                for (int t=0; t < 5;++t){
                                                   used[den%10]++;
                                                   den/=10;      
                                                }
                                                for (int z=0; z < 10; ++z)
                                                    if (used[z] > 1){
                                                       ok = false;
                                                       break;            
                                                    }
                                                den = num / n;
                                                for (int t=0; t < 5;++t){
                                                   used[den%10]--;
                                                   den/=10;      
                                                }
                                                if (ok){
                                                   den = num / n;
                                                   sol = true;
                                                   printf("%05d / %05d = %d\n",num,den,n);        
                                                }        
                                             }
                                             used[m]--;              
                                          }    
                                      }
                                      used[l]--;              
                                   }    
                               }
                               used[k]--;
                            }    
                        }
                        used[j]--;              
                     }    
                 }
                 used[i]--;              
              }    
          }
          if (!sol) printf("There are no solutions for %d.\n",n);           
    }
    return 0;    
}
