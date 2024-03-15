/*
 * ADC_32U4.cpp
 *
 * Created: 12/03/2024 15:37:25
 * Author : Luis Mi CONTROLLIUM
 */ 

#include <avr/io.h>
#include <avr/io.h>
int valor=0;
void ADC_init() {
	// Configurar el ADC para usar la referencia AVCC y ajustar a la derecha
	ADMUX = (1 << REFS0);

	// Habilitar el ADC y configurar el prescaler según el reloj de 16 MHz
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
uint16_t ADC_read(uint8_t adcPin) {
	// Verificar que el pin sea un pin de ADC válido (PF4 a PF7)
	if (adcPin < 4 || adcPin > 7) {
		return 0;  // Enviar un valor nulo si el pin no es válido
	}

	// Configurar el pin de ADC
	ADMUX = (ADMUX & 0xF0) | (adcPin & 0x0F);

	// Iniciar la conversión ADC
	ADCSRA |= (1 << ADSC);

	// Esperar a que la conversión se complete
	while (ADCSRA & (1 << ADSC));

	// Combinar los registros ADCL y ADCH para obtener el valor de 10 bits
	uint16_t adcValue = ADC;
	return adcValue;
}

int main(void)
{	
	DDRB|=(1<<PINB0);

	
    ADC_init();
	
    while (1) 
    {	
		int valor = ADC_read(7);
		if(valor == 1023)
		{		
			PORTB &=~(1<<PINB0);	
		}else{
			PORTB|=(1<<PINB0);
		}
    }
}

