#include "Ordonnanceur.h"
#include "File.h"
#include "Processus.h"
#include <limits>
#include "ContratException.h"

namespace TP {
    /**
     * \brief Algorithme FCFS (First-Come, First-Served).
     *
     *        Cette fonction ordonne les processus selon leur ordre d'arrivée.
     *        Le premier processus arrivé est le premier à être servi.
     *
     * \param f_entree La file de processus d'entrée.
     * \param temps Le temps de décalage.
     * \return La file de processus ordonnancés avec les temps d'attente et de fin calculés.
     */
    File<Processus> fcfs(const File<Processus>& f_entree, const int &temps) {
        PRECONDITION(temps >= 0);
        File<Processus> result;
        File<Processus> travail(f_entree);
        int Attente = 0;
        int clock = temps;

        result.setNomTest("FCFS");

        while (!travail.estVide()) {
            int minIndex = -1;
            int minArrivee = std::numeric_limits<int>::max();

            for (int i = 0; i < travail.taille(); i++) {
                Processus curr = travail.getValeur(i);

                if (curr.getArrivee() < minArrivee) {
                    minArrivee = curr.getArrivee();
                    minIndex = i;
                }
            }
            Processus pris = travail.getValeur(minIndex);

            travail.supprimer(pris);
            pris.setAttente(clock-pris.getArrivee());
            clock += pris.getDuree();
            pris.setFin(clock);
            result.insererDernier(pris);
        }

        for (int i = 0; i < result.taille(); i++) {
            Processus copie = result.getValeur(i);
            Attente += static_cast<float>(copie.getAttente());
        }
        float moyenneTemps = (Attente) / static_cast<float>(result.taille());
        result.setTempsMoy(moyenneTemps);

        return result;
    }

    /**
     * \brief Algorithme FJS (Shortest Job First).
     *
     *        Cette fonction ordonne les processus selon leur durée de traitement,
     *        le processus ayant la durée la plus courte étant servi en premier.
     *
     * \param f_entree La file de processus d'entrée.
     * \param temps Le temps de décalage.
     * \return La file de processus ordonnancés avec les temps d'attente et de fin calculés.
     */
    File<Processus> fjs(const File<Processus>& f_entree, const int &temps) {
        PRECONDITION(temps >= 0);
        File<Processus> result;
        File<Processus> travail(f_entree);
        int Attente = 0;
        int clock = temps;

        result.setNomTest("FJS");

        while (!travail.estVide()) {
            int minIndex = -1;
            int minArrivee = std::numeric_limits<int>::max();
            int minDuree = std::numeric_limits<int>::max();

            for (int i = 0; i < travail.taille(); i++) {
                Processus curr = travail.getValeur(i);

                if (curr.getArrivee() < minArrivee) {
                    minArrivee = curr.getArrivee();
                    minDuree = curr.getDuree();
                    minIndex = i;
                }else if(curr.getArrivee() == minArrivee) {
                    if (curr.getDuree() < minDuree) {
                        minDuree = curr.getDuree();
                        minIndex = i;
                    }
                }
            }
            Processus pris = travail.getValeur(minIndex);

            travail.supprimer(pris);
            pris.setAttente(clock-pris.getArrivee());
            clock += pris.getDuree();
            pris.setFin(clock);
            result.insererDernier(pris);
        }

        for (int i = 0; i < result.taille(); i++) {
            Processus copie = result.getValeur(i);
            Attente += static_cast<float>(copie.getAttente());
        }
        float moyenneTemps = (Attente) / static_cast<float>(result.taille());
        result.setTempsMoy(moyenneTemps);

        return result;
    }

