/*
 * raidzz_if.h
 *
 *	Raidzz interface file.
 */

#define raidzz_OK					0
#define	raidzz_ERR_num_parity		1
#define	raidzz_ERR_num_data			2
#define raidzz_ERR_unrecoverable	3
#define raidzz_ERR_badparams		4

int raidzz_gen_parity(
	unsigned int	   data_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_data,
	unsigned char	** data_table,
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,
	unsigned char	** parity_table,
	size_t			   data_len
);

int	raidzz_recover(
	unsigned int	   error_mask,		/* A 1 bit indicates the error	*/
	unsigned int	   num_data,		/* Number of data buffers		*/
	unsigned char	** data_table,		/* List of data buffer pointers	*/
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,		/* Number of parity buffers		*/
	unsigned char	** parity_table,	/* List of parity buffer ptrs	*/
	size_t			   data_len,		/* Length of buffers			*/
	unsigned int	   num_error		/* Number of errors being recovered*/
);

