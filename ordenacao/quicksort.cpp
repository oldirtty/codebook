// O(N * logN)
int partition(vector<int>& vet, int left, int right) {
  int mid = left + (right - left) / 2;
  int pivot = vet[mid];
  swap(vet[mid], vet[right]);
  int i = left - 1;
  for (int j = left; j < right; j++) {
    if (vet[j] <= pivot) {
      i++;
      swap(vet[i], vet[j]);
    }
  }
  swap(vet[i + 1], vet[right]);
  return i + 1;
}


// Chamada => quick_sort(v, 0, v.size() - 1);
void quick_sort(vector<int>& vet, int left, int right) {
  if (left < right) {
    int pivot = partition(vet, left, right);
    quick_sort(vet, left, pivot - 1);
    quick_sort(vet, pivot + 1, right);
  }
}