    /**
     * \brief Algorithme Round Robin.
     *
     *        Cette fonction utilise l'algorithme Round Robin pour ordonnancer
     *        les processus, en leur attribuant un quantum de temps fixe.
     *
     * \param f_entree La file de processus d'entrée.
     * \param f_quantum Le temps de quantum pour chaque processus.
     * \param temps Le temps de décalage.
     * \return La file de processus ordonnancés avec les temps d'attente et de fin calculés.
     */
    File<Processus> round_robin(const File<Processus>& f_entree,const int& f_quantum, const int &temps) {
        PRECONDITION(temps >= 0);
        PRECONDITION(f_quantum >= 0);
        File<Processus> result;
        File<Processus> travail(f_entree);
        File<Processus> copie(f_entree);
        File<Processus> temp;

        int quantum = f_quantum;
        int Clock = 0;
        float Attente = 0;

        result.setNomTest("Round Robin");

        while (!travail.estVide()) {
            int minIndex = -1;
            int minArrivee = std::numeric_limits<int>::max();

            for (int i = 0; i < travail.taille(); i++) {
                Processus curr = travail.getValeur(i);

                if (curr.getArrivee() < minArrivee) {
                    minArrivee = curr.getArrivee();
                    minIndex = i;
                }
            }

            Processus t_pris = travail.getValeur(minIndex);
            Processus C_pris = copie.getValeur(minIndex);

            travail.supprimer(t_pris);

            if (t_pris.getDuree() <= quantum) {
                int t_temps = t_pris.getDuree();

                while (travail.taille() > 0) {
                    Processus Autre = travail.getValeur(0);

                    if (Autre.getArrivee() <= Clock) {
                        travail.supprimer(Autre);
                        Autre.incAttente(t_temps);
                        temp.insererDernier(Autre);
                    }else if (Autre.getArrivee() > Clock && Autre.getArrivee() <= Clock + t_temps) {
                        int partialWait = (Clock + t_temps) - Autre.getArrivee();
                        travail.supprimer(Autre);
                        Autre.incAttente(partialWait);
                        temp.insererDernier(Autre);
                    }else {
                        travail.supprimer(Autre);
                        temp.insererDernier(Autre);
                    }
                }

                while (temp.taille() > 0) {
                    Processus retour = temp.getValeur(0);
                    temp.supprimerPremier();
                    travail.insererDernier(retour);
                }

                C_pris.setAttente(t_pris.getAttente());
                C_pris.incAttente(temps);
                Clock += t_temps;
                C_pris.setFin(Clock+temps);
                copie.supprimer(C_pris);
                result.insererDernier(C_pris);

            }

            else if (t_pris.getDuree() > quantum) {
                int t_temps = quantum;

                while (travail.taille() > 0) {
                    Processus Autre = travail.getValeur(0);

                    if (Autre.getArrivee() > Clock && Autre.getArrivee() <= Clock + t_temps) {
                        int partialWait = (Clock + t_temps) - Autre.getArrivee();

                        travail.supprimer(Autre);
                        Autre.incAttente(partialWait);
                        temp.insererDernier(Autre);
                    }else if (Autre.getArrivee() <= Clock) {
                        travail.supprimer(Autre);
                        Autre.incAttente(t_temps);
                        temp.insererDernier(Autre);
                    }else {
                        travail.supprimer(Autre);
                        temp.insererDernier(Autre);
                    }
                }

                while (temp.taille() > 0) {
                    Processus retour = temp.getValeur(0);
                    temp.supprimerPremier();
                    travail.insererDernier(retour);
                }

                t_pris.redDuree(quantum);
                t_pris.incArrivee(quantum);
                travail.insererDernier(t_pris);
                copie.supprimer(C_pris);
                copie.insererDernier(C_pris);
                Clock += quantum;
            }
        }
        for (int i = 0; i < result.taille(); i++) {
            Attente += static_cast<float>(result.getValeur(i).getAttente());
        }
        float moyenneTemps = (Attente) / static_cast<float>(result.taille());
        result.setTempsMoy(moyenneTemps);

        return result;

    }

