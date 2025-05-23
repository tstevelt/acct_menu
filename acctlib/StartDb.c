/*----------------------------------------------------------------------------
	Program : StartDb.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Connect to mysql/mariadb database
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

static	int		DebugStartDb = 0;

int StartDb ( char *DbName )
{
	static	int		CheckStatus = 1;
			int		rv;
		   WEBPARMS    *ptrWebParms;

//	rv = dbyConnect ( &MySql, DbName, "tms", CheckStatus, stderr );
	rv = dbyConnect ( &MySql, DbName, "tms", CheckStatus, stdout );

	if ( DebugStartDb )
	{
		printf ( "StartDb: dbyConnect returned %d<br>\n", rv );
		printf ( "StartDb: DbName %s, User %s, CheckStatus %d<br>\n", DbName, "tms", CheckStatus );
	}

	if ( rv != DBY_CONN_SUCCESS )
	{
    	ptrWebParms = webInitParms ();
		webContentHtml ();
		ptrWebParms->WP_Title = "Connect Error";
		webStartHead ( ptrWebParms );

		printf ( "%s<br>\n", mysql_error(&MySql) );
		printf ( "%s<br>\n", dbyConnectErrorStr(rv) );
		
		webEndPage ();

		exit ( 0 );
	}
	return ( 0 );
}
