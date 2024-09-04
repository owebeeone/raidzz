/*
 *
 * raidzz_mktable.c
 *
 *      Generate raid 10 tables.
 */

#include <stdio.h>
#include <string.h>
#include "raidzz_tabs.h"

typedef unsigned char rzz_functab[ 0x10 ];

rzz_functab rzz_commonfunc[1] =
{
	{
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00,
	}
};

rzz_functab rzz_fb1[1] = {
	{
		0x02, 0x03, 0x01, 0x08, 0x0a, 0x0b, 0x09, 0x0c,
        0x0e, 0x0f, 0x0d, 0x04, 0x06, 0x07, 0x05, 0x00,
	}
};

rzz_functab rzz_fb2[1] = {
	{
		0x03, 0x01, 0x02, 0x0c, 0x0f, 0x0d, 0x0e, 0x04,
        0x07, 0x05, 0x06, 0x08, 0x0b, 0x09, 0x0a, 0x00,
	}
};

rzz_functab rzz_fb3[1] = {
	{
		0x04, 0x08, 0x0c, 0x06, 0x02, 0x0e, 0x0a, 0x0b,
        0x0f, 0x03, 0x07, 0x0d, 0x09, 0x05, 0x01, 0x00,
	}
};

rzz_functab rzz_fb4[1] = {
	{
		0x05, 0x0a, 0x0f, 0x02, 0x07, 0x08, 0x0d, 0x03,
        0x06, 0x09, 0x0c, 0x01, 0x04, 0x0b, 0x0e, 0x00,
	}
};

rzz_functab rzz_fb5[1] = {
	{
		0x06, 0x0b, 0x0d, 0x0e, 0x08, 0x05, 0x03, 0x07,
        0x01, 0x0c, 0x0a, 0x09, 0x0f, 0x02, 0x04, 0x00,
	}
};

rzz_functab rzz_fb6[1] = {
	{
		0x07, 0x09, 0x0e, 0x0a, 0x0d, 0x03, 0x04, 0x0f,
        0x08, 0x06, 0x01, 0x05, 0x02, 0x0c, 0x0b, 0x00,
	}
};

rzz_functab rzz_fb7[1] = {
	{
		0x08, 0x0c, 0x04, 0x0b, 0x03, 0x07, 0x0f, 0x0d,
        0x05, 0x01, 0x09, 0x06, 0x0e, 0x0a, 0x02, 0x00,
	}
};

rzz_functab rzz_fb8[1] = {
	{
		0x09, 0x0e, 0x07, 0x0f, 0x06, 0x01, 0x08, 0x05,
        0x0c, 0x0b, 0x02, 0x0a, 0x03, 0x04, 0x0d, 0x00,
	}
};

rzz_functab rzz_fb9[1] = {
	{
		0x0a, 0x0f, 0x05, 0x03, 0x09, 0x0c, 0x06, 0x01,
        0x0b, 0x0e, 0x04, 0x02, 0x08, 0x0d, 0x07, 0x00,
	}
};

rzz_functab rzz_fb10[1]= {
	{
		0x0b, 0x0d, 0x06, 0x07, 0x0c, 0x0a, 0x01, 0x09,
        0x02, 0x04, 0x0f, 0x0e, 0x05, 0x03, 0x08, 0x00,
	}
};

rzz_functab rzz_fb11[1]= {
	{
		0x0c, 0x04, 0x08, 0x0d, 0x01, 0x09, 0x05, 0x06,
        0x0a, 0x02, 0x0e, 0x0b, 0x07, 0x0f, 0x03, 0x00,
	}
};

rzz_functab rzz_fb12[1]= {
	{
		0x0d, 0x06, 0x0b, 0x09, 0x04, 0x0f, 0x02, 0x0e,
        0x03, 0x08, 0x05, 0x07, 0x0a, 0x01, 0x0c, 0x00,
	}
};

rzz_functab rzz_fb13[1]= {
	{
		0x0e, 0x07, 0x09, 0x05, 0x0b, 0x02, 0x0c, 0x0a,
        0x04, 0x0d, 0x03, 0x0f, 0x01, 0x08, 0x06, 0x00,
	}
};

rzz_functab rzz_fb14[1]= {
	{
		0x0f, 0x05, 0x0a, 0x01, 0x0e, 0x04, 0x0b, 0x02,
		0x0d, 0x07, 0x08, 0x03, 0x0c, 0x06, 0x09, 0x00,
	}
};



rzz_functab * rzz_funclist[ 2 ][ 15 ] =
{
    {
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
        rzz_commonfunc,
    },
    {
        rzz_commonfunc,
        rzz_fb1,
        rzz_fb2,
        rzz_fb3,
        rzz_fb4,
        rzz_fb5,
        rzz_fb6,
        rzz_fb7,
        rzz_fb8,
        rzz_fb9,
        rzz_fb10,
        rzz_fb11,
        rzz_fb12,
        rzz_fb13,
        rzz_fb14
    }
};

