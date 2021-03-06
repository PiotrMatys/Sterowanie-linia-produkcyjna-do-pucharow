/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2017-02-16
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <mega128.h>
#include <stdio.h>
#include <delay.h>
//#include <alcd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Declare your global variables here
long int sek0,sek1,sek2,sek3,sek4;
long int ulamki_sekund_0,ulamki_sekund_1;
int proces[10];
int skonczony_proces[10];
long int czas_monterow;
long int pomocnicza;
long int stala_czasowa;
int start;
int licznik_nakretek;
//char *dupa1;
int nakretka;
//int nakretka_1;
int licznik_nakretek;
int czekaj_komunikacja;
int ff;
int podaj_nakretke;
int wcisnalem_pedal;
int zezwolenie_na_zacisniecie_szczek_od_master;
int zacisnalem_szczeki;
int jest_nakretka_przy_dolnym;
int wlaczam_dodatkowe_wibracje_i_psikanie;
long int licznik_drgania;
int wystarczy_zejscia;
int licznik_widzenia_nakretki;
int ilosc_prob_wybicia_zakretki_do_gory;
int wcisniete_zakonczone;
int zezwolenie_od_master;
int basia1;
int pozycja_wiezy;
int kkk;
int kkk1;
int v1;
int wielkosc_przesuniecia_kamien;
int kamien;
int speed_normal;
int bufor_bledu;
int zliczylem_male_puchary;
int licznik_impulsow_male_puchary;
int tryb_male_puchary;
int test_zjezdzalni_nakretek;
int przeslano_informacje_male_puchary;
int male_puchary_pozwolenie_wyjecia_puchara_monter_3;
int wieza;
int jedz_wieza_cykl_znacznik;
long int sek5;
int wyzerowalem_sek5;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
sek0++;
sek1++;
sek2++;
sek3++;
sek4++;
sek5++;
}

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
// Place your code here
ulamki_sekund_0++;
ulamki_sekund_1++;
}


int obroc_o_1_8_stopnia(int speed, int r)
{
PORTE.5 = 0;
if(ulamki_sekund_0 >= speed)  
    {
    PORTE.5 = 1;
    ulamki_sekund_0 = 0;
    r++;
    }
return r; 
}


void drgania()
{
licznik_drgania++;
if(licznik_drgania == 6000)  //6666
    PORTD.4 = 1;
if(licznik_drgania == 12000)//26666
    {
    PORTD.4 = 0;
    licznik_drgania = 0;
    }
}




void obsluga_startowa_dozownika_kleju()
{
int ss;
ss = 0;

PORTB.1 = 1;  //zasilanie 220V na dozownik kleju
PORTB.4 = 1;  //cisnienie na dozownik kleju


while(PINA.6 == 1)
  {
  if(PINA.3 == 0)
    {
    //lcd_clear();
    //lcd_gotoxy(0,0);
    //lcd_puts("1");
    delay_ms(1000);
    if(ss == 0)
        {
        putchar(0);       //dozownik kleju nie gotowy
        ss = 1;
        }
  
    }  
  }
putchar(1);  //jest wszystko ok z dozownikiem


  //sle komunikat
  //dozownik kleju nie gotowy
  //poprawnie - jak w naczelnym 1 to na pina.3=0
  
  //lcd_clear();
  //lcd_gotoxy(0,0);
  //lcd_puts("petla");
  //delay_ms(1000);
  //}
  //else
  //{
  //brak sygnalu z master PINA.3
  //delay_ms(1000);
  //lcd_clear();
  //lcd_gotoxy(0,0);
  //lcd_puts("petla222");
  //delay_ms(1000);
    
}






void komunikacja_bez_rs232()
{

/*
if(PINA.3 == 0 & poczatek == 0)
      {
      PORTB.6 = 1;
      poczatek = 1;
      }
      
if(PINA.3 == 1 & poczatek == 1)
      {
      PORTB.6 = 0;
      wcisniete_zakonczone = 2;
      poczatek = 3;
      }
*/

if(tryb_male_puchary == 3)
    {
    if(PINF.5 == 0)
        zezwolenie_od_master = 1;
    else
        zezwolenie_od_master = 0; 

                                             //dodaje do uzwglednienia komunikacje male puchary
    if(PINA.3 == 0 & wcisniete_zakonczone == 1 & PINF.7 == 1)
       {
       PORTB.6 = 1;
       wcisniete_zakonczone = 2;
       }

                                             //dodaje do uzwglednienia komunikacje male puchary
    if(PINA.3 == 1 & wcisniete_zakonczone == 2 & PINF.7 == 1)
        PORTB.6 = 0;
    }    
else
    {
    if(PINF.5 == 0)
        zezwolenie_od_master = 1;
    else
        zezwolenie_od_master = 0;
    
    
    if(PINA.3 == 0 & wcisniete_zakonczone == 1 & PINF.7 == 1)
       {                                                     //zezwolenie na jazde tasmy
       PORTB.6 = 1;
       wcisniete_zakonczone = 2;
       }
       
       if(PINA.3 == 1 & wcisniete_zakonczone == 2 & PINF.7 == 1)
            PORTB.6 = 0;
           
    }



}





void obsluga_dozownika_kleju_i_komunikacja()
{
int znak;

znak = 0;

if(PINA.3 == 0 & znak == 0 & czekaj_komunikacja == 0)      
    {
    znak = getchar();
    
    if(PINA.6 == 1 & znak == 1)   //brak kleju
       {
       //putchar(0); 
       putchar(1);
       }
    
    if(PINA.6 == 0 & znak == 1)  //klej jest
       {
       putchar(1); 
       }
    
    /*
    
    if(wcisnalem_pedal == 1 & znak == 4)
        {
        putchar(1);
        }
    
    if(wcisnalem_pedal == 0 & znak == 4)
        {
        putchar(0);
        }
    
    */
    
    if(wcisniete_zakonczone == 1 & znak == 4)
        {
        putchar(1);
        }
    
    if(wcisniete_zakonczone == 0 & znak == 4)
        {
        putchar(0);
        }
    
    if(zacisnalem_szczeki == 1 & znak == 6)
        {
        putchar(1);
        }
    
    if(zacisnalem_szczeki == 0 & znak == 6)
        {
        putchar(0);
        }
    

    if(znak == 2)
       {
       pomocnicza = getchar();
       czas_monterow = pomocnicza * stala_czasowa;
       putchar(3);     //ze przyjalem
       }
       
    if(znak == 3)
       {
       podaj_nakretke = getchar();
       zezwolenie_na_zacisniecie_szczek_od_master = 0; 
       wcisnalem_pedal = 0;
       zacisnalem_szczeki = 0;
       wcisniete_zakonczone = 0;
       putchar(3);     //ze przyjalem
       }
    
    if(znak == 5)
       {
       zezwolenie_na_zacisniecie_szczek_od_master = getchar(); 
       putchar(3);     //ze przyjalem
       }   
    }
                                                             
if(znak == 1 | znak == 2 | znak == 3 | znak == 4 | znak == 5  | znak == 6  | czekaj_komunikacja > 0)  //tu jeszcze poprawic
    czekaj_komunikacja++;
if(czekaj_komunikacja == 1000)
    czekaj_komunikacja = 0;


}


