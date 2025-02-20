#include <iostream>
#include <fstream>
#include "Processus.h"
#include "File.h"
#include "Ordonnanceur.h"
#include "ContratException.h"

using namespace std;

/**
 * \brief Charge un processus à partir d'une ligne de texte.
 * \param[in] ligne Une chaîne de caractères représentant les informations du processus.
 * \return Un objet Processus créé à partir des données fournies dans la ligne.
 *
 * La ligne doit contenir les éléments suivants, séparés par des espaces :
 * - ID du processus
 * - Temps d'arrivée
 * - Durée
 * - Priorité
 * - Type de processus (entier)
 */
Processus chargerProcessus(const string& ligne) {
    string id;
    int arrivee, duree, priorite;
    int type;

    istringstream ss(ligne);
    ss >> id >> arrivee >> duree >> priorite >> type;

    TypeProcessus processusType = static_cast<TypeProcessus>(type);

    return Processus(id, arrivee, duree, priorite, processusType);
}

/**
 * \brief Charge une file de processus à partir d'un fichier.
 * \param[in] nomFichier Le nom du fichier à charger.
 * \return Une File<Processus> contenant les processus chargés du fichier.
 *
 * Si le fichier ne peut pas être ouvert, un message d'erreur est affiché et le programme se termine.
 * Chaque ligne du fichier doit représenter un processus, formatée conformément à
 * la fonction `chargerProcessus`.
 */
File<Processus> ChargerFile(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cout << "Erreur de chargement du fichier: " << nomFichier << endl;
        exit(1);
    }

    File<Processus> fileProcessus;
    string ligne;

    while (getline(fichier, ligne)) {
        Processus p = chargerProcessus(ligne);
        fileProcessus.insererDernier(p);
    }
    fichier.close();

    return fileProcessus;
}

/**
 * \brief Point d'entrée du programme.
 *
 * Cette fonction charge plusieurs files de processus à partir de fichiers,
 * exécute différents algorithmes d'ordonnancement (FCFS, FJS, Round Robin, Priorité, Multiniveaux),
 * et affiche les résultats de chaque algorithme.
 *
 * Les fichiers chargés sont :
 * - "FCFS_FJS_Round"
 * - "Multiniveaux"
 * - "Priorite"
 *
 * Les résultats de chaque algorithme sont affichés dans la console.
 *
 * \return Un entier représentant le statut de sortie du programme (0 pour le succès).
 */
int main() {
    int temps = 0;
    int quantum = 4;

    File<Processus> fileGen = ChargerFile("FCFS_FJS_Round");
    File<Processus> file_multiniveaux = ChargerFile("Multiniveaux");
    File<Processus> file_priorite = ChargerFile("Priorite");

    File<Processus> fcfs = TP::fcfs(fileGen, temps);
    cout << fileGen.toString() << endl;
    cout << fcfs.toString() << endl;

    temps = 0;
    File<Processus> fjs = TP::fjs(fileGen, temps);
    cout << fjs.toString() << endl;

    temps = 0;
    File<Processus> round = TP::round_robin(fileGen, quantum, temps);
    cout << round.toString() << endl;

    temps = 0;
    File<Processus> priorite = TP::priorite(file_priorite, temps);
    cout << file_priorite.toString() << endl;
    cout << priorite.toString() << endl;

    temps = 0;
    File<Processus> multiniveaux = TP::multiniveaux(file_multiniveaux, quantum, temps);
    cout << file_multiniveaux.toString() << endl;
    cout << multiniveaux.toString() << endl;

    cout << "Fin du programme" << endl;
    return 0;
}