#ifndef TEST
raidzz_FunctionStruct_t  raidzz_FunctionStruct[ 1 ];
#endif

/* ======== MakeParityFunctions ======================================= */
/* PURPOSE:
 *	Generate all parity functions.
 *
 */

void	MakeParityFunctions()
{

	unsigned int		p;
	unsigned int		m;
	unsigned int		i;

	rzz_functab		  * nfpm;
	raidzz_func_t	  * fpm;
	raidzz_func_t	  * Ifpm;

	/* span all parities and data functions								*/
	for ( p = 0; p < raidzz_max_parity; p ++ ) {
		for ( m = 0; m < raidzz_max_data; m ++ ) {
			
			nfpm = rzz_funclist[ p ][ m ];
			fpm = & raidzz_FunctionStruct->raidzz_functab[ p ][ m ];
			Ifpm = & raidzz_FunctionStruct->raidzz_Ifunctab[ p ][ m ];

			/* Scan through all possible values							*/
			for ( i = 0; i < 0x100; i ++ ) {
				( * fpm )[ i ] = ( * nfpm )[ i & 0xf ] | ( ( * nfpm )[ ( i >> 4 ) & 0xf ] << 4 );
				( * Ifpm )[ ( * fpm )[ i ] ] = i;
			}
		}
	}

    return;

} /* end MakeParityFunctions */


/* ======== MakeIFxy_lm =============================================== */
/* PURPOSE:
 *	Make inverse double parity functions
 *
 * RETURNS:
 * 	yes - it does return
 */

void	MakeIFxy_lm()
{

	unsigned int		l;
	unsigned int		m;
	unsigned int		i;
	unsigned int		j;

	unsigned int		p0;
	unsigned int		p1;

	rzz_functab		  * nfp0l;
	rzz_functab		  * nfp0m;
	rzz_functab		  * nfp1l;
	rzz_functab		  * nfp1m;

	raidzz_IFxy_lm_t	check;
	raidzz_IFxy_lm_t  * IFxy_lm;

	/* span all parities and data functions								*/
	for ( l = 0; l < raidzz_max_data; l ++ ) {
		for ( m = 0; m < raidzz_max_data; m ++ ) {

			/* Can't have l == m										*/
			if ( l == m ) {
				continue;
			}
			
			nfp0l = rzz_funclist[ 0 ][ l ];
			nfp0m = rzz_funclist[ 0 ][ m ];
			nfp1l = rzz_funclist[ 1 ][ l ];
			nfp1m = rzz_funclist[ 1 ][ m ];

			memset( check, 0, sizeof( check ) );
			IFxy_lm = & raidzz_FunctionStruct->raidzz_IFxy_lmTab[ l ][ m ];

			/* Scan through all possible values							*/
			for ( i = 0; i < 0x10; i ++ ) {
				for ( j = 0; j < 0x10; j ++ ) {
					p0 = ( * nfp0l )[ i ] ^ ( * nfp0m )[ j ];
					p1 = ( * nfp1l )[ i ] ^ ( * nfp1m )[ j ];

					/* Just make sure that the inverse mapping is possible*/
					if ( check[ p0 ][ p1 ] ) {
						fprintf(
							stderr,
							"raidzz_mktable: "
							"Unable to make inverse double error "
							"mapping function for data lines %d and %d "
							"for valies 0x%02x and 0x%02x\n",
							l, m, i, j
						);
					}
					check[ p0 ][ p1 ] = 1;

					/* Generate the inverse mapping values				*/
					( * IFxy_lm )[ p0 ][ p1 ] = i | ( j << 4 );
					
				}
			}
		}
	}

    return;

} /* end MakeIFxy_lm */


/* ======== DumpFunctionStruct ======================================== */
/* PURPOSE:
 *	Dump the FunctionStruct table
 *
 * RETURNS:
 * 	most times
 */