void kontrola_czujnika_dolnego_nakretek()
{
if(PINF.4 == 0)
    {
    PORTD.5 = 1;
    //PORTB.5 = 1;  //drgania wibracyjne
    PORTD.6 = 0;  //silownik podaje nakretke monterowi
    }
else
    {
    PORTD.5 = 0;
    }
    
}



void kontrola_orientatora_nakretek_nowa_zjezdzalnia()
{
if(PINA.0 == 0)
    {
    //licznik_widzenia_nakretki++;
    //if(licznik_widzenia_nakretki > 1000)
    //    {
        PORTB.0 = 0;
    //    licznik_widzenia_nakretki = 0;
    //    }
    }
else
    {
    PORTB.0 = 1;
    //licznik_widzenia_nakretki = 0;
    }
}



void kontrola_orientatora_nakretek()
{
if(PINA.0 == 0 & nakretka < 7)  //to chyba spowoduje ze nie bedzie licznik nakretek sie zapetlal
        {
        licznik_nakretek++;
        }
if(licznik_nakretek > 700)
        {
        //if(
            PORTB.0 = 0;  //wylacz orientator bo juz na pewno jedna spadla
        nakretka++;
        //nakretka_1++;
        //lcd_clear();
        //lcd_gotoxy(0,0);
        //itoa(licznik_nakretek,dupa1);       
        //lcd_puts(dupa1);
        //lcd_gotoxy(0,1);
        //itoa(nakretka_1,dupa1);       
        //lcd_puts(dupa1);
        licznik_nakretek = 0;
        }

//wyniki pomiarow
//1 nakretka - 1643
//              1616
//              1590
//              1493

}


void jedz_wieza_cykl_nowy_procesor()
{

PORTE.0 = 1;
if(PINE.7 == 1)
    {
    if(wyzerowalem_sek5 == 0)
        {
        sek5 = 0;
        wyzerowalem_sek5 = 1;
        }
    
    if(sek5 > 5 & PINE.7 == 1)
        {
        jedz_wieza_cykl_znacznik = 0;
        PORTC.1 = 0;
        PORTE.0 = 0;
        wyzerowalem_sek5 = 0;
        }
    }
    
if(PINE.7 == 0 & wyzerowalem_sek5 == 1)
    wyzerowalem_sek5 = 0;
    
}

void jedz_wieza_cykl()
{

//pomysl - wyysylac w czasie drogi impulsy - to bedzie wielkosc kamienia
//pomysl - wyysylac w czasie postoju - to bedzie predkosc
//to nawet moge zrobic tu

//w prawo
  
    
    switch(pozycja_wiezy)
        
        {
               
        case 0:
        
                
                PORTE.7 = 1; //enable (1 uruchamia)
                sek2 = 0;
                pozycja_wiezy = 1;
                ulamki_sekund_1 = 0;   
                
                
        break;
        
        case 1:
                
                if(kkk == kkk1)
                    kkk1 = obroc_o_1_8_stopnia(v1, kkk);
                else
                    {                    //30 ok    //60 * 16 * 2 ok na szybki zegar
                    if(ulamki_sekund_1 > 60 * 8 * 2)        
                        {
                        v1--;
                        ulamki_sekund_1 = 0;
                        }    
                    kkk1 = kkk;
                    }
               
                 if(v1 == speed_normal) //6 sie pieprzy po 30 min, daje 3 ale zmieniam kroki
                    {
                    kkk = 0;
                    if(PORTE.4 == 1)   //DIR du�y silnik
                        pozycja_wiezy = 2;
                    else
                        pozycja_wiezy = 3;        
                    }
                    
                if(sek2 > 170)
                    {
                    kkk = 0;
                    kkk1 = 0;
                    bufor_bledu = 25;
                    v1 = speed_normal;
                    ulamki_sekund_1 = 0;
                    if(PORTE.4 == 1)
                        pozycja_wiezy = 2;
                    else
                        pozycja_wiezy = 3;
                    }    
                
        
        break;
        
        //ustalic wielkosc przesuniecia kamien dla bez bufor bledu i z bufor bledu
        
        case 2:
            if(PINE.0 != 0)    //czujnik indukcyjny
                obroc_o_1_8_stopnia(v1 + bufor_bledu, 0);  
            else
                {
                if(kamien == 50)
                    wielkosc_przesuniecia_kamien = 770+60;
                if(kamien == 55)
                    wielkosc_przesuniecia_kamien = 740+60;
                if(kamien == 60)
                    wielkosc_przesuniecia_kamien = 710+60;
                if(kamien == 65)
                    wielkosc_przesuniecia_kamien = 680+60;
                if(kamien == 70)                                              
                    wielkosc_przesuniecia_kamien = 650+60;
                if(kamien == 75)
                    wielkosc_przesuniecia_kamien = 620+60;
                
                pozycja_wiezy = 4;
                }
            
            if(sek2 > 170 & bufor_bledu == 0)
                    {
                    pozycja_wiezy = 2;
                    bufor_bledu = 25;
                    }    
                
        break;
        
        case 3:
            
            if(PINE.1 != 0)
                obroc_o_1_8_stopnia(v1+ bufor_bledu, 0);
            else
                {
                if(kamien == 50)
                    wielkosc_przesuniecia_kamien = 770+60; 
                if(kamien == 55)//przesuwamy o 2,5mm
                    wielkosc_przesuniecia_kamien = 740+60;
                if(kamien == 60)
                    wielkosc_przesuniecia_kamien = 710+60;
                if(kamien == 65)
                    wielkosc_przesuniecia_kamien = 680+60;
                if(kamien == 70)
                    wielkosc_przesuniecia_kamien = 650+60;
                if(kamien == 75)
                    wielkosc_przesuniecia_kamien = 620+60; //tu ma byc 8mm + 25/2mm = 20,5    18mm
                
                pozycja_wiezy = 4;
                }
            
            if(sek2 > 170 & bufor_bledu == 0)
                    {
                    pozycja_wiezy = 3;
                    bufor_bledu = 25;
                    }    
        break;
       
        
        case 4: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1+ bufor_bledu, kkk);  //jedziemy jeszcze kawalek z pelna pyta
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 5;
                    }
    
        break;
        
    
        case 5: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 6;
                    }
    
        break;
        
        case 6: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 7;
                    }
    
        break;
        
        case 7: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 8;
                    }
    
        break;
        
        
          
        case 8:          
                if(kkk < wielkosc_przesuniecia_kamien)                          
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  
                else
                    {
                    pozycja_wiezy = 10;//9
                    ulamki_sekund_1 = 0;
                    v1 = v1 + 6;
                    kkk = 0;
                    kkk1 = 0;
                    }
                        
        break;
        
        case 9:
                
                
                  if(kkk == kkk1)
                        kkk1 = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);
                  else
                        {  
                        if(ulamki_sekund_1 > 60 * 6 * 2) 
                            {
                            v1++;
                            ulamki_sekund_1 = 0;
                            }    
                        kkk1 = kkk;
                        }
                  if(v1 == 40)
                        {
                        kkk = 0;
                        pozycja_wiezy = 10;
                        }            
            
        break;
        
        case 10:
                    
                PORTE.7 = 0;  //koniec enable
                PORTC.1 = 0;  //silownik dociskowy os pozioma
                kkk = 0;
                kkk1 = 0;
                v1 = 60;
                bufor_bledu = 0;  
                if(PORTE.4 == 1)
                    PORTE.4 = 0;  //zmieniamy dir
                else
                    PORTE.4 = 1;   
                
                pozycja_wiezy = 11;
                jedz_wieza_cykl_znacznik = 0;    
                
                
        break;
        }
    
        
    
    
    
    
    
}







