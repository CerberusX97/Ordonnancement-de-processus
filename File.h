//
// Created by Vincent on 10/1/2024.
//

#ifndef FILE_H
#define FILE_H
#include <sstream>
#include <cassert>
#include "ContratException.h"

/**
 * \brief Classe générique représentant une file circulaire.
 *
 *        La classe permet d'ajouter, de supprimer et d'accéder à des éléments
 *        de manière ordonnée. Elle gère également les statistiques comme le temps
 *        d'attente moyen et le nom du test.
 *
 * \tparam T Type des éléments stockés dans la file.
 */
template <typename T>
class File {
public:
  File();
  File(const File& source);
  ~File();

  void insererDernier(const T& data) ;
  void inserer(size_t index, T& data) ;

  void supprimerPremier();
  void supprimer(const T& data);

  T getValeur(size_t index) const;
  float getTempsMoy() const;

  float setTempsMoy(float tempsMoy);
  std::string setNomTest(const std::string& nom);


  size_t taille() const;
  bool estVide() const;
  std::string toString() const;

private:
  struct Node {
    T valeur ;
    Node* next ;
    explicit Node(const T& val) : valeur(val), next(nullptr) {}
  };

  Node* dernier ;
  size_t size ;
  float m_tempsMoy ;
  std::string m_NomTest ;
  bool invariant() const ;
};


/**
 * \brief Constructeur par défaut de la classe File.
 * \post Une file vide est créée avec une taille de 0.
 */
template<typename T>
File<T>::File() : dernier(nullptr), size(0), m_tempsMoy(0), m_NomTest("") {
  assert(invariant());
}


/**
 * \brief Constructeur de copie pour créer une nouvelle file à partir d'une source existante.
 * \param[in] source La file à copier.
 * \post La nouvelle file contient les mêmes éléments que la source.
 */
template<typename T>
File<T>::File(const File &source) : dernier(nullptr), size(0), m_tempsMoy(0), m_NomTest("") {
  if (source.dernier != nullptr) {
    auto p = source.dernier;
    do {
      p = p->next;
      insererDernier(p->valeur);
    }
    while (p != source.dernier);
  }
  assert(invariant());
}

/**
 * \brief Destructeur pour libérer la mémoire utilisée par la file.
 * \post Tous les noeuds de la file sont supprimés.
 */
template<typename T>
File<T>::~File() {
  while (!estVide()) supprimerPremier();
}

/**
 * \brief Insère un élément à la fin de la file.
 * \param[in] data L'élément à insérer.
 * \post L'élément est ajouté à la fin de la file et la taille est incrémentée.
 */
template<typename T>
void File<T>::insererDernier(const T &data) {
  auto nouveau = new Node(data);
  if (dernier == nullptr) {
    nouveau->next = nouveau;
  }
  else {
    nouveau->next = dernier->next;
    dernier->next = nouveau;
  }
    dernier = nouveau;
  size++;

  assert(invariant());
}

/**
 * \brief Insère un élément à un index spécifié dans la file.
 * \param[in] index L'index où l'élément doit être inséré.
 * \param[in] data L'élément à insérer.
 * \pre index <= taille()
 * \post L'élément est ajouté à l'index spécifié et la taille est incrémentée.
 */
template<typename T>
void File<T>::inserer(size_t index, T &data) {
  PRECONDITION(index >= 0);
  assert(index <= size && "Index out of range");

  Node* nouveau = new Node(data);

  if (estVide()) {
    dernier = nouveau;
    dernier->next = dernier;
  } else if (index == 0) {
    nouveau->next = dernier->next;
    dernier->next = nouveau;
  } else {
    Node* current = dernier->next;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    nouveau->next = current->next;
    current->next = nouveau;
  }

  size++;
  assert(invariant());
}

/**
 * \brief Supprime le premier élément de la file.
 * \pre !estVide()
 * \post Le premier élément est supprimé et la taille est décrémentée.
 */
template<typename T>
void File<T>::supprimerPremier() {
  assert(!estVide());
  if (size == 1) {
    delete dernier;
    dernier = nullptr;
  }
  else {
    auto p = dernier->next;
    dernier->next = p->next;
    delete p;
  }
  --size;

  assert(invariant());
}

