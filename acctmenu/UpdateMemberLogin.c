/*----------------------------------------------------------------------------
	Program : UpdateMemberLogin.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Update member table on login
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

void UpdateMemberLogin ()
{
	char		*cp;
	DATEVAL		Today;
	long		CurrentTime;
#define		MAXTOKS		10
	char	*tokens[MAXTOKS];
	int		tokcnt, xt;

	CurrentDateval ( &Today );
	CurrentTime = time ( NULL );

	MenuNumber = GL_MENU;

	snprintf ( StatementTwo, sizeof ( StatementTwo ),
		"update member set Mlogdt = '%04d-%02d-%02d', updated = %ld",
				Today.year4, Today.month, Today.day, CurrentTime );

	if ( RunMode == MODE_EXEC_TWO_FACTOR )
	{
		nsStrcat ( StatementTwo, ", Mpasstwo = ' '" );
	}

	snprintf ( WhereClause, sizeof ( WhereClause ), " where member.Mname = '%s'", SessionRecord.UserName );

	nsStrcat ( StatementTwo, WhereClause );

	dbyUpdate ( "acctmenu", &MySql, StatementTwo, 0, LOGFILENAME );

	if (( cp = getenv ( "REMOTE_ADDR" )) != (char *)0 )
	{
		snprintf ( StatementTwo, sizeof ( StatementTwo ),
			"update member set Mipaddr = '%s' where member.Mname = '%s'", cp, SessionRecord.UserName );

		dbyUpdate ( "acctmenu", &MySql, StatementTwo, 0, LOGFILENAME );
	}

	if ( LicenseInfo.DaysToExpiration < 7 )
	{
		sprintf ( msgbuf, "Software license expires in %d days.", LicenseInfo.DaysToExpiration );
		SaveError ( msgbuf );
	}

	if ( SessionRecord.HasGL == 0 )
	{
		tokcnt = GetTokensStd ( LicenseInfo.AppString, " 123456789", tokens, MAXTOKS, 0 );
		for ( xt = 0; xt < tokcnt; xt++ )
		{
			if ( nsStrcmp ( tokens[xt], "GL" ) == 0 )
			{
				SessionRecord.HasGL = 1;
			}
			else if ( nsStrcmp ( tokens[xt], "AP" ) == 0 )
			{
				SessionRecord.HasAP = 1;
			}
			else if ( nsStrcmp ( tokens[xt], "AR" ) == 0 )
			{
				SessionRecord.HasAR = 1;
			}
			else if ( nsStrcmp ( tokens[xt], "IC" ) == 0 )
			{
				SessionRecord.HasIC = 1;
			}
			else if ( nsStrcmp ( tokens[xt], "AM" ) == 0 )
			{
				SessionRecord.HasAM = 1;
			}
			else
			{
				sprintf ( msgbuf, "Unknown token [%s] in LicenseInfo.AppString", tokens[xt] );
				SaveError ( msgbuf );
			}
		}
	}

}
