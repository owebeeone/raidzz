/*
 * raidzz_test.c
 *
 *		Test this raidzz thing.
 */

#include <sys/types.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <alloca.h>

#include "raidzz_if.h"

#define MAX_BUFFERS		15

/* int		buffer_size = sizeof( "HELLO" ); */
int		buffer_size = 1024;
int		num_buffers = MAX_BUFFERS;
unsigned char	* buffers[ MAX_BUFFERS ];

unsigned char	* parity_buffers[ 2 ];
unsigned char	* saved_parity_buffers[ 2 ];

void fill_junk( unsigned char * ptr )
{
	int			len;

	if ( buffer_size == sizeof( "HELLO" ) ) {
		memcpy( ptr, "HELLO", buffer_size );
	} else {
		for ( len = buffer_size; len; len -- ) {
			ptr[ len - 1 ] = rand();
		}
	}
}

void allocate_buffers()
{
	int			i;

	for ( i = 0; i < MAX_BUFFERS; i ++ ) {
		buffers[ i ] = ( unsigned char * ) malloc( buffer_size );

		fill_junk( buffers[ i ] );
	}

	parity_buffers[ 0 ] = ( unsigned char * ) malloc( buffer_size );
	parity_buffers[ 1 ] = ( unsigned char * ) malloc( buffer_size );
	saved_parity_buffers[ 0 ] = ( unsigned char * ) malloc( buffer_size );
	saved_parity_buffers[ 1 ] = ( unsigned char * ) malloc( buffer_size );

}

void compute_parity()
{

	memset( saved_parity_buffers[ 0 ], 0, buffer_size );
	memset( saved_parity_buffers[ 1 ], 0, buffer_size );

	raidzz_gen_parity(
		0,
		num_buffers,
		buffers,
		0,
		2,
		saved_parity_buffers,
		buffer_size
	);

}

void copy_parity()
{
	
	memcpy( parity_buffers[ 0 ], saved_parity_buffers[ 0 ], buffer_size );
	memcpy( parity_buffers[ 1 ], saved_parity_buffers[ 1 ], buffer_size );

}

void test_recovery_1( int badblk0 )
{
	unsigned char * blocks[ 1 ];
	unsigned char * new_blocks[ 1 ];

	copy_parity();

	blocks[ 0 ] = buffers[ badblk0 ];

	new_blocks[ 0 ] = buffers[ badblk0 ] = alloca( buffer_size );

	raidzz_recover(
		( 1 << badblk0 ),
		num_buffers,
		buffers,
		( 1 << ( rand() & 1 ) ),	/* Pick a parity buffer				*/
		2,
		parity_buffers,
		buffer_size,
		1
	);

	buffers[ badblk0 ] = blocks[ 0 ];

	if ( memcmp( blocks[ 0 ], new_blocks[ 0 ], buffer_size ) ) {
		fprintf( stderr, "Recovery error in block\n" );
	}
	
}

void test_recovery_2( int badblk0, int badblk1 )
{
	unsigned char * blocks[ 2 ];
	unsigned char * new_blocks[ 2 ];

	if ( badblk0 == badblk1 ) {
		test_recovery_1( badblk0 );
		return;
	}

	copy_parity();
	
	blocks[ 0 ] = buffers[ badblk0 ];
	blocks[ 1 ] = buffers[ badblk1 ];

	new_blocks[ 0 ] = buffers[ badblk0 ] = alloca( buffer_size );
	new_blocks[ 1 ] = buffers[ badblk1 ] = alloca( buffer_size );

	raidzz_recover(
		( 1 << badblk0 ) | ( 1 << badblk1 ),
		num_buffers,
		buffers,
		0,
		2,
		parity_buffers,
		buffer_size,
		2
	);

	buffers[ badblk0 ] = blocks[ 0 ];
	buffers[ badblk1 ] = blocks[ 1 ];

	if ( memcmp( blocks[ 0 ], new_blocks[ 0 ], buffer_size ) ) {
		fprintf( stderr, "Recovery error in first block\n" );
	}
	
	if ( memcmp( blocks[ 1 ], new_blocks[ 1 ], buffer_size ) ) {
		fprintf( stderr, "Recovery error in second block\n" );
	}
	
}

int main( int argc, char ** argv )
{
	int			i;

	allocate_buffers();

	compute_parity();

	for ( i = 0; i < 10000; i ++ ) {

		int		l = rand() % num_buffers;
		int		m = rand() % num_buffers;

		if ( ! (i % 10) ) {
			fprintf( stderr, "\r%5d tests", i );
		}
		fflush( stderr );

		test_recovery_2( l, m );

	}

	fprintf( stderr, "\n" );
		
}