/**
 * \brief Supprime un élément spécifique de la file.
 * \param[in] data L'élément à supprimer.
 * \post Si l'élément est trouvé, il est supprimé et la taille est décrémentée.
 */
template<typename T>
void File<T>::supprimer(const T &data) {
  PRECONDITION(!estVide());
  if (estVide()) return;
  Node* curr = dernier->next;
  Node* prev = dernier;

  if (size == 1 ) {
    if (curr->valeur == data) {
      delete curr;
      dernier = nullptr;
      --size;
      return;
    }
  }

  do {
    if (curr->valeur == data) {
      prev->next = curr->next;

      if (curr == dernier) {
        dernier = prev;
      }

      if (curr == dernier->next) {
        dernier->next = curr->next;
      }

      delete curr;
      size--;
      assert(invariant());
      return;
    }
    prev = curr;
    curr = curr->next;
  } while (curr != dernier->next);
}


/**
 * \brief Obtient la valeur d'un index spécifié.
 * \param[in] index L'index dont la valeur doit être obtenue.
 * \return La valeur à l'index spécifié.
 * \pre index < taille()
 * \throw std::out_of_range Si l'index est hors limites.
 */
template<typename T>
T File<T>::getValeur(size_t index) const {
  PRECONDITION(index >= 0);
  Node* current = dernier->next;
  size_t count = 0;
  while (current) {
    if (count == index) {
      return current->valeur;
    }
    current = current->next;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

/**
 * \brief Obtient le temps d'attente moyen.
 * \return Le temps d'attente moyen actuel.
 */
template<typename T>
float File<T>::getTempsMoy() const {
  return m_tempsMoy;
}

/**
 * \brief Définit le temps d'attente moyen.
 * \param[in] tempsMoy Le nouveau temps d'attente moyen.
 * \return Le temps d'attente moyen mis à jour.
 */
template<typename T>
float File<T>::setTempsMoy(float tempsMoy) {
  PRECONDITION(tempsMoy >= 0);
  m_tempsMoy = tempsMoy;
  return m_tempsMoy;
  POSTCONDITION(m_tempsMoy == tempsMoy);
}

/**
 * \brief Définit le nom du test.
 * \param[in] nom Le nom du test à définir.
 * \return Le nom du test mis à jour.
 */
template<typename T>
std::string File<T>::setNomTest(const std::string &nom) {
  PRECONDITION(nom != "");
  m_NomTest = nom;
  return m_NomTest;
  POSTCONDITION(m_NomTest == nom);
}

/**
 * \brief Obtient la taille de la file.
 * \return La taille actuelle de la file.
 */
template<typename T>
size_t File<T>::taille() const {
  return size;
}

/**
 * \brief Vérifie si la file est vide.
 * \return Vrai si la file est vide, faux sinon.
 */
template<typename T>
bool File<T>::estVide() const {
  return taille() == 0 ;
}


/**
 * \brief Obtient une représentation en chaîne de la file.
 * \return Une chaîne contenant le contenu de la file.
 */
template<typename T>
std::string File<T>::toString() const {
  std::ostringstream os;

  if (m_NomTest != "") {
    os << "simulation de " << m_NomTest <<  " Resultat:" << std::endl;
  }


  if (dernier != nullptr) {
    auto p = dernier ;
    do {
      p = p->next ;
      os << p->valeur ;
      os << std::endl ;
    } while (p != dernier) ;
  }
  if(m_tempsMoy > 0) {
    os << "Temps d'attente moyen : "<< m_tempsMoy << std::endl; ;
  }else {
    os << "fin chargement" << std::endl;
  }


  return os.str();

}

/**
 * \brief Vérifie l'invariant de la structure de données de la file.
 * \return Vrai si l'invariant est respecté, faux sinon.
 *
 * L'invariant stipule que :
 * - Si la taille de la file est 0, le dernier noeud doit être nul.
 * - Si la taille est supérieure à 0, en parcourant les noeuds à partir du dernier,
 *   on doit revenir au même noeud (c'est-à-dire que la file est circulaire).
 */
template<typename T>
bool File<T>::invariant() const {
  if (size == 0) return (dernier == nullptr);
  auto p = dernier ;
  for (size_t i = 0; i < size; ++i) p = p->next ;
  return (p == dernier);
}
#endif //FILE_H