int proces_0()
{
int wynik;
wynik = 0;

switch(proces[0])
    {
    case 0:
        if(test_zjezdzalni_nakretek == 0)
            proces[0] = 1;
        else
            proces[0] = 111;
        sek0 = 0;    
    break;
    
      
    case 111:                        
            if(PINA.7 == 1)
                {
                ilosc_prob_wybicia_zakretki_do_gory = 0;
                PORTD.5 = 1;  //silownik kolejkujacy nakretki otworz
                PORTB.3 = 1;  //psikanie
                PORTB.5 = 1;  //wibrator nowy
                PORTD.4 = 1;  //zeby na pewno byl wysuniety wstepnie ten co robi drgania
                sek0 = 0;       
                proces[0] = 2;
                }    
    break;
    
    case 1:                          //zeby wrocila karetka nakretek sek0 > 40
            
            //if(podaj_nakretke == 1)
            //    PORTB.5 = 1;  //wibrator nowy        
    
            if(podaj_nakretke == 1 & sek0 > 40)
                {
                ilosc_prob_wybicia_zakretki_do_gory = 0;
                PORTD.5 = 1;  //silownik kolejkujacy nakretki otworz
                PORTB.5 = 1;  //wibrator nowy
                PORTB.3 = 1;  //psikanie
                PORTD.4 = 1;  //zeby na pewno byl wysuniety wstepnie ten co robi drgania
                sek0 = 0;       
                proces[0] = 2;
                }    
    break;
    
    
    case 2:
                if(sek0>15)
                    {
                    sek0 = 0;       
                    proces[0] = 3;
                    }
    break;
    
    case 3:  
            drgania();
            
            if(sek0 > 5 & PORTB.3 == 1)
                 PORTB.3 = 0; //psikanie
            
            if(sek0 > 20)  //silownik kolejkujacy nakretki w dol  //35
                {
                PORTB.5 = 0;  //wibrator nowy
                PORTD.5 = 0;  //zamknij
                sek0 = 0;
                proces[0] = 4;
                }
    break;

    
    case 4:
            
            if(PINA.4 == 0)
                wystarczy_zejscia = 1;
            drgania(); 
            if(sek0 > 25)   
                {
                sek0 = 0;
                proces[0] = 5;
                if(PINA.4 == 0)
                    wystarczy_zejscia = 1;
                }
    
    break; 


    case 5:
            if(PINA.4 == 0 | wystarczy_zejscia == 1)   //zszedl na sam dol, czyli ok
                {
                //proces[0] = 8;
                //PORTD.2 = 0; //przysun igle z klejem nie dawaj igly z klejem
                PORTD.4 = 0;  //zeby na pewno byl schowany ten co robi drgania
                wystarczy_zejscia = 0;
                proces[0] = 10;
                sek0 = 50;
                }
            else
                {
                wystarczy_zejscia = 0;      
                ilosc_prob_wybicia_zakretki_do_gory++;
                if(ilosc_prob_wybicia_zakretki_do_gory > 3)
                    {
                    proces[0] = 10;
                    ilosc_prob_wybicia_zakretki_do_gory = 0;
                    PORTD.4 = 0;  //zeby na pewno byl schowany ten co robi drgania
                    }
                else
                    {
                    PORTD.5 = 1;  //do gory silownik otworz
                    PORTB.3 = 1;   //psikanie
                    PORTB.5 = 1;  //wibrator nowy
                    proces[0] = 6;
                    }
                sek0 = 0;
                }

    break;

    case 6:
            drgania();
            
            if(sek0 > 130 & PORTB.3 == 1)
                 {
                 PORTB.3 = 0; //psikanie
                 PORTB.5 = 0;  //wibrator nowy
                 }
            if(sek0 > 150)  //czekaj na pukniecie
               {
               PORTD.5 = 0;  //na dol
               sek0 = 0;
               proces[0] = 7;
               } 
    break;

    case 7:
            drgania();
            if(PINA.4 == 0)
                wystarczy_zejscia = 1;
            if(sek0 > 80)  
               {
               proces[0] = 5;
               } 
    break;
    
    case 8:
            if(sek0 > 20)
                {
                //PORTB.7 = 1; //nie lej kleju na razie
                sek0 = 0;
                proces[0] = 9;
                }
    
    break; 
    
    case 9:
            if(sek0 > 50)
                {
                PORTB.7 = 0;//przestan lac klej
                PORTD.2 = 1; //cofnij igle z klejem
                sek0 = 0;
                proces[0] = 10;
                }
    
    break; 
    
    
    
    case 10:
            if(sek0 > 50)
                {
                PORTD.6 = 1; //silownik podaje nakretke monterowi
                sek0 = 0;
                 if(test_zjezdzalni_nakretek == 0)
                    proces[0] = 11;
                 else
                    proces[0] = 1111;
                sek0 = 0;    
                }          
                  
    break;
    case 11:
            if(sek0 > 50)
                {                       
                kontrola_czujnika_dolnego_nakretek();
                
                if(wcisnalem_pedal == 1)  
                   {
                   PORTD.6 = 0;  //cofnij podajnik nakretek 
                   //PORTB.5 = 1;  //wibrator
                   sek0 = 0;
                   proces[0] = 12;
                   }
                else
                   sek0 = 51;
                    
                } 
    break;
    case 1111:
            if(sek0 > 50)
                {                       
                if(PINA.7 == 1)  
                   {
                   PORTD.5 = 0;   //zamknij przegrode nakretek
                   PORTD.6 = 0;  //cofnij podajnik nakretek 
                   //PORTB.5 = 1;  //wibrator
                   sek0 = 0;
                   }           
                }
            kontrola_czujnika_dolnego_nakretek();
            if(PORTD.6 == 0 & sek0 > 50 & PORTD.5 == 0)
                    {
                    proces[0] = 12;
                    }
                 
    break;
    
    
    
    
    
    
    
    case 12:
            if(sek0 > 1)    
               proces[0] = 13; 
    break;
    
    case 13:
            
                sek0 = 0;
                proces[0] = 0;
                wynik = 1;
                podaj_nakretke = 0;
                wcisnalem_pedal = 0;   
                                    
    break;
    }




return wynik;
}


