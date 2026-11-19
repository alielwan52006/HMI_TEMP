#include <avr/io.h>  
#include <stdint.h>  
#include "adc.h"     
void adc_init(void) // initializes the ADC
{
    
    ADMUX = (1 << REFS0); // select the 5v as the adc refrence voltage

    // Enable the adc and set its prescaler to 128
    // ADEN enable the adc
    // ADC clock = 16 MHz / 128 = 125 kHz
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
}

// This function reads an analog value from a selected adc channel
uint16_t adc_read(uint8_t channel)
{
    channel &= 0x07;

    // Select the ADC input channel
    // & 0xF0 reserve the upper 4 bits of ADMUX
    ADMUX = (ADMUX & 0xF0) | channel;

    // Set ADSC to 1 to start the ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait till conversion is done
    // ADSC becomes 0 automatically when conversion is complete
    while (ADCSRA & (1 << ADSC))
    {
        // Stay here while the ADC is converting
    }

    // Return the digital conversion result (0 to 1023)
    return ADC;
}
