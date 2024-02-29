/*----------------------------------------------------------------------------
	Program : ExecLogin.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Login the user. If user prefers 2FA, the paint 2FA prompt.
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

void ExecLogin ()
{
	int			xl, xi, xn;
	char		Salt[20];
	char		FormEncrypted [41];
	
	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: start\n" );
		fflush ( fpDebug );
	}

	StartDb ( SessionRecord.DbName );

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: db start okay\n" );
		fflush ( fpDebug );
	}

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: before load system\n" );
		fflush ( fpDebug );
	}

	LoadSystem ();

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: load system okay\n" );
		fflush ( fpDebug );
	}

	snprintf ( WhereClause, sizeof(WhereClause), "Mname = '%s'", SessionRecord.UserName );
	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: %s\n", WhereClause );
		fflush ( fpDebug );
	}
	if ( LoadMember ( WhereClause, &xmember, 0 ) != 1 )
	{
		sprintf ( msgbuf, "unknown user %s on db %s", SessionRecord.UserName, SessionRecord.DbName );
		SaveError ( msgbuf );
		RunMode = MODE_PAINT_LOGIN;
		nsStrcpy ( SessionRecord.UserName, "unknown" );
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "ExecLogin: LoadMember failed\n" );
			fflush ( fpDebug );
		}
		return;
	}

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ExecLogin: Loaded %s password %s\n", xmember.xmname, xmember.xmpassword );
		fflush ( fpDebug );
	}

	/*--------------------------------------------------------------
		if xmember.xmpassword starts with $1$, then check for 
		MD5 crypt password.
	--------------------------------------------------------------*/
	if ( nsStrncmp ( xmember.xmpassword, "$1$", 3 ) == 0 )
	{
		for ( xi = 0, xl = sizeof(Salt) - 1, xn = 0;
			  xi < xl; 
			  xi++ )
		{
			Salt[xi] = xmember.xmpassword[xi];
			if ( Salt[xi] == '$' )
			{
				xn++;
				if ( xn == 3 )
				{
					xi++;
					break;
				}
			}
		}
		Salt[xi] = '\0';

		sprintf ( FormEncrypted, "%s", crypt ( FormPassword, Salt ) );

		if ( nsStrcmp ( xmember.xmpassword, FormEncrypted ) == 0 )
		{
			SessionRecord.LoggedIn = 1;
			SessionRecord.MemberID = xmember.xid;
		}
	}
	/*--------------------------------------------------------------
		if xmember.xmpassword is 40 char long, then check for basic
		SHA1 password.
	--------------------------------------------------------------*/
	else if ( nsStrlen ( xmember.xmpassword ) == 40 )
	{
		if ( nsStrcmp ( xmember.xmpassword, (char *)pw_sha_make_pw((unsigned char *)FormPassword)  ) == 0 )
		{
			SessionRecord.LoggedIn = 1;
			SessionRecord.MemberID = xmember.xid;
		}

	}
	/*--------------------------------------------------------------
		if xmember.xmpassword is 13 char long, then check for basic
		crypt password. 2 character salt.
	--------------------------------------------------------------*/
	else if ( nsStrlen ( xmember.xmpassword ) == 13 )
	{
		sprintf ( Salt, "%2.2s", xmember.xmpassword );
		sprintf ( FormEncrypted, "%s", crypt ( FormPassword, Salt ) );

		if ( nsStrcmp ( xmember.xmpassword, FormEncrypted ) == 0 )
		{
			SessionRecord.LoggedIn = 1;
			SessionRecord.MemberID = xmember.xid;
		}

	}
#define ALLOW_PLAIN_TEXT_PASSWORDS
#ifdef ALLOW_PLAIN_TEXT_PASSWORDS
	/*--------------------------------------------------------------
		check for plain text match
	--------------------------------------------------------------*/
	else if ( nsStrcmp ( xmember.xmpassword, FormPassword ) == 0 )
	{
		SessionRecord.LoggedIn = 1;
		SessionRecord.MemberID = xmember.xid;
	}
#endif

	/*--------------------------------------------------------------
		if user logged in okay, then check account status.
		we don't reveal any information to hackers.
	--------------------------------------------------------------*/
	if ( SessionRecord.LoggedIn != 1 )
	{
		SaveError ( "unknown database/username/password" );
		RunMode = MODE_PAINT_LOGIN;
		nsStrcpy ( SessionRecord.UserName, "unknown" );
		sleep ( 2 );
		return;
	}

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "ChkInput: twofactor %c\n", xsystem.xtwofactor[0] );
		fflush ( fpDebug );
	}

	if ( xsystem.xtwofactor[0] == 'Y' )
	{
		SessionRecord.LoggedIn = 0;
		SendTwoFactor ();
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

	UpdateMemberLogin ();

	RunMode = MODE_PAINT_MENU;
}