int proces_1()
{
int wynik;
wynik = 0;

switch(proces[1])
    {
    case 0:
        if(podaj_nakretke == 1)
            proces[1] = 1;
    break;
    
    case 1:             
            if(PINA.2 == 0 & wcisniete_zakonczone == 2) //widzi kamien
            {
            sek1 = 0;       
            proces[1] = 2;    
            }
    break;
    
    case 2:             
            if(PINA.2 == 1 & zezwolenie_od_master == 1) //przejechal kamien na pewno
            {
            sek1 = 0;       
            proces[1] = 3;
               
            }
    break;
    
    case 3:
           
           sek1 = 0;
           proces[1] = 4;
           
    break;
    
    case 4: 
            if(sek1 > 0) ////////////////////////dam tu wiecej 20, 28.11.2017
                {
                PORTD.7 = 1;
                sek1 = 0;       
                proces[1] = 5;
                }            
    
    break;
    
    case 5:  
            if(sek1 > 100)  
                {
                if(PINA.7 == 1 & proces[0] == 11) //monter nacisnal pedal
                    {                
                    PORTD.3 = 1;  //zluzuj chwyt grzybka
                    PORTD.7 = 0; //pusc kamien
                    wcisnalem_pedal = 1;   
                    sek1 = 0;
                    proces[1] = 6;
                    }
                else
                    sek1 = 101;
                } 
                        
    break;
  

//teraz jest dane ze natychmiast ruszy, moge dac alternatywe ze po chwili zmieniajac case 5 i case 6


    case 6:  
            if(sek1 > 1)      //50 31.07.2017
                { 
                sek1 = 0;
                proces[1] = 7;
                }    
                            
    break;
    
    
    
    case 7:
            if(sek1 > 30) //20 31.07.2017
               {
               PORTD.3 = 0;  //zacisnij z powrotem szczeki
               proces[1] = 8;
               } 
    break;
    
    case 8:
            
                sek1 = 0;
                proces[1] = 0;
                wynik = 1;
               
                                    
    break;
    }




return wynik;
}



int proces_3()
{
int wynik;
wynik = 0;

switch(proces[3])
    {                 //ZMIENIAM PINE.2 NA PINE.6
    case 0: //pedal monter 2   //
        if(PINE.6 == 1 & zezwolenie_od_master == 1)
            {
            PORTC.5 = 1;     //wysun silownik otwierajacy wieze
            PORTC.6 = 0;     //wysun silownik otwierajacy wieze
            if(wieza == 0)
                PORTC.2 = 0;  //stan otwart wejsciowy wie�a 1
            else
                {
                PORTC.3 = 1;  //stan otwarcia wejsciowy wie�a 2 
                PORTC.7 = 0;  //stan otwarcia wejsciowy wie�a 2
                }
            sek3 = 0;       
            proces[3] = 1;
            }    
    break;
    
    case 1:
    
            if(sek3 > 20)
                {
                wcisniete_zakonczone = 1;
                PORTC.5 = 0;  //schowaj silownik otwierajacy wieze
                PORTC.6 = 1;
                sek3 = 0;       
                proces[3] = 2;
                }
    
    break;
    
    case 2:
            if(PINE.6 == 0)//ZMIENIAM PINE.2 NA PINE.6
            {
            if(wieza == 0)
                {
                PORTC.2 = 1;  //stan zamkniecia wieza 1
                //wieza = 1;
                }
            else
                {
                PORTC.3 = 0;  //stan zamkniecia wejsciowy wie�a 2 
                PORTC.7 = 1;  //stan zamkniecia wejsciowy wie�a 2
                //wieza = 0;
                }
            sek3 = 0;       
            proces[3] = 3;
            }
    break;
    
    case 3:
            if(sek3 > 2)
            {
            sek3 = 0;       
            proces[3] = 4;
            }
    break;
    
    case 4:
            if(PINE.6 == 1)  //ZMIENIAM PIN.2 NA E.6
            {
            sek3 = 0;       
            proces[3] = 5;
            }
    break;
    
    
    case 5:
               //pozycja_wiezy != 11
            if(male_puchary_pozwolenie_wyjecia_puchara_monter_3 == 0)
            {
            
                //jedz_wieza_cykl();
                if(wieza == 0)
                    wieza = 1;
                else
                    wieza = 0;
                jedz_wieza_cykl_znacznik = 1;   
                male_puchary_pozwolenie_wyjecia_puchara_monter_3 = 1;
                proces[3] = 6;
            }
            //else 
            //{
            //sek3 = 0;       
            //proces[3] = 0;
            //pozycja_wiezy = 0;
            //male_puchary_pozwolenie_wyjecia_puchara_monter_3 = 1;
            //wynik = 1;
            //}
    break;
            
    case 6:
             
             if(PINE.6 == 0)  //zmieniam PINE.2 na PINE.6
             {
             skonczony_proces[3] = 0;
             sek3 = 0;       
             proces[3] = 0;
             pozycja_wiezy = 0;
             wynik = 0;
             }
    break;
    
    
    
    
    
    
}




return wynik;
}


int proces_4()
{
int wynik;
wynik = 0;

switch(proces[4])
    {
    
   case 0:     //monter 3 nacisnal pedal
            if(PINA.7 == 1 & male_puchary_pozwolenie_wyjecia_puchara_monter_3 == 1)
            {
             if(PORTC.0 == 0) //silownik obrotowy o osi pionowej //monter wyciaga puchar
                PORTC.0 = 1;
             else
                PORTC.0 = 0;
            PORTC.1 = 1;  //silownik dociskowy os pozioma
            
            if(wieza == 1)
                PORTC.2 = 0;  //stan otwart wejsciowy wie�a 1
            else
                {
                PORTC.3 = 1;  //stan otwarcia wejsciowy wie�a 2 
                PORTC.7 = 0;  //stan otwarcia wejsciowy wie�a 2
                }
            
            sek4 = 0;
            proces[4] = 1;
            }
            
    break; 
    
    case 1:
          if(sek4 > 60)
            {
            male_puchary_pozwolenie_wyjecia_puchara_monter_3 = 0;
            wcisnalem_pedal = 1;      
            proces[4] = 0;
            wynik = 1;
            }
    break;
    
        
    }




return wynik;
}







