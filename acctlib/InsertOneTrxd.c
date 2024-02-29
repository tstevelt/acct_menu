/*----------------------------------------------------------------------------
	Program : InsertOneTrxd.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Insert one trxd record and update associate account balance
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

int InsertOneTrxd ( XTRXD *NewTrxd )
{
	int		rv = 0;
	int		Affected;

	sprintf ( MyStatementOne,
		"insert into trxd (trxnum,seqnum,acctnum,payee,amount) values ( %ld,   %d,    %ld,   '%s',  %ld )",
				NewTrxd->xtrxnum,
				NewTrxd->xseqnum,
				NewTrxd->xacctnum,
				NewTrxd->xpayee,
				NewTrxd->xamount  );
				
	Affected = dbyInsert ( "import", &MySql, MyStatementOne, 0, LOGFILENAME );
	if ( Affected > 0 )
	{
		rv = 1;

		sprintf ( MyStatementOne,
			"update account set currbal = currbal + %ld where acctnum = %ld",
				NewTrxd->xamount, NewTrxd->xacctnum );

		Affected = dbyUpdate ( "import", &MySql, MyStatementOne, 0, LOGFILENAME );
		if ( Affected == 0 )
		{
			SaveError ( "update account current balance failed" );
		}
	}

	return ( rv );
}
