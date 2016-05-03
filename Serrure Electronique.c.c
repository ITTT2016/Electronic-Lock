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
unsigned short Kp;

void Lcd_Menu()
{
Lcd_Init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Lcd_Out(2,5,"ITTT NewTech");
delay_ms(1000);
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
        case 10: Kp=56; break;    //8
        case 11: Kp=57; break;    //9
        case 13:Kp=42; break;    //*
        case 14:Kp=48; break;    //0
        case 15: Kp=35; break;   //#
}

}

//switch off the Lcd if "exit" is chosen
void Lcd_off()
{
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"see you next time");
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

void main(){
Lcd_menu();
for(;;){
Lire_Pad();
if(Kp==52) Lcd_off();
if(Kp==49) configuration();
   }

}
