#ifndef _VDP_VDU_H
#define _VDP_VDU_H

#include <stdbool.h>
#include <stdint.h>
#include <mos_api.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VDP_PUTS(S) mos_puts( (char *)&(S), sizeof(S), 0)

// ========= VDU Commands ==========
volatile SYSVAR *vdp_vdu_init( void );
// VDU 1: Send next character to "printer" (if "printer" is enabled)
void vdp_send_to_printer( char ch );
// VDU 2: Enable "printer"
void vdp_enable_printer( void );
// VDU 3: Disable "printer"
void vdp_disable_printer( void );
// VDU 4: Write text at text cursor
void vdp_write_at_text_cursor( void );
// VDU 5: Write text at graphics cursor
void vdp_write_at_graphics_cursor( void );
// VDU 6: Enable screen (opposite of VDU 21)
void vdp_enable_screen( void );
// VDU 7: Make a short beep (BEL)
void vdp_bell( void );
// VDU 8: Move cursor back one character
void vdp_cursor_left( void );
// VDU 9: Move cursor forward one character
void vdp_cursor_right( void );
// VDU 10: Move cursor down one line
void vdp_cursor_down( void );
// VDU 11: Move cursor up one line
void vdp_cursor_up( void );
// VDU 12: Clear text area (CLS)
void vdp_clear_screen( void );
#define vdp_cls() vdp_clear_screen()
// VDU 13: Carriage return
void vdp_carriage_return( void );
// VDU 14: Page mode On
void vdp_page_mode_on( void );
// VDU 15: Page mode Off
void vdp_page_mode_off( void );
// VDU 16: Clear graphics area (CLG)
void vdp_clear_graphics( void );
#define vdp_clg() vdp_clear_graphics()
// VDU 17, colour: Set text colour
void vdp_set_text_colour( int colour );
// VDU 18, mode, colour: Set graphics colour (GCOL mode, colour)
void vdp_set_graphics_colour( int mode, int colour );
#define vdp_gcol( M, C ) vdp_set_graphics_colour( M, C )
// VDU 19, l, p, r, g, b: Define logical colour
void vdp_define_colour(int logical, int physical, int red, int green, int blue );
// VDU 20: Reset palette and text/graphics colours and drawing modes
void vdp_reset_graphics( void );
// VDU 21: Disable screen
void vdp_disable_screen( void );
// VDU 22, n: Select screen mode (MODE n)
int vdp_mode( int mode );

// VDU 23, n: Re-program display character
void vdp_redefine_character( int char_num, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 );
// VDU 23, 0, <command>, [<arguments>]: System commands
// -- see below --
// VDU 23, 1, n: Cursor control
void vdp_cursor_enable( bool flag );
// VDU 23, 6, n1, n2, n3, n4, n5, n6, n7, n8: Set dotted line pattern
void vdp_set_dotted_line_pattern( uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 );
// VDU 23, 7, extent, direction, movement: Scroll
void vdp_scroll_screen(int direction, int speed);
void vdp_scroll_screen_extent( int extent, int direction, int speed );
// VDU 23, 16, setting, mask: Define cursor movement behaviour
void vdp_cursor_behaviour( int setting, int mask );
// VDU 23, 23, n: Set line thickness
void vdp_set_line_thickness( int pixels );
// VDU 23, 27, <command>, [<arguments>]: Bitmap and sprite commands
// -- see below --

// VDU 24, left; bottom; right; top;: Set graphics viewport
void vdp_set_graphics_viewport( int left, int bottom, int right, int top );
//VDU 25, mode, x; y;: PLOT command
void vdp_plot( int plot_mode, int x, int y );
void vdp_move_to( int x, int y );
void vdp_line_to( int x, int y );
void vdp_point( int x, int y );
void vdp_triangle( int x, int y );
void vdp_circle_radius( int x, int y );
void vdp_circle( int x, int y );
void vdp_filled_rect( int x, int y );

// VDU 26: Reset graphics and text viewports
void vdp_reset_viewports( void );
// VDU 27, char: Output character to screen
// -- not implemented -- 
// VDU 28, left, bottom, right, top: Set text viewport
void vdp_set_text_viewport( int left, int bottom, int right, int top );
// VDU 29, x; y;: Set graphics origin
void vdp_graphics_origin( int x, int y );
// VDU 30: Home cursor
void vdp_cursor_home( void );
// VDU 31, x, y: Move text cursor to x, y text position
void vdp_cursor_tab( int row, int col );