void procesy()
{
if(skonczony_proces[0] == 0)
  skonczony_proces[0] = proces_0();          

if(skonczony_proces[1] == 0 & tryb_male_puchary == 3)
  skonczony_proces[1] = proces_1();  
  
if(skonczony_proces[3] == 0 & tryb_male_puchary == 2 & jedz_wieza_cykl_znacznik == 0)
  skonczony_proces[3] = proces_3();  
  
if(skonczony_proces[4] == 0 & tryb_male_puchary == 2)
  skonczony_proces[4] = proces_4();              

}

void zerowanie_procesow()
{                                                       
if(skonczony_proces[0] == 1 & skonczony_proces[1] == 1 & test_zjezdzalni_nakretek == 0 & tryb_male_puchary == 3)
    {
    skonczony_proces[0] = 0;
    skonczony_proces[1] = 0;
    wcisniete_zakonczone = 1;
    podaj_nakretke = 1;
    } 


if(skonczony_proces[0] == 1 & test_zjezdzalni_nakretek == 1)
    {
    skonczony_proces[0] = 0;
    skonczony_proces[1] = 0;
    wcisniete_zakonczone = 1;
    podaj_nakretke = 1;
    } 
    

                            //& skonczony_proces[3] == 1
if(skonczony_proces[0] == 1  & skonczony_proces[4] == 1 & test_zjezdzalni_nakretek == 0 & tryb_male_puchary == 2)
    {
    skonczony_proces[0] = 0;                  //tryb male puchary
    //skonczony_proces[3] = 0;
    skonczony_proces[4] = 0;
    podaj_nakretke = 1;
    } 





}


void wypozucjonuj_wieze_wolno()
{

PORTE.7 = 1;  //enable na silnik krok

//+_+__________o ___________   
//+_+__________ o _________  //dolny - do tego pozycjonujemy
//
PORTE.4 = 0;
while(PINE.1 != 0)//kiedy nie widzi czujnik czujnik - jestesmy daleko  
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);                     
    }

//zwolnij
PORTE.5 = 1;
delay_us(2000);
PORTE.5 = 0;
delay_us(2000);

PORTE.5 = 1;
delay_us(4000);
PORTE.5 = 0;
delay_us(4000);


    
//teraz sie cofniemy
PORTE.4 = 1;  //zmieniamy dir
while(basia1 < 1000)  //musimy przejechac tak, ze na pewno miniemy czujnuk gdybysmy byli miedzy nimi, zmieniam mikrokroki wiec daje mniej, by�o 2000
    {                                                         //2000 //1000  //500
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    basia1++;
    }

//zwolnij
PORTE.5 = 1;
delay_us(4000);
PORTE.5 = 0;
delay_us(4000);

PORTE.5 = 1;
delay_us(4000);
PORTE.5 = 0;
delay_us(4000);


PORTE.4 = 0;  //zmieniamy dir
basia1 = 0;
while(PINE.1 != 0)//i znowu do czujnika  
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    }
while(basia1 < 10)  //kawaleczk zeby nie byc na granicy czujnuika
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    basia1++;
    }
while(PINE.1 != 1)//i znowu teraz jak czujnik swieci  
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    }
basia1 = 0;
while(basia1 < 10)  //kawaleczk zeby nie byc na granicy czujnuika
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    basia1++;
    }
while(PINE.1 != 0)//i znowu do czujnika  
    {
    PORTE.5 = 1;
    delay_us(1000);
    PORTE.5 = 0;
    delay_us(1000);
    }

//zwolnij
PORTE.5 = 1;
delay_us(2000);
PORTE.5 = 0;
delay_us(2000);

PORTE.5 = 1;
delay_us(4000);
PORTE.5 = 0;
delay_us(4000);




PORTE.4 = 1;  //zmieniamy dir
delay_ms(3000);
PORTE.7 = 0;
}


void wypozucjonuj_wieze_szybko()
{
PORTE.7 = 1;  //enable na silnik krok

//+_+__________o ___________   
//+_+__________ o _________  //dolny - do tego pozycjonujemy
//
PORTE.4 = 0;
while(PINE.1 != 0)//kiedy nie widzi czujnik czujnik - jestesmy daleko  
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);                     
    }

//zwolnij
PORTE.5 = 1;
delay_us(500);
PORTE.5 = 0;
delay_us(500);

PORTE.5 = 1;
delay_us(1000);
PORTE.5 = 0;
delay_us(1000);


    
//teraz sie cofniemy
PORTE.4 = 1;  //zmieniamy dir
while(basia1 < 250)  //musimy przejechac tak, ze na pewno miniemy czujnuk gdybysmy byli miedzy nimi, zmieniam mikrokroki wiec daje mniej, by�o 2000
    {                                                         //2000 //1000  //500
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    basia1++;
    }

//zwolnij
PORTE.5 = 1;
delay_us(500);
PORTE.5 = 0;
delay_us(500);

PORTE.5 = 1;
delay_us(1000);
PORTE.5 = 0;
delay_us(1000);


PORTE.4 = 0;  //zmieniamy dir
basia1 = 0;
while(PINE.1 != 0)//i znowu do czujnika  
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    }
while(basia1 < 10)  //kawaleczk zeby nie byc na granicy czujnuika
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    basia1++;
    }
while(PINE.1 != 1)//i znowu teraz jak czujnik swieci  
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    }
basia1 = 0;
while(basia1 < 10)  //kawaleczk zeby nie byc na granicy czujnuika
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    basia1++;
    }
while(PINE.1 != 0)//i znowu do czujnika  
    {
    PORTE.5 = 1;
    delay_us(500);
    PORTE.5 = 0;
    delay_us(500);
    }

//zwolnij
PORTE.5 = 1;
delay_us(500);
PORTE.5 = 0;
delay_us(500);

PORTE.5 = 1;
delay_us(1000);
PORTE.5 = 0;
delay_us(1000);




PORTE.4 = 1;  //zmieniamy dir
delay_ms(3000);
PORTE.7 = 0;
}




