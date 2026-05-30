#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ======================
// Road LEDs
// ======================

#define ROAD_GREEN     PB4
#define ROAD_YELLOW    PB3
#define ROAD_RED       PB2

// ======================
// Pedestrian LEDs
// ======================

#define PED_GREEN      PB0
#define PED_RED        PB1

// ======================
// Buttons
// ======================

#define EMERGENCY_BTN  PD2
#define PEDESTRIAN_BTN PD3
#define MAINTAIN_BTN   PC0


//OUTPUT INPUT DEFINING

DDRB |= (1 << ROAD_GREEN);
DDRB |= (1 << ROAD_YELLOW);
DDRB |= (1 << ROAD_RED);
DDRB |= (1 << PED_GREEN);
DDRB |= (1 << PED_RED);

DDRD &= ~(1 << EMERGENCY_BTN);
DDRD &= ~(1 << PEDESTRIAN_BTN);
DDRC &= ~(1 << MAINTAIN_BTN);

//PULLUP
PORTD |= (1 << EMERGENCY_BTN);
PORTD |= (1 << PEDESTRIAN_BTN);
PORTC |= (1 << MAINTAIN_BTN);


