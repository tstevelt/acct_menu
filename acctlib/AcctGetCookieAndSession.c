/*----------------------------------------------------------------------------
	Program : AcctGetCookieAndSession.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Read the cookie, read session record into *SessionRecord
	Return  : void
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

void AcctGetCookieAndSession ( SESSION_RECORD *SessionRecord )
{
	COOKIE_RECORD	*AcctCookie;
	char	CommandLine[1024];
	char	*DocRoot;
	char	*Argv[2];
	int		GlobalDebug = 0;
	FILE	*fpDebug = stderr;

	if ((( AcctCookie = acctGetCookie ( COOKIE_NAME, GlobalDebug, fpDebug )) == (COOKIE_RECORD *)0 ) ||
		( ReadSession ( AcctCookie->SessionID, SessionRecord  ) != 0         ) ||
		( SessionRecord->LoggedIn == 0                                       ))
	{
		DocRoot = getenv ( "DOCUMENT_ROOT" );
		sprintf ( CommandLine, "%s/acctmenu.cgi", DocRoot );

		Argv[0] = CommandLine;
		Argv[1] = (char *)0;
		execvp ( CommandLine, Argv );
	}
}