void jedz_wieza()
{

//pomysl - wyysylac w czasie drogi impulsy - to bedzie wielkosc kamienia
//pomysl - wyysylac w czasie postoju - to bedzie predkosc
//to nawet moge zrobic tu

//w prawo
  
    
    switch(pozycja_wiezy)
        
        {
               
        case 0:
        
                
                PORTE.7 = 1;
                sek2 = 0;
                pozycja_wiezy = 1;
                ulamki_sekund_1 = 0;   
                
                
        break;
        
        case 1:
                
                if(kkk == kkk1)
                    kkk1 = obroc_o_1_8_stopnia(v1, kkk);
                else
                    {                    //30 ok    //60 * 16 * 2 ok na szybki zegar
                    if(ulamki_sekund_1 > 60 * 8 * 2)        
                        {
                        v1--;
                        ulamki_sekund_1 = 0;
                        }    
                    kkk1 = kkk;
                    }
               
                 if(v1 == speed_normal) //6 sie pieprzy po 30 min, daje 3 ale zmieniam kroki
                    {
                    kkk = 0;
                    if(PORTE.4 == 1)
                        pozycja_wiezy = 2;
                    else
                        pozycja_wiezy = 3;        
                    }
                    
                if(sek2 > 170)
                    {
                    kkk = 0;
                    kkk1 = 0;
                    bufor_bledu = 25;
                    v1 = speed_normal;
                    ulamki_sekund_1 = 0;
                    if(PORTE.4 == 1)
                        pozycja_wiezy = 2;
                    else
                        pozycja_wiezy = 3;
                    }    
                
        
        break;
        
        //ustalic wielkosc przesuniecia kamien dla bez bufor bledu i z bufor bledu
        
        case 2:
            if(PINE.0 != 0)
                obroc_o_1_8_stopnia(v1 + bufor_bledu, 0);  
            else
                {
                kamien = 50;
                if(kamien == 50)
                    wielkosc_przesuniecia_kamien = 770+60;
                if(kamien == 55)
                    wielkosc_przesuniecia_kamien = 740;
                if(kamien == 60)
                    wielkosc_przesuniecia_kamien = 710;
                if(kamien == 65)
                    wielkosc_przesuniecia_kamien = 680;
                if(kamien == 70)                                              
                    wielkosc_przesuniecia_kamien = 650;
                if(kamien == 75)
                    wielkosc_przesuniecia_kamien = 620;
                
                pozycja_wiezy = 4;
                }
            
            if(sek2 > 170 & bufor_bledu == 0)
                    {
                    pozycja_wiezy = 2;
                    bufor_bledu = 25;
                    }    
                
        break;
        
        case 3:
            
            if(PINE.1 != 0)
                obroc_o_1_8_stopnia(v1+ bufor_bledu, 0);
            else
                {
                kamien = 50;
                if(kamien == 50)
                    wielkosc_przesuniecia_kamien = 770 + 60; //tu ma byc 8mm zgodnie z rys mariusz    //650 - 21mm    //700 - 15mm      //760 //9mm
                if(kamien == 55)//przesuwamy o 2,5mm
                    wielkosc_przesuniecia_kamien = 740;
                if(kamien == 60)
                    wielkosc_przesuniecia_kamien = 710;
                if(kamien == 65)
                    wielkosc_przesuniecia_kamien = 680;
                if(kamien == 70)
                    wielkosc_przesuniecia_kamien = 650;
                if(kamien == 75)
                    wielkosc_przesuniecia_kamien = 620; //tu ma byc 8mm + 25/2mm = 20,5    18mm
                
                pozycja_wiezy = 4;
                }
            
            if(sek2 > 170 & bufor_bledu == 0)
                    {
                    pozycja_wiezy = 3;
                    bufor_bledu = 25;
                    }    
        break;
       
        
        case 4: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1+ bufor_bledu, kkk);  //jedziemy jeszcze kawalek z pelna pyta
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 5;
                    }
    
        break;
        
    
        case 5: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 6;
                    }
    
        break;
        
        case 6: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 7;
                    }
    
        break;
        
        case 7: 
                if(kkk < 2)                           
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  //zwalniamy do stalej predkosci
                else
                    {
                    kkk = 0;
                    pozycja_wiezy = 8;
                    }
    
        break;
        
        
          
        case 8:          
                if(kkk < wielkosc_przesuniecia_kamien)                          
                    kkk = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);  
                else
                    {
                    pozycja_wiezy = 10;//9
                    ulamki_sekund_1 = 0;
                    v1 = v1 + 6;
                    kkk = 0;
                    kkk1 = 0;
                    }
                        
        break;
        
        case 9:
                
                
                  if(kkk == kkk1)
                        kkk1 = obroc_o_1_8_stopnia(v1 + bufor_bledu, kkk);
                  else
                        {  
                        if(ulamki_sekund_1 > 60 * 6 * 2) 
                            {
                            v1++;
                            ulamki_sekund_1 = 0;
                            }    
                        kkk1 = kkk;
                        }
                  if(v1 == 40)
                        {
                        kkk = 0;
                        pozycja_wiezy = 10;
                        }            
            
        break;
        
        case 10:
                    
                PORTE.7 = 0;  //koniec enable
                PORTC.1 = 0;  //silownik dociskowy os pozioma
                kkk = 0;
                kkk1 = 0;
                v1 = 60;
                bufor_bledu = 0;  
                if(PORTE.4 == 1)
                    PORTE.4 = 0;  //zmieniamy dir
                else
                    PORTE.4 = 1;
                pozycja_wiezy = 0;   
                delay_ms(2000);
                if(PORTC.0 == 0) //silownik obrotowy o osi pionowej
                    PORTC.0 = 1;
                else
                    PORTC.0 = 0;
                PORTC.1 = 1;  //silownik dociskowy os pozioma    
                delay_ms(2000);
                
                
                
        break;
        }
    
        
    
    
    
    
    
}