// ========= System Commands ==========
// VDU 23, 0, <command>, [<arguments>]: System commands

// VDU 23, 0, &0A, n: Set cursor start line and appearance
void vdp_set_cursor_start_line( int n );

// VDU 23, 0, &0B, n: Set cursor end line
void vdp_set_cursor_end_line( int n );

// VDU 23, 0, &81, n: Set the keyboard locale
void vdp_set_keyboard_locale( int locale );

// VDU 23, 0, &82: Request text cursor position
//   Helper function to request cursor position and wait for results if asked
//   Results are in sys_vars
void vdp_request_text_cursor_position( bool wait );
//   Helper function to read and return cursor X,Y position.
void vdp_return_text_cursor_position( uint8_t* return_x, uint8_t* return_y );

// VDU 23, 0, &83, x; y;: Get ASCII code of character at character position x, y
//   Helper function to request the character at x, y and wait if asked.
//   Results are in sys_vars
void vdp_request_ascii_code_at_position( int x, int y, bool wait );
//   Helper function to return the character at x, y
uint8_t vdp_return_ascii_code_at_position( int x, int y );

// VDU 23, 0, &84, x; y;: Get colour of pixel at pixel position x, y
void vdp_request_pixel_colour( int x, int y, bool wait );
//   Helper function for read pixel colour. Returns pixel colour as 24-bit value.
uint24_t vdp_return_pixel_colour( int x, int y );

// VDU 23, 0, &85, channel, command, <args>: Audio commands
// -- see below --

// VDU 23, 0, &86: Fetch the screen dimensions
//     -- not implemented --
//    "Generally applications should not need to call this, as this information will
//     be automatically sent to MOS when the screen mode is changed."
//     The application should read the screen dimension using the getsysvar_scr*() calls
//     (waiting for vdp_pflag_mode to be set if mode was changed)

// VDU 23, 0, &87: RTC control
//     VDU 23, 0, &87, 0: Read the RTC 
void vdp_request_rtc( bool wait );
//     VDU 23, 0, &87, 1, y, m, d, h, m, s: Set the RTC
// VDU 23, 0, &88, delay; rate; led: Keyboard Control
void vdp_keyboard_cotrol( int delay, int rate, int led );
// VDU 23, 0, &89, command, [<args>]: Mouse control
// -- see below --
// VDU 23, 0, &8A, n: Set the cursor start column
void vdp_set_cursor_start_column( int n );
// VDU 23, 0, &8B, n: Set the cursor end column
void vdp_set_cursor_end_column( int n );
// VDU 23, 0, &8C, x; y;: Relative cursor movement (by pixels)
void vdp_move_cursor_relative( int x, int y );
// VDU 23, 0, &90, n, b1, b2, b3, b4, b5, b6, b7, b8: Redefine character n (0-255)
void vdp_redefine_character_special( int char_num, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7 );
void vdp_define_character( int char_num, uint8_t *data ); // uses VDP2.3.0 redefine special char 23,0,0x90
// VDU 23, 0, &91: Reset all system font characters to original definition
void vdp_reset_system_font( void );
// VDU 23, 0, &93, x; y;: Get ASCII code of character at graphics position x, y
void vdp_request_ascii_code_at_graphics_position( int x, int y, bool wait );
// 
uint8_t vdp_return_ascii_code_at_graphics_position( int x, int y );
// VDU 23, 0, &94, n: Read colour palette entry n (returns a pixel colour data packet)
void vdp_request_palette_entry( int n, bool wait );
uint8_t vdp_read_palette_entry( int n );
// VDU 23, 0, &95, <command>, [<args>]: Font management commands
// -- see below --
// VDU 23, 0, &98, n: Turn control keys on and off
void vdp_control_keys( bool on );
// VDU 23, 0, &9C: Set the text viewport using graphics coordinates
void vdp_set_text_viewport_via_plot( void );
// VDU 23, 0, &9D: Set the graphics viewport using graphics coordinates
void vdp_set_graphics_viewport_via_plot( void );
// VDU 23, 0, &9E: Set the graphics origin using graphics coordinates
void vdp_set_graphics_origin_via_plot( void );
// VDU 23, 0, &9F: Move the graphics origin and viewports
void vdp_move_graphics_origin_and_viewport( void );
// VDU 23, 0, &A0, <bufferId>, <command>, [<args>]
// -- see below --
// VDU 23, 0, &C0, n: Turn logical screen scaling on and off
void vdp_logical_scr_dims( bool flag );
// VDU 23, 0, &C1, n: Switch legacy modes on or off
void vdp_legacy_modes( bool on );
// VDU 23, 0, &C3: Swap the screen buffer and/or wait for VSYNC
void vdp_swap( void );
// VDU 23, 0, &C8, <command>, [<args>]: Context management API 
// -- see below --
// VDU 23, 0, &CA: Flush current drawing commands
void vdp_flush_drawing_commands( void );
// VDU 23, 0, &F2, n: Set dot-dash pattern length
void vdp_set_dash_pattern_length( int n );
// VDU 23, 0, &FE, n: Console mode
void vdp_console_mode( bool on );
// VDU 23, 0, &FF: Switch to or resume "terminal mode"
void vdp_terminal_mode( void );

