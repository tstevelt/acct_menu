/*----------------------------------------------------------------------------
	Program : PaintLogin.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint login screen.
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

void PaintLogin ()
{
	int		Row = 0;

	webStartJava ();

	printf ( "function RunForgot ()\n" );
	printf ( "{\n" );
//	printf ( "alert ( 'hi' );\n" );
	printf ( "var options = 'screenX=10,screenY=10,width=600,height=500,resizable=1,menubar=0,scrollbars=1';\n" );
	printf ( "var w = window.open ( 'acctmenu.cgi?paintForgot=true', 'results', options );\n" );
// https://acct.silverhammersoftware.com/chpw.cgi
	printf ( "}\n" );

	webEndJava ();

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>database</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='database' size='12' value='%s'></td>\n", SessionRecord.DbName );
	printf ( "</tr>\n" );
	Row++;

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>user name</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='username' size='12' value='%s'></td>\n", SessionRecord.UserName );
	printf ( "</tr>\n" );
	Row++;

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>password</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='password' name='password' size='12' value='%s'></td>\n", FormPassword );
	printf ( "</tr>\n" );
	Row++;

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td align='center' colspan='2'>\n" );
	printf ( "<input type='submit' name='submitLogin' value='login'>\n" );
	printf ( "&emsp;<input type='button' name='submitForgot' value='forgot password' onclick='javascript:RunForgot();'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );
	Row++;

}
