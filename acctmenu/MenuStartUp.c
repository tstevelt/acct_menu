/*----------------------------------------------------------------------------
	Program : MenuStartUp.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint menu
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

void MenuStartUp ( char *Title, 
					int InitDB, 
					int PaintHeader, 
					int WriteMeta, 
					char *OnLoad, 
					int Menu )
{
	/*--------------------------------------------------------------
		if initialize DB
	--------------------------------------------------------------*/
	if ( InitDB > 0 )
	{
		if ( StartDb ( SessionRecord.DbName ) != 0 )
		{
			printf ( "DB [%s], Init %d<br>\n", SessionRecord.DbName, InitDB );
			exit ( 0 );
		}

		if ( EasterEggLicense && ClickWidth )
		{
			PaintShowLicense ();
		}
	}

	/*--------------------------------------------------------------
		paint accounting system header
	--------------------------------------------------------------*/
	if ( PaintHeader )
	{
		if ( InitDB )
		{
			LoadSystem ();
		}
		else 
		{
			snprintf ( xsystem.xname, sizeof(xsystem.xname), "%s", Title );
		}

		printf ( "<table align='center' border='0' cellspacing='0' cellpadding='3' width='92%%'>\n" );
		printf ( "<tr class='HeadingRow'>\n" );

		if ( ClickWidth )
		{
			printf ( "<td width='%d%%' onclick='javascript:SlideShow(-1);'>&nbsp;</td>", ClickWidth );
			printf ( "<td align='left' width='%d%%'>", LeftWidth );
		}
		else
		{
			printf ( "<td align='left' width='%d%%'>", LeftWidth );
		}

		/*--------------------------------------------------------------
			if there is a menu
		--------------------------------------------------------------*/
		switch ( Menu )
		{
			case GL_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=gl'>menu</a>" );
				break;
			case GL_RPT_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=reports'>menu</a>" );
				break;
			case SYS_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=setup'>menu</a>" );
				break;
			case AR_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=ar'>menu</a>" );
				break;
			case AM_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=asset'>menu</a>" );
				break;
			case IC_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=inven'>menu</a>" );
				break;
			case AP_MENU:
				printf ( "<a class='Heading' href='acctmenu.cgi?menu=ap'>menu</a>" );
				break;
			// case LOGIN_MENU:
			case LINK_MENU:
			default:
				if ( SessionRecord.LoggedIn )
				{
					printf ( "[%s]", SessionRecord.UserName );
				}
				else
				{
					printf ( "&nbsp;" );
				}
				break;
		}

		printf ( "</td>\n" );

		if ( EasterEggLicense && ClickWidth )
		{
			printf ( "<td align='center' width='%d%%' onclick='javascript:ShowLicense();'>%s</td>\n", CenterWidth, xsystem.xname );
		}
		else
		{
			printf ( "<td align='center' width='%d%%'>%s</td>\n", CenterWidth, xsystem.xname );
		}

		/*--------------------------------------------------------------
			if there is help
		--------------------------------------------------------------*/
		printf ( "<td align='right' width='%d%%'>\n", RightWidth );

		if ( SessionRecord.LoggedIn )
		{
			printf ( "<a class='Heading' href='acctmenu.cgi?submitLogout=1'>logout</a></td>\n" );
		}
		else
		{
			printf ( "&nbsp;</td>\n" );
		}

		if ( EasterEggImages && ClickWidth )
		{
			printf ( "<td width='%d%%' onclick='javascript:SlideShow(1);'>&emsp;</td>\n", ClickWidth );
		}
		printf ( "</tr>\n" );

		printf ( "</table>\n" );

		printf ( "<p>\n" );
	}

}
