#include <iostream>
#include <string>
#include "dictionar.h"

using namespace std;
int main() {
    Dictionar<string, int> d;

    d["cheie1"] = 10;
    d["cheie2"] = 20;

    cout << "Valoarea pentru cheia 'cheie1': " << d["cheie1"] << endl;
    cout << "Valoarea pentru cheia 'cheie2': " << d["cheie2"] << endl;

    return 0;
}