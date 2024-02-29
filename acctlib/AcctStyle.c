/*----------------------------------------------------------------------------
	Program : AcctStyle.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint the style sheet info in HTML <head>
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

#include	"acctprivate.h"

void AcctStyle ( char *ImageFileName )
{
	printf ( "<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>\n" );
	printf ( "<link rel='stylesheet' href='acct.css'>\n" );

	if ( nsStrlen ( ImageFileName ) > 0 )
	{
		printf ( "<style type='text/css'>\n" );
		printf ( "body {\n" );
		printf ( "background-image: url('images/%s');\n", ImageFileName );
		printf ( "background-repeat: no-repeat;\n" );
		printf ( "background-attachment: fixed;\n" );
		printf ( "background-size: cover;\n" );
		printf ( "}\n" );
		printf ( "</style>\n" );
	}

}
