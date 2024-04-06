#include "piste.h"
#include "Adafruit_NeoPixel.h"

#define relais 4
#define btp_AU 5
#define btp_SW 7
#define BlinkJaune 500

#define NUMPIXELS 16
#define pixelPin   6
Adafruit_NeoPixel strip(NUMPIXELS, pixelPin, NEO_GRB + NEO_KHZ800);
//							red, green, blue
uint32_t depart = strip.Color(255, 0, 255);
uint32_t marche = strip.Color(255, 0, 255);
uint32_t arret = strip.Color(255, 0, 0);
uint32_t jaune = strip.Color(255, 255, 0);
uint32_t stopgo = strip.Color(255, 0, 255);
uint32_t fuelOut = strip.Color(0, 0, 255);


String Code, laChaine;
int ouca, Etat, YFlag;
bool AUstep=true, SWstep=true;
unsigned long previousMillis = 0;

void setup() {
	Serial.begin(9600); // Communication PC
	Serial.println("Penn Ar Slot piste");
	
	pinMode(btp_AU, INPUT_PULLUP);
	pinMode(btp_SW, INPUT_PULLUP);
	pinMode(relais, OUTPUT); digitalWrite(relais, LOW);
	strip.begin(); // INITIALIZE NeoPixel
}

void loop() {
	// arret urgence déclenché
	if(digitalRead(btp_AU)) {
		if(AUstep) {
			Serial.println(BUTTON_RACE_PAUSE);
			AUstep=false; 
		}
	} else { AUstep = true; }
	// interrupteur jaune
	if(!digitalRead(btp_SW)) {
		if(AUstep) {
			Serial.println(BUTTON_TOGGLE_YELLOW_FLAG);
			SWstep=false; 
		}
	} else { SWstep = true; }

	// si YFlag = 1, fait clignoter la led jaune
	unsigned long currentMillis = millis();
	if (YFlag)  {
		if (currentMillis - previousMillis >= BlinkJaune) {
			strip.clear();
			if(YFlag%2) {
				for(int i=0; i<NUMPIXELS; i++) {
					strip.setPixelColor(i, jaune);
				}
			}
			strip.show();

			previousMillis = currentMillis;
			YFlag++;
		}
	}
	
	//             Réception_PC  Serial
	if ( Serial.available()>0 ) {
		String debut = Serial.readStringUntil('[');
		laChaine = Serial.readStringUntil(']');
	}
	if (laChaine != "") {
		Code = laChaine.substring( 0, 2); // 'SL'021
		ouca = laChaine.substring( 2, 4).toInt(); // SL0'2'1
		Etat = laChaine.substring( 4, 5).toInt(); // SL02'1'

		// feux depart + course
		if (Code == "SL") {
			strip.clear();
			// rebourd
			if(ouca<6 && Etat==1) {
				for(int i=0; i<ouca; i++) {
					strip.setPixelColor(i, depart);
				}
			} else
			// depart
			if(ouca==6 && Etat==1) {
				for(int i=0; i<NUMPIXELS; i++) {
					strip.setPixelColor(i, marche);
				}
			} else
			// arret
			if(ouca==7 && Etat==1) {
				for(int i=0; i<NUMPIXELS; i++) {
					strip.setPixelColor(i, arret);
				}
			} else
			// jaune
			if(ouca==8) {  YFlag = Etat; }
			strip.show();
		} else
		// Stop & Go
		if (Code == "SG") {
			strip.clear();
			for(int i=0; i<NUMPIXELS; i++) {
				strip.setPixelColor(i, (Etat==1) ? stopgo : marche);
			}
			strip.show();
		} else
		// out fuel
		if (Code == "OF") {
			strip.clear();
			for(int i=0; i<NUMPIXELS; i++) {
				strip.setPixelColor(i, (Etat==1) ? fuelOut : marche);
			}
			strip.show();
		} else
		// Fuel
		if (Code == "FL") {
			Etat = laChaine.substring( 4, 7).toInt(); // %
		}
		laChaine = "";
		ouca = "";
	}
}
