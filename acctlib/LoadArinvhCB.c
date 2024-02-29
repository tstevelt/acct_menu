/*----------------------------------------------------------------------------
	Program : LoadArinvhCB.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Load <table> with CallBack function
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

#define		ARINVH
#include	"acctprivate.h"

static  char    Statement[MAXSTATEMENT];

int LoadArinvhCB ( char * WhereClause, char * OrderByClause, XARINVH *ptrARINVH, int (*CallBack)(), int PrintErrors )
{
	DBY_QUERY     *MyQuery;
	int		NumberOfRows = 0;

	// ErrorCount = 0;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from arinvh", FIELDS_ARINVH );

	if ( WhereClause != NULL && nsStrlen ( WhereClause ) > 1 && nsStrcmp ( WhereClause, "all" ) != 0 )
	{
		strcat ( Statement, " where " );
		strcat ( Statement, WhereClause );
	}

	if ( OrderByClause != NULL && nsStrlen ( OrderByClause ) > 1 )
	{
		strcat ( Statement, " order by " );
		strcat ( Statement, OrderByClause );
	}

#ifdef DEBUG
#define DEBUG
	printf ( "LoadArinvhCB: %s\n", Statement );
	fflush ( stdout );
#endif

	MyQuery = dbySelect ( "LoadArinvhCB", &MySql, Statement, LOGFILENAME );

#ifdef DEBUG
	printf ( "LoadArinvhCB: %s<br>\n", PtrToStr ( (char *) MyQuery ) );
	fflush ( stdout );
#endif 

	if ( MyQuery == (DBY_QUERY *) 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArinvhCB select returned NULL. %s\n", WhereClause );
		}
		return ( -1 );
	}
	else if (( NumberOfRows = MyQuery->NumRows ) == 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArinvhCB select returned zero rows.\n" );
			fprintf ( stderr, "WhereClause: [%s]\n", WhereClause );
			fprintf ( stderr, "Statement: [%s]\n", Statement );
		}
		dbyFreeQuery ( MyQuery );
		MyQuery = (DBY_QUERY *) 0;
		return ( 0 );
	}
	else 
	{
		while (( MyQuery->EachRow = mysql_fetch_row ( MyQuery->Result )) != NULL )
		{
			ptrARINVH->xid = nsAtol( MyQuery->EachRow[ARINVH_id] );
			ptrARINVH->xcustomer = nsAtol( MyQuery->EachRow[ARINVH_customer] );
			StringToDateval ( MyQuery->EachRow[ARINVH_invdate], &ptrARINVH->xinvdate );
			snprintf ( ptrARINVH->xterms, sizeof(ptrARINVH->xterms), "%s", MyQuery->EachRow[ARINVH_terms] );
			snprintf ( ptrARINVH->xstatus, sizeof(ptrARINVH->xstatus), "%s", MyQuery->EachRow[ARINVH_status] );
			snprintf ( ptrARINVH->xponum, sizeof(ptrARINVH->xponum), "%s", MyQuery->EachRow[ARINVH_ponum] );
			ptrARINVH->xdiscount = nsAtol( MyQuery->EachRow[ARINVH_discount] );
			ptrARINVH->xpayment = nsAtol( MyQuery->EachRow[ARINVH_payment] );
			snprintf ( ptrARINVH->xrefnum, sizeof(ptrARINVH->xrefnum), "%s", MyQuery->EachRow[ARINVH_refnum] );
			StringToDateval ( MyQuery->EachRow[ARINVH_paydate], &ptrARINVH->xpaydate );
			ptrARINVH->xinserted = nsAtol( MyQuery->EachRow[ARINVH_inserted] );
			ptrARINVH->xupdated = nsAtol( MyQuery->EachRow[ARINVH_updated] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrARINVH ) != 0 )
				{
					break;
				}
			}
		}
	}

	dbyFreeQuery ( MyQuery );
	MyQuery = (DBY_QUERY *) 0;

	return ( NumberOfRows );
}
