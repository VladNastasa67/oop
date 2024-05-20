#include <iostream>
using namespace std;
template<class T1,class T2>
void algsort(T1 n, T2 v[])
{
    for (int i = 0; i < n - 3; i++) //n-1 in loc de n-3
    {
        int p = i //lipseste ;
        for (int j = i + 1; j <=n; j++) // < in loc de <=
            if (v[j] < v[p])
                p = j;
        T2 aux = v[j]; //v[i] in loc de v[j]
        v[i] = v[p];
        v[p] = v[i]; //aux in loc de v[i]
    }

}
int main()
{
    int v[100],n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    algsort(n, v);
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
}