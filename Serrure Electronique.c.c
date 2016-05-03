//LCD module connections

sbit LCD_RS at RB4_bit;

sbit LCD_EN at RB5_bit;

sbit LCD_D4 at RB0_bit;

sbit LCD_D5 at RB1_bit;

sbit LCD_D6 at RB2_bit;

sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;

sbit LCD_EN_Direction at TRISB5_bit;

sbit LCD_D4_Direction at TRISB0_bit;

sbit LCD_D5_Direction at TRISB1_bit;

sbit LCD_D6_Direction at TRISB2_bit;

sbit LCD_D7_Direction at TRISB3_bit;

//End LCD module connections

//KeyPad module connections

char KeypadPort at PORTD;
unsigned short Kp;     //valeur lu par Pad
char Pass[5];          //password
int i=0; //compteur

 void Lcd_intro()
{
Lcd_Init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Lcd_Out(2,5,"ITTT NewTech");
delay_ms(1000);

}

void Lcd_Menu()
{

Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"1-Configuration");
Lcd_Out(2,1,"2-Access By Pad");
Lcd_Out(3,1,"3-Access By Voice");
Lcd_Out(4,1,"4-Exit");
}

void Lire_Pad()
{
Kp=0;
do{
 Keypad_Init();
 Kp=Keypad_Key_Click();
 delay_ms(100);
 }
while(!Kp);
       //prepare value for output,transform key to it's ASCII value
 switch (Kp){
        case 1: Kp=49; break;    //1
        case 2: Kp=50; break;       //2
        case 3: Kp=51; break;      //3
        case 5: Kp=52; break;     //4
        case 6: Kp=53; break;     //5
        case 7: Kp=54; break;     //6
        case 9: Kp=55; break;     //7
        case 10:Kp=56; break;    //8
        case 11:Kp=57; break;    //9
        case 13:Kp=42; break;    //*
        case 14:Kp=48; break;    //0
        case 15:Kp=35; break;   //#
}



}

//switch off the Lcd if "exit" is chosen
void Lcd_off()
{
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"see you next time");
 delay_ms(500);
 Lcd_cmd(_LCD_TURN_OFF);
}

void Configuration()
{

Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"1-Change Password");
Lcd_Out(2,1,"2-Password Forgotten");
Lcd_Out(3,1,"press # to go back");
Lire_Pad();
if(Kp==35) Lcd_menu();

}

void Set_password()
{
Lcd_Init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"Set your Password");
for(i=1;i<6;i++)
{
 Lire_Pad();
 EEPROM_Write(Pass[i],Kp);
 Lcd_chr(2,i,Kp);
}

}

char txt[5]; // to use it to compare with the pass

int check()  //check the old password to change it
{

Lcd_Init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"yourold pass");

   for(i=1;i<6;i++)
{
 Lire_Pad();
 Pass[i]=Kp;
 Lcd_chr(2,i,'*');
}

 if(strcmp(txt,pass)) return 1;
   

}

void warning()
{

Lcd_Init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"your Password is wrong!");
Lcd_off();

}

int a=1; // to use it boolean

void main(){



Lcd_intro();
if(a) {B:Set_password(); a=0;}

A:Lcd_menu();

for(;;) {
while(Kp!=49||Kp!=50||Kp!=51 ||Kp!=52)
   {
    Lire_Pad();
    if(Kp==52) Lcd_off();
    if(Kp==49) {
               configuration();
              while(Kp!=49||Kp!=35 || Kp!= 50)
                {
                 Lire_Pad();
                 if(Kp==35) goto A;
                 if(Kp==49) { if(check()) goto B; else warning();}
                }
               
               }

   }
        }

}