#include "Processus.h"
#include "ContratException.h"

/**
 * \brief Constructeur de la classe Processus
 * \param[in] p_pid Identifiant unique du processus.
 * \param[in] p_arrivee Temps d'arrivée du processus dans le système.
 * \param[in] p_duree Durée totale d'exécution du processus.
 * \param[in] p_priorite Priorité du processus (un entier plus bas signifie une priorité plus haute).
 * \param[in] p_type Type du processus (SYSTEME, INTERACTIF, BATCH, UTILISATEUR).
 * \pre p_arrivee >= 0, p_duree > 0, p_priorite >= 0
 * \post Un objet Processus valide est créé avec les valeurs assignées.
 */
Processus::Processus(const std::string& p_pid, int p_arrivee, int p_duree, int p_priorite, TypeProcessus p_type)
    : m_pid(p_pid), m_arrivee(p_arrivee), m_duree(p_duree), m_restant(p_duree), m_attente(0),
      m_fin(0), m_priorite(p_priorite), m_type(p_type) {
    PRECONDITION(p_pid != "")
    PRECONDITION(p_arrivee >= 0);
    PRECONDITION(p_duree > 0);
    PRECONDITION(p_priorite >= 0);

    POSTCONDITION(m_pid == p_pid);
    POSTCONDITION(m_arrivee == p_arrivee);
    POSTCONDITION(m_duree == p_duree);
    POSTCONDITION(m_priorite == p_priorite);
}

/**
 * \brief Retourne l'identifiant unique du processus.
 * \return Une chaîne de caractères contenant l'identifiant du processus.
 * \post L'identifiant retourné est non vide.
 */
std::string Processus::getId() const {
    ASSERTION(m_pid != "");
    return m_pid;
}

/**
 * \brief Retourne le temps d'arrivée du processus.
 * \return Le temps d'arrivée (entier).
 * \post Le temps d'arrivée est supérieur ou égal à zéro.
 */
int Processus::getArrivee() const {
    ASSERTION(m_arrivee >= 0);
    return m_arrivee;
}

/**
 * \brief Retourne la durée totale d'exécution du processus.
 * \return La durée (entier).
 * \post La durée retournée est positive.
 */
int Processus::getDuree() const {
    ASSERTION(m_duree >= 0);
    return m_duree;
}

/**
 * \brief Retourne le temps restant d'exécution du processus.
 * \return Le temps restant (entier).
 * \post Le temps restant est supérieur ou égal à zéro.
 */
int Processus::getRestant() const {
    ASSERTION(m_restant >= 0);
    return m_restant;
}

/**
 * \brief Retourne le temps d'attente du processus.
 * \return Le temps d'attente (entier).
 * \post Le temps d'attente est supérieur ou égal à zéro.
 */
int Processus::getAttente() const {
    ASSERTION(m_attente >= 0);
    return m_attente;
}

/**
 * \brief Retourne le temps de fin du processus.
 * \return Le temps de fin (entier).
 * \post Le temps de fin est supérieur ou égal à zéro.
 */
int Processus::getFin() const {
    ASSERTION(m_fin >= 0);
    return m_fin;
}

/**
 * \brief Retourne la priorité du processus.
 * \return La priorité (entier).
 * \post La priorité est un entier supérieur ou égal à zéro.
 */
int Processus::getPriorite() const {
    ASSERTION(m_priorite >= 0);
    return m_priorite;
}

/**
 * \brief Retourne le type du processus.
 * \return Le type du processus (SYSTEME, INTERACTIF, BATCH, UTILISATEUR).
 * \post Le type est un type valide de TypeProcessus.
 */
TypeProcessus Processus::getType() const {
    ASSERTION(m_type == TypeProcessus::SYSTEME ||
              m_type == TypeProcessus::INTERACTIF ||
              m_type == TypeProcessus::BATCH ||
              m_type == TypeProcessus::UTILISATEUR);
    return m_type;
}

/**
 * \brief Met à jour le temps restant pour le processus.
 * \param[in] restant Temps restant à exécuter pour le processus.
 * \pre restant >= 0
 * \post m_restant est mis à jour avec la nouvelle valeur.
 */
void Processus::setRestant(int restant) {
    PRECONDITION(restant >= 0);
    m_restant = restant;
    POSTCONDITION(m_restant == restant);
}

/**
 * \brief Met à jour le temps d'attente du processus.
 * \param[in] attente Le nouveau temps d'attente.
 * \pre attente >= 0
 * \post Le temps d'attente est mis à jour avec la nouvelle valeur.
 */
void Processus::setAttente(int attente) {
    PRECONDITION(attente >= 0);
    m_attente = attente;
    POSTCONDITION(m_attente == attente);
}

/**
 * \brief Met à jour le temps de fin du processus.
 * \param[in] fin Le nouveau temps de fin.
 * \pre fin >= 0
 * \post Le temps de fin est mis à jour avec la nouvelle valeur.
 */
void Processus::setFin(int fin) {
    PRECONDITION(fin >= 0);
    m_fin = fin;
    POSTCONDITION(m_fin == fin);
}

/**
 * \brief Met à jour la priorité du processus.
 * \param[in] priorite La nouvelle priorité à attribuer.
 * \pre priorite >= 0
 * \post La priorité est mise à jour avec la nouvelle valeur.
 */
