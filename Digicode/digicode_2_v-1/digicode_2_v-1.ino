/*
 *       Matthis Sanier
 *       digicode_1_v-1
 *       Système de digicode avec mot de passe à entrer
 *
 *       carte arduino, afficheur serial
 *
 *       16/09/2024 digicode_2_v-1
*/

// Déclaration
char Codebon[4] = {0x31, 0x32, 0x33, 0x34}; // Code initial
char Codenoter[4]; // Code entré par l'utilisateur
bool codeCorrect; // Variable pour vérifier si le code est correct

void codesaisie() {
  // Compare le code entré avec le code défini dans le programme
  codeCorrect = true;
  for (byte i = 0; i < 4; i++) {
    if (Codenoter[i] != Codebon[i]) {
      codeCorrect = false;
      break;
    }
  }
}

void afficherMenu() {
  Serial.println("Menu principal :");
  Serial.println("A : Vérifier le code");
  Serial.println("B : Modifier le code");
  Serial.println("C : Quitter");
}

void verifierCode() {
  Serial.println("Entrez le code (4 chiffres) : ");
  while (Serial.available() < 4) {
    // Attend que l'utilisateur entre 4 chiffres
  }
  delay(100);

  // Lit les 4 caractères du code entré
  for (byte i = 0; i < 4; i++) {
    Codenoter[i] = Serial.read();
  }

  Serial.print("Code reçu : ");
  Serial.println(Codenoter);

  codesaisie();

  if (codeCorrect) {
    Serial.println("Code Bon");
  } else {
    Serial.println("Code incorrect");
  }
}

void modifierCode() {
  Serial.println("Entrez le nouveau code (4 chiffres) : ");
  while (Serial.available() < 4) {
    // Attend que l'utilisateur entre 4 chiffres
  }
  delay(100);

  // Lit les 4 caractères du nouveau code
  for (byte i = 0; i < 4; i++) {
    Codebon[i] = Serial.read();
  }

  Serial.print("Nouveau code enregistré : ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(Codebon[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  afficherMenu(); // Affiche le menu principal au démarrage
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read(); // Lit la commande

    switch (command) {
      case 'A':
        verifierCode(); // Appelle la fonction pour vérifier le code
        break;
        
      case 'B':
        modifierCode(); // Appelle la fonction pour modifier le code
        break;

      case 'C':
        Serial.println("Retour au menu principal...");
        afficherMenu(); // Affiche le menu principal
        break;

      default:
        Serial.println("Commande non reconnue. Entrez 'A' pour vérifier le code, 'B' pour modifier le code, 'C' pour quitter.");
        break;
    }
    
    // Réinitialise le buffer Serial
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
