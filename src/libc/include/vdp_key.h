#ifndef _VDP_KEY_H
#define _VDP_KEY_H

#include <stdbool.h>
#include <stdint.h>

typedef union {
	uint32_t key_data;
	struct {
		uint8_t ascii;
		uint8_t mods;
		uint8_t code;
		uint8_t down;
	};
} KEY_EVENT;


extern uint8_t vdp_key_bits[32];

typedef void (*KEY_EVENT_HANDLER)(KEY_EVENT key_event);

int vdp_key_init( void );
void vdp_key_reset_interrupt( void );

void vdp_update_key_state();
bool vdp_check_key_press( uint8_t key_code );
void vdp_set_key_event_handler( KEY_EVENT_HANDLER event_handler );

#endif