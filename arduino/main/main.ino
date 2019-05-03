#include <TimerOne.h>
#include <SPI.h>
#include <DAC_MCP49xx.h>
#define SS_PIN 10
DAC_MCP49xx dac(DAC_MCP49xx::MCP4921, SS_PIN);
int msen = 3; //señal senoidal
int mcua = 4; // señal cuadrada
int mtri = 5; //señal triangular
int bandera;
int x;
int yf;
int muestra=0; // numero de muestra
float frecuencia; // frecuencia de senal a generar
float frecuenciadigital; // frecuencia digital
float frecuenciamuestreo=1000; // 4 K Hz
float amplitud;
float amplitudx;
float xanterior=0; // declaramos bandera
float yanterior=0; // declaramos bandera
void ISR_timer(){
 bandera=1;
 }
void setup(){
 pinMode(msen,INPUT); // se define entrada digital
 pinMode(mcua,INPUT);
 pinMode(mtri,INPUT);

 Serial.begin(9600); // incializa comunicacions serial
 Timer1.initialize(250); // Dispara cada 1 ms f=1/10ms = 1kHz
 Timer1.attachInterrupt(ISR_timer); // Activa la interrupcion y la asocia a ISR_timer
 dac.setSPIDivider(SPI_CLOCK_DIV16);
 dac.setPortWrite(true);
 }
void loop(){
//Sin Signal
if (digitalRead(msen) == true ){
if (bandera== 1 ){

 frecuencia =floor(98.0*((analogRead(1)*5.0)/(1024.0))+10.0); //frecuencia A0 potenciometr0
 frecuenciadigital = frecuencia/frecuenciamuestreo;
 amplitud=0.18*((analogRead(0)*5.0)/(1024.0))+0.1; //amplitud A1 potenciometro
 bandera=0;
 Serial.println(frecuencia);

 Serial.println(amplitud);
 x=(amplitud*sin(2*3.1416*muestra*frecuenciadigital))*2048+2048; //calculo seno digital de 12 bits // calculo sino digital de
 //12 bits; // calculo sino digital de 12 bits
 yf=0.29291*x +0.2929*xanterior+ 0.4142*yanterior;

 xanterior=x;

 yanterior=yf;
 int yf2 = floor(yf);

 muestra=muestra+1;

 dac.output(yf2);
 }

}
// Square signal
else if (digitalRead(mcua) == true ){
frecuencia =floor(98.0*((analogRead(1)*5.0)/(1024.0))+10.0);

amplitud = 0;
for (int i=0; i< frecuencia; i++)
dac.output(amplitud);
amplitudx=0.18*((analogRead(0)*5.0)/(1024.0))+0.1;
amplitud = amplitudx*4095;
for (int i=0; i< frecuencia; i++)
dac.output(amplitud);
 }
// Triangle wave
else if (digitalRead(mtri) == true ){

/*amplitudx=0.18*((analogRead(0)*5.0)/(1024.0))+0.1;
amplitud = amplitudx*4095;
for (int i=frecuencia; i<25; i++)
{
 dac.output(amplitud);
}
frecuencia =floor(98.0*((analogRead(1)*5.0)/(1024.0))+10.0);

amplitud = 0;
for (int i=24; i>=frecuencia; i--)
{
 dac.output(i*100);
}
}
}
*/
// triangle wave
for (int i=0; i<25; i++)
{
 dac.output(i*100);
}
for (int i=24; i>=0; i--)
{
 dac.output(i*100);
}
}
}
