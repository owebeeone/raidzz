/*
 * raidzz_impl.c
 *
 *	This impliments the multiple redundancy RAID algorithm as per
 *	the comp.arch.storage article posted in November '94.
 *
 */

#include <sys/types.h>

#include "raidzz_if.h"
#include "raidzz_tabs.h"

/* ======== check_params ============================================== */
/* PURPOSE:
 *	Check parameters
 *
 * RETURNS:
 * 	raidzz_OK if everything is OK
 */

static int check_params(
	unsigned int	   num_data,
	unsigned int	   num_parity
) {

	/* Verify what is required											*/

	if ( num_parity > raidzz_max_parity ) {
		/* Too many parities requestsed									*/
		return raidzz_ERR_num_parity;
	}

	if ( num_data > raidzz_max_data ) {
		/* Too many data tables requested								*/
		return raidzz_ERR_num_data;
	}

    return raidzz_OK;

} /* end check_params */

/* =================================================================== */
#define CHECK_PARAMS()													\
	{																	\
		int status = check_params( num_data, parity_mask );				\
																		\
		if ( status != raidzz_OK ) {									\
			return status;												\
		}																\
	}																	\
/* =================================================================== */


/* ======== raidzz_compute_parity ===================================== */
/* PURPOSE:
 *	Compute the parity bits requested
 *
 * RETURNS:
 * 	nothing
 */

void raidzz_compute_parity(
	unsigned int	   data_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_data,
	unsigned char	** data_table,
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,
	unsigned char	** parity_table,
	size_t			   data_len,
	int				 * err_bufs
) {

	register unsigned char	* data_ptr;
	register unsigned char	* parity_ptr;
	register unsigned char  * func;
	unsigned int			  mask = 0x1;
	int						  i;
	int						  j;
	int						  k;

	for ( i = 0; i < num_data; i ++, mask <<= 1 ) {

		if ( data_mask & mask ) {
			// Set the error buffer
			if ( err_bufs && ( err_bufs[ 0 ] == -1 ) ) {
				err_bufs[ 0 ] = i;
				err_bufs ++;
			}
			continue;
		}
		for ( j = 0; j < num_parity; j ++ ) {

			if ( parity_mask & ( 1<<j ) ) {
				continue;
			}
			parity_ptr = parity_table[ j ];
			data_ptr = data_table[ i ];
			func = raidzz_FunctionStruct->raidzz_functab[ j ][ i ];

			/* great candidate for loop unrolling						*/
			for ( k = data_len; k >= 0; k -- ) {
				parity_ptr[ 0 ] ^= func[ data_ptr[ 0 ] ];
				parity_ptr ++;
				data_ptr ++;
			}
		}
	}

    return;

} /* end raidzz_compute_parity */


/* ======== raidzz_gen_parity ========================================= */
/* PURPOSE:
 *	Generate contents of parity buffers.
 *  parity_mask will only compute the contents of parity buffers marked
 *	with a 0 bit in the parity_mask value.  This could be used to
 *	recompute parity values for only those buffers requested.  This is
 *  useful to reduce the load when rebuilding a parity block.
 *  Parity buffers are added to.  Set them to 0 before calling this function.
 *
 * RETURNS:
 * 	Error code - raidzz_OK when everything is OK
 */

int raidzz_gen_parity(
	unsigned int	   data_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_data,
	unsigned char	** data_table,
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,
	unsigned char	** parity_table,
	size_t			   data_len
) {

	CHECK_PARAMS()
	
	raidzz_compute_parity(
		data_mask,
		num_data,
		data_table,
		parity_mask,
		num_parity,
		parity_table,
		data_len,
		0
	);

    return raidzz_OK;

} /* end raidzz_gen_parity												*/


/* ======== raidzz_recover_single ===================================== */
/* PURPOSE:
 *	Recover from a single block error
 *
 * RETURNS:
 * 	
 */

int	raidzz_recover_single(
	unsigned int	   error_mask,		/* A 1 bit indicates the error	*/
	unsigned int	   num_data,		/* Number of data buffers		*/
	unsigned char	** data_table,		/* List of data buffer pointers	*/
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,		/* Number of parity buffers		*/
	unsigned char	** parity_table,	/* List of parity buffer ptrs	*/
	size_t			   data_len,		/* Length of buffers			*/
	unsigned int	   num_error		/* Number of errors being recovered*/
) {
	int				   err_bufs[ 3 ];
	unsigned int	   parity_num;

	/* Make sure at least one parity buffer is valid					*/
	if ( ( parity_mask & 0x3 ) == 0x3 ) {
		/* need at least one parity buffer								*/
		return raidzz_ERR_unrecoverable;
	}

	err_bufs[ 0 ] = -1;
	err_bufs[ 1 ] = -1;
	err_bufs[ 2 ] = 0;

	parity_num = parity_mask & 1 ? 1 : 0;

	/* Compute only the parity we care to use							*/
	parity_mask = ~ ( 1 << parity_num );

	raidzz_compute_parity(
		error_mask,
		num_data,
		data_table,
		parity_mask,
		num_parity,
		parity_table,
		data_len,
		err_bufs
	);

	/* Did we find more than one buffer masked							*/
	if ( err_bufs[ 1 ] != -1 ) {
		return raidzz_ERR_badparams;
	}

	/* Was there one buffer missing ?									*/
	if ( err_bufs[ 0 ] == -1 ) {
		return raidzz_ERR_badparams;
	}

	/* recover the error												*/
	{
		register unsigned char	* data_ptr;
		register unsigned char	* parity_ptr;
		register unsigned char  * func;
		register size_t			  k;

		parity_ptr = parity_table[ parity_num ];
		data_ptr = data_table[ err_bufs[ 0 ] ];

		/* Get the inverse parity function								*/
		func = raidzz_FunctionStruct->raidzz_Ifunctab
			[ parity_num ][ err_bufs[ 0 ] ]
		;

		/* great candidate for loop unrolling							*/
		for ( k = data_len; k; k -- ) {
			* data_ptr = func[ * parity_ptr ];
			parity_ptr ++;
			data_ptr ++;
		}
	}

    return raidzz_OK;

} /* end raidzz_recover_single */



