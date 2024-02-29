/*----------------------------------------------------------------------------
	Program : LoadOneRpt.c
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

#define		RPT
#include	"acctprivate.h"

static	char		MyStatementOne[4096];

int LoadOneRpt ( char RptName[], char AccountType )
{
	DBY_QUERY		*Query;

	sprintf ( MyStatementOne, 
		"select %s from rpt where rptname = '%s' and accttype = '%c'", 
				FIELDS_RPT, RptName, AccountType );

	Query = dbySelect ( "acctlib", &MySql, MyStatementOne, LOGFILENAME );

	if (( Query->EachRow = mysql_fetch_row ( Query->Result )) == NULL )
	{
		return ( 0 );
	}

	sprintf ( xrpt.xrptname, "%s", Query->EachRow[RPT_rptname] );
	sprintf ( xrpt.xtitle,   "%s", Query->EachRow[RPT_title] );
	StringToDateval ( Query->EachRow[RPT_startdate], &xrpt.xstartdate );
	StringToDateval ( Query->EachRow[RPT_enddate  ], &xrpt.xenddate   );
	xrpt.xaccttype[0] = Query->EachRow[RPT_accttype][0];

	return ( 1 );
}
