#include <Keypad.h>
#include <LiquidCrystal.h>

 struct Staq//structura na staq
{
  String ime;
  int pin;
  bool alarma;
};
char pad[4][4]=
{
  {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}

};//zapolojenie na klavishite
byte rowPins[4] = {9,8,7,6};
byte ColPins[4] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(pad),rowPins,ColPins,4,4);//nastroika na keypada
LiquidCrystal lcd(12, 11,15, 16, 17, 18);//nastroika na lcd
int pir = 7;
bool zashtita = true;//statusa na zashtitata
String parola = "1234";//default parola
Staq stai[2] = {{"Room 1",10,false},{"Room 2",13,false}};//masiv ot staite
void changenamesandpinsmenu(int a)//menu za smqna na pinovete
{
      
 
     switch(a)
     {
           
    case 0:
       lcd.clear();
       lcd.print("->"+stai[0].ime+"-"+stai[0].pin);
       lcd.setCursor(0,1);
       lcd.print(stai[1].ime+"-"+stai[1].pin); 
       
       break;
       
    case 1:
         lcd.clear();
         lcd.print(stai[0].ime+"-"+stai[0].pin); 
      lcd.setCursor(0,1);
        lcd.print("->"+stai[1].ime+"-"+stai[1].pin);
         
      }  
  
}
int changeimeipin(int i)//metod za smqna na pin
{
  
            lcd.clear();
            
            lcd.print("PIN:");
            int pin =  atoi(inputpin().c_str());
  stai[i].pin = pin;
  lcd.clear();
  return 0;
         

}
void clear()//izkluchva vsi4ki alarmi
{
 int i =0;
  while(i<(sizeof(stai)/sizeof(*stai)))
  {
    
    stai[i].alarma=false;
    i++;
  
  
}
noTone(19);//digitalWrite(19,LOW);



}
void sensor()//metod za chetene ot sensora i pri zasichane vklu4va alarmata 
{
  
 int i =0;
  while(i<(sizeof(stai)/sizeof(*stai)))
  {
    int val;
    
    lcd.setCursor(0,i);
    if(digitalRead(stai[i].pin)==1){stai[i].alarma=true;}
    if(stai[i].alarma == true)      
    {
      lcd.print(stai[i].ime + " "+"Threat!!!");tone(19,1000);//digitalWrite(19,HIGH);
    }
    else
    {
    lcd.print(stai[i].ime + " "+"No threat");    
    }       
         i++;
 
  }
  
}
String input()//metod za chetene na parolata
{
  int i=0;
   String word = "";
  while(i<4)
  {
    char test = keypad.getKey();
    
    if(test!=NO_KEY)
    {
      word=word+test;
      lcd.print(test);
      i++; 
      if(test=='D'){word="";i=0;lcd.setCursor(0,1);lcd.print("                   ");lcd.setCursor(0,1);}       
     
         
     
    }  
  }     
return word;
  word="";
}
String inputpin()//metod za chetene na pina 
{
  int i=0;
   String word = "";
  while(i<2)
  {
    char test = keypad.getKey();
    
    if(test!=NO_KEY)
    {
      word=word+test;
      lcd.print(test);
      i++; 
          
     
         
     
    }  
  }     
return word;
  word="";
}
void setup() {
  Serial.begin(9600);
  analogWrite(A0, 10);
  
  lcd.begin(16, 2);
  
  //lcd.print("lol");
}

void loop() {
  
  char button = keypad.getKey();//chetene na klavish
  
  if(zashtita==true)
  {
      sensor();
    if(button=='*')
    {
      lcd.clear();
      lcd.print("PIN:");
      lcd.setCursor(0,1);
      if(input()==parola){zashtita=false;lcd.clear();} else{lcd.clear();}       
    }
   
  }
  else
  {
	  //sledvashite redove sa menuto za lognatiq potrebitel
    clear();
    lcd.print("A-Change pass");
    lcd.setCursor(0,1);
    lcd.print("B-Change pins");
    lcd.setCursor(0,0);
    if(button=='*')
    {
      lcd.clear();
      clear();
      zashtita= true;
    
        
    }
    if(button=='A')
    {
      String temp1;
      String temp2;
        lcd.clear();
        lcd.print("New password:");
          lcd.setCursor(0,1);
        temp1 = input();
      lcd.clear();
      lcd.print("Confirm:");
        lcd.setCursor(0,1);
      temp2 = input();
      lcd.clear();
      if(temp1 ==temp2){parola=temp1;lcd.print("Smenena!");delay(2000);}
      else{lcd.print("Razlichni sa!");delay(2000);}
        
        lcd.clear();
    
    }
    
    if(button=='B'){
      
      lcd.clear();
      int abc = 0;
      changenamesandpinsmenu(abc);
      while(zashtita==false)
      {
        button =keypad.getKey();
        if(button!=NO_KEY)
        {
        if(button=='B'){
          abc=0;changenamesandpinsmenu(abc);}
           delay(200);
          
       
        if(button=='C'){abc=1;changenamesandpinsmenu(abc);}
          if(button=='A')
          {
             changeimeipin(abc);
             changenamesandpinsmenu(abc);
          
          }
          if(button=='*'){zashtita=true;}
          }
        
      }
      
    
    
    }      
  }
  
}
