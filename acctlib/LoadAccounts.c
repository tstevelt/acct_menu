/*----------------------------------------------------------------------------
	Program : LoadAccounts.c
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

#define		MAXACCOUNT	100
XACCOUNT	AcctsArray[MAXACCOUNT];
int		AcctsCount;

void LoadAccounts ( char *AccountTypes )
{
	DBY_QUERY		*Query;

	/*--------------------------------------------------------------
		get selected accounts from database, save in array.  
	--------------------------------------------------------------*/
	sprintf ( StatementOne, 
		"select %s from account where %s order by accttype, acctnum", FIELDS_ACCOUNT, AccountTypes );

// printf ( "%s<br>\n", StatementOne );

	Query = dbySelect ( "entry", &MySql, StatementOne, LOGFILENAME );

	AcctsCount = 0;
	while (( Query->EachRow = mysql_fetch_row ( Query->Result )) != NULL )
	{
		if ( AcctsCount >= MAXACCOUNT )
		{
			sprintf ( StatementOne, "Exceeds MAXACCOUNT." );
			SaveError ( StatementOne );
			break;
		}

		AcctsArray[AcctsCount].xacctnum = safe_atol ( Query->EachRow[ACCOUNT_acctnum] );
		AcctsArray[AcctsCount].xaccttype[0] = Query->EachRow[ACCOUNT_accttype][0];
		snprintf ( AcctsArray[AcctsCount].xacctname,  30, "%s", Query->EachRow[ACCOUNT_acctname] );
/*
xxx	sprintf ( AcctsArray[AcctsCount].xextranum, "%s", Query->EachRow[ACCOUNT_extranum] );
xxx	sprintf ( AcctsArray[AcctsCount].xextraline, "%s", Query->EachRow[ACCOUNT_extraline] );
*/
		if ( Query->EachRow[ACCOUNT_extranum] == NULL )
		{
			lset ( AcctsArray[AcctsCount].xextranum, " ", sizeof(xaccount.xextranum) );
		}
		else
		{
			sprintf ( AcctsArray[AcctsCount].xextranum, "%s", Query->EachRow[ACCOUNT_extranum] );
		}
		if ( Query->EachRow[ACCOUNT_extraline] == NULL )
		{
			lset ( AcctsArray[AcctsCount].xextraline, " ", sizeof(xaccount.xextraline) );
		}
		else
		{
			sprintf ( AcctsArray[AcctsCount].xextraline, "%s", Query->EachRow[ACCOUNT_extraline] );
		}

		AcctsArray[AcctsCount].xopenbal = safe_atol ( Query->EachRow[ACCOUNT_openbal] );
		AcctsArray[AcctsCount].xcurrbal = safe_atol ( Query->EachRow[ACCOUNT_currbal] );
		StringToDateval ( Query->EachRow[ACCOUNT_recondate], &AcctsArray[AcctsCount].xrecondate );
		AcctsArray[AcctsCount].xreconbal = safe_atol ( Query->EachRow[ACCOUNT_reconbal] );
		AcctsArray[AcctsCount].xdaterange = safe_atos ( Query->EachRow[ACCOUNT_daterange] );

		AcctsCount++;
	}
}
