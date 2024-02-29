/*----------------------------------------------------------------------------
	Program : LoadOneTrxd.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Load <table>
	Return  : 
----------------------------------------------------------------------------*/
//     Accounting Menu
// 
//     Copyright (C)  2000-2024 Tom Stevelt
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.
// 
//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#define		TRXD
#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int LoadOneTrxd ( long TrxNumber, int SeqNumber )
{
	DBY_QUERY		*Query;

	sprintf ( MyStatementOne, 
		"select %s from trxd where trxnum = %ld and seqnum = %d", 
					FIELDS_TRXD, TrxNumber, SeqNumber );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	xtrxd.xtrxnum = safe_atol ( Query->EachRow[TRXD_trxnum] );
	xtrxd.xseqnum = safe_atos ( Query->EachRow[TRXD_seqnum] );
	xtrxd.xacctnum = safe_atol ( Query->EachRow[TRXD_acctnum] );
	sprintf ( xtrxd.xpayee, "%s", Query->EachRow[TRXD_payee] );
	xtrxd.xamount = safe_atol ( Query->EachRow[TRXD_amount] );

	return ( 1 );
}
