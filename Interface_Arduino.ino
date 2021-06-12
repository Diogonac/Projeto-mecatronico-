#include <millisDelay.h>
#include "EasyNextionLibrary.h"  

EasyNex myNex(Serial); //Crio o objeto do nextion display

//Variaveis para comando customizado
int value;
int arrayPlace;    
int dataS[4] = {1}; //Armazena a leitura do comando customizado
unsigned char  number;
unsigned char  pagina; 
String numericAttribute;

//=========== Variáveis globais int, float, string ==========

String pega = "";
String solta = "";
int contador = 0;
int quantidade_ml; //Armazena a quantidade de volume desejada na posição
int botao0, inChar;
String inString = ""; //Armazena o que é recebido da nucleo 
String movimenta = "";
String velocidade = ""; //Armazena a velocidade desejada para o JOG
const int RESET_PIN = 2; //Pino para Reset da placa 
String ultimo_valor_X = ""; //Armazena o ultimo valor de X para atualizar na página
String ultimo_valor_Y = ""; //Armazena o ultimo valor de Y para atualizar na página
String ultimo_valor_Z = ""; //Armazena o ultimo valor de Z para atualizar na página
unsigned long delayStart = 0; // the time the delay started

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    ; 
  }
  
  myNex.begin(115200); //Comunicação com o Nextion Display
  Serial1.begin(115200); //Comunicação com a Nucleo
  
  pinMode(LED_BUILTIN, OUTPUT);   
  digitalWrite(LED_BUILTIN, LOW);
  
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  
  delay(150);
  
  myNex.writeStr("page 0"); //Forço o Nextion Display ir para pagina 0
  ultimo_valor_X = "";
  ultimo_valor_Y = "";
  ultimo_valor_Z = "";
  movimenta = "";
  solta = "";
  pega = "";
  dataS[arrayPlace] = 1;
  quantidade_ml = 0;
  
}

void loop() { 

  myNex.NextionListen(); 

  while (Serial1.available() > 0) {
    inChar = Serial1.read();
    inString += (char)inChar;

    if (inChar == '\n') {

      if (inString[0] == 'E' & inString[1] == '1') { 
        myNex.writeStr("page 11"); //Forço o Nextion Display ir para pagina 11
      }

      if (inString[0] == 'D') { 
        
        String inString = "";   
        String ultimo_valor_X = "";    
        String ultimo_valor_Y = "";   
        String ultimo_valor_Z = "";    
        String velocidade = "";   
        
        movimenta = "";
        solta = "";
        pega = "";
        quantidade_ml = 0;

        myNex.writeStr("page 1"); //Forço o Nextion Display ir para pagina 1
        
        delay(5);
        
        myNex.writeNum("x0.val", ultimo_valor_X.toFloat() * 100); //Escrevo o valor float na variável ""
        myNex.writeNum("x1.val", ultimo_valor_Y.toFloat() * 100); //Escrevo o valor float na variável ""
        myNex.writeNum("x2.val", ultimo_valor_Z.toFloat() * 100);  //Escrevo o valor float na variável ""
        myNex.writeStr("page 1"); //Forço o Nextion Display ir para pagina 11

      }
      
      if (inString[0] == 'X') { 
        
        ultimo_valor_X = inString;
        ultimo_valor_X.remove(0, 1); 
        myNex.writeNum("x0.val", ultimo_valor_X.toFloat() * 100);

      }
      
      if (inString[0] == 'Y') { 
        
        ultimo_valor_Y = inString;
        ultimo_valor_Y.remove(0, 1); 
        myNex.writeNum("x1.val", ultimo_valor_Y.toFloat() * 100);

      }
      if (inString[0] == 'Z') { 
        
        ultimo_valor_Z = inString;
        ultimo_valor_Z.remove(0, 1); 
        myNex.writeNum("x2.val", ultimo_valor_Z.toFloat() * 100);

      }
      inString = "";
    }
  }
}

void(* resetFunc) (void) = 0; //Força o RESET

void easyNexReadCustomCommand() {

  switch (myNex.cmdGroup) {
    
    case 'S': 

      arrayPlace = myNex.readByte();
      value = myNex.readByte();

      dataS[arrayPlace] = value;

      velocidade = dataS[arrayPlace];
      
      Serial1.println(dataS[arrayPlace] * 1000);
      delay(1);
      break;
      
  }
}

void trigger0() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.write("+Y000");
  delay(1);
  
}

void trigger1() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.write("-Y000");
  delay(1);
  
}

void trigger2() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.write("+X000");
  delay(1);

}
void trigger3() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.write("-X000");
  delay(1);

}
void trigger4() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.write("+Z000");
  delay(1);

}

void trigger5() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial1.write("-Z000");
  delay(1);

}

void trigger6() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1);

  digitalWrite(RESET_PIN, HIGH);
  delay(10);
  
  ultimo_valor_X = "";
  ultimo_valor_Y = "";
  ultimo_valor_Z = "";
  movimenta = "";
  solta = "";
  pega = "";
  dataS[arrayPlace] = 1;
  quantidade_ml = 0;
  resetFunc();
  
}

void trigger7() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  Serial1.println("RF000");
  delay(1);
  Serial1.println("NN000");
  delay(1);

  myNex.writeStr("page 3"); 
  
}

void trigger9() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  myNex.writeNum("x0.val", ultimo_valor_X.toFloat() * 100);
  myNex.writeNum("x1.val", ultimo_valor_Y.toFloat() * 100);
  myNex.writeNum("x2.val", ultimo_valor_Z.toFloat() * 100); 
  myNex.writeNum("n0.val", dataS[arrayPlace]);

}

void trigger10() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  myNex.writeNum("x0.val", ultimo_valor_X.toFloat() * 100);
  myNex.writeNum("x1.val", ultimo_valor_Y.toFloat() * 100);
  myNex.writeNum("x2.val", ultimo_valor_Z.toFloat() * 100); 
  myNex.writeNum("n0.val", dataS[arrayPlace]);
  
}

void trigger11() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  quantidade_ml = 0;
  quantidade_ml = myNex.readNumber("n6.val");
  
}

void trigger12() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial1.println("CI000");
  delay(1);

}

void trigger8() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  pega = String(String("P1") + quantidade_ml);
  Serial1.println(pega); 
  delay(1);
  Serial1.println("0000");
  pega = "";
  
}
void trigger13() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S1") + quantidade_ml);
  Serial1.println(solta); 
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger14() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S2") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger15() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S3") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger16() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S4") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger17() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S5") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger18() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S6") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}


void trigger19() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  solta = String(String("S7") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger20() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S8") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

void trigger21() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  solta = String(String("S9") + quantidade_ml);
  Serial1.println(solta);
  delay(1);
  Serial1.println("0000");
  solta = "";
  
}

//==================== Mover até as posições =======================================
void trigger22() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  movimenta = String("MP10");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
}
void trigger23() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS10");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger24() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS20");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger25() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS30");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}


void trigger26() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS40");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger27() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS50");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger28() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS60");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}


void trigger29() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  movimenta = String("MS70");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger30() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  movimenta = String("MS80");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger31() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  movimenta = String("MS90");
  Serial1.println(movimenta);
  delay(1);
  Serial1.println("0000");
  movimenta = "";
  
}

void trigger32() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  digitalWrite(RESET_PIN, HIGH);
  delay(10);
  digitalWrite(RESET_PIN, LOW);
  delay(1);
  Serial1.println("CC00");
  myNex.writeStr("page 1");
  
}