// ========= Bitmaps and Sprites ==========
// VDU 23, 27, 0, n: Select bitmap n
void vdp_select_bitmap( int n );
// VDU 23, 27, 1, w; h; b1, b2 ... bn: Load colour bitmap data into current bitmap
void vdp_load_bitmap( int width, int height, uint32_t *data );
// helper function to load bitmap from file
int vdp_load_bitmap_file( const char *fname, int width, int height );
// VDU 23, 27, 1, n, 0, 0;: Capture screen data into bitmap n
// -- not implemented --
// VDU 23, 27, 2, w; h; col1; col2;: Create a solid colour rectangular bitmap
void vdp_solid_bitmap( int width, int height, int r, int g, int b, int a );
// VDU 23, 27, 3, x; y;: Draw current bitmap on screen at pixel position x, y
void vdp_draw_bitmap( int x, int y );
// VDU 23, 27, &20, bufferId;: Select bitmap using a 16-bit buffer ID
void vdp_adv_select_bitmap(int bufferId);
// VDU 23, 27, &21, w; h; format: Create bitmap from selected buffer
void vdp_adv_bitmap_from_buffer(int width, int height, int format);

// VDU 23, 27, 4, n: Select sprite n
void vdp_select_sprite( int n );
// VDU 23, 27, 5: Clear frames in current sprite
void vdp_clear_sprite( void );
// VDU 23, 27, 6, n: Add bitmap n as a frame to current sprite (where bitmap's buffer ID is 64000+n)
void vdp_add_sprite_bitmap( int n );
// VDU 23, 27, 7, n: Activate n sprites
void vdp_activate_sprites( int n );
// VDU 23, 27, 8: Select next frame of current sprite
void vdp_next_sprite_frame( void );
// VDU 23, 27, 9: Select previous frame of current sprite
void vdp_prev_sprite_frame( void );
// VDU 23, 27, 10, n: Select the nth frame of current sprite
void vdp_nth_sprite_frame( int n );
// VDU 23, 27, 11: Show current sprite
void vdp_show_sprite( void );
// VDU 23, 27, 12: Hide current sprite
void vdp_hide_sprite( void );
// VDU 23, 27, 13, x; y;: Move current sprite to pixel position x, y
void vdp_move_sprite_to( int x, int y );
// VDU 23, 27, 14, x; y;: Move current sprite by x, y pixels
void vdp_move_sprite_by( int x, int y );
// VDU 23, 27, 15: Update the sprites in the GPU
void vdp_refresh_sprites( void );
// VDU 23, 27, 16: Reset bitmaps and sprites and clear all data
void vdp_reset_sprites( void );
// VDU 23, 27, 17: Reset sprites (only) and clear all data
void vdp_reset_sprites_only( void );
// VDU 23, 27, 18, n: Set the current sprite GCOL paint mode to n **
void vdp_set_sprite_paint_mode( int n );
// VDU 23, 27, &26, n;: Add bitmap n as a frame to current sprite using a 16-bit buffer ID
void vdp_adv_add_sprite_bitmap( int bitmap_num );

// Helper function to load bitmaps from file and assign to a sprite
// see below for 16-bit bufferID version vdp_adv_load_sprite_bitmaps
int vdp_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format,
							int width, int height, int num, int bitmap_num );
// Helper function to assign sequence of bitmaps to a sprite (activates all sprites to n)
// see below for 16-bit bufferID version vdp_adv_create_sprite
void vdp_create_sprite( int sprite, int bitmap_num, int frames );

