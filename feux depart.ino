// https://pclapcounter.forumotion.com/t1638-feux-de-depart-en-quelques-lignes-y-flag-clignotant
const int LedSL[] = {2,3,4,5,6,7,8,9}; // Starting Lights x 8
long delaiReception = 10; //
String leCode, laChaine;
int ledDecompte, Etat, YFlag; 

void setup() 
{
 Serial.begin(9600); // Communication PC
 Serial.println("Nano_Feux de Départ");

 for (int i = 2 ; i <= 9 ; i++) 
   { 
     pinMode( i, OUTPUT); // Définit les broches 2 à 9 comme sorties
     digitalWrite(i, LOW); // éteint les sorties
   }
}

void loop() 
{
 //             Réception_PC  Serial
 if ( Serial.available()>0 )
     {
       String debut = Serial.readStringUntil('[');
       { laChaine = Serial.readStringUntil(']'); }
     }
 
// si YFlag = 1, fait clignoter la led jaune
      if ( YFlag == 1)  { digitalWrite(LedSL[7], millis() / 500 % 2 );}    

 if (laChaine != "") 
  {
     leCode = laChaine.substring( 0, 2); // 'SL'021
     Etat = laChaine.substring( 4, 5).toInt(); // SL02'1'
     ledDecompte = laChaine.substring( 3, 4).toInt(); // SL0'2'1
     laChaine = "";

     if (leCode == "SL")  
      {
        {
          digitalWrite(LedSL[ledDecompte - 1], Etat);
          if (ledDecompte == Cool {  YFlag = Etat; } // if (ledDecompte == huit en chiffre) {  YFlag = Etat; }
        }
        ledDecompte = "";
      }
      
   }
}
