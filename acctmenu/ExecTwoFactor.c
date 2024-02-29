/*----------------------------------------------------------------------------
	Program : ExecTwoFactor.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Check the 2FA entry
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

void ExecTwoFactor ()
{
	StartDb ( SessionRecord.DbName );

	snprintf ( WhereClause, sizeof(WhereClause), "Mname = '%s'", SessionRecord.UserName );
	if ( LoadMember ( WhereClause, &xmember, 0 ) != 1 )
	{
		sprintf ( msgbuf, "unknown user %s", SessionRecord.UserName );
		SaveError ( msgbuf );
		RunMode = MODE_PAINT_LOGIN;
		nsStrcpy ( SessionRecord.UserName, "unknown" );
		return;
	}

	if ( nsStrcmp ( TwoFactorCode, xmember.xmpasstwo ) != 0 )
	{
		SaveError ( "code does not match" );
		RunMode = MODE_PAINT_TWO_FACTOR;
		return;
	}

	if ( LicenseInfo.DaysToExpiration < 0 )
	{
		sprintf ( msgbuf, "Software license is expired." );
		SaveError ( msgbuf );
		RunMode = MODE_PAINT_LOGIN;
		SessionRecord.LoggedIn = 0;
		return;
	}

	SessionRecord.LoggedIn = 1;

	UpdateMemberLogin ();

	RunMode = MODE_PAINT_MENU;
}
