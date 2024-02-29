/*----------------------------------------------------------------------------
	Program : PaintShowLicense.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint popup showing license information.
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

#include	"acctmenu.h"

extern	LICENSE_RECORD	LicenseInfo;

void PaintShowLicense ()
{
	int		ndx;

	for ( ndx = 0; ndx < nsStrlen(LicenseInfo.AppString); ndx++ )
	{
		if ( isdigit(LicenseInfo.AppString[ndx]) )
		{
			LicenseInfo.AppString[ndx] = ' ';
		}
	}

	webStartJava ();

	printf ( "function ShowLicense ()\n" );

	printf ( "{\n" );

	// printf ( "var options = 'screenX=10,screenY=10,width=700,height=300,resizable=1,menubar=0,scrollbars=1';\n" );
	printf ( "var options = 'width=300,height=150,resizable=0,menubar=0,scrollbars=0';\n" );
    printf ( "var w = window.open ( '', 'results', options );\n" );
    printf ( "var d = w.document;\n" );

	printf ( "d.writeln ( '<!DOCTYPE HTML>' );\n" );
	printf ( "d.writeln ( '<html>' );\n" );
	printf ( "d.writeln ( '<head>' );\n" );
	printf ( "d.writeln ( '<title>license info</title>' );\n" );
	printf ( "d.writeln ( '</head>' );\n" );
	printf ( "d.writeln ( '<body>' );\n" );
	printf ( "d.writeln ( '<p>' );\n" );
	printf ( "d.writeln ( 'Database %s<br>' );\n", LicenseInfo.Database );
	printf ( "d.writeln ( 'App String %s<br>' );\n", LicenseInfo.AppString );
	printf ( "d.writeln ( 'Expires %d/%d/%d<br>' );\n", 
			LicenseInfo.ExpirationDate.month, LicenseInfo.ExpirationDate.day, LicenseInfo.ExpirationDate.year4 );
	printf ( "d.writeln ( 'Days %d<br>' );\n", LicenseInfo.DaysToExpiration );
	printf ( "d.writeln ( 'Host %s<br>' );\n", getenv("HTTP_HOST") );
	printf ( "d.writeln ( 'Cookie %s<br>' );\n", getenv("HTTP_COOKIE") );
	printf ( "d.writeln ( 'Server %s<br>' );\n", getenv("SERVER_ADDR") );
	printf ( "d.writeln ( 'Client %s<br>' );\n", getenv("REMOTE_ADDR") );
	printf ( "d.writeln ( 'User %s<br>' );\n", SessionRecord.UserName );
	printf ( "d.writeln ( 'SessionID %s<br>' );\n", SessionRecord.SessionID );
	printf ( "d.writeln ( '</body>' );\n" );
	printf ( "d.writeln ( '</html>' );\n" );

	printf ( "d.close ();\n" );

	printf ( "}\n" );
	webEndJava ();
}
