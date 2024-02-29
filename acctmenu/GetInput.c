/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Get user input from screen
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

void GetInput()
{
	int		xa;

	/*----------------------------------------------------------
		get user input
	----------------------------------------------------------*/
	webGetInput ();

	RunMode = MODE_PAINT_LOGIN;
	MenuNumber = GL_MENU;

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );
		TrimRightAndLeft ( webValues[xa] );
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "%s=%s\n", webNames[xa],  webValues[xa] );
			fflush ( fpDebug );
		}

		if ( nsStrcmp ( webNames[xa], "menu" ) == 0 )
		{
			if ( nsStrcmp ( webValues[xa], "gl" ) == 0 )
			{
				MenuNumber = GL_MENU;
			}
			if ( nsStrcmp ( webValues[xa], "reports" ) == 0 )
			{
				MenuNumber = GL_RPT_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "setup" ) == 0 )
			{
				MenuNumber = SYS_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "admin" ) == 0 )
			{
				MenuNumber = ADMIN_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "ar" ) == 0 )
			{
				MenuNumber = AR_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "asset" ) == 0 )
			{
				MenuNumber = AM_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "inven" ) == 0 )
			{
				MenuNumber = IC_MENU;
			}
			else if ( nsStrcmp ( webValues[xa], "ap" ) == 0 )
			{
				MenuNumber = AP_MENU;
			}

			RunMode = MODE_PAINT_MENU;
		}
		else if ( nsStrcmp ( webNames[xa], "database" ) == 0 )
		{
			snprintf ( SessionRecord.DbName , sizeof(SessionRecord.DbName) , "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "username" ) == 0 )
		{
			snprintf ( SessionRecord.UserName, sizeof(SessionRecord.UserName), "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "password" ) == 0 )
		{
			snprintf ( FormPassword, sizeof(FormPassword), "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "TwoFactorCode" ) == 0 )
		{
			snprintf ( TwoFactorCode, sizeof(TwoFactorCode), "%s", webValues[xa] );
		}

		else if ( nsStrcmp ( webNames[xa], "submitLogin" ) == 0 )
		{
			RunMode = MODE_EXEC_LOGIN;
		}
		else if ( nsStrcmp ( webNames[xa], "paintForgot" ) == 0 )
		{
			RunMode = MODE_PAINT_FORGOT;
		}

		else if ( nsStrcmp ( webNames[xa], "forgotemail" ) == 0 )
		{
			snprintf ( ForgotEmail, sizeof(ForgotEmail), "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "submitForgot" ) == 0 )
		{
			RunMode = MODE_EXEC_FORGOT;
		}

		else if ( nsStrcmp ( webNames[xa], "submitLogout" ) == 0 )
		{
			RunMode = MODE_EXEC_LOGOUT;
		}

		else if ( nsStrcmp ( webNames[xa], "submitTwoFactor" ) == 0 )
		{
			RunMode = MODE_EXEC_TWO_FACTOR;
		}
#ifdef DEBUG
		else
		{
			sprintf ( Buffer, "unknown: %s = %s", webNames[xa], webValues[xa] );
			SaveError ( Buffer );
		}
#endif
	}
}
