



#include "ADC.h"

void ADC_init(){
	
	// Choosing reference voltage option.
	// the AVCC pin with a capacitor at the AREF pin.
	SET_BIT(ADMUX,REFS0_PIN);
	
	// Choosing Channel One (Single Ended In.) at A0 pin.
	CLR_BIT(ADMUX,MUX0_PIN);
	CLR_BIT(ADMUX,MUX1_PIN);
	CLR_BIT(ADMUX,MUX2_PIN);
	CLR_BIT(ADMUX,MUX3_PIN);
	CLR_BIT(ADMUX,MUX4_PIN);
	
	// Choosing the Data to be Right Adjusted in the Data Reg.
	CLR_BIT(ADMUX,ADLAR_PIN);
	
	// Choosing Prescaler for the ADC clock.
	// the following is choosing (2) as a Prescaler.
	SET_BIT(ADCSRA,ADPS0_PIN);
	CLR_BIT(ADCSRA,ADPS1_PIN);
	CLR_BIT(ADCSRA,ADPS2_PIN);
	
	// Enable the ADC
	SET_BIT(ADCSRA,ADEN_PIN);
	
}

Uint_16 ADC_read(){
	
	Uint_16 data;
	
	// Start Conversion
	SET_BIT(ADCSRA,ADSC_PIN);
	
	// Wait for flag to be set.
	// Indication of finished conversion
	while(IS_CLR(ADCSRA,ADIF_PIN));
	
	// Read Data from the ADC Data Register
	// Read the Low register first!
	data = ADCL;
	data |= (ADCH<<8);
	
	// Clear Flag (As we are not using the interrupt)
	// It won't be cleared automatically!
	SET_BIT(ADCSRA,ADIF_PIN);
	
	return data;
}