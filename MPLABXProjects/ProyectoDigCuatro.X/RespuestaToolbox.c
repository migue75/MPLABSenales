/*
 * File:   RespuestaToolbox.c
 * Author: Miguel Angel Echavarria
 *
 * Created on 6 de mayo de 2021, 06:43 PM
 */


#define FCY 40000000
#include "configuracionPragma.h"
#include "xc.h"
#include"p33FJ32MC204.h"
#include "libpic30.h"
#include "toolbox.h"

void configurarReloj(void);

int main(void){
    float *s;
    float *s1;
    float *s2;
  
  
    int muestras,n=0;

    configurarReloj();

    s=seno(1,60,6000,&muestras);
    s1=cuadrada(1,60,6000,&muestras);
    s2=triangular(1,60,6000,&muestras);
    
  
    TRISB=0;//puerto B como salida
    TRISCbits.TRISC0=0;
   
    while(1){
        if(PORTCbits.RC1==1 && PORTCbits.RC2==0 &&PORTCbits.RC3==0){
            PORTCbits.RC0=PORTCbits.RC0;
            PORTB=(uint16_t)((*(s+n)+1)*(4095/2));//(uint16_t)time casting
            
            n++;
            if (n>= muestras)
            n=0;
            __delay_ms(1);
      
    }
        if(PORTCbits.RC1==0 && PORTCbits.RC2==1 &&PORTCbits.RC3==0){
            
                  
            PORTCbits.RC0=PORTCbits.RC0;
            PORTB=(uint16_t)((*(s1+n)+1)*(4095/2));//(uint16_t)time casting
           
        
            n++;
            if (n>= muestras)
            n=0;
            __delay_ms(1);
      
        } 
         if(PORTCbits.RC1==0 && PORTCbits.RC2==0 &&PORTCbits.RC3==1){
          
            
            
            PORTCbits.RC0=PORTCbits.RC0;
            PORTB=(uint16_t)((*(s2+n)+1)*(4095/2));//(uint16_t)time casting
            
            n++;
            if (n>= muestras)
            n=0;
            __delay_ms(1);
      
        } 
        
       
    }
    return 0;
}

//Filtro FIIR
/*int main(void){
    float *q;
    float t[6]={2,4,6,8,7,9};
    
    int tk;
    q=(float *)(malloc(tk*sizeof(float)));
    q=filtroFir(&t[0],6);
}

 //Filtro IIR
/*int main(void){
float *p;
float t[6]={2,4,6,8,7,9};

int tk;
p=(float *)(malloc(tk*sizeof(float)));
p=filtroIir(&t[0],6);

    
}   
*/
//convolucion

  
int main(void){
float *q;
float x[12]={-3, 5,6,7,8,9,4,2,1,-8,-3,0};
float h[3]={3,3,3};
  
float y[14];

int tk;
q=(float *)(malloc(tk*sizeof(float)));
q=convolution(&x[0],&h[0],12);
}

void configurarReloj(void){
    OSCCON=0X0101;
    OSCTUN=0;//Fin=7.37MHz Frecuencia del FRC
    PLLFBD=41;//M=43
    /*CLKDIV=0;//N1=2,N2=2,SE CONFIGURA TODO EL REGISTRO*/
    CLKDIVbits.PLLPOST=0;//N2=2
    CLKDIVbits.PLLPRE=0;//N1=2
    RCONbits.SWDTEN=0;//WDT disable 
    
}
