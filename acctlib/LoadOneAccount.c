/*----------------------------------------------------------------------------
	Program : LoadOneAccount.c
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

#define		ACCOUNT
#include	"acctprivate.h"

static	char		MyStatementOne[4096];
static	int			DebugLoadOneAccount = 0;

int LoadOneAccount ( int AccountNumber )
{
	DBY_QUERY		*Query;

	snprintf ( MyStatementOne, sizeof ( MyStatementOne ), 
		"select %s from account where acctnum = %d", FIELDS_ACCOUNT, AccountNumber );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}
	
	if ( DebugLoadOneAccount )
	{
		printf ( "%s<br>\n", MyStatementOne );
	}

	xaccount.xacctnum = safe_atol ( Query->EachRow[ACCOUNT_acctnum] );
	xaccount.xaccttype[0] = Query->EachRow[ACCOUNT_accttype][0];
	snprintf ( xaccount.xacctname, sizeof ( xaccount.xacctname ),
					"%s", Query->EachRow[ACCOUNT_acctname] );
	if ( Query->EachRow[ACCOUNT_extranum] == NULL )
	{
		lset ( xaccount.xextranum, " ", sizeof(xaccount.xextranum) );
	}
	else
	{
		snprintf ( xaccount.xextranum, sizeof ( xaccount.xextranum ),
						"%s", Query->EachRow[ACCOUNT_extranum] );
	}
	if ( Query->EachRow[ACCOUNT_extraline] == NULL )
	{
		lset ( xaccount.xextraline, " ", sizeof(xaccount.xextraline) );
	}
	else
	{
		snprintf ( xaccount.xextraline, sizeof ( xaccount.xextraline ),
						"%s", Query->EachRow[ACCOUNT_extraline] );
	}
	xaccount.xopenbal = safe_atol ( Query->EachRow[ACCOUNT_openbal] );
	xaccount.xcurrbal = safe_atol ( Query->EachRow[ACCOUNT_currbal] );
	StringToDateval ( Query->EachRow[ACCOUNT_recondate], &xaccount.xrecondate );
	xaccount.xreconbal = safe_atol ( Query->EachRow[ACCOUNT_reconbal] );
	xaccount.xdaterange = safe_atos ( Query->EachRow[ACCOUNT_daterange] );

	if ( DebugLoadOneAccount )
	{
		printf ( "%ld<br>\n", xaccount.xreconbal );
	}

	return ( 1 );
}
