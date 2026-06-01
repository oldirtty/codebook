// O(N * log(logN))
vector <bool> eh_primo(TAM, true);
void crivo(int n) {
  eh_primo[0] = eh_primo[1] = false
   for (int p = 2; p * p <= n; p++) {
     if (eh_primo[p]) {
       for (int i = p * p; i <= n; i += p)
         eh_primo[i] = false;
     }
   }
}
