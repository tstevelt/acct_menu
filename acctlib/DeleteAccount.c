/*----------------------------------------------------------------------------
	Program : DeleteAccount.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Delete a G/L account if it does not have transactions.
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

#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int DeleteAccount ( short AccountNumber )
{
	int		rv = 0;
	DBY_QUERY		*Query;
	int		MyCount;

	/*----------------------------------------------------------
		see if there are transactions, if so, return.
	----------------------------------------------------------*/
	sprintf ( MyStatementOne, 
		"select count(*) from trxd where acctnum = %d", AccountNumber );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		SaveError ( "an error occurred in transaction count, account not deleted." );
		return ( rv );
	}

	if (( MyCount = safe_atoi ( Query->EachRow[0] )) > 0 )
	{
		sprintf (  MyStatementOne, "account has %d transactions, account not deleted.", MyCount );
		SaveError ( MyStatementOne );
		return ( rv );
	}

	/*----------------------------------------------------------
		see if there is an import, if so, delete it
	----------------------------------------------------------*/
	sprintf ( MyStatementOne, 
		"select count(*) from import where acctnum = %d", AccountNumber );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		SaveError ( "an error occurred in transaction count, account not deleted." );
		return ( rv );
	}

	if (( MyCount = safe_atoi ( Query->EachRow[0] )) > 0 )
	{
		if ( DeleteImport ( AccountNumber ) == 0 )
		{
			return ( 0 );
		}
	}

	/*----------------------------------------------------------
		delete the account record
	----------------------------------------------------------*/
	sprintf ( MyStatementOne, 
		"delete from account where acctnum = %d", AccountNumber );
	
	rv = dbyDelete  ( "import", &MySql, MyStatementOne, 0, LOGFILENAME );

	if ( rv == 0 )
	{
		SaveError ( "an error occurred, account not deleted." );
	}
	
	return ( rv );
}
