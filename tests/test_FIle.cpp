//
// Created by Vincent on 10/1/2024.
//

#include "gtest/gtest.h"
#include "File.h"

class FileTest : public ::testing::Test {
  protected:
  void SetUp() override {
    F1.insererDernier(1);
    F5.insererDernier(1);
    F5.insererDernier(2);
    F5.insererDernier(3);
    F5.insererDernier(4);
    F5.insererDernier(5);
  }

  File<int> F0;
  File<int> F1;
  File<int> F5;
};

TEST(File, constructeur_vide ) {
  File<int> l ;
  EXPECT_TRUE(l.estVide());
}

TEST(File, Vide_toString){
  File<int> l ;
  EXPECT_EQ(l.toString(), "");
}

TEST(File, vide_insertion_nouveau_element) {
  File<int> l ;
  l.insererDernier(42);
  EXPECT_EQ(1, l.taille());
  EXPECT_EQ(l.toString(), "42\n");
}

TEST_F(FileTest, F5_Copie_F5) {
  File<int> Fcopie(F5) ;
  EXPECT_EQ(Fcopie.toString(), F5.toString());
}

TEST_F(FileTest, F5_supprimerPremier_4_element) {
  F5.supprimerPremier();
  EXPECT_EQ(F5.toString(), "2\n3\n4\n5\n" );
}

TEST_F(FileTest, F0_supression) {
  F1.supprimer(1);
  EXPECT_EQ(F0.toString(), "" );
}

TEST_F(FileTest, F1_supression) {
  F1.supprimer(1);
  EXPECT_EQ(F1.toString(), "" );
}

TEST_F(FileTest, F5_supprimer_1) {
  F5.supprimer(1);
  EXPECT_EQ(F5.toString(), "2\n3\n4\n5\n" );
}

TEST_F(FileTest, F5_supprimer_2) {
  F5.supprimer(2);
  EXPECT_EQ(F5.toString(), "1\n3\n4\n5\n" );
}

TEST_F(FileTest, F5_supprimer_3) {
  F5.supprimer(3);
  EXPECT_EQ(F5.toString(), "1\n2\n4\n5\n" );
}

TEST_F(FileTest, F5_supprimer_4) {
  F5.supprimer(4);
  EXPECT_EQ(F5.toString(), "1\n2\n3\n5\n" );
}

TEST_F(FileTest, F5_supprimer_5) {
  F5.supprimer(5);
  EXPECT_EQ(F5.toString(), "1\n2\n3\n4\n" );
}

TEST_F(FileTest, F5_supprimer_1_3) {
  F5.supprimer(1);
  F5.supprimer(3);
  EXPECT_EQ(F5.toString(), "2\n4\n5\n" );
}

TEST_F(FileTest, F5_supprimer_5_2) {
  F5.supprimer(5);
  F5.supprimer(2);
  EXPECT_EQ(F5.toString(), "1\n3\n4\n" );
}

TEST_F(FileTest, F5_supprimer_tous) {
  F5.supprimer(1);
  F5.supprimer(2);
  F5.supprimer(3);
  F5.supprimer(4);
  F5.supprimer(5);
  EXPECT_EQ(F5.toString(), "" );
}

TEST_F(FileTest, F5_get1) {
  EXPECT_EQ(F5.getValeur(0), 1 );
}