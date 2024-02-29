/*----------------------------------------------------------------------------
	Program : LoadArinvlCB.c
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

#define		ARINVL
#include	"acctprivate.h"

static  char    Statement[MAXSTATEMENT];

int LoadArinvlCB ( char * WhereClause, char * OrderByClause, XARINVL *ptrARINVL, int (*CallBack)(), int PrintErrors )
{
	DBY_QUERY     *MyQuery;
	int		NumberOfRows = 0;

	// ErrorCount = 0;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from arinvl", FIELDS_ARINVL );

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
	printf ( "LoadArinvlCB: %s\n", Statement );
	fflush ( stdout );
#endif

	MyQuery = dbySelect ( "LoadArinvlCB", &MySql, Statement, LOGFILENAME );

#ifdef DEBUG
	printf ( "LoadArinvlCB: %s<br>\n", PtrToStr ( (char *) MyQuery ) );
	fflush ( stdout );
#endif 

	if ( MyQuery == (DBY_QUERY *) 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArinvlCB select returned NULL. %s\n", WhereClause );
		}
		return ( -1 );
	}
	else if (( NumberOfRows = MyQuery->NumRows ) == 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArinvlCB select returned zero rows.\n" );
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
			ptrARINVL->xid = nsAtol( MyQuery->EachRow[ARINVL_id] );
			ptrARINVL->xinvoice = nsAtol( MyQuery->EachRow[ARINVL_invoice] );
			snprintf ( ptrARINVL->xdescr, sizeof(ptrARINVL->xdescr), "%s", MyQuery->EachRow[ARINVL_descr] );
			ptrARINVL->xamount = nsAtol ( MyQuery->EachRow[ARINVL_amount] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrARINVL ) != 0 )
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
