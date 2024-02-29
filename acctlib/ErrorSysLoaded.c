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

static	char		MyStatementOne[4096];

void ErrorSysLoaded  ( char *FunctionName )
{
	int		xe, xl;

	webStartJava ();

	printf ( "function %s ()\n", FunctionName );
	printf ( "{\n" );

	if ( AcctErrorCount == 0 || UseErrorSys == 0 )
	{
		printf ( "window.focus();\n" );
	}
	else
	{
		memset ( MyStatementOne, 0, sizeof(MyStatementOne) );

		for ( xe = 0; xe < AcctErrorCount; xe++ )
		{
			xl = nsStrlen ( MyStatementOne );
			if ( xl + nsStrlen(AcctErrorArray[xe]) + 2 > 4096 )
			{
				break;
			}
			sprintf ( &MyStatementOne[xl], "%s\\n", AcctErrorArray[xe] );
		}

		printf ( "alert ( '%s' );\n", MyStatementOne );
	}

	printf ( "}\n" );
	webEndJava ();
}
