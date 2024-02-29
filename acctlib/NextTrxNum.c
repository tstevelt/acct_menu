/*----------------------------------------------------------------------------
	Program : NextTrxNum.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Get the next trx number from the system record.  Increment the
				system record.
	Return  : The next number to use.
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

#define		SYSTEM
#include	"acctprivate.h"

long NextTrxNum ( int UpdateSystem )
{
	long		rv, Affected;
	DBY_QUERY		*Query;

	rv = 0L;

	sprintf ( StatementOne, "select trxnext from system" );

	Query = dbySelect ( "import", &MySql, StatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	xsystem.xtrxnext = safe_atol ( Query->EachRow[0] );

	rv = xsystem.xtrxnext;

	if ( UpdateSystem )
	{
		xsystem.xtrxnext++;

		sprintf ( StatementOne, "update system set trxnext = %ld", xsystem.xtrxnext );
		Affected = dbyUpdate ( "acct", &MySql, StatementOne, 0, LOGFILENAME );
		if ( Affected == 0 )
		{
			SaveError ( "update system next transaction number failed" );
		}
	}

	return ( rv );
}

