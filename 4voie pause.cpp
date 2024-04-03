// https://pclapcounter.forumotion.com/t1298-sketch-with-4-lanes-pause-button-power-control-for-analogue-track

// Pclapcounter & Arduino
// sketch for 4 lanes - 1 power rele - 1 PauseButton
// Autor: Steve112
// 
// Lanes = InputPins 2-3-4-5€
// Pause Button = InputPin 8
// Porew control = OutputPin 6

int LANE1 = 2;
int LANE2 = 3;
int LANE3 = 4;
int LANE4 = 5;
int RELE = 12;
int LED = 13;
int PAUSA = 6;

int L1Flag = 0;
int L2Flag = 0;
int L3Flag = 0;
int L4Flag = 0;
int PAFlag = 0;
int ledState = LOW; 
long Inibit_Lane=2400;
long Inibit_Button=300;

unsigned long L1;
unsigned long L2;
unsigned long L3;
unsigned long L4;
unsigned long P1;
unsigned long TLED=1000;
long previousMillis = 0; 



int val=0;
int L1State = 0;
int L2State = 0;
int L3State = 0;
int L4State = 0;
int Pa=0;
// setup routine :
void setup() {
    // serial communication at 9600 bits :
    Serial.begin(9600);
    // here we set input/output Pins :
    pinMode(LANE1, INPUT);
    pinMode(LANE2, INPUT);
    pinMode(LANE3, INPUT);
    pinMode(LANE4, INPUT);
    pinMode(PAUSA, INPUT);//pause button
    pinMode(LED, OUTPUT);
    pinMode(RELE, OUTPUT);//power
}


void loop() {
L1State = digitalRead(LANE1);
L2State = digitalRead(LANE2);
L3State = digitalRead(LANE3);
L4State = digitalRead(LANE4);
Pa = digitalRead(PAUSA);


unsigned long currentMillis = millis();


if ( Serial.available() ) {
    String b;
    b = Serial.readStringUntil('[');
    {
        String s;
        //power control
        s = Serial.readStringUntil(']');
        if ( s == "PW000" ) { 
            digitalWrite(RELE, LOW);
            val = 0;
        }
        if ( s == "PW001" ) { 
            digitalWrite(RELE, HIGH);
            val = 1;
        }
        if ( s == "SL071" ) {   TLED=800; }
        if ( s == "SL051" ) {   TLED=500; }
        if ( s == "SL041" ) {   TLED=400; }
        if ( s == "SL031" ) {   TLED=300; }
        if ( s == "SL021" ) {   TLED=200; }
        if ( s == "SL011" ) {   TLED=70; }
        if ( s == "SL061" ) {   TLED=1; }
    }
}


if(currentMillis - previousMillis > TLED) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis; 

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
        ledState = HIGH;
    else
        ledState = LOW;

    if (TLED == 1){ ledState = HIGH; }
    // set the LED with the ledState of the variable:
    digitalWrite(LED, ledState);
}


if (val == 1) { 
    // Car cross the Start/Finish line
    if ((L1State == 1) && ((currentMillis-L1)>Inibit_Lane) && (L1Flag == 0) ){ 
        Serial.println("[SF01]"); 
        L1=currentMillis;
        L1Flag = 1;
    };
    if ((L2State == 1)&& ((currentMillis-L2)>Inibit_Lane)&& (L2Flag == 0)){ 
        Serial.println("[SF02]"); 
        L2=currentMillis;
        L2Flag = 1;
    };
    if ((L3State == 1)&& ((currentMillis-L3)>Inibit_Lane)&& (L3Flag == 0)){ 
        Serial.println("[SF03]"); 
        L3=currentMillis;
        L3Flag = 1;
    };
    if ((L4State == 1)&& ((currentMillis-L4)>Inibit_Lane)&& (L4Flag == 0)){ 
        Serial.println("[SF04]"); 
        L4=currentMillis;
        L4Flag = 1;
    };

    if ((L1State == 0) && ((currentMillis-L1)>Inibit_Lane) ){   L1Flag = 0; };
    if ((L2State == 0) && ((currentMillis-L2)>Inibit_Lane) ){   L2Flag = 0; };
    if ((L3State == 0) && ((currentMillis-L3)>Inibit_Lane) ){   L3Flag = 0; };
    if ((L4State == 0) && ((currentMillis-L4)>Inibit_Lane) ){   L4Flag = 0; };
}

//pause/resume command 


if ((Pa == 0) && (PAFlag == 2)){ 
    P1=currentMillis;
    PAFlag = 0;
}
if ((Pa == 1)&& (PAFlag == 0)){ 
    PAFlag = 1;
    P1=currentMillis;
}
if ((Pa == 1) && (PAFlag == 1)&& ((currentMillis-P1)>Inibit_Button)){ 
    PAFlag = 2;
    Serial.println("[BT04]");
}

if ((Pa == 0)&& ((currentMillis-P1) PAFlag = 0;
}
}
