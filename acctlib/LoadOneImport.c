/*----------------------------------------------------------------------------
	Program : LoadOneImport.c
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

#define		IMPORT
#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int LoadOneImport ( int AccountNumber )
{
	DBY_QUERY		*Query;

	memset ( &ximport, 0, sizeof(ximport) );

	sprintf ( MyStatementOne, 
		"select %s from import where acctnum = %d", FIELDS_IMPORT, AccountNumber );

// printf ( "%s<br>\n", MyStatementOne );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	ximport.xacctnum = safe_atol ( Query->EachRow[IMPORT_acctnum] );
	if ( Query->EachRow[IMPORT_website] != NULL )
	{
		sprintf ( ximport.xwebsite, "%s", Query->EachRow[IMPORT_website] );
	}
	if ( Query->EachRow[IMPORT_login] != NULL )
	{
		sprintf ( ximport.xlogin, "%s", Query->EachRow[IMPORT_login] );
	}
	StringToDateval ( Query->EachRow[IMPORT_previous], &ximport.xprevious );
	ximport.xpayments[0] = Query->EachRow[IMPORT_payments][0];

	ximport.xreverse[0] = Query->EachRow[IMPORT_reverse][0];

#ifdef VERSION_ONE
	ximport.xautoparse[0] = Query->EachRow[IMPORT_autoparse][0];
	sprintf ( ximport.xparsefunc, "%s", Query->EachRow[IMPORT_parsefunc] );
	ximport.xheadrows = (short) safe_atos ( Query->EachRow[IMPORT_headrows] );
	ximport.xcolcount = (short) safe_atos ( Query->EachRow[IMPORT_colcount] );
	ximport.xrefnum = (short) safe_atos ( Query->EachRow[IMPORT_refnum] );
	ximport.xdate = (short) safe_atos ( Query->EachRow[IMPORT_date] );
	ximport.xpayee = (short) safe_atos ( Query->EachRow[IMPORT_payee] );
	ximport.xincrease = (short) safe_atos ( Query->EachRow[IMPORT_increase] );
	ximport.xincsign[0] = Query->EachRow[IMPORT_incsign][0];
	ximport.xdecrease = (short) safe_atos ( Query->EachRow[IMPORT_decrease] );
	ximport.xdecsign[0] = Query->EachRow[IMPORT_decsign][0];
#endif

	return ( 1 );
}
