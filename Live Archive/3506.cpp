#include <cstdio>

int abs(int i) { return i<0? -i : i; }
 
// table de hashage int -> int pour representer des multi-ensembles.
// h[v] va etre le nombre d'occurrences de v dans le multiensemble
// code par h.
struct hash_map_int_int {
  static const int N=32000011;    // prochain nombre premier apres 4000*4000*2
  int v[N], n[N];                 // v=valeur (cle), n=nombre d'occurences(val)
  hash_map_int_int() {
    for (int i=0; i<N; i++)       // initialement vide
      n[i] = 0;
  }
  void init(){
	 for (int i=0; i<N; i++)       // initialement vide
      n[i] = 0;
  }
  unsigned int hash1(unsigned int a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
  }
  unsigned int hash2(unsigned int a) {
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
  }
  int idx(int i) {                // double hashage
    int k=hash1(i)%N, offset = hash2(i)%(N-1)+1;
    while (v[k]!=i && n[k]!=0)
      k = abs(k+offset)%N;
    return k;
  }
  void add(int i) {               // ajouter i au multi-ensemble
    int k = idx(i);
    v[k] = i;
    n[k]++;
  }
  int operator[](int i) {         // retourner la valeur associee `a la cle i
    return n[idx(i)];
  }
};
const int N=4000;
int A[N],B[N],C[N],D[N];
hash_map_int_int cd; 

int main() {
  int n;
  int runs;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		for (int i=0; i<n; i++)
		  scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
		// cd[i] : nombre de c dans C et d dans D tel que c+d==i
		for (int i=0; i<n; i++)
		  for (int j=0; j<n; j++)
			 cd.add(C[i]+D[j]);
		// r : nombre de quadruplets sommant a zero
		long long r=0;
		for (int i=0; i<n; i++)
		  for (int j=0; j<n; j++) {
			 r+= cd[-A[i]-B[j]];
		}
		printf("%lld\n", r);
		if (runs){
		  putchar('\n');  cd.init();
		}
  }
  return 0;
}