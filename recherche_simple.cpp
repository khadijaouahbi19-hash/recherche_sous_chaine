#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;

int recherche(string& m1, string& m2)
{
    string petit, grand;

    if (m1.size() < m2.size())
    {
        petit = m1;
        grand = m2;
    }
    else
    {
        petit = m2;
        grand = m1;
    }

    int i = 0, j = 0;

    while (i < petit.size() && j < grand.size())
    {
        if (petit[i] == grand[j])
        {
            i++;
        }

        j++;
    }

    return i == petit.size();
}

int main()
{
    string m1, m2;

    // Saisie des deux chaînes
    cout << "Entrez la premiere chaine : ";
    cin >> m1;

    cout << "Entrez la deuxieme chaine : ";
    cin >> m2;

    // Début du chronométrage
    auto debut = high_resolution_clock::now();

    // Appel de la fonction
    int resultat = recherche(m1, m2);

    // Fin du chronométrage
    auto fin = high_resolution_clock::now();

    // Calcul du temps en microsecondes
    auto duree = duration_cast<microseconds>(fin - debut);

    // Affichage du résultat
    if (resultat)
    {
        cout << "\nLes deux chaines sont compatibles." << endl;
    }
    else
    {
        cout << "\nLes deux chaines ne sont pas compatibles." << endl;
    }

    cout << "Temps d'execution : "
         << duree.count()
         << " microsecondes" << endl;

    return 0;
}