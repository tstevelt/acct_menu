/*----------------------------------------------------------------------------
	Program : CalcTrxBalance.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Calculate transaction balance for all the detail for given trx.
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
#define		TRXD
#include	"acctprivate.h"

static	char		MyStatementOne[4096];
static	char		MyStatementTwo[4096];

long CalcTrxBalance ( long TrxNumber )
{
	DBY_QUERY		*QueryOne;
	DBY_QUERY		*QueryTwo;
	long			DebitSum, CreditSum, TrxBalance;

	sprintf ( MyStatementOne, 
		"select sum(amount) from trxd, account where trxd.acctnum = account.acctnum and trxnum = %ld",
			TrxNumber );

	snprintf ( MyStatementTwo, sizeof(MyStatementTwo), "%s and accttype in ( 'A', 'X' )", MyStatementOne );

	QueryOne = dbySelect ( "acct", &MySql, MyStatementTwo, LOGFILENAME );
	if (( QueryOne->EachRow = mysql_fetch_row ( QueryOne->Result )) == NULL )
	{
		DebitSum = 0L;
	}
	else
	{
		DebitSum = safe_atol ( QueryOne->EachRow[0] );
	}

	snprintf ( MyStatementTwo, sizeof(MyStatementTwo), "%s and accttype in ( 'L', 'E', 'I' )", MyStatementOne );

	QueryTwo = dbySelect ( "acct", &MySql, MyStatementTwo, LOGFILENAME );
	if (( QueryTwo->EachRow = mysql_fetch_row ( QueryTwo->Result )) == NULL )
	{
		CreditSum = 0L;
	}
	else
	{
		CreditSum = safe_atol ( QueryTwo->EachRow[0] );
	}

	TrxBalance = DebitSum - CreditSum;

	return ( TrxBalance );
}
