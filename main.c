#include "fsl_device_registers.h"

void delay_ms(unsigned int n) {
    unsigned int i = 0;
    for(i = 0; i < n; i++) {
        // Add some delay mechanism here
    }
}

int main(void) {
    // Turn on clock gating for ports CDE
    SIM->SCGC5 |= (1 << 11);	// PTC - SW1
    SIM->SCGC5 |= (1 << 12); 	// PTD - Red LED
	SIM->SCGC5 |= (1 << 13);	// PTE - Green LED

	// Set Port Control Registers (PCR) to GPIO mode

	// Set Port Data Direction Register (PDDR) to input mode (0)


	// Setup SW1 (PTC3)


    // Setup GREEN LED (PTD5)
    PORTD->PCR[5] &= ~0x700;			// Clear MUX bits
    PORTD->PCR[5] |= 0x700 & (1 << 8);	// Set MUX bits to GPIO
    GPIOD->PDDR |= (1 << 5);			// Set Data Direction as output

    // Setup RED LED (PTE29)
    PORTE->PCR[29] &= ~0x700;			// Clear MUX bits
    PORTE->PCR[29] |= 0x700 & (1 << 8);	// Set MUX bits to GPIO
    GPIOE->PDDR |= (1 << 29);			// Set Data Direction as output

    // Turn off both RED and Green LED at the start
    GPIOE->PDOR |= (1 << 29);			// Turn off GREEN LED
    GPIOD->PDOR |= (1 << 5);			// Turn off RED LED

    // Setup Yellow LED (E31)
    PORTE->PCR[31] &= ~0x700;			// Clear MUX bits
    PORTE->PCR[31] |= 0x700 & (1 << 8);	// Set MUX bits to GPIO
    GPIOE->PDDR |= (1 << 31);			// Set Data Direction as output

    // Setup SW1 (C3)
    PORTC->PCR[3] &= ~0x703;						// Clear MUX and PE/PS bits
    PORTC->PCR[3] |= 0x703 & ((1 << 8) | 0x03);		// Set MUX bits to GPIO, Set pull up and pull enable.
    GPIOC->PDDR &= ~(1 << 3);						// Clear Data direction (input)

    while(1) {
    	// If switch is pressed, blink YELLOW LED
        if(!(GPIOC->PDIR & (1 << 3))) {
                GPIOE->PDOR |= (1 << 31);		// Turn on YELLOW LED
                delay_ms(1000000);
                GPIOE->PDOR &= ~(1 << 31);		// Turn off YELLOW LED
                delay_ms(1000000);
        } else {
//
        GPIOE->PDOR &= ~(1 << 29); // Turn on RED LED
        delay_ms(1000000);
        GPIOE->PDOR |= (1 << 29); // Turn off RED LED
        delay_ms(1000000);

        GPIOD->PDOR &= ~(1 << 5); // Turn on GREEN LED
        delay_ms(1000000);
        GPIOD->PDOR |= (1 << 5); // Turn off GREEN LED
        delay_ms(1000000);

        GPIOE->PDOR |= (1 << 31); // Turn on YELLOW LED
        delay_ms(1000000);
        GPIOE->PDOR &= ~(1 << 31); // Turn off YELLOW LED
        delay_ms(1000000);
        }
    }

    /* Never leave main */
    return 0;
}
