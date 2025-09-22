#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pi = pair<int,int>;
using pll = pair<ll,ll>;

#define mp make_pair
#define f first
#define s second 
#define all(x) x.begin(), x.end()

#define ffor(x, y) for(int x = 0; x < y; x++)
#define log(x) cout << x << "\n"
#define dbg(x) cout << #x << " : " << x << "\n"

const ll MOD = 1000000007;
const ll IMOD = 500000004;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    map<char, int> oc;
    string s; cin >> s;
    ll n; cin >> n;

    vector<ll> l(s.size(), 0), r(s.size(), 0);
    
    ffor(i, s.size())
    {
        char c = s[i];
        oc[c]++;
        for(auto &[k, v] : oc){
            if(k >= c) break;
            l[i] += v;
        }
    }
    ffor(i, s.size())
    {
        char c = s[i];
        for(auto &[k, v] : oc){
            // cout << c << ", " << k << endl;
            if(k >= c) break;
            // cout << "sumado = " << v << " - " << l[i] << endl;
            r[i] += v;
        }
        r[i] -= l[i];
    }

    ll res = 0;

    // ffor(i, s.size())
    // {
    //     res += l[i] * (n - 1) * (n / 2);
    //     res += r[i] * n * (n + 1) / 2;
    // }

    ll n_mod = n % MOD; // Trabajar siempre con n modulo MOD

    // 2. Calcular coef_l de forma modular
    ll n_minus_1_mod = (n_mod - 1 + MOD) % MOD; // (n-1) % MOD
    ll term_l_num = (n_minus_1_mod * n_mod) % MOD;   // (n-1)*n % MOD
    ll coef_l = (term_l_num * IMOD) % MOD;         // ((n-1)*n / 2) % MOD

    // 3. Calcular coef_r de forma modular
    ll n_plus_1_mod = (n_mod + 1) % MOD;           // (n+1) % MOD
    ll term_r_num = (n_mod * n_plus_1_mod) % MOD;   // n*(n+1) % MOD
    ll coef_r = (term_r_num * IMOD) % MOD;         // (n*(n+1) / 2) % MOD

    // 4. Realizar el bucle con operaciones modulares
    for (ll i = 0; i < s.size(); i++) {
        // Calcular la contribución de l[i]
        ll term_l = (l[i] * coef_l) % MOD;

        // Calcular la contribución de r[i]
        ll term_r = (r[i] * coef_r) % MOD;
        
        // Sumar ambas contribuciones al resultado
        res = (res + term_l) % MOD;
        res = (res + term_r) % MOD;
    }


    // for(char &c : s){
    //     cout << c << ": l, r = " << l[di] << ", " << r[di++] <<"\n";
    // }


    // int i = 0;

    // cout << "OCs\n";
    // for(auto &[k, v] : oc){
    //     cout << k << ", " << v << "\n";
    //     i++;
    // }



    
    cout << res << "\n";
    
    return 0;
}

/*

    Mi suposición, basado en pruebas empíricas, es la siguiente:
    el número de inversiones se puede calcular calculando dos valores para cada letra del string original,
    l y r. l es el número de letras a la izquierda de la letra actual con las cuales causaría una inversión,
    r es el número de letras que causan una inversión a la derecha de la letra actual.
    Se puede sumar el resultado final calculando = l * (n - 1) + r * n, para cada letra y cada valor de n hasta 1.
    

*/