void	DumpFunctionStruct()
{

	unsigned int		p;
	unsigned int		l;
	unsigned int		m;
	unsigned int		i;
	unsigned int		j;

	FILE				* fout = stdout;
	
	raidzz_func_t	  * fpm;
	raidzz_IFxy_lm_t  * IFxy_lm;

	fprintf(
		fout,
		"/*\n"
		" * This file is generated by raidzz_mktable.c\n"
		" * Edits to this file will be lost.\n"
		" */\n"
		"\n"
		"#include \"raidzz_tabs.h\"\n"
		"\n"
		"raidzz_FunctionStruct_t  raidzz_FunctionStruct[ 1 ] = {{\n"
		"/* raidzz_func_t   raidzz_functab[ raidzz_max_parity ][ raidzz_max_data ] */\n"
		"{\n"
	);
	/* span all parities and data functions								*/
	for ( p = 0; p < raidzz_max_parity; p ++ ) {
		fprintf(
			fout,
			"	{\n"
		);
			
		for ( m = 0; m < raidzz_max_data; m ++ ) {
			
			fprintf(
				fout,
				"		/* raidzz_func_t   raidzz_functab[ %d ][ %d ] */\n"
				"		{\n"
				"			",
				p, m
			);
			fpm = &raidzz_FunctionStruct->raidzz_functab[ p ][ m ];
			
			/* Scan through all possible values							*/
			for ( i = 0; i < 0x100; i ++ ) {

				fprintf( fout, " 0x%02x,", ( * fpm )[ i ] );
				
				if ( i && ! ( (i + 1) & 0x7 ) ) {
					fprintf(
						fout,
						" /* 0x%02x-0x%02x */\n			",
						i - 0x7,
						i
					);
				}
			}
			fprintf(
				fout,
				"\n"
				"		},\n"
			);
		}
		fprintf(
			fout,
			"	},\n"
		);
	}
	
	fprintf(
		fout,
		"},\n"
		"/* raidzz_func_t	raidzz_Ifunctab[ raidzz_max_parity ][ raidzz_max_data ] */\n"
		"{\n"
	);
	
	for ( p = 0; p < raidzz_max_parity; p ++ ) {
		fprintf(
			fout,
			"	  {\n"
		);
			
		for ( m = 0; m < raidzz_max_data; m ++ ) {
			
			fprintf(
				fout,
				"		/* raidzz_func_t	raidzz_Ifunctab[ %d ][ %d ] */\n"
				"		{\n"
				"			",
				p, m
			);

			fpm = & raidzz_FunctionStruct->raidzz_Ifunctab[ p ][ m ];
			
			/* Scan through all possible values							*/
			for ( i = 0; i < 0x100; i ++ ) {

				fprintf( fout, " 0x%02x,", ( * fpm )[ i ] );
				if ( i && ! ( ( i + 1 ) & 0x7 ) ) {
					fprintf(
						fout,
						" /* 0x%02x-0x%02x */\n			",
						i - 0x7,
						i
					);
				}
			}
			fprintf(
				fout,
				"\n"
				"		},\n"
			);
		}
		fprintf(
			fout,
			"	  },\n"
		);
	}
	
	fprintf(
		fout,
		"},\n"
		"/* raidzz_IFxy_lm_t raidzz_IFxy_lmTab[ raidzz_max_data ][ raidzz_max_data ] */\n"
		"{\n"
	);
	/* span all parities and data functions								*/
	for ( l = 0; l < raidzz_max_data; l ++ ) {
		
		fprintf(
			fout,
			"	{\n"
		);
			
		for ( m = 0; m < raidzz_max_data; m ++ ) {

			fprintf(
				fout,
				"		/* raidzz_IFxy_lm_t raidzz_IFxy_lmTab[ 0x%x ][ 0x%x ] */\n"
				"		{\n",
				l, m
			);
			IFxy_lm = &raidzz_FunctionStruct->raidzz_IFxy_lmTab[ l ][ m ];

			/* Scan through all possible values							*/
			for ( i = 0; i < 0x10; i ++ ) {
				
				fprintf(
					fout,
					"			/* raidzz_IFxy_lmTab[ 0x%x ][ 0x%x ][ 0x%x ] */\n"
					"			{\n"
					"				",
					l, m, i
				);
				
				for ( j = 0; j < 0x10; j ++ ) {
					fprintf( fout, " 0x%02x,", ( * IFxy_lm )[ i ][ j ] );
					if ( j && ! ( ( j + 1 )& 0x7 ) ) {
						fprintf(
							fout,
							" /* 0x%02x-0x%02x */\n				",
							j - 0x7,
							j
						);
					}
					
				}
				
				fprintf(
					fout,
					"\n"
					"			},\n"
				);
			}
			fprintf(
				fout,
				"		},\n"
			);
		}
		fprintf(
			fout,
			"	},\n"
		);
	}
	fprintf(
		fout,
		"}\n"
		"}};\n"
		"\n"
		"/* End of generated data */\n"
	);
		
    return;

} /* end DumpFunctionStruct */



int main( int argc, char ** argv )
{
#ifndef TEST
	fprintf(
		stderr,
		"raidzz_mktable : generating raidzz table %d bytes\n",
		sizeof( raidzz_FunctionStruct )
	);
	/* Set everything to -1												*/
	memset( raidzz_FunctionStruct, -1, sizeof( raidzz_FunctionStruct ) );

	/* Make the parity functions										*/
	MakeParityFunctions();

	/* Make the double error recovery functions							*/
	MakeIFxy_lm();
#endif

	DumpFunctionStruct();
	/* Dump a compilable version of this thing							*/

	return 0;
}
