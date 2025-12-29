#include <Wire.h> 
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>


//=========================================================// 


LiquidCrystal_I2C lcd(0x27,16,2);

int menu =1;
int submenu =0;
int contador = 0;
int golpes = 0;
void programa();
int sensor;
bool estadobase = LOW;
bool estadonovo;
int maximo = 0;

//=========================================================// 

void setup()
{
	lcd.init();
  Serial.begin(9600);
  lcd.backlight();
  
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(11,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
}

//=========================================================// 

void loop()
{
  switch (menu){
    
//=========================================================//    
    
    case 0:
    //Parada e contagem.
    	if (digitalRead(8) == LOW) {

            digitalWrite(12, LOW);   
            lcd.clear();
            lcd.home();
            lcd.print("PARADA ACIONADA");
            delay(1200);
          	lcd.clear();

            while (true) {

                
                lcd.home();
                lcd.print("RESET[X]VOLTA[O]");
                lcd.setCursor(0,1);
                lcd.print("Contador: ");
                lcd.print(contador);
             	

                
                if (digitalRead(8) == LOW) {
                    contador = 0;
                    submenu = 0;
                    menu = 1;       
                    lcd.clear();
                    lcd.print("RESET FEITO!");
                    delay(3000);
                    lcd.clear();
                    break;          
                }

                
                if (digitalRead(9) == LOW) {
                    lcd.clear();
                    lcd.print("RETOMANDO...");
                    delay(3000);
                    lcd.clear();
                    
                    digitalWrite(12, HIGH);  
                    break;                   
                }

                
            }

            break;  //Sai do case caso a parada seja confirmada
        }

        digitalWrite(12,HIGH);
        lcd.home();
        lcd.print("Contagem:");
        lcd.print(contador);
        sensor=digitalRead(13);
        estadonovo=sensor;

        if (estadonovo != estadobase){
        	if (estadonovo==HIGH){
            	contador++;

                    }
            estadobase = estadonovo;
            }
        if (contador == maximo){
            lcd.clear();
            lcd.home();
            lcd.print("    CONTAGEM");
            lcd.setCursor(0,1);
            lcd.print("   ENCERRADA!");
            menu = 1;
            digitalWrite(12,LOW);
            delay(5000);
            submenu =0;
            lcd.clear();

                }
        break;
//=========================SUBMENUS 0====================//     
    
    case 1:
    	contador =0;
  		lcd.home();
  		lcd.print("      MENU     >");
    	lcd.setCursor(0,1);
    	lcd.print("  COMPACTADOR.");
    	break;
    
//=========================================================//     
    case 2:
    	lcd.home();
    	lcd.print("<   PROGRAMAR  >");
    	lcd.setCursor(0,1);
    	lcd.print("MODO DE OPERACAO");
    	//Se o botão selecionar for apertado, entra o menu 4.
    	if (digitalRead(9) == LOW){
          menu = 4;
          submenu =1;
          lcd.clear();
          delay(300);
        }
    	break;

//=========================================================//     
    
    case 3:
    	lcd.home();
    	lcd.print("<   ESCOLHER   >");
    	lcd.setCursor(0,1);
    	lcd.print("  PROGRAMACAO.");
    	//Menu 8.
    	if (digitalRead(9) == LOW){
          menu = 8;
          submenu =3;
          lcd.clear();
          delay(300);
        }
    	break;
    

//==========================SUBMENUS 1====================//    
    
    case 4://Submenu 4 - Programação.
    	lcd.home();
  		if (submenu == 1) {
    		lcd.print("  PROGRAMACAO  >");
    		lcd.setCursor(0,1);
    		lcd.print(" P1 - ");
		    lcd.print(EEPROM.read(0));
    		lcd.print(" GOLPES");
    
    		// Entra no modo ajuste
    		if (digitalRead(9) == LOW){
      			submenu = 2;
      			lcd.clear();
      			delay(300);
   		 	}
 		 } 
    
    	else if (submenu == 2) {
    		lcd.print(" AJUSTE DE GOLPES");
    		lcd.setCursor(0,1);
    		lcd.print("P1: ");
    		lcd.print(golpes);
   			lcd.print("    ");
    
   		 // Confirma.Quando confirmar lembra de colocar o valor 
         //de golpes na memoria depois zerar golpes.
    		if (digitalRead(9) == LOW) {
      			submenu = 1;
      			lcd.clear();
            EEPROM.write(0,golpes);
            golpes = 0;
      			delay(300);
    		}
  		}
  		break;
//=========================================================//    
    case 5://Submenu 5 - Programação.
    	lcd.home();
  		if (submenu == 1) {
    		lcd.print("< PROGRAMACAO  >");
    		lcd.setCursor(0,1);
    		lcd.print(" P2 - ");
		    lcd.print(EEPROM.read(2));
    		lcd.print(" GOLPES");
    
    		if (digitalRead(9) == LOW){
      			submenu = 2;
      			lcd.clear();
      			delay(300);
    		}
 		} 
  		else if (submenu == 2) {
    		lcd.print(" AJUSTE DE GOLPES");
    		lcd.setCursor(0,1);
    		lcd.print("P2: ");
    		lcd.print(golpes);
   			lcd.print("    ");
    
    		if (digitalRead(9) == LOW) {
      			submenu = 1;
      			lcd.clear();
            EEPROM.write(2,golpes);
            golpes = 0;
      			delay(300);
    		}
  		}
  		break;
    
//=========================================================//     
    
    case 6://Submenu 6 - Programação.
    	lcd.home();
  		if (submenu == 1) {
    		lcd.print("< PROGRAMACAO  >");
    		lcd.setCursor(0,1);
    		lcd.print(" P3 - ");
		    lcd.print(EEPROM.read(4));
    		lcd.print(" GOLPES");
    
    		if (digitalRead(9) == LOW){
      			submenu = 2;
      			lcd.clear();
      			delay(300);
    		}
 		} 
  		else if (submenu == 2) {
    		lcd.print(" AJUSTE DE GOLPES");
    		lcd.setCursor(0,1);
    		lcd.print("P3: ");
    		lcd.print(golpes);
   			lcd.print("    ");
    
    		if (digitalRead(9) == LOW) {
      			submenu = 1;
      			lcd.clear();
            EEPROM.write(4,golpes);
            golpes = 0;
      			delay(300);
    		}
  		}
  		break;
    
//=========================================================//     
    
    case 7:
    	lcd.home();
    	lcd.print("<   VOLTAR AO");
    	lcd.setCursor(0,1);
    	lcd.print(" MENU PRINCIPAL");
    	if (digitalRead(9) == LOW) {
      		lcd.clear();
          submenu = 0;
    			menu =1;
    		}
    	break;
  
  
//=========================================================//   
  	case 8:
    	lcd.home();
  		lcd.print("    PROGRAMAS  >");
    	lcd.setCursor(0,1);
    	lcd.print(" P1 - ");
	    lcd.print(EEPROM.read(0));
    	lcd.print(" GOLPES");
    	if (digitalRead(9) == LOW) {
      		lcd.clear();       	
          	lcd.home();
    				lcd.print("INICIANDO P1...");
          	delay(3000);
          	lcd.clear();
						submenu =4;
    				menu = 0;
          	maximo = EEPROM.read(0);
    		}
    	break;
    
//=========================================================// 
    
  	case 9:
    	lcd.home();
    	lcd.print("<   PROGRAMAS  >");
    	lcd.setCursor(0,1);
    	lcd.print(" P2 - ");
	    lcd.print(EEPROM.read(2));
    	lcd.print(" GOLPES");
    	if (digitalRead(9) == LOW) {
      		lcd.clear();
          	lcd.home();
    				lcd.print("INICIANDO P2...");
          	delay(3000);
          	lcd.clear();
						submenu =4;
    				menu = 0;
          	maximo = EEPROM.read(2);
    		}
    	break;
    
//=========================================================// 
    
  	case 10:
    	lcd.home();
    	lcd.print("<   PROGRAMAS  >");
    	lcd.setCursor(0,1);
    	lcd.print(" P3 - ");
	    lcd.print(EEPROM.read(4));
    	lcd.print(" GOLPES");
    	if (digitalRead(9) == LOW) {
      		lcd.clear();
          	lcd.home();
    				lcd.print("INICIANDO P3...");
          	delay(3000);
          	lcd.clear();
						submenu =4;
    				menu = 0;
          	maximo = EEPROM.read(4);
    		}
    	
    	break;
	
  
//=========================================================// 
  
  	case 11:
    	lcd.home();
    	lcd.print("<   VOLTAR AO");
    	lcd.setCursor(0,1);
    	lcd.print(" MENU PRINCIPAL");
    	if (digitalRead(9) == LOW) {
      		lcd.clear();
          submenu = 0;
    			menu =1;
    		}
    	break;
	}
  
//=========================================================//

  //Botão direito.
  if (digitalRead(10) == LOW){
    if (menu<3 && submenu == 0){
  		menu += 1;
    }
  	else if (menu<7 && submenu == 1){
  		menu += 1;
    }
    else if (submenu ==2){
    	golpes +=5;
    }
    else if (menu<11 && submenu == 3){
  		menu += 1;
    }
    
    delay(300);
    lcd.clear();
    }

//=========================================================// 
  
  //Botão esquerdo.
  if (digitalRead(11) == LOW){
    if (menu>1 && submenu == 0){
  		menu -= 1;
    }
    else if (menu>4 && submenu == 1){
  		menu -= 1;
    }
    else if (golpes !=0 && submenu ==2){
    	golpes -=5;
    }
    else if (menu>8 && submenu == 3){
  		menu -= 1;
    }
    
    delay(300);
    lcd.clear();
    }

}