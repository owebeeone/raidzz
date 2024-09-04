
# raidzz

Written by Gianni Mariani

LICENCE MUMBO JUMBO
-------------------

This is available under the terms of the GNU Public Licence (GPL).  Go
fetch yourself a copy.

The author accepts no responsibility at all for any malfunction, loss
of revenue, loss of mental health or loss of anything from anyone
using his software.  If you use it, it is up to you to make sure
that the software performs to your expectations.  In short, throw me
praise and money, but do not expect anything from me.

INTRODUCTION
------------

raidzz impliments a double error recovery algorithm suitable for
use in RAID like error recovery systems.  This library could be used
for things other than RAID.  A similar concept could be used for tape
drives, where an array of `inexpensive' tape drives are used and
error recovery is performed by having multiple parity tapes.

The word `parity' here is used somewhat incorrectly.  The `parity'
here refers to the moral equivalent of what RAID refers to as
parity but it is computed using functions as per the theory described
in the file RAIDZZ.

This scheme seems to impliment the moral equivalent of RAID-6, although
the author is not familiar with the details of RAID-6 implimentations.
If this implimentation is identical, it was coincidnece.  The author's
interest is to enable someone to integrate true double redundantcy
error recovery RAID into any OS even though the commercial viability is
somewhat unclear, he believes that there exists people that are as
paranoid as he is and are willing to take the pain for the percieved
gain.  Yes the author has had many disk failures and believes they are
out to get him. `they' are little nonobots that go around looking for
his hard drives to trash them.

This library impliments two `parity' buffers.  For instance, 10 disk
blocks to be striped over 10 disks could have 8 payload blocks and 2
parity blocks.  The error recovery algorithm will be capable of
recovering the loss of any 2 blocks.  The tables will allow up to 15
data blocks and 2 parity blocks.

API
---

The basic concept of the API is that the parity buffers are computed
by raidzz_gen_parity() and can be later used by raidzz_recover().  The
API is somewhat general but the valid parameters are limited.

raidzz_gen_parity
-----------------

#include <raidzz_if.h>

int raidzz_gen_parity(
	unsigned int	   data_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_data,		/*
	unsigned char	** data_table,
	unsigned int	   parity_mask,		/* A 1 bit indicates not to use buffer*/
	unsigned int	   num_parity,
	unsigned char	** parity_table,
	size_t			   data_len
);

raidzz_gen_parity will compute the contents of the `parity' buffers
passed in by parity_table.  The parity buffers need to be initialized
to zeros.

num_data and data_table indicate the number of data buffers and pointers
to the data buffers respectively.

data_mask indicates that the buffer in the data_table where the
a bit position is set should not to be used to compute of the parity.
This can be used to control how the parity buffer is built.
raidzz_gen_parity can be called repeatedly with the same parity buffers.

num_parity and parity_table indicate the number of parity buffers and
pointers to the parity buffers respectively.

parity_mask indicates that the buffer in the parity_table where the
a bit position is set should not to be used.

Return values:

	raidzz_OK				(0) Parity was computed OK
	raidzz_ERR_num_parity		num_parity is out of range
	raidzz_ERR_num_data			num_data is out of range

raidzz_recover
--------------

#include <raidzz_if.h>

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

raidzz_recover will recover from 1 or 2 errors.  error_mask should
be constructed to indicate what buffers have errors.  num_error should
also be set to 1 or 2.  parity_mask could also indicate which buffer
not to use when recovering from single errors.  Double errors require
2 parity buffers.

The recovered data will be placed into buffers that are pointed to
by the respective entries in the data_table.  The contents of the
recovered buffers will be destroyed and replaced by the "recovered"
data.

The contents of the parity buffers use to recover data will be destroyed.

Return values:

	raidzz_OK				(0) Parity was computed OK
	raidzz_ERR_num_parity		num_parity is out of range
	raidzz_ERR_num_data			num_data is out of range
	raidzz_ERR_unrecoverable	error is unrecoverable
	raidzz_ERR_badparams		the parameters passed in don't make sense

OS KERNEL
---------

The raidzz tables are large, ~73k, and should be placed in non-paged
memory for obvious reasons.

PERFORMANCE
-----------

It is inevitable that the performance of a software based dual
redundantcy system will be slower than single redundantcy system
because two parity buffers need to be computed.  The computation also
requires a function table lookup while a parity system does not. 
However, with faster CPU's and more cache, it is possible to get fairly
good performance.  The algorithms in this implimentation are not the
highest performance possible.  Loop unrolling and cache blocking would
go a long way to improving it's performance.  Some "table" specific
improvements could work.  Emperical data suggests that on a 350Mhz
PII, the data througput is about 2MB/sec through the parity generator.
As a guess, parity generation could be optimized to about 6MB/sec
on this kind of system.

The parity functions can easily be implimented in hardware and
conceptually be made VERY fast.


BACKGROUND
----------

This scheme was concieved sometime in 1993. An article was posted by
Gianni Mariani in comp.arch.storage in 1994 with enough details to
build the first engine for raidzz.  The raidzz parity tables were
computed by using a brute force algorithm.  The mathematical proof
for these formulas is by existance.  The tables are limited to 15
channels of data, it is unclear if there exists tables that are
that can handle more than these.  It is probable that the tables
in raidzz could handle 7 channels with 3 parity redundantcy, there
was some emperical data that the 15 functions to compute the
second parity are also mutually exclusive although this has not
been confirmed.

A similar concept now dubbed RAID-6 was detailed in 1988 by ???.
This work is unrelated but similar.

Why is it called raidzz ?  I originally dubbed it RAID10.  Then
it was suggested to be called RAID6 which it is not. So, it's called
raidzz since it will probably be a while before someone calls it
anything. zz is for "snoozzing" wiating for a name. `z' 'z' is
also the sound when two hard drives go "Zap".  There are so many
good reasons to call it zz that it has stuck after I changed it
from raid10.