// VDU 23, 27, &40, hotX, hotY: Setup a mouse cursor

// ========= Advanced Buffer Commands =========
// Command 0: Write block to a buffer
// 	VDU 23, 0 &A0, bufferId; 0, length; <buffer-data>
void vdp_adv_write_block(int bufferID, int length);
void vdp_adv_write_block_data(int bufferID, int length, char *data);
// Command 1: Call a buffer
// 	VDU 23, 0 &A0, bufferId; 1
void vdp_adv_call_buffer(int bufferID);
// Command 2: Clear a buffer
// 	VDU 23, 0 &A0, bufferId; 2
void vdp_adv_clear_buffer(int bufferID);
// Command 3: Create a writeable buffer
// 	VDU 23, 0 &A0, bufferId; 3, length;
void vdp_adv_create(int bufferID, int length);
// Command 4: Set output stream to a buffer
// 	VDU 23, 0 &A0, bufferId; 4
void vdp_adv_stream(int bufferID);
// Command 5: Adjust buffer contents
// 	VDU 23, 0, &A0, bufferId; 5, operation, offset; [count;] <operand>, [arguments]
void vdp_adv_adjust(int bufferID, int operation, int offset );
// Command 6: Conditionally call a buffer
// 	VDU 23, 0, &A0, bufferId; 6, operation, checkBufferId; checkOffset; [arguments]
void vdp_adv_call_conditional(int bufferId, int operation, int checkBufferId, int checkOffset );
// Command 7: Jump to a buffer
// 	VDU 23, 0, &A0, bufferId; 7
void vdp_adv_jump_buffer(int bufferID);
// Command 8: Conditional Jump to a buffer
// 	VDU 23, 0, &A0, bufferId; 8, operation, checkBufferId; checkOffset; [arguments]
void vdp_adv_call_conditional(int bufferId, int operation, int checkBufferId, int checkOffset );
// Command 9: Jump to an offset in a buffer
// 	VDU 23, 0, &A0, bufferId; 9, offset; offsetHighByte, [blockNumber;]
void vdp_adv_jump_offset( int bufferId, int offset );
void vdp_adv_jump_offset_block( int bufferId, int offset, int block );
// Command 10: Conditional jump to an offset in a buffer
// 	VDU 23, 0, &A0, bufferId; 10, offset; offsetHighByte, [blockNumber;] [arguments]
void vdp_adv_jump_offset_conditional( int bufferId, int offset );
void vdp_adv_jump_offset_block_conditional( int bufferId, int offset, int block );
// Command 11: Call buffer with an offset
// 	VDU 23, 0, &A0, bufferId; 11, offset; offsetHighByte, [blockNumber;]
void vdp_adv_call_offset( int bufferId, int offset );
void vdp_adv_call_offset_block( int bufferId, int offset, int block );
// Command 12: Conditional call buffer with an offset
// 	VDU 23, 0, &A0, bufferId; 12, offset; offsetHighByte, [blockNumber;] [arguments]
void vdp_adv_call_offset_conditional( int bufferId, int offset );
void vdp_adv_call_offset_block_conditional( int bufferId, int offset, int block );
// Command 13: Copy blocks from multiple buffers into a single buffer
// 	VDU 23, 0, &A0, targetBufferId; 13, sourceBufferId1; sourceBufferId2; ... 65535;
void vdp_adv_copy_multiple( int bufferId, int num_buffers, ... );
// Command 14: Consolidate blocks in a buffer
// 	VDU 23, 0, &A0, bufferId; 14
void vdp_adv_consolidate(int bufferID);
// Command 15: Split a buffer into multiple blocks
// 	VDU 23, 0, &A0, bufferId; 15, blockSize;
void vdp_adv_split( int bufferID, int blockSize );
// Command 16: Split a buffer into multiple blocks and spread across multiple buffers
// 	VDU 23, 0, &A0, bufferId; 16, blockSize; [targetBufferId1;] [targetBufferId2;] ... 65535;
void vdp_adv_split_multiple( int bufferId, int blockSize,  int num_buffers, ... );
// Command 17: Split a buffer and spread across blocks, starting at target buffer ID
// 	VDU 23, 0, &A0, bufferId; 17, blockSize; targetBufferId;
void vdp_adv_split_multiple_from( int bufferID, int blockSize, int targetBufferID );
// Command 18: Split a buffer into blocks by width
// 	VDU 23, 0, &A0, bufferId; 18, width; blockCount;
void vdp_adv_split_by_width( int bufferID, int width, int blockCount );
// Command 19: Split by width into blocks and spread across target buffers
// 	VDU 23, 0, &A0, bufferId; 19, width; [targetBufferId1;] [targetBufferId2;] ... 65535;
void vdp_adv_split_by_width_multiple( int bufferId, int width, int num_buffers, ... );
// Command 20: Split by width into blocks and spread across blocks starting at target buffer ID
// 	VDU 23, 0, &A0, bufferId; 20, width; blockCount; targetBufferId;
void vdp_adv_split_by_width_multiple_from( int bufferID, int width, int blockCount, int targetBufferID );
// Command 21: Spread blocks from a buffer across multiple target buffers
// 	VDU 23, 0, &A0, bufferId; 21, [targetBufferId1;] [targetBufferId2;] ... 65535;
void vdp_adv_spread_multiple( int bufferId, int num_buffers, ... );
// Command 22: Spread blocks from a buffer across blocks starting at target buffer ID
// 	VDU 23, 0, &A0, bufferId; 22, targetBufferId;
void vdp_adv_spread_multiple_from( int bufferID, int targetBufferID );
// Command 23: Reverse the order of blocks in a buffer
// 	VDU 23, 0, &A0, bufferId; 23
void vdp_adv_reverse_block_order( int bufferID );
// Command 24: Reverse the order of data of blocks within a buffer
// 	VDU 23, 0, &A0, bufferId; 24, options, [valueSize;] [chunkSize;]
void vdp_adv_reverse_block_data( int bufferID, int options, int valueSize, int chunkSize );
// Command 25: Copy blocks from multiple buffers by reference
// 	VDU 23, 0, &A0, targetBufferId; 25, sourceBufferId1; sourceBufferId2; ...; 65535;
void vdp_adv_copy_multiple_by_reference( int bufferId, int num_buffers, ... );
// Command 26: Copy blocks from multiple buffers and consolidate
// 	VDU 23, 0, &A0, targetBufferId; 26, sourceBufferId1; sourceBufferId2; ...; 65535;
void vdp_adv_copy_multiple_consolidate( int bufferId, int num_buffers, ... );
// Command 64: Compress a buffer
// 	VDU 23, 0, &A0, targetBufferId; 64, sourceBufferId;
void vdp_adv_compress_buffer( int targetBufferID, int sourceBufferId );
// Command 65: Decompress a buffer
// 	VDU 23, 0, &A0, targetBufferId; 65, sourceBufferId;
void vdp_adv_decompress_buffer( int targetBufferID, int sourceBufferId );