/* ======== raidzz_recover_double ===================================== */
/* PURPOSE:
 *	Recover from double errors
 *
 * RETURNS:
 * 	raidzz_OK if all is OK
 */

int raidzz_recover_double(
	unsigned int	   error_mask,		/* A 1 bit indicates the error	*/
	unsigned int	   num_data,		/* Number of data buffers		*/
	unsigned char	** data_table,		/* List of data buffer pointers	*/
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,		/* Number of parity buffers		*/
	unsigned char	** parity_table,	/* List of parity buffer ptrs	*/
	size_t			   data_len,		/* Length of buffers			*/
	unsigned int	   num_error		/* Number of errors being recovered*/
) {

	int				   err_bufs[ 4 ];

	/* Make sure both parity buffers are valid							*/
	if ( ( parity_mask & 0x3 ) != 0 ) {
		/* need two parity buffers for this one							*/
		return raidzz_ERR_unrecoverable;
	}

	err_bufs[ 0 ] = -1;
	err_bufs[ 1 ] = -1;
	err_bufs[ 2 ] = -1;
	err_bufs[ 3 ] = 0;

	raidzz_compute_parity(
		error_mask,
		num_data,
		data_table,
		parity_mask,
		num_parity,
		parity_table,
		data_len,
		err_bufs
	);

	/* Did we find more than two buffers masked							*/
	if ( err_bufs[ 2 ] != -1 ) {
		return raidzz_ERR_badparams;
	}

	/* Was there two buffers missing ?									*/
	if ( err_bufs[ 1 ] == -1 ) {
		return raidzz_ERR_badparams;
	}

	/* recover from two errors											*/
	{
		register unsigned char	* data0_ptr;
		register unsigned char	* data1_ptr;
		register unsigned char	* parity0_ptr;
		register unsigned char	* parity1_ptr;
		register raidzz_IFxy_lm_t * IFxy_lm;
		register unsigned char	  v0;
		register unsigned char	  v1;
		register size_t			  k;

		/* Select the correct inverse correction function				*/
		IFxy_lm = & raidzz_FunctionStruct->raidzz_IFxy_lmTab
			[ err_bufs[ 0 ] ][ err_bufs[ 1 ] ]
		;

		parity0_ptr = parity_table[ 0 ];
		parity1_ptr = parity_table[ 1 ];
		data0_ptr = data_table[ err_bufs[ 0 ] ];
		data1_ptr = data_table[ err_bufs[ 1 ] ];
		
		/* great candidate for loop unrolling							*/
		for ( k = data_len; k; k -- ) {

			v0 = ( * IFxy_lm )[(* parity0_ptr) & 0xf][(* parity1_ptr) & 0xf];
			v1 = ( * IFxy_lm )[(* parity0_ptr) >> 4][(* parity1_ptr) >> 4];

			* data0_ptr = ( v0 & 0xf ) | ( v1 << 4 );
			* data1_ptr = ( v0 >> 4 ) | ( v1 & 0xf0 );

			parity0_ptr ++;
			parity1_ptr ++;
			data0_ptr ++;
			data1_ptr ++;
		}
	}
    return raidzz_OK;

} /* end raidzz_recover_double */



/* ======== raidzz_recover ============================================ */
/* PURPOSE:
 *	Do data recovery.
 *	This assumes that the parity buffers were computed using the same
 *	contents as the raidzz_gen_parity function except for the buffers
 *  marked with errors.  There should be at least as many valid parity
 *	buffers as there are data errors.  Parity buffers that are marked
 *	as "not valid" ('1' bit) are not used.
 *
 *	Contents of the parity buffers are destroyed.
 *
 * RETURNS:
 * 	Error code - raidzz_OK when everything is OK
 * 	
 */

int	raidzz_recover(
	unsigned int	   error_mask,		/* A 1 bit indicates the error	*/
	unsigned int	   num_data,		/* Number of data buffers		*/
	unsigned char	** data_table,		/* List of data buffer pointers	*/
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,		/* Number of parity buffers		*/
	unsigned char	** parity_table,	/* List of parity buffer ptrs	*/
	size_t			   data_len,		/* Length of buffers			*/
	unsigned int	   num_error		/* Number of errors being recovered*/
) {

	CHECK_PARAMS()

	/* Make sure we have enough data to recover from the error			*/
	if ( num_error > num_parity ) {
		return raidzz_ERR_unrecoverable;
	}

	if ( num_error == 1 ) {
		/* Simple - one parity required.								*/
		return raidzz_recover_single(
			error_mask,
			num_data,
			data_table,
			parity_mask,
			num_parity,
			parity_table,
			data_len,
			num_error
		);
	}

	if ( num_error == 2 ) {
		/* Simple - one parity required.								*/
		return raidzz_recover_double(
			error_mask,
			num_data,
			data_table,
			parity_mask,
			num_parity,
			parity_table,
			data_len,
			num_error
		);
	}

	/* don't know how to do 3 error recovery							*/
    return raidzz_ERR_unrecoverable;

} /* end raidzz_recover */

