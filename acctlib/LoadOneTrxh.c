/*----------------------------------------------------------------------------
	Program : LoadOneTrxh.c
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

#define		TRXH
#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int LoadOneTrxh ( long TrxNumber )
{
	DBY_QUERY		*Query;

	sprintf ( MyStatementOne, 
		"select %s from trxh where trxnum = %ld", 
					FIELDS_TRXH, TrxNumber );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	xtrxh.xtrxnum = safe_atol ( Query->EachRow[TRXH_trxnum] );
	xtrxh.xstatus = safe_atos ( Query->EachRow[TRXH_status] );
	sprintf ( xtrxh.xrefnum, "%s", Query->EachRow[TRXH_refnum] );
	StringToDateval ( Query->EachRow[TRXH_trxdate], &xtrxh.xtrxdate );

	return ( 1 );
}
