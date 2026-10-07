#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;

bool remplacerToutes(string& mot, const string& sousChaine, const string& remplacement)
{
    bool modifie = false;
    size_t position = 0;

    while ((position = mot.find(sousChaine, position)) != string::npos)
    {
        mot.replace(position, sousChaine.length(), remplacement);
        position += remplacement.length();
        modifie = true;
    }

    return modifie;
}

int main()
{
    string sousChaine;
    string remplacement;
    string mot;

    vector<string> motsModifies;   // mots APRÈS remplacement

    cout << "Entrez la sous-chaine a rechercher : ";
    cin >> sousChaine;
    cout << "Entrez la sous-chaine de remplacement : ";
    cin >> remplacement;

    ifstream fichier("fichier.txt");

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    // ------------------------------------------------
    // Mesure du temps : lecture + remplacement
    // ------------------------------------------------
    auto debut = steady_clock::now();

    while (fichier >> mot)
    {
        if (remplacerToutes(mot, sousChaine, remplacement))
        {
            motsModifies.push_back(mot);
        }
    }

    auto fin = steady_clock::now();
    duration<double, milli> duree = fin - debut;

    fichier.close();


    int nombreResultats = motsModifies.size();

    if (nombreResultats > 0)
    {
        cout << "\nNombre de mots contenant \"" << sousChaine
             << "\" : " << nombreResultats << endl;

        // Vérification : aucun mot modifié ne doit encore contenir la sous-chaîne
        bool remplacementCorrect = true;
        for (const string& m : motsModifies)
        {
            if (m.find(sousChaine) != string::npos)
            {
                remplacementCorrect = false;
                break;
            }
        }

        if (remplacementCorrect)
            cout << "Verification : remplacement effectue correctement." << endl;
        else
            cout << "Attention : certains mots contiennent encore la sous-chaine." << endl;

     }
    else
    {
        cout << "Aucun mot ne contient \"" << sousChaine << "\"." << endl;
    }

    cout << "\nTemps de traitement : " << duree.count() << " ms" << endl;

    return 0;
}