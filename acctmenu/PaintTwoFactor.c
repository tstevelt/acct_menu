/*----------------------------------------------------------------------------
	Program : PaintTwoFactor.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: If user prefers 2FA, then tell them code was sent
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

void PaintTwoFactor ()
{
	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td colspan='2'>" );
	switch ( xmember.xmtwopref[0] )
	{
		case 'E':
			printf ( "Code sent to your email" );
			break;
		case 'P':
			printf ( "Code sent to your phone" );
			break;
		case 'N':
		default:
			printf ( "Code preference not set. See admin." );
			break;
	}
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td>code</td>\n" );
	printf ( "<td><input class='w3-pale-red' type='search' name='TwoFactorCode' size='8'></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr class='MenuRow'>\n" );
	printf ( "<td align='center' colspan='2'>" );
	printf ( "<input type='submit' name='submitTwoFactor' value='login'>" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

}
