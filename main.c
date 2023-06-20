#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>



void adc_init();
uint8_t adc_read(uint8_t ch);


int main(void){

//output on portC
DDRC=0xFF;
DDRA=0x11;
adc_init();
uint8_t r;
float v;

while(1){
r=adc_read(1);

v=(r*5.0)/255;
if(v<=0.45){
    PORTA|=(1<<0);  
}
else {
      PORTA&=(~(1<<0));  

}

  if(PINC & (1<<0) ){
        PORTA&=(~(1<<0));  
       

       }
}


} 

void adc_init(){
  //for the referance voltage
  ADMUX|=(1<<REFS0);
  
  //to adjust frequency of prescaler 
  ADCSRA|=(1<<ADPS0) ;
  ADCSRA|=(1<<ADPS1);
  ADCSRA|=(1<<ADPS2);

  //To activate the adc enable 
  ADCSRA |=(1<<ADEN);
  ADMUX|=(1<<ADLAR);

}

uint8_t adc_read(uint8_t ch){
ch&=0b00000111;
//Channel selection 
ADMUX=0b11100000;//here I keep the reference voltage the same and make mux bits zero to receive the channel
ADMUX|=ch;
// To start conversion
ADCSRA|=(1<< ADSC);//start one sampling 
while(ADCSRA &(1<<ADSC));// as long as adsc is 1 which means the conversion is on then the loop continue

return ADCH;
}