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

    set<int> s; 

    int main(void)
    {
        ios::sync_with_stdio(false); cin.tie(nullptr);
        int N; cin >> N;
        vi viaje(N);
        vi valores_iniciales; valores_iniciales.reserve(N);

        int anterior = 0, nval;

        vi::iterator l, x;
        reverse_iterator<vi::iterator> r, y;

        ffor(i, N) {
            cin >> viaje[i];
            s.insert(i + 1);
            valores_iniciales.emplace_back(viaje[i]);
        }

        for(int &i : valores_iniciales) {
            s.erase(i);
        }

        l = viaje.begin(); r = viaje.rbegin();

        nval = 0;
        while(nval < N)
        {
            nval++;
            // for(int &i : viaje) cout << i << " ";
            // cout << endl;
            bool ya_esta = s.count(nval) == 0;

            if(ya_esta and !(*l == nval or *r == nval))
            {
                goto fallo;
            }

            if(*l == nval or *r == nval)
            {
                if(*l == nval)
                {
                    l++;
                }
                else
                {
                    r++;
                }
            }
            else if(*l == 0 or *r == 0)
            {
                if(*l == 0 and *r == 0)
                {
                    x = find_if(l, viaje.end(), [](int v){return v != 0;});
                    y = find_if(r, viaje.rend(), [](int v){return v != 0;});

                    if(x == viaje.end() or y == viaje.rend())
                    {
                        goto desempate;
                    }
                    else if(*x == *y)
                    {
                        desempate:
                        if(distance(l, x) < distance(r, y))
                        {
                            *l = nval; l++;
                        }
                        else
                        {
                            *r = nval; r++; 
                        }
                    }
                    else if(*x < *y)
                    {
                        *l = nval; l++;
                    }
                    else
                    {
                        *r = nval; r++;
                    }
                }
                else if(*l == 0)
                {
                    *l = nval; l++;
                }
                else
                {
                    *r = nval; r++;
                }
            }
            else
            {
                goto fallo;
            }
        }

        exito:
        for(int &i : viaje) cout << i << " ";
        cout << endl;
        // for(const int &i : s) cout << i << " ";
        // cout << endl;
        return 0;

        fallo:
        cout << "*";
        
        return 0;
    }

    /*

        Hay N estaciones desde 1 hasta N, el numero indica la altitud.
        El viaje consiste SÍ o SÍ en una subida seguida de una bajada, no se puede bajar y volver a subir ni subir y volver a bajar sin antes llegar a la cima.
        De modo que un viaje, que incluye todas las estaciones, pasa en algún punto por la cima N.
        En la secuencia de viaje solo hay subida hasta que aparece la estación N, y luego solo hay bajada.
        En el caso N = 5, 3 0 5 0 0; la segunda estación solo puede un numero mayor que 3 y menor que N, es decir, solo puede ser 4.
        Y los siguientes 0's solo pueden ser 2, 1 en ese orden, porque si fuese 1, 2 sería una subida, lo que no se permite. 

        Un poco retrasado de mi parte el haberlo intentado de forma tan naive.
        La cosa se reduce a que es una permutación de tipo montaña.
        Si analizas bien la cosa se extrapola que la estación 1 solo puede estar al principio o al final,
        porque si no está al principio no puede estar en ninguna parte de la subida, y en la bajada solo puede estar de ultima.
        Y si no está al final, solo puede estar al principio. Y esto se cumple de forma recursiva con todo numero mayor.

        Al final la solución consistía en un concepto clave y no en la situación pintada.
        Inicié con una especie de adhoc, el enunciado parecía hacerte pensar que se trataba de un problema de recorrido de grafos.
        Pero al final se trataba de construcción de permutaciones.

        La solución se resume en:
        guardar la entrada tal cual te la dan, tener guardados los elementos ya presentes, y proceder de la siguiente manera:
        iterar desde 1 hasta N, chequear si el numero ya está en la lista, si no está en los extremos de la ventana, está malo.
        Si está en los extremos, es valido, siguiente numero.
        Si no está presente, chequear si los extremos están vacíos.
        Si está uno solo vacío, ahí va.
        Si están ambos vacíos, se buscan los numeros diferentes de cero mas cercanos (en dirección al centro) a cada extremo.
        Y se elige el lado más restringido, de modo que se resuelva ese lado primero y luego el que tiene más libertades.
    */