// Helper functions using full 16-bit buffer-id
int vdp_adv_load_sprite_bitmaps( const char *fname_prefix, const char *fname_format, int width, int height, int num, int bitmap_num );
void vdp_adv_create_sprite( int sprite, int bitmap_num, int frames );

// ========= Audio Commands =========
// Command 0: Play note 
// 	VDU 23, 0, &85, channel, 0, volume, frequency; duration;
void vdp_audio_play_note( int channel, int volume, int frequency, int duration);
// Command 1: Status 
// 	VDU 23, 0, &85, channel, 1
void vdp_audio_status( int channel );
// Command 2: Set volume
// 	VDU 23, 0, &85, channel, 2, volume
void vdp_audio_set_volume( int channel, int volume );
// Command 3: Set frequency
//	VDU 23, 0, &85, channel, 3, frequency;
void vdp_audio_set_frequency( int channel, int frequency );
#define VDP_AUDIO_WAVEFORM_SQUARE 0
#define VDP_AUDIO_WAVEFORM_TRIANGLE 1
#define VDP_AUDIO_WAVEFORM_SAWTOOTH 2
#define VDP_AUDIO_WAVEFORM_SINEWAVE 3
#define VDP_AUDIO_WAVEFORM_NOISE 4
#define VDP_AUDIO_WAVEFORM_VICNOISE 5
// Command 4 (types 0-5): Set waveform
//	VDU 23, 0, &85, channel, 4, waveformOrSample, [bufferId;]
void vdp_audio_set_waveform( int channel, int waveform );
// Command 4 (type 8): Set sample
void vdp_audio_set_sample( int channel, int bufferID );
// Command 5: Sample management
// 	VDU 23, 0, &85, channelOrSample, 5, sampleCommand, [parameters]
//	Command 5, 0: Load sample
//		VDU 23, 0, &85, sample, 5, 0, length; lengthHighByte, <sampleData>
//		the sample data is assumed to be 8-bit signed PCM samples at 16kHz
void vdp_audio_load_sample( int sample, int length, uint8_t *data);
// 	Command 5, 1: Clear sample
//		VDU 23, 0, &85, sample, 5, 1
void vdp_audio_clear_sample( int sample );
#define VDP_AUDIO_SAMPLE_FORMAT_8BIT_SIGNED 0
#define VDP_AUDIO_SAMPLE_FORMAT_8BIT_UNSIGNED 1
#define VDP_AUDIO_SAMPLE_FORMAT_SAMPLE_RATE_FOLLOWS 8
#define VDP_AUDIO_SAMPLE_FORMAT_SAMPLE_TUNEABLE 8
//	Command 5, 2: Create a sample from a buffer
//		VDU 23, 0, &85, channel, 5, 2, bufferId; format, [sampleRate;]
void vdp_audio_create_sample_from_buffer( int channel, int bufferID, int format);
//	Command 5, 3: Set sample base frequency
//		VDU 23, 0, &85, sample, 5, 3, frequency;
void vdp_audio_set_sample_frequency( int sample, int frequency );
//	Command 5, 4: Set sample frequency for a sample by buffer ID
//		VDU 23, 0, &85, channel, 5, 4, bufferId; frequency;
void vdp_audio_set_buffer_frequency( int channel, int bufferID, int frequency );
//	Command 5, 5: Set sample repeat start point
//		VDU 23, 0, &85, sample, 5, 5, repeatStart; repeatStartHighByte
void vdp_audio_set_sample_repeat_start( int sample, int repeatStart );
//	Command 5, 6: Set sample repeat start point by buffer ID
//		VDU 23, 0, &85, channel, 5, 6, bufferId; repeatStart; repeatStartHighByte
void vdp_audio_set_buffer_repeat_start( int channel, int bufferID, int repeatStart );
//	Command 5, 7: Set sample repeat length
//		VDU 23, 0, &85, sample, 5, 7, repeatLength; repeatLengthHighByte
void vdp_audio_set_sample_repeat_length( int sample, int repeatLength );
//	Command 5, 8: Set sample repeat length by buffer ID
//		VDU 23, 0, &85, channel, 5, 8, bufferId; repeatLength; repeatLengthHighByte
void vdp_audio_set_buffer_repeat_length( int channel, int bufferID, int repeatLength );
// Command 6: Volume envelope. Type 0: Disable
//	VDU 23, 0, &85, channel, 6, type, [parameters]
void vdp_audio_volume_envelope_disable( int channel );
// Command 6: Volume envelope. Type 1: ADSR
// 	VDU 23, 0, &85, channel, 6, 1, attack; decay; sustain, release;
void vdp_audio_volume_envelope_ADSR( int channel, int attack, int decay, int sustain, int release );
// Command 6: Volume envelope. Type 2: Multi-phase ADSR
// 	VDU 23, 0, &85, channel, 6, 2, attackCount, [level, duration;]*, sustainCount, [level, duration;]*, releaseCount, [level, duration;]*
// 	variable length parameters - leave to user to send separately
void vdp_audio_volume_envelope_multiphase_ADSR( int channel ); // variable length parameters to be send separately
// Command 7: Frequency envelope
//	VDU 23, 0, &85, channel, 7, type, [parameters]
// 	Type 0: None
//		VDU 23, 0, &85, channel, 7, 0
void vdp_audio_frequency_envelope_disable( int channel );
//	Type 1: Stepped frequency envelope
//		VDU 23, 0, &85, channel, 7, 1, phaseCount, controlByte, stepLength; [phase1Adjustment; phase1NumberOfSteps; phase2Adjustment; phase2NumberOfSteps; ...]
#define VDP_AUDIO_FREQ_ENVELOPE_CONTROL_REPEATS 1
#define VDP_AUDIO_FREQ_ENVELOPE_CONTROL_CUMULATIVE 2
#define VDP_AUDIO_FREQ_ENVELOPE_CONTROL_RESTRICT 4
void vdp_audio_frequency_envelope_stepped( int channel, int phaseCount, int controlByte, int stepLength );
// Command 8: Enable Channel
// 	VDU 23, 0, &85, channel, 8
void vdp_audio_enable_channel( int channel );
// Command 9: Disable Channel
//  	VDU 23, 0, &85, channel, 9
void vdp_audio_disable_channel( int channel );
// Command 10: Reset Channel
//  	VDU 23, 0, &85, channel, 10
void vdp_audio_reset_channel( int channel );
// Command 11: Seek to position
// 	VDU 23, 0, &85, channel, 11, position; positionHighByte
void vdp_audio_sample_seek( int channel, int position );
// Command 12: Set duration
// 	VDU 23, 0, &85, channel, 12, duration; durationHighByte
void vdp_audio_sample_duration( int channel, int duration );
// Command 13: Set sample rate
// 	VDU 23, 0, &85, channel, 13, sampleRate;
void vdp_audio_sample_rate( int channel, int rate );
// Command 14: Set channel waveform parameters
// 	VDU 23, 0, &85, channel, 14, parameter, value
void vdp_audio_set_waveform_parameter( int channel, int parameter, int value );


