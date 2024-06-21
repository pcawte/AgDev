
// Check key status based on VDP protocol data
//
// - should call vdp_update_key_state() in the main game loop otherwise may miss events
// - in theory should be integrated into the interrupt handler (TODO)

#include <vdp_key.h>
#include <vdp_vdu.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>

// Array to be updated by the interrupt routine

uint8_t vdp_key_bits[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Information is extracted from the existing interrupt routine to allow it to be cloned & modified

/* Existing interrupt routine

 - Check fingerprint of this routine
 - and extract addresses to use in own interrupt routine

; AGON UART0 Interrupt Handler
;
_uart0_handler:		DI 							; f3
			PUSH	AF 							; f5
			PUSH	BC 							; c5
			PUSH	DE 							; d5
			PUSH	HL 							; e5
			CALL	UART0_serial_RX				; cd ## ## ##
			LD		C, A						; 4f
			LD		HL, _vdp_protocol_data 		; 21 ## ## ##
			CALL	vdp_protocol 				; cd ## ## ##
			POP		HL 							; e1
			POP		DE 							; d1
			POP		BC 							; c1
			POP		AF 							; f1
			EI 									; fb
			RETI.L								; 5b ed 4d
*/

static uint8_t fp1[] = { 0xf3, 0xf5, 0xc5, 0xd5, 0xe5, 0xcd, 0 };
static uint8_t fp2[] = { 0x4f, 0x21, 0 };
static uint8_t fp3[] = { 0xcd, 0 };
static uint8_t fp4[] = { 0xe1, 0xd1, 0xc1, 0xf1, 0xfb, 0x5b, 0xed, 0x4d, 0 };

extern uint24_t _agdev_UART0_serial_RX;				// Address of UART0_serial_RX call
extern uint24_t _agdev_vdp_protocol_data;			// Address of vdp_protocol_data buffer
extern uint24_t _agdev_vdp_protocol; 				// Address of vdp_protocol call

typedef void(*INTERRUPT_HANDLER)(void);

extern void _agdev_default_mi_handler( void );
extern void _agdev_uart0_handler( void );

const uint8_t *check_bytes( const uint8_t *mem_ptr, const uint8_t *finger_print );
const uint8_t *check_bytes_get_int( const uint8_t *mem_ptr, const uint8_t *finger_print, uint24_t *value );
void vdp_key_reset_interrupt( void );

static INTERRUPT_HANDLER uart0_orig_handler = NULL;


typedef union {
	uint24_t vdp_prot_ctrl;
	struct {
   		uint8_t vdp_protocol_state;
    	uint8_t vdp_protocol_cmd;
    	uint8_t vdp_protocol_len;
 	};
} VDP_CTRL;

static VDP_CTRL *vdp_ctrl_ptr = NULL;
static KEY_EVENT *vdp_key_event_ptr = NULL;

// Returns -1 if fails to set interrupt handler else returns 0

int vdp_key_init( void )
{
	// Get UART0 interrupt vector by setting it to dummy and then restoring it

	uart0_orig_handler = mos_setintvector( 0x18, _agdev_default_mi_handler );
	mos_setintvector( 0x18, uart0_orig_handler );

	// Check "finger print" of existing routine & get addresses

	const uint8_t *mem_ptr = (uint8_t *)uart0_orig_handler;

	if ( !(mem_ptr = check_bytes_get_int( mem_ptr, fp1, &_agdev_UART0_serial_RX )) ) return -1;
	if ( !(mem_ptr = check_bytes_get_int( mem_ptr, fp2, &_agdev_vdp_protocol_data )) ) return -1;
	if ( !(mem_ptr = check_bytes_get_int( mem_ptr, fp3, &_agdev_vdp_protocol )) ) return -1;
	if ( !(mem_ptr = check_bytes( mem_ptr, fp4 )) ) return -1;

	vdp_ctrl_ptr = (VDP_CTRL *)(_agdev_vdp_protocol_data-6);
	vdp_key_event_ptr = (KEY_EVENT *)_agdev_vdp_protocol_data;

	// The above sets the 3 address in the interrupt code to the values from the original routine

	atexit( &vdp_key_reset_interrupt );
	mos_setintvector( 0x18, &_agdev_uart0_handler );
	return 0;
}

// Restore interrupt vector on exit from program

void vdp_key_reset_interrupt( void )
{
	if ( !uart0_orig_handler ) return;
	mos_setintvector( 0x18, uart0_orig_handler );
	uart0_orig_handler = NULL;	
}


// Check for "finger_print" in memory
// - returns address of end of finger print or NULL if doesn't match

const uint8_t *check_bytes( const uint8_t *mem_ptr, const uint8_t *finger_print )
{
	while ( *finger_print ) {
		if ( *mem_ptr++ != *finger_print++ ) return NULL;
	}
	return mem_ptr;
}

// Check for "finger_print" in memory and gets uint24_t at end
// - returns address of end of finger print or NULL if doesn't match

const uint8_t *check_bytes_get_int( const uint8_t *mem_ptr, const uint8_t *finger_print, uint24_t *value )
{
	if ( !(mem_ptr = check_bytes( mem_ptr, finger_print )) ) return NULL;
	*value = *(uint24_t *)mem_ptr;
	mem_ptr += 3;
	return mem_ptr;
}

// Update key state routine to be called from main game loop

static KEY_EVENT prev_key = { 0 };
static KEY_EVENT_HANDLER event_handler = NULL;

void vdp_set_key_event_handler( KEY_EVENT_HANDLER key_event_handler ) {
	event_handler = key_event_handler;
}

void vdp_update_key_state( void )
{
	if ( !vdp_key_event_ptr ) return;

	uint24_t vdp_prot_ctrl;
	KEY_EVENT key_event;

	vdp_prot_ctrl = vdp_ctrl_ptr->vdp_prot_ctrl;
	key_event = *vdp_key_event_ptr;

	if ( vdp_prot_ctrl != 0x000100 ) return;

	if ( key_event.key_data != prev_key.key_data ) {
		if ( event_handler ) (*event_handler)( key_event );

		// Setting of bit mask is done in the interrupt routine
	}
	return;
}

static uint8_t bit_masks[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

bool vdp_check_key_press( uint8_t key_code )
{
	uint8_t mask = key_code & 0x07;
	uint8_t byte = key_code >> 3;
	return vdp_key_bits[byte] & bit_masks[mask];
}


