/*----------------------------------------------------------------------------
	Program : PaintForgot.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint screen for user who forgot their paassword.
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

void PaintForgot ()
{
//	printf ( "<div class='acct-display-topmiddle w3-full w3-padding'>\n" );
//	printf ( "<div class='w3-padding w3-border w3-opacity-min w3-white w3-text-black w3-center'>\n" );
//	printf ( "<table class='AppMedium'>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>database</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='database' size='12' value='%s'></td>\n", SessionRecord.DbName );
	printf ( "</tr>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>user&nbsp;name</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='username' size='12' value='%s'></td>\n", SessionRecord.UserName );
	printf ( "</tr>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>email</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='forgotemail' size='40' maxlength='59'></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td align='center' colspan='2'>" );
	printf ( "<input type='submit' name='submitForgot' value='send instructions'>" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

//	printf ( "</table>\n" );
//	printf ( "</div>\n" );
//	printf ( "</div>\n" );
}