// ========= Context Management =========
// VDU 23, 0, &C8, 0, contextId: Select context stack
void vdp_context_select( int context_id );
// VDU 23, 0, &C8, 1, contextId: Delete context stack
void vdp_context_delete( int context_id );
// VDU 23, 0, &C8, 2, flags: Reset
void vdp_context_reset( int flags );
// VDU 23, 0, &C8, 3: Save context
void vdp_context_save( void );
// VDU 23, 0, &C8, 4: Restore context
void vdp_context_restore( void );
// VDU 23, 0, &C8, 5, contextId: Save and select a copy of a context
void vdp_context_save_copy( int context_id );
// VDU 23, 0, &C8, 6: Restore all
void vdp_context_restore_all( void );
// VDU 23, 0, &C8, 7: Clear stack
void vdp_context_clear_stack( void );

// ========= Font Management =========
// VDU 23, 0, &95: Font management
// VDU 23, 0, &95, 0, bufferId; flags: Select font
void vdp_font_select( int buffer_id );
// VDU 23, 0, &95, 1, bufferId; width, height, ascent, flags: Create font from buffer
void vdp_font_create( int buffer_id, int width, int height, int ascent, int flags );
// VDU 23, 0, &95, 2, bufferId; field, value;: Set or adjust font property
void vdp_font_adjust( int buffer_id, int field, int value );
// VDU 23, 0, &95, 3, bufferId; [<args>]: Reserved
// VDU 23, 0, &95, 4, bufferId;: Clear/Delete font
void vdp_font_delete( int buffer_id );
// VDU 23, 0, &95, 5, bufferId;: Copy system font to buffer
void vdp_font_copy( int buffer_id );

