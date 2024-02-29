/*----------------------------------------------------------------------------
	Program : LoadMemberCB.c
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

#define		MEMBER
#include	"acctprivate.h"

static  char    Statement[MAXSTATEMENT];

int LoadMemberCB ( char * WhereClause, char * OrderByClause, XMEMBER *ptrMember, int (*CallBack)(), int PrintErrors )
{
	DBY_QUERY     *MyQuery;
	int		NumberOfRows = 0;
	int		rv;

	// ErrorCount = 0;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from member", FIELDS_MEMBER );

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

	if ( PrintErrors )
	{
		fprintf ( stderr, "%s\n", Statement );
	}

	MyQuery = dbySelect ( "LoadMemberCB", &MySql, Statement, LOGFILENAME );

	if ( MyQuery == (DBY_QUERY *) 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadMemberCB select returned NULL. %s\n", WhereClause );
		}
		return ( -1 );
	}
	else if (( NumberOfRows = MyQuery->NumRows ) == 0 )
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadMemberCB select returned zero rows.\n" );
			fprintf ( stderr, "WhereClause: [%s]\n", WhereClause );
			fprintf ( stderr, "Statement: [%s]\n", Statement );
		}
		dbyFreeQuery ( MyQuery );
		MyQuery = (DBY_QUERY *) 0;
		return ( 0 );
	}
	else 
	{
		if ( PrintErrors )
		{
			fprintf ( stderr, "LoadMemberCB %d rows.\n",  NumberOfRows );
		}

// don't use sprintf (or snprintf) in Load functions, writes (null) if null.
		while (( MyQuery->EachRow = mysql_fetch_row ( MyQuery->Result )) != NULL )
		{
			ptrMember->xid         =  nsAtol( MyQuery->EachRow[MEMBER_id] );
			nsStrcpy ( ptrMember->xmname, MyQuery->EachRow[MEMBER_Mname] );
			nsStrcpy ( ptrMember->xmemail, MyQuery->EachRow[MEMBER_Memail] );
			nsStrcpy ( ptrMember->xmphone, MyQuery->EachRow[MEMBER_Mphone] );
			nsStrcpy ( ptrMember->xmcarrier, MyQuery->EachRow[MEMBER_Mcarrier] );
			nsStrcpy ( ptrMember->xmpassword, MyQuery->EachRow[MEMBER_Mpassword] );
			nsStrcpy ( ptrMember->xmpasstwo, MyQuery->EachRow[MEMBER_Mpasstwo] );
			ptrMember->xmtwopref[0]   =  MyQuery->EachRow[MEMBER_Mtwopref][0];
			ptrMember->xmrole[0]   =  MyQuery->EachRow[MEMBER_Mrole][0];
			nsStrcpy ( ptrMember->xmipaddr, MyQuery->EachRow[MEMBER_Mipaddr] );
			StringToDateval ( MyQuery->EachRow[MEMBER_Minsdt], &ptrMember->xminsdt );
			StringToDateval ( MyQuery->EachRow[MEMBER_Mlogdt], &ptrMember->xmlogdt );
			ptrMember->xinserted =  nsAtol( MyQuery->EachRow[MEMBER_inserted] );
			ptrMember->xupdated  =  nsAtol( MyQuery->EachRow[MEMBER_updated] );

			if ( CallBack != NULL )
			{
				if (( rv = CallBack ( ptrMember )) != 0 )
				{
					break;
				}
			}
		}
	}

	if ( PrintErrors )
	{
		fprintf ( stderr, "LoadMemberCB before free.\n" );
		fflush ( stderr );
	}

	dbyFreeQuery ( MyQuery );
	MyQuery = (DBY_QUERY *) 0;

	if ( PrintErrors )
	{
		fprintf ( stderr, "LoadMemberCB after free.\n" );
		fflush ( stderr );
	}

	return ( NumberOfRows );
}