void komunikacja_male_puchary()
{

//kod u slava


if(PINF.7 == 0)
    {
    if(PINF.6 == 0 & zliczylem_male_puchary == 0)
        {
        PORTB.6 = 1;
        przeslano_informacje_male_puchary = 1;
        licznik_impulsow_male_puchary++;
        zliczylem_male_puchary = 1;
        }



        if(PINF.6 == 1 & zliczylem_male_puchary == 1)
        {
        PORTB.6 = 0;
        zliczylem_male_puchary = 0;
        }

    }
               //& pozycja_wiezy == 0
if(PINF.7 == 1 & przeslano_informacje_male_puchary == 1)
    {
    
    switch(licznik_impulsow_male_puchary)
        {
        case 0:
              tryb_male_puchary = 0;  //ze nie dokonano zadnego wyboru
              przeslano_informacje_male_puchary = 0;
        break;
        
        case 3:
              tryb_male_puchary = 3;   //ze nie bedzie malych malych pucharow
              licznik_impulsow_male_puchary = 0;
              przeslano_informacje_male_puchary = 0;
              podaj_nakretke = 1;
              PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 0;
           
              
        break;
        
        case 11:
             tryb_male_puchary = 2;
             kamien = 50;
             PORTE.0 = 0;
              PORTE.1 = 1;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 0;
              
             
             //speed_normal = 10;
             speed_normal = 8;  
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 12:
             tryb_male_puchary = 2;
             kamien = 55;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 1;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 0;
             
             //speed_normal = 10;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 13:
             tryb_male_puchary = 2;
             kamien = 60;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 1;
              PORTE.4 = 0;
              PORTE.5 = 0;
             
             //speed_normal = 10;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 14:
             tryb_male_puchary = 2;
             kamien = 65;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 1;
              PORTE.5 = 0;
             
             //speed_normal = 10;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 15:
             tryb_male_puchary = 2;
             kamien = 70;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 1;
             
             //speed_normal = 10;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;
                  
        break;
        
        case 16:
             tryb_male_puchary = 2;
             kamien = 75;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 1;
              PORTE.5 = 1;
          
             //speed_normal = 10;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 17:
             tryb_male_puchary = 2;
             kamien = 50;
             PORTE.0 = 0;
              PORTE.1 = 1;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 0;
             
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 18:
             tryb_male_puchary = 2;
             kamien = 55;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 1;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 0;
             
             speed_normal = 8; 
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;    
        break;
        
        case 19:
             tryb_male_puchary = 2;
             kamien = 60;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 1;
              PORTE.4 = 0;
              PORTE.5 = 0;
              
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 20:
             tryb_male_puchary = 2;
             kamien = 65;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 1;
              PORTE.5 = 0;
             
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 21:
             tryb_male_puchary = 2;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 0;
              PORTE.5 = 1;
             kamien = 70;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        case 22:
             tryb_male_puchary = 2;
             kamien = 75;
             PORTE.0 = 0;
              PORTE.1 = 0;
              PORTE.2 = 0;
              PORTE.3 = 0;
              PORTE.4 = 1;
              PORTE.5 = 1;
             speed_normal = 8;
             licznik_impulsow_male_puchary = 0;
             przeslano_informacje_male_puchary = 0;     
        break;
        
        
        
        
        }
    }

/*
if(PINC.7 == 0)
    PORTB.7 = 1;
else
    PORTB.7 = 0;
    
if(PINC.6 == 0)
    PORTB.6 = 1;
else
    PORTB.6 = 0;
    
if(PINC.5 == 0)
    PORTB.5 = 1;
else
    PORTB.5 = 0;
    
if(PINC.4 == 0)
    PORTB.4 = 1;
else
    PORTB.4 = 0;
    
if(PINC.3 == 0)
    PORTB.3 = 1;
else
    PORTB.3 = 0;
    
if(PINC.2 == 0)
    PORTB.2 = 1;
else
    PORTB.2 = 0;
    
if(PINC.1 == 0)
    PORTB.1 = 1;
else
    PORTB.1 = 0;
    
if(PINC.0 == 0)
    PORTB.0 = 1;
else
    PORTB.0 = 0;
*/



}


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0x00;
DDRD=0xFF;

// Port E initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=0 State5=0 State4=0 State3=T State2=T State1=T State0=T      //stary przy starych malych pucharach
//PORTE=0x00;
//DDRE=0xF0;

// Port E initialization
// Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=T State6=T State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTE=0x00;
DDRE=0x3F;

// Port F initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTF=0x00;
DDRF=0x00;

// Port G initialization
// Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State4=0 State3=0 State2=0 State1=0 State0=0 
PORTG=0x00;
DDRG=0x1F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 15,625 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
ASSR=0x00;
TCCR0=0x07;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// OC1C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
//TCCR2=0x00;
//TCNT2=0x00;
//OCR2=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 250,000 kHz
// Mode: Normal top=0xFF
// OC2 output: Disconnected
//TCCR2=0x03;
//TCNT2=0x00;
//OCR2=0x00;


// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 2000,000 kHz
// Mode: Normal top=0xFF
// OC2 output: Disconnected
//TCCR2=0x02;
//TCNT2=0x00;
//OCR2=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 16000,000 kHz
// Mode: Normal top=0xFF
// OC2 output: Disconnected
TCCR2=0x01;
TCNT2=0x00;
OCR2=0x00;



// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: Timer3 Stopped
// Mode: Normal top=0xFFFF
// OC3A output: Discon.
// OC3B output: Discon.
// OC3C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=0x00;
TCCR3B=0x00;
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;
OCR3CH=0x00;
OCR3CL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// INT3: Off
// INT4: Off
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=0x00;
EICRB=0x00;
EIMSK=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
//TIMSK=0x01;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x41;




ETIMSK=0x00;


/*
// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: On
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 2400
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x01;
UBRR0L=0xA0;
*/


/*
// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: On
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 9600
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x00;
UBRR0L=0x67;

*/
// USART0 initialization
// USART0 disabled
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);


// USART1 initialization
// USART1 disabled
UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);

// USART1 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART1 Receiver: On
// USART1 Transmitter: On
// USART1 Mode: Asynchronous
// USART1 Baud Rate: 9600
//UCSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<<DOR1) | (0<<UPE1) | (0<<U2X1) | (0<<MPCM1);
//UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (1<<RXEN1) | (1<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
//UCSR1C=(0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
//UBRR1H=0x00;
//UBRR1L=0x67;


// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;


// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTG Bit 4
// RD - PORTD Bit 6
// EN - PORTD Bit 7
// D4 - PORTG Bit 0
// D5 - PORTG Bit 1
// D6 - PORTG Bit 2
// D7 - PORTG Bit 3
// Characters/line: 16
//lcd_init(16);
//BEZ WYSWIETLACZ

//WE
//PINA.0    czujnik widzenia nakr�tki
//PINA.1    uszkodzonie na karcie - Pan Bogdan zwar�
//PINA.2    czujnik widzenia kamienia
//PINA.3    sygnal odpytania od procesora glownego    
//PINA.4    czujnik do silownika kolejkujacego nakretki - lampka nie chodzi   
//PINA.5    czujnik czy jest klej 
//PINA.6    czujnik czy jest gotowy do pracy dozownik kleju
//PINA.7    pedal montera 3 - informacja ze zwolnil zacisk grzybka i jednoczesnie ze nakretka pobrana

//PINF.0    uszkodzone
//PINF.1    uszkodzona karta
//PINF.2    
//PINF.3    
//PINF.4    czujnik dolny nakretek ten cienki magnetyczny
//PINF.5    ze MAster dal zgode na zacisniecie szczek
//PINF.6    do komunikacji z male puchary - NOWY KABEL
//PINF.7    do komunikacji z male puchary sygnal przecinka - NOWY KABEL

