// O(N * logN)
void merge(vector<int>& vet, int left, int mid, int right){
  vector<int> temp(right - left + 1);
  int i = left, j = mid + 1, k = 0;
  while (i <= mid && j <= right) {
    if (vet[i] <= vet[j])
      temp[k++] = vet[i++];
    else
      temp[k++] = vet[j++];
  }
  while (i <= mid)
    temp[k++] = vet[i++];
  while (j <= right)
    temp[k++] = vet[j++];
  for (i = left, k = 0; i <= right; i++, k++)
    vet[i] = temp[k];
}


// Chamada => merge_sort(vet, 0, vet.size() - 1);
void merge_sort(vector<int>& vet, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort(vet, left, mid);
    merge_sort(vet, mid + 1, right);
    merge(vet, left, mid, right);
  }
}
