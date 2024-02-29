/*----------------------------------------------------------------------------
	Program : SessionFuncs.c
	Author  : Tom Stevelt
	Date    : 01/11/2021
	Synopsis: Read Write [Dump] Session Record 
	Return  : 0 on success, -1 on failure.
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

int ReadSession ( char SessionID[], SESSION_RECORD *sr )
{
	char	fn[256];
	FILE	*fp;
	int		rv;

	sprintf ( fn, "%s/%s.sr", RW_DIRECTORY, SessionID );
	if (( fp = fopen ( fn, "r" )) == (FILE *)0 )
	{
		fprintf ( stderr, "Cannot open session %s\n", fn );
		return ( -1 );
	}

	rv = fread ( sr, sizeof(SESSION_RECORD), 1, fp );

	fclose ( fp );

	if ( rv != 1 )
	{
		fprintf ( stderr, "Read session rv %d\n", rv );
		return ( -1 );
	}

	return ( 0 );
}

int WriteSession ( SESSION_RECORD *sr )
{
	char	fn[256];
	FILE	*fp;
	int		rv;

	sprintf ( fn, "%s/%s.sr", RW_DIRECTORY, sr->SessionID );
	if (( fp = fopen ( fn, "w" )) == (FILE *)0 )
	{
		fprintf ( stderr, "Cannot create session %s\n", fn );
		return ( -1 );
	}

	rv = fwrite ( sr, sizeof(SESSION_RECORD), 1, fp );

	fclose ( fp );

	if ( rv != 1 )
	{
		fprintf ( stderr, "Write session rv %d\n", rv );
		return ( -1 );
	}

	return ( 0 );
}

int DeleteSession ( SESSION_RECORD *sr )
{
	char	fn[256];
	int		rv;

	sprintf ( fn, "%s/%s.sr", RW_DIRECTORY, sr->SessionID );
	rv = unlink ( fn );
	if ( rv != 0 )
	{
		fprintf ( stderr, "unlink %s failed, %s\n", fn, strerror(errno) );
	}
	return ( rv );
}

void DumpSession ( SESSION_RECORD *sr )
{
	printf ( "SessionID   %s\n", sr->SessionID );
	printf ( "DbName      %s\n", sr->DbName );
	printf ( "UserName    %s\n", sr->UserName );
	printf ( "MemberID    %ld\n", sr->MemberID );
	printf ( "LoggedIn    %d\n", sr->LoggedIn );
	printf ( "CurrentMenu %d\n", sr->CurrentMenu );
	printf ( "HasGL       %d\n", sr->HasGL );
	printf ( "HasAR       %d\n", sr->HasAR );
	printf ( "HasAP       %d\n", sr->HasAP );
	printf ( "HasIC       %d\n", sr->HasIC );
	printf ( "HasAM       %d\n", sr->HasAM );
}


