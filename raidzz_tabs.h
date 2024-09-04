/*
 * raidzz_tabs.h
 *
 *	Definition of tables.
 */



#define raidzz_max_parity		2
#define raidzz_max_data			15

/* ======== raidzz_func_t ============================================= */
/* PURPOSE:
 *	Type for function converter
 */

typedef unsigned char raidzz_func_t[ 0x100 ];


/* ======== raidzz_IFxy_lm_t ========================================== */
/* PURPOSE:
 *	Nibble inverse double parity error recovery function type.
 *  If we use bytes as indicies, the total size of raidzz_FunctionStruct_t
 *	is around 2MB.  This way it's only around 72K, it could be halved
 *	since the inverse only the elements where l < m are used.
 */

typedef unsigned char raidzz_IFxy_lm_t[ 0x10 ][ 0x10 ];


/* ======== raidzz_FunctionStruct_t =================================== */
/* PURPOSE:
 *	A struct containing all pre-computed mapping functions.
 */

typedef struct  raidzz_FunctionStruct_t {

	/* All parity functions												*/
	raidzz_func_t	raidzz_functab[ raidzz_max_parity ][ raidzz_max_data ];

	/* All inverse parity functions										*/
	raidzz_func_t	raidzz_Ifunctab[ raidzz_max_parity ][ raidzz_max_data ];

	/* All inverse double parity functions								*/
	raidzz_IFxy_lm_t raidzz_IFxy_lmTab[ raidzz_max_data ][ raidzz_max_data ];

} raidzz_FunctionStruct_t;

/* The struct containing all tables.									*/
extern raidzz_FunctionStruct_t	raidzz_FunctionStruct[ 1 ];


