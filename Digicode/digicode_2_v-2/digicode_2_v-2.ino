char code[]="1234";
char DataRx[4];
char NvCode[4];
boolean CodeValide;
byte ValCode;

//************************************************************************************
//************************************************************************************
void setup() {
  Serial.begin(9600);
}
//************************************************************************************
//************************************************************************************
void loop() {
  Serial.println();
  Serial. println("A : Se connecter");
  Serial. println("B : Modifier mon code");
  while (Serial.available()==0){}
  delay(100);
  if(Serial.available()==1){
    char choix=Serial.read();
    
    switch (choix){
      //*** Connexion ***************************************************************
      case 'A':
        Serial.println();
        Serial.println("Entrez le mot de passe à 4 chiffres");
        ValCode=Saisie(); //appel la capture des caractéres et verif conformité 
      
        switch (ValCode){
          case 0:
            CodeValide=1;
            for (byte x=0;x<4;x++){
              if (DataRx[x]!=code[x]) CodeValide=0;
            }
            if (CodeValide==0) Serial.println("Erreur Code");
            if (CodeValide==1) Serial.println ("Code Valide");
            break;
          case 1:
            Serial.println("Nombre de Caractéres incorrecte");
            break;
          case 2:
            Serial.println("Mot de passe ne doit comporter que des des chiffres");
            break;
        }
      break;
      //***   Mofification du Code*******************************************************
      case 'B':
        // *** Ancien Code ***
        Serial.println();
        Serial.println("Entrez le mot de passe à 4 chiffres");
        ValCode=Saisie(); //appel la capture des caractéres et verif conformité 
        
        switch (ValCode){
          case 0:
            CodeValide=1;
            for (byte x=0;x<4;x++){
              if (DataRx[x]!=code[x]) CodeValide=0; // Verif Code
            }
            if (CodeValide==0) Serial.println("Erreur Code");
            if (CodeValide==1) Serial.println ("Code Valide");
            break;
          case 1:
            Serial.println("Nombre de Caractéres incorrecte");
            break;
          case 2:
            Serial.println("Mot de passe ne doit comporter que des des chiffres");
            break;
        }
        if(CodeValide==1){
          //*** Nouveau Code ***
          Serial.println();
          Serial.println("Entrez le Nouveau mot de passe à 4 chiffres");
          ValCode=Saisie(); //appel la capture des caractéres et verif conformité
  
          switch (ValCode){
            case 0:
              for (byte x=0;x<4;x++){
                NvCode[x]=DataRx[x]; //Save NvCode
              }
              break;
            case 1:
              Serial.println("Nombre de Caractéres incorrecte");
              break;
            case 2:
              Serial.println("Mot de passe ne doit comporter que des des chiffres");
              break;
          }
          //*** Confirme Code ***
          Serial.println();
          Serial.println("Confirmez le Nouveau mot de passe à 4 chiffres");
          ValCode=Saisie(); //appel la capture des caractéres et verif conformité
  
          switch (ValCode){
            case 0:
              CodeValide=1;
              for (byte x=0;x<4;x++){
                if (DataRx[x]!=NvCode[x]) CodeValide=0;
              }
              if (CodeValide==0) Serial.println("Erreur Confirmation");
              if (CodeValide==1){
                for (byte x=0;x<4;x++){
                  code[x]=NvCode[x];
                }
                Serial.println ("Code Enregistré");
                
              }
              break;
            case 1:
              Serial.println("Nombre de Caractéres incorrecte");
              break;
            case 2:
              Serial.println("Mot de passe ne doit comporter que des des chiffres");
              break;
          }
        }

        

      break;
      //*** Ni A ni B *******************************************************************
      default :
        Serial.println("Veuillez saisir A ou B !");
        
    }
  }
  else{ 
    Serial.println("Veuillez saisir A ou B !");
    while (Serial.available () > 0){ // Purge le Tampon
      char bidon= Serial.read();
    }
  }
}
//************************************************************************************
//************************************************************************************
// renvoie 0:Code comforme 1:Nbre  de car incorrect 2:Pas que des chiffres

byte Saisie(){
  byte erreur=0;
  while (Serial.available()==0){}
  delay(100);

  if (Serial.available() == 4){
    for(byte x=0;x<4;x++){              // Memo caracteres recus
      DataRx[x]=Serial.read();
    }
    
    for(byte x=0;x<4;x++){              // Test Chiffres ?
      if (DataRx[x]<'0' || DataRx[x]>0x39 ) erreur=2;
    }
  }
  else{
    erreur=1;
    while (Serial.available () > 0){ // Purge du Tampon
      char bidon= Serial.read();
    }
  }
 return erreur;  
}
//************************************************************************************
