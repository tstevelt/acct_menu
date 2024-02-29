/*----------------------------------------------------------------------------
	Program : AddDoubleEntryTrx.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Add a double entry transaction
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

void AddDoubleEntryTrx ( long AcctOne, double AmtOne,  long AcctTwo, double AmtTwo, char *Ref, char *Payee, DATEVAL Date )
{
	long	TrxNum = 1;
	long	Affected;

	/*----------------------------------------------------------
		get next trx num
	----------------------------------------------------------*/
	TrxNum = NextTrxNum ( 1 );

	/*----------------------------------------------------------
		insert header trx
	----------------------------------------------------------*/
	sprintf ( StatementOne, 
		"insert into trxh (trxnum,status,refnum,trxdate) values ( %ld, %d, '%s', '%04d-%02d-%02d' )",
			TrxNum, STATUS_OPEN, Ref, Date.year4, Date.month, Date.day );
	dbyInsert ( "acctdemo", &MySql, StatementOne, 0, LOGFILENAME );

	/*----------------------------------------------------------
		insert detail trx one
	----------------------------------------------------------*/
	sprintf ( StatementOne,
		"insert into trxd ( trxnum,seqnum,acctnum,payee,amount) values ( %ld, 1, %ld, '%s', %ld )",
			TrxNum, AcctOne, Payee, (long) (AmtOne * 100.0) );
	dbyInsert ( "acctdemo", &MySql, StatementOne, 0, LOGFILENAME );

	/*----------------------------------------------------------
		update account one balance
	----------------------------------------------------------*/
	sprintf ( StatementOne, "update account set currbal = currbal + %ld where acctnum = %ld",
					(long) (AmtOne * 100.0), AcctOne );
	Affected = dbyUpdate ( "acct", &MySql, StatementOne, 0, LOGFILENAME );
	if ( Affected == 0 )
	{
		SaveError ( "update account one failed" );
	}
			
	/*----------------------------------------------------------
		insert detail trx two
	----------------------------------------------------------*/
	sprintf ( StatementOne,
		"insert into trxd ( trxnum,seqnum,acctnum,payee,amount) values ( %ld, 2, %ld, '%s', %ld )",
			TrxNum, AcctTwo, Payee, (long) (AmtTwo * 100.0) );
	dbyInsert ( "acctdemo", &MySql, StatementOne, 0, LOGFILENAME );

	/*----------------------------------------------------------
		update account two balance
	----------------------------------------------------------*/
	sprintf ( StatementOne, "update account set currbal = currbal + %ld where acctnum = %ld",
					(long) (AmtTwo * 100.0), AcctTwo );
	Affected = dbyUpdate ( "acct", &MySql, StatementOne, 0, LOGFILENAME );
	if ( Affected == 0 )
	{
		SaveError ( "update account two failed" );
	}
			
}
