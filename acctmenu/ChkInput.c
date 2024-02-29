/*----------------------------------------------------------------------------
	Program : ChkInput.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Validate user input
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

int ChkInput ()
{
	int		rv = 0;

	switch ( RunMode )
	{
		case MODE_PAINT_LOGIN:
			break;

		case MODE_EXEC_LOGIN:
			SessionRecord.LoggedIn = 0;
			if ( lastchr ( SessionRecord.DbName, nsStrlen(SessionRecord.DbName) ) == 0 )
			{
				rv = -1;
				RunMode = MODE_PAINT_LOGIN;
				SaveError ( "missing database" );
			}

			if ( lastchr ( SessionRecord.UserName, nsStrlen(SessionRecord.UserName) ) == 0 )
			{
				rv = -1;
				RunMode = MODE_PAINT_LOGIN;
				SaveError ( "missing user name" );
			}

			if ( lastchr ( FormPassword, nsStrlen(FormPassword) ) == 0 )
			{
				rv = -1;
				RunMode = MODE_PAINT_LOGIN;
				SaveError ( "missing password" );
			}
			break;

		case MODE_PAINT_TWO_FACTOR:
			break;

		case MODE_EXEC_TWO_FACTOR:
			if ( lastchr ( TwoFactorCode, nsStrlen(TwoFactorCode) ) != 6 )
			{
				rv = -1;
				RunMode = MODE_PAINT_TWO_FACTOR;
				SaveError ( "missing/invalid code" );
			}
			break;

		case MODE_PAINT_FORGOT:
			break;

		case MODE_EXEC_FORGOT:
			if ( ValidEmailAddress ( ForgotEmail ) == 0 )
			{
				RunMode = MODE_PAINT_FORGOT;
				rv = -1;
				SaveError ( "missing/invalid email address" );
			}
			break;

		case MODE_PAINT_MENU:
			StartDb ( SessionRecord.DbName );
			snprintf ( WhereClause, sizeof(WhereClause), "Mname = '%s'", SessionRecord.UserName );
			LoadMember ( WhereClause, &xmember, 0 );
			break;

		case MODE_EXEC_LOGOUT:
			break;
	}

	return ( rv );
}
