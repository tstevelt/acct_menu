/*----------------------------------------------------------------------------
	Program : ReportUp.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Start up a report screen.
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
#include	"rptlib.h"

void ReportUp ( char *Title, char *DbName, char *OnLoad, char ReportFormat, char *ReportName )
{
	char	*UserName;
	char	ReportNameWithExtension[128];
	WEBPARMS	*ptrWebParms;

	ptrWebParms = webInitParms ();

	/*----------------------------------------------------------
		output first part of HTML ...
	----------------------------------------------------------*/
	if ( ReportFormat == RPT_FORMAT_PDF_VIEW )
	{
		sprintf ( ReportNameWithExtension, "%s", ReportName );
		ptrWebParms->WP_FileName = ReportNameWithExtension;
    	webContentPDF ( ptrWebParms );
	}
	else
	{
		webContentHtml ();

		ptrWebParms->WP_Title = Title;
		webStartHead ( ptrWebParms );

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

	}

	webFreeParms ( ptrWebParms );

	if (( UserName = webGetOneEnv ( "REMOTE_USER" )) == (char *)0 )
	{
		UserName = "unknown";
	}

//	gethostname ( HostName, sizeof(HostName) );

	StartDb ( DbName );

	LoadSystem ();

}