//PINE.0    czujnik 1 indukcyjnych pozycjonujacey wieze
//PINE.1    czujnik 1 indukcyjnych pozycjonujacey wieze
//PINE.2    peda� 2    //zmieniam na pine.6
//PINE.3    czujnik na silowniku otwierania wiezyczki tym nowym

//WNIOSKI:
//C ZMIENIC NA F
//DO C PODPIAC NOWA WYSPE
//DO E PODPISAC KARTE 4 + SILNIK KROK


//WY
//PORTB.0   orientator nakretek
//PORTB.1   za��czenie 220V na dozownik kleju  
//PORTB.2      
//PORTB.3   psikanie
//PORTB.4   cisnienia na dozownik kleju
//PORTB.5   wibrator nowy
//PORTB.6   SYGAN POTWIERDZENIA DO MASTER
//PORTB.7   podawanie kleju

//PORTD.0 
//PORTD.1  
//PORTD.2   silownik podawania kleju
//PORTD.3   silownik otwierania lancy
//PORTD.4   silownik wykonujacy drgania
//PORTD.5   silownik kolejkujacy nakr�tki na zjezdzalni  
//PORTD.6   tacka pobierajaca nakretki
//PORTD.7   chwytanie kamienia   
            

//PORTC.0   // silownik obrotowy os pionowa
//PORTC.1  //silownik obrotowy os pozioma w gore czyli nie ma kolizji
//PORTC.2  //zamykanie wiezyczki 1   
//PORTC.3  //zamykanie wiezyczki 2
//PORTC.4  
//PORTC.5
//PORTC.6
//PORTC.7  //zamykanie wiezyczki 2

//WPROWADZAM MODYFIKACJE POD MALE PUCHARY
//PORTE.4 - DIR du�y silnik
//PORTE.5 - CLK
//PORTE.7 - enable (1 uruchamia)

//PROCESY
//proces_0 - podawanie nakretki monterowi
//proces_1 - chwytanie kamienia


//////////////////////////////////////////
////obsluga_startowa_dozownika_kleju();    //wywalam bo modul male puchary
//////////////////////////////////////////

/*
delay_ms(2000);
delay_ms(2000);

PORTC.2 = 0;  //stan otwart wejsciowy wie�a 1
PORTC.3 = 1;  //stan otwarcia wejsciowy wie�a 2 
PORTC.7 = 0;  //stan otwarcia wejsciowy wie�a 2
//(aby zamknac: PORTC.3 = 0; PORTC.7 = 1;)

PORTC.5 = 0;  //schowaj silownik otwierajacy wieze - ustawienie wstepne
PORTC.6 = 1;
delay_ms(2000);
delay_ms(2000);


PORTC.5 = 1;     //wysun silownik
PORTC.6 = 0;

delay_ms(2000);
delay_ms(2000);
PORTC.5 = 0;  //schowaj silownik
PORTC.6 = 1;


delay_ms(2000);
delay_ms(2000);
*/


PORTC.5 = 0;  //schowaj silownik otwierajacy wieze
PORTC.6 = 1;

PORTC.3 = 1;  //stan otwarcia wejsciowy wie�a 2 
PORTC.7 = 0;  //stan otwarcia wejsciowy wie�a 2


pomocnicza = 7;
stala_czasowa = 62;
czas_monterow = pomocnicza * stala_czasowa;
start = 0;
PORTD.2 = 1;  //igla wysunieta z klejem czyli wysuniety silownik
nakretka = 1; //silownik z dysza kleju do gory
licznik_nakretek = 0;

czekaj_komunikacja = 0;
podaj_nakretke = 0;
wcisnalem_pedal = 0;
zezwolenie_na_zacisniecie_szczek_od_master = 0;
zacisnalem_szczeki = 0;
ff = 0;
jest_nakretka_przy_dolnym = 0;
wlaczam_dodatkowe_wibracje_i_psikanie = 0;
licznik_drgania = 0;
wystarczy_zejscia = 0;
licznik_widzenia_nakretki = 0;
wcisniete_zakonczone = 0;
wielkosc_przesuniecia_kamien = 0;
kamien = 0;
test_zjezdzalni_nakretek = 0;  //TEST ZJEZDZALNI NAKRETEK
male_puchary_pozwolenie_wyjecia_puchara_monter_3 = 0;

podaj_nakretke = 1; 
wcisnalem_pedal = 0;
zacisnalem_szczeki = 0;
zezwolenie_od_master = 0;
wcisniete_zakonczone = 2;
wieza = 0;

pozycja_wiezy = 0;
kkk = 0;
kkk1 = 0;
v1 = 60; 
speed_normal = 8;  //8 to totalny maks , 09.08.2018 bylo 10, zmieniam na 12, bo wtedy jest stabilnie
tryb_male_puchary = 0;
jedz_wieza_cykl_znacznik = 0;

PORTC.0 = 1;  // silownik obrotowy os pionowa
PORTC.1 = 1;  //silownik obrotowy os pozioma w gore czyli nie ma kolizji
PORTB.5 = 1;  //wibrator nowy

delay_ms(1000);
delay_ms(1000);

//////////////////////////////////////////////////////////////
//wypozucjonuj_wieze_wolno();

//#asm("sei")
//while(1)
//    jedz_wieza();

////////////////////////////////////////////

while(tryb_male_puchary == 0)
     komunikacja_male_puchary();


//wypozucjonuj_wieze_wolno();

while(PINE.7 == 0)
   {
   PORTE.0 = 1;    //zadanie wypozycjonowania
   } 
PORTE.0 = 0;
PORTB.5 = 0;  //wibrator nowy stop

// Global enable interrupts
#asm("sei")

//while(1)
//    jedz_wieza();


while (1)
      { 
            
      procesy();
      
      
      //if(proces[3] != 4)
      //  {
        zerowanie_procesow();
        kontrola_orientatora_nakretek_nowa_zjezdzalnia();
        komunikacja_bez_rs232();
        komunikacja_male_puchary();
      //  }
      
      while(jedz_wieza_cykl_znacznik == 1 & tryb_male_puchary == 2)
          {
          //jedz_wieza_cykl();
          jedz_wieza_cykl_nowy_procesor();
          if(skonczony_proces[0] == 0)
                skonczony_proces[0] = proces_0();
          if(skonczony_proces[3] == 0)
                skonczony_proces[3] = proces_3();
          }
        
      }
//kontrola_czujnika_dolnego_nakretek();
//kontrola_orientatora_nakretek();
//obsluga_dozownika_kleju_i_komunikacja();
//drgania();
//obsluga_probna_pobierania_nakretek();
}