    /**
     * \brief Algorithme d'ordonnancement par priorité.
     *
     *        Cette fonction ordonne les processus selon leur priorité, le processus
     *        ayant la plus haute priorité étant servi en premier.
     *
     * \param f_entree La file de processus d'entrée.
     * \param temps Le temps de décalage.
     * \return La file de processus ordonnancés avec les temps d'attente et de fin calculés.
     */
    File<Processus> priorite(const File<Processus>& f_entree, const int &temps) {
        PRECONDITION(temps >= 0);
        File<Processus> result;
        File<Processus> travail(f_entree);
        int Attente = 0;
        int clock = temps;

        result.setNomTest("priorite");

        while (!travail.estVide()) {
            int minIndex = -1 ;
            int minPrio = -1 ;
            int minArrivee = std::numeric_limits<int>::max();

            for (int i = 0; i < travail.taille(); i++) {
                Processus curr = travail.getValeur(i);

                if (curr.getArrivee() < minArrivee) {
                        minPrio = curr.getPriorite();
                        minArrivee = curr.getArrivee();
                        minIndex = i;
                }else if (curr.getArrivee() == minArrivee) {
                    if (curr.getPriorite() > minPrio) {
                        minPrio = curr.getPriorite();
                        minIndex = i;
                    }
                    }
            }
            Processus pris = travail.getValeur(minIndex);

            travail.supprimer(pris);
            pris.setAttente(clock-pris.getArrivee());
            clock += pris.getDuree();
            pris.setFin(clock);
            result.insererDernier(pris);
        }

        for (int i = 0; i < result.taille(); i++) {
            Attente += static_cast<float>(result.getValeur(i).getAttente());
        }
        float moyenneTemps = (Attente) / static_cast<float>(result.taille());
        result.setTempsMoy(moyenneTemps);

        return result;
    }

    /**
     * \brief Algorithme d'ordonnancement multiniveaux.
     *
     *        Cette fonction ordonne les processus en plusieurs niveaux
     *        selon leur type et utilise différentes stratégies d'ordonnancement.
     *
     * \param f_entree La file de processus d'entrée.
     * \param f_quantum Le temps de quantum pour les processus interactifs.
     * \param temps Le temps de décalage.
     * \return La file de processus ordonnancés avec les temps d'attente et de fin calculés.
     */
    File<Processus> multiniveaux(const File<Processus>& f_entree,const int& f_quantum, const int &temps) {
        PRECONDITION(temps >= 0);
        PRECONDITION(f_quantum > 0);
        File<Processus> result;
        File<Processus> travail(f_entree);
        File<Processus> SYSTEME;
        File<Processus> INTERACTIF;
        File<Processus> BATCH;
        File<Processus> UTILISATEUR;
        int Attente = 0;

        while (!travail.estVide()) {
            Processus curr = travail.getValeur(0);
            TypeProcessus type = curr.getType();
            travail.supprimer(curr);

            if (type == TypeProcessus(1)) {
                SYSTEME.insererDernier(curr);
            }
            else if (type == TypeProcessus(2)) {
                INTERACTIF.insererDernier(curr);
            }
            else if (type == TypeProcessus(3)) {
                BATCH.insererDernier(curr);
            }
            else if (type == TypeProcessus(4)) {
                UTILISATEUR.insererDernier(curr);
            }
        }
        File<Processus> Sys = TP::priorite(SYSTEME, temps);
        while (!Sys.estVide()) {
            Processus copie1 = Sys.getValeur(0);
            Sys.supprimer(copie1);
            result.insererDernier(copie1);
        }


        File<Processus> Int =TP::round_robin(INTERACTIF, f_quantum, result.getValeur(result.taille()-1).getFin());
        while (!Int.estVide()) {
            Processus copie2 = Int.getValeur(0);
            Int.supprimer(copie2);
            result.insererDernier(copie2);
        }
        File<Processus> batch = TP::fcfs(BATCH, result.getValeur(result.taille()-1).getFin());
        while (!batch.estVide()) {
            Processus copie3 = batch.getValeur(0);
            batch.supprimer(copie3);
            result.insererDernier(copie3);
        }
        File<Processus> utilisateur = TP::fcfs(UTILISATEUR, result.getValeur(result.taille()-1).getFin());
        while (!utilisateur.estVide()) {
            Processus copie4 = utilisateur.getValeur(0);
            utilisateur.supprimer(copie4);
            result.insererDernier(copie4);
        }

        for (int i = 0; i < result.taille(); i++) {
            Processus copie = result.getValeur(i);
            Attente += static_cast<float>(copie.getAttente());
        }
        float moyenneTemps = (Attente) / static_cast<float>(result.taille());
        result.setTempsMoy(moyenneTemps);

        return result;
    }
}

