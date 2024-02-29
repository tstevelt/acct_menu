/*----------------------------------------------------------------------------
	Program : LoadArcustCB.c
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

#define		ARCUST
#include	"acctprivate.h"

static  char    Statement[MAXSTATEMENT];

#define DEBUG
#undef DEBUG

int LoadArcustCB ( char * WhereClause, char * OrderByClause, XARCUST *ptrARCUST, int (*CallBack)(), int PrintErrors )
{
	DBY_QUERY     *MyQuery;
	int		NumberOfRows = 0;
	int			rv;

	// ErrorCount = 0;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from arcust", FIELDS_ARCUST );

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
	printf ( "LoadArcustCB: %s<br>\n", Statement );
	fflush ( stdout );
#endif

	MyQuery = dbySelect ( "LoadArcustCB", &MySql, Statement, LOGFILENAME );

#ifdef DEBUG
	printf ( "LoadArcustCB: %s<br>\n", PtrToStr ( (char *) MyQuery ) );
	fflush ( stdout );
#endif 

	if ( MyQuery == (DBY_QUERY *) 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArcustCB select returned NULL. %s\n", WhereClause );
		}
#ifdef DEBUG
	printf ( "LoadArcustCB: MyQuery is NULL<br>\n" );
	fflush ( stdout );
#endif 
		return ( -1 );
	}
	else if (( NumberOfRows = MyQuery->NumRows ) == 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadArcustCB select returned zero rows.\n" );
			fprintf ( stderr, "WhereClause: [%s]\n", WhereClause );
			fprintf ( stderr, "Statement: [%s]\n", Statement );
		}
		dbyFreeQuery ( MyQuery );
		MyQuery = (DBY_QUERY *) 0;
#ifdef DEBUG
	printf ( "LoadArcustCB: NumRows is ZERO<br>\n" );
	fflush ( stdout );
#endif 
		return ( 0 );
	}
	else 
	{
		while (( MyQuery->EachRow = mysql_fetch_row ( MyQuery->Result )) != NULL )
		{
			ptrARCUST->xid = nsAtol( MyQuery->EachRow[ARCUST_id] );
			snprintf ( ptrARCUST->xname, sizeof(ptrARCUST->xname), "%s", MyQuery->EachRow[ARCUST_name] );
			snprintf ( ptrARCUST->xaddr1, sizeof(ptrARCUST->xaddr1), "%s", MyQuery->EachRow[ARCUST_addr1] );
			// snprintf ( ptrARCUST->xaddr2, sizeof(ptrARCUST->xaddr2), "%s", MyQuery->EachRow[ARCUST_addr2] );
			nsStrcpy ( ptrARCUST->xaddr2, MyQuery->EachRow[ARCUST_addr2] );
			snprintf ( ptrARCUST->xcity, sizeof(ptrARCUST->xcity), "%s", MyQuery->EachRow[ARCUST_city] );
			snprintf ( ptrARCUST->xstate, sizeof(ptrARCUST->xstate), "%s", MyQuery->EachRow[ARCUST_state] );
			snprintf ( ptrARCUST->xzipcode, sizeof(ptrARCUST->xzipcode), "%s", MyQuery->EachRow[ARCUST_zipcode] );
			snprintf ( ptrARCUST->xphone, sizeof(ptrARCUST->xphone), "%s", MyQuery->EachRow[ARCUST_phone] );
			snprintf ( ptrARCUST->xcontact, sizeof(ptrARCUST->xcontact), "%s", MyQuery->EachRow[ARCUST_contact] );

#ifdef DEBUG
	printf ( "LoadArcustCB: Got %ld<br>\n", ptrARCUST->xid );
	fflush ( stdout );
#endif 
			if ( CallBack != NULL )
			{
#ifdef DEBUG
	printf ( "LoadArcustCB: Calling CallBack<br>\n" );
	fflush ( stdout );
#endif 
				if (( rv = CallBack ( ptrARCUST )) != 0 )
				{
#ifdef DEBUG
	printf ( "LoadArcustCB: CallBack returned %d<br>\n", rv );
	fflush ( stdout );
#endif 
					break;
				}
			}
		}
	}

	dbyFreeQuery ( MyQuery );
	MyQuery = (DBY_QUERY *) 0;

#ifdef DEBUG
	printf ( "LoadArcustCB: Return %d<br>\n", NumberOfRows );
	fflush ( stdout );
#endif 

	return ( NumberOfRows );
}
