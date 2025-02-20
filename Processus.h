#ifndef PROCESSUS_H
#define PROCESSUS_H

#include <string>
#include <iostream>

/**
 * \enum TypeProcessus
 * \brief Cette énumération représente les différents types de processus dans un système d'exploitation ou un simulateur de gestion de processus.
 *
 *        Chaque processus est classé en fonction de son rôle ou de sa nature dans le système.
 *        Voici les différents types possibles :
 *        - SYSTEME : Processus essentiel au fonctionnement du système.
 *        - INTERACTIF : Processus qui interagit avec l'utilisateur ou répond à des requêtes en temps réel.
 *        - BATCH : Processus traité en lot, souvent en arrière-plan, sans interaction directe avec l'utilisateur.
 *        - UTILISATEUR : Processus démarré par un utilisateur pour exécuter une tâche.
 */
enum class TypeProcessus {
    SYSTEME = 1,
    INTERACTIF = 2,
    BATCH = 3,
    UTILISATEUR = 4
};

/**
 * \class Processus
 * \brief Cette classe représente un processus dans un système d'exploitation ou un simulateur de gestion de processus.
 *
 *        La classe Processus maintient un état cohérent des caractéristiques d'un processus, telles que son ID,
 *        son temps d'arrivée, sa durée, sa priorité, et son type. Elle permet de manipuler et modifier ces informations.
 *        <p>
 *        Cette classe gère différents types de processus, définis par une énumération `TypeProcessus`,
 *        et fournit des opérateurs pour comparer les priorités des processus.
 *        <p>
 *        Chaque processus est doté de caractéristiques suivantes :
 *        - Un ID unique sous forme de chaîne de caractères (m_pid)
 *        - Un temps d'arrivée dans le système (m_arrivee)
 *        - Une durée totale (m_duree)
 *        - Un temps restant pour l'exécution (m_restant)
 *        - Un temps d'attente dans la file d'attente des processus (m_attente)
 *        - Un temps de fin (m_fin)
 *        - Une priorité (m_priorite)
 *        - Un type de processus (m_type)
 *
 * \invariant Le processus doit avoir une priorité positive ou nulle.
 * \invariant Le ID doit être non vide.
 * \invariant Le temps d'arrivée, la durée, et le temps restant doivent être positifs ou nuls.
 * \invariant Le temps d'attente doit être positif ou nul.
 * \invariant Le type de processus doit être valide (SYSTEME, INTERACTIF, BATCH, UTILISATEUR).
 */
class Processus {
public:
    Processus(const std::string& p_id, int p_arrivee, int p_duree, int p_priorite, TypeProcessus p_type);

    std::string getId() const;
    int getArrivee() const;
    int getDuree() const;
    int getRestant() const;
    int getAttente() const;
    int getFin() const;
    int getPriorite() const;
    TypeProcessus getType() const;


    void setRestant(int restant);
    void setAttente(int attente);
    void setFin(int fin);
    void setPriorite(int priorite);
    void redDuree(int duree);
    void incArrivee(int arrivee);
    void incAttente(int attente);
    void setType(TypeProcessus type);


    bool operator<(const Processus& other) const;
    bool operator>(const Processus& other) const;
    bool operator==(const Processus& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Processus& processus);

private:
    std::string m_pid;
    int m_arrivee;
    int m_duree;
    int m_restant;
    int m_attente;
    int m_fin;
    int m_priorite;
    TypeProcessus m_type;
    void verifieInvariant () const;
};

#endif // PROCESSUS_H
