/*----------------------------------------------------------------------------
	Program : LoadSystem.c
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

#define		SYSTEM
#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int LoadSystem ( void )
{
	DBY_QUERY		*Query;

	sprintf ( MyStatementOne, 
		"select %s from system", FIELDS_SYSTEM );

	Query = dbySelect ( "import", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	snprintf ( xsystem.xname, sizeof(xsystem.xname), "%s", Query->EachRow[SYSTEM_name] );
	snprintf ( xsystem.xaddress, sizeof(xsystem.xaddress), "%s", Query->EachRow[SYSTEM_address] );
	snprintf ( xsystem.xcity, sizeof(xsystem.xcity), "%s", Query->EachRow[SYSTEM_city] );
	snprintf ( xsystem.xstate, sizeof(xsystem.xstate), "%s", Query->EachRow[SYSTEM_state] );
	snprintf ( xsystem.xzipcode, sizeof(xsystem.xzipcode), "%s", Query->EachRow[SYSTEM_zipcode] );
	snprintf ( xsystem.xphone , sizeof(xsystem.xphone ), "%s", Query->EachRow[SYSTEM_phone] );
	xsystem.xassetnext   = safe_atol ( Query->EachRow[SYSTEM_assetnext] );
	xsystem.xliabnext    = safe_atol ( Query->EachRow[SYSTEM_liabnext] );
	xsystem.xequitynext  = safe_atol ( Query->EachRow[SYSTEM_equitynext] );
	xsystem.xincomenext  = safe_atol ( Query->EachRow[SYSTEM_incomenext] );
	xsystem.xexpensenext = safe_atol ( Query->EachRow[SYSTEM_expensenext] );
	xsystem.xtrxnext = safe_atol ( Query->EachRow[SYSTEM_trxnext] );
	xsystem.xshowamts[0] = Query->EachRow[SYSTEM_showamts][0];
	StringToDateval ( Query->EachRow[SYSTEM_closedate], &xsystem.xclosedate );
	xsystem.xreconcile[0] = Query->EachRow[SYSTEM_reconcile][0];
	xsystem.xprintdest[0] = Query->EachRow[SYSTEM_printdest][0];
	xsystem.xnumtrxnew = (short) safe_atos ( Query->EachRow[SYSTEM_numtrxnew] );
	xsystem.xnumtrxedit = (short) safe_atos ( Query->EachRow[SYSTEM_numtrxedit] );
	xsystem.xtwofactor[0] = Query->EachRow[SYSTEM_twofactor][0];

	xsystem.xtrxpermonth = (short) safe_atos ( Query->EachRow[SYSTEM_trxpermonth] );
	StringToDateval ( Query->EachRow[SYSTEM_trxstartdate], &xsystem.xtrxstartdate );
	xsystem.xtrxstarttrx = (long) safe_atol ( Query->EachRow[SYSTEM_trxstarttrx] );
	xsystem.xtrxrollover = (short) safe_atos ( Query->EachRow[SYSTEM_trxrollover] );

	xsystem.xclosemethod[0] = Query->EachRow[SYSTEM_closemethod][0];
	xsystem.xretainequity = (short) safe_atos ( Query->EachRow[SYSTEM_retainequity] );
	xsystem.xretainincome = (short) safe_atos ( Query->EachRow[SYSTEM_retainincome] );
	return ( 1 );
}