// ========= Mouse Control =========
// VDU 23, 0, &89, command, [<args>]: Mouse control
// 	VDU 23, 0, &89, 0: Enable the mouse
void vdp_mouse_enable( void );
// 	VDU 23, 0, &89, 1: Disable the mouse
void vdp_mouse_disable( void );
// 	VDU 23, 0, &89, 2: Reset the mouse
void vdp_mouse_reset( void );
// 	VDU 23, 0, &89, 3, cursorId;: Set mouse cursor
void vdp_mouse_set_cursor( int cursorId );
// 	VDU 23, 0, &89, 4, x; y;: Set mouse cursor position
void vdp_mouse_set_position( int X, int Y );
// 	VDU 23, 0, &89, 5, x1; y1; x2; y2;: Reserved
// 	VDU 23, 0, &89, 6, sampleRate: Set mouse sample rate
void vdp_mouse_sample_rate( int sampleRate );
// 	VDU 23, 0, &89, 7, resolution: Set mouse resolution
void vdp_mouse_resolution( int resolution );
// 	VDU 23, 0, &89, 8, scaling: Set mouse scaling
void vdp_mouse_scaling( int scaling );
// 	VDU 23, 0, &89, 9, acceleration;: Set mouse acceleration
void vdp_mouse_acceleration( int acceleration );
// 	VDU 23, 0, &89, 10, wheelAcceleration; wheelAccHighByte: Set mouse wheel acceleration (accepts a 24-bit value)
void vdp_mouse_wheel_accel( int wheelAccel );


#ifdef __cplusplus
}
#endif

#endif
