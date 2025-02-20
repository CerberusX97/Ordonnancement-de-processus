/**
* \file Ordonneur.h
 * \brief Déclarations des fonctions d'ordonnancement pour le traitement des processus.
 *
 *        Ce fichier contient les prototypes des fonctions d'ordonnancement
 *        utilisées dans la simulation de gestion des processus. Ces fonctions
 *        prennent en entrée une file de processus et un temps donné, et retournent
 *        une file de processus ordonnancés selon la méthode spécifiée.
 *
 *        Les méthodes d'ordonnancement incluses sont :
 *        - FCFS (First-Come, First-Served)
 *        - FJS (Shortest Job First)
 *        - Round Robin
 *        - Priorité
 *        - Multiniveaux
 */

#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H
#include "File.h"
#include "Processus.h"


namespace TP {
  File<Processus> fcfs(const File<Processus>& f_entree, const int& temps);
  File<Processus> fjs(const File<Processus>& f_entree, const int& temps);
  File<Processus> round_robin(const File<Processus>& f_entree,const int& quantum, const int& temps);
  File<Processus> priorite(const File<Processus>& f_entree, const int& temps);
  File<Processus> multiniveaux(const File<Processus>& f_entree,const int& quantum, const int& temps);
}

#endif //ORDONNANCEUR_H
