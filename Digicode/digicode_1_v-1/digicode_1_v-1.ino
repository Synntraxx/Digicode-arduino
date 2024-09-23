
/*       
 *       Matthis Sanier
 *       digicode_1_v-1
 *       Système de digicode avec mot de passe a entrer
 *       
 *       carte arduino, afficheur serial
 *       
 *       09/09/2024 digicode_1_v-1
*/


//Déclaration
char Codebon[4] = {0x31, 0x32, 0x33, 0x34};
char Codenoter[4];


void setup() {
  Serial.begin(9600);
  Serial.println("Entrez le code : ");
}

void loop() {

  //Tant que le code est inférerieur à 4 alors continuer à lire l'entrée
  while (Serial.available() < 4) {
  }

  delay(100); 

  //Une fois les 4 carractère entrée, lire les carractères
  for (byte i = 0; i < 4; i++) {
    Codenoter[i] = Serial.read();
  }

  //Noté les carractères écris dans le serial
  Serial.print("Code reçu : ");
  Serial.println(Codenoter);


  //Compare le code écris et le code mis en dure dans le programme
  bool codeCorrect = true;
  for (byte i = 0; i < 4; i++) {
    if (Codenoter[i] != Codebon[i]) {
      codeCorrect = false;
      break;
    }
  }

  //Si le code = à celui mis dans le programme alors mettre "code bon", si celui ci n'est pas égal alors noté "Code incorrect"
  if (codeCorrect) {
    Serial.println("Code Bon");
  } else {
    Serial.println("Code incorrect");
  }

  //Reset la loop pour revenir au début
  while (Serial.available() > 0) {
    Serial.read();
  }
}
