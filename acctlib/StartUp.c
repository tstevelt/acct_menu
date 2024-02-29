/*----------------------------------------------------------------------------
	Program : StartUp.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Start a normal (not a report) HTML page.
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

#define		SYSTEM
#include	"acctprivate.h"

void StartUp ( char *Title, char *DbName, int InitDB, int PaintHeader, int WriteMeta, char *OnLoad, int Menu )
{
	WEBPARMS	*ptrWebParms;

	ptrWebParms = webInitParms ();

	/*----------------------------------------------------------
		output first part of HTML ...
	----------------------------------------------------------*/
	webContentHtml ();

    ptrWebParms->WP_Title = Title;
    webStartHead ( ptrWebParms );

	if ( WriteMeta )
	{
		AcctMeta ();
	}

	/*--------------------------------------------------------------
		if on load function or not
	--------------------------------------------------------------*/
	if ( OnLoad == (char *)0 )
	{
		ptrWebParms->WP_Color = COLOR_BACKGROUND;
		webHeadToBody ( ptrWebParms );
	}
	else
	{
		ptrWebParms->WP_Color = COLOR_BACKGROUND;
		ptrWebParms->WP_OnLoad = OnLoad;
		webHeadToBody ( ptrWebParms );
	}

	/*--------------------------------------------------------------
		if initialize DB
	--------------------------------------------------------------*/
	if ( nsStrlen( DbName ) > 0 && (InitDB > 0) )
	{
		if ( StartDb ( DbName ) != 0 )
		{
			printf ( "DB [%s], Init %d<br>\n", DbName, InitDB );
			exit ( 0 );
		}
	}

	/*--------------------------------------------------------------
		paint accounting system header
	--------------------------------------------------------------*/
	if ( PaintHeader )
	{
		AcctStyle ( NULL );

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

		/*--------------------------------------------------------------
			if there is a menu
		--------------------------------------------------------------*/
		printf ( "<td align='left' width='20%%'>" );
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
			case LINK_MENU:
			default:
				if ( 1 == 2 /* fixit UserLoggedIn */ )
				{
					printf ( "[%s]", "fixit" /* UserName  */ );
				}
				else
				{
					printf ( "&nbsp;" );
				}
				break;
		}

		printf ( "</td>\n" );

		printf ( "<td align='center' width='60%%'>%s</td>\n", xsystem.xname );

		printf ( "<td width='20%%'>&nbsp;</td>\n" );

		printf ( "</tr>\n" );

		printf ( "</table>\n" );

		printf ( "<p>\n" );
	}

	webFreeParms ( ptrWebParms );
}
