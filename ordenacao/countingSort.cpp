// O(N + K), K = max_val
void counting_sort(vector<int>& vet, int max_val) {
  vector<int> count(max_val + 1, 0);
  for (int x : vet) count[x]++;
  int idx = 0;
  for (int i = 0; i <= max_val; i++)
    while (count[i]--) vet[idx++] = i;
}