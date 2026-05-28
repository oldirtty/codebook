// O(logN); n = min(a,b)
// existe a função gdc()
ll mdc(ll a, ll b) {
   if (b == 0) return a;
   return mdc(b, a%b);
}

// existe a função lcm()
ll mmc(ll a, ll b) {
   return (a*b)/mdc(a,b);
}
