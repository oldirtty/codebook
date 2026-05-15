#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace __gnu_pbds;

// ordered_set s;
// s.insert(10); s.insert(20); s.insert(30);
// O(logN):
// s.find_by_order(1); // Retorna iterador para o 20 (s[i])
// s.order_of_key(30); // Retorna 2 (posição do valor X no set)