void Processus::setPriorite(int priorite) {
    PRECONDITION(priorite >= 0);
    m_priorite = priorite;
    POSTCONDITION(m_priorite == priorite);
}

/**
 * \brief Réduit la durée d'exécution restante du processus.
 * \param[in] duree Durée à soustraire à la durée totale.
 * \pre duree >= 0
 * \post La durée restante est réduite de la valeur indiquée.
 */
void Processus::redDuree(int duree) {
    PRECONDITION(duree >= 0);
    m_duree -= duree;
}

/**
 * \brief Incrémente le temps d'arrivée du processus.
 * \param[in] arrivee Le temps à ajouter au temps d'arrivée initial.
 * \pre arrivee >= 0
 * \post Le temps d'arrivée est augmenté de la valeur donnée.
 */
void Processus::incArrivee(int arrivee) {
    PRECONDITION(arrivee >= 0);
    m_arrivee += arrivee;
}

/**
 * \brief Incrémente le temps d'attente du processus.
 * \param[in] attente Temps à ajouter au temps d'attente actuel.
 * \pre attente >= 0
 * \post Le temps d'attente est augmenté de la valeur donnée.
 */
void Processus::incAttente(int attente) {
    PRECONDITION(attente >= 0);
    m_attente += attente;
}

/**
 * \brief Met à jour le type du processus.
 * \param[in] type Le nouveau type du processus (SYSTEME, INTERACTIF, BATCH, UTILISATEUR).
 * \post Le type du processus est mis à jour avec la nouvelle valeur.
 */
void Processus::setType(TypeProcessus type) {
    PRECONDITION(type == TypeProcessus::SYSTEME ||
              type == TypeProcessus::INTERACTIF ||
              type == TypeProcessus::BATCH ||
              type == TypeProcessus::UTILISATEUR)
    m_type = type;
    POSTCONDITION(m_type == type);
}

/**
 * \brief Surcharge de l'opérateur < pour comparer les priorités des processus.
 * \param[in] other Processus à comparer.
 * \return true si le processus courant a une priorité plus basse (c'est-à-dire un nombre plus élevé), sinon false.
 * \post Retourne true si m_priorite < other.m_priorite.
 */
bool Processus::operator<(const Processus& other) const {
    return m_priorite < other.m_priorite;
}

/**
 * \brief Compare la priorité du processus courant avec celle d'un autre processus.
 * \param[in] other Le processus avec lequel comparer.
 * \return true si la priorité du processus courant est supérieure à celle du processus passé en paramètre, sinon false.
 * \pre Aucun.
 * \post Le résultat de la comparaison est retourné.
 */
bool Processus::operator>(const Processus& other) const {
    return m_priorite > other.m_priorite;
}

/**
 * \brief Surcharge de l'opérateur == pour vérifier si deux processus sont identiques.
 * \param[in] other Processus à comparer.
 * \return true si les deux processus ont le même identifiant, sinon false.
 * \post Retourne true si les identifiants des processus sont identiques.
 */
bool Processus::operator==(const Processus& other) const {
    return m_pid == other.m_pid;
}

/**
 * \brief Surcharge de l'opérateur << pour afficher les informations d'un processus.
 * \param[in] os Flux de sortie où écrire les informations.
 * \param[in] processus Processus à afficher.
 * \return Le flux de sortie contenant les informations du processus.
 * \post Les informations du processus sont correctement affichées dans le flux.
 */
std::ostream& operator<<(std::ostream& os, const Processus& processus) {
    os << processus.m_pid
       << " arrivee : " << processus.m_arrivee
       << " Duree : " << processus.m_duree
       << " temps d'attente : " << processus.m_attente
       << " Priorite : " << processus.m_priorite
       << " Type : ";

    switch (processus.m_type) {
        case TypeProcessus::SYSTEME:
            os << 1;
        break;
        case TypeProcessus::INTERACTIF:
            os << 2;
        break;
        case TypeProcessus::BATCH:
            os << 3;
        break;
        case TypeProcessus::UTILISATEUR:
            os << 4;
        break;
    }

    return os;
}

/**
 * \brief Vérifie l'invariant de la classe Processus.
 *
 * L'invariant de cette classe s'assure que :
 * - La priorité du processus est positive ou nulle.
 * - Le temps d'arrivée est positif ou nul.
 * - La durée totale du processus est positive ou nulle.
 * - Le temps d'attente est positif ou nul.
 * - Le temps restant est positif ou nul.
 * - Le type de processus est valide (SYSTEME, INTERACTIF, BATCH, UTILISATEUR).
 *
 * \post Les conditions mentionnées ci-dessus doivent toujours être vérifiées pour maintenir l'intégrité de l'objet.
 */
void Processus::verifieInvariant() const {
    INVARIANT(m_pid != "")
    INVARIANT(m_priorite >= 0);
    INVARIANT(m_arrivee >= 0);
    INVARIANT(m_duree >= 0);
    INVARIANT(m_attente >= 0);
    INVARIANT(m_restant >= 0);
    INVARIANT(m_type == TypeProcessus::SYSTEME ||
              m_type == TypeProcessus::INTERACTIF ||
              m_type == TypeProcessus::BATCH ||
              m_type == TypeProcessus::UTILISATEUR);
}