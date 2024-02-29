/*----------------------------------------------------------------------------
	Program : PaintTop.c
	Author  : Tom Stevelt
	Date    : 01/10/2021
	Synopsis: Write everything from content-type to end head start body.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
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

void PaintTop ( char *Title, int RunMode, int UserLoggedIn, int WriteMeta, char *OnLoad )
{
	WEBPARMS	*ptrWebParms;
	int			ndx, ImageIndex, ImageOffset;
	char		*http_host;
	long	xtime;
	struct	tm	*tm;

	/*----------------------------------------------------------
		output first part of HTML ...
	----------------------------------------------------------*/
	webContentHtml ();

	time ( &xtime );
	tm = localtime ( &xtime );
	ImageOffset = IMAGES_PHOTO;
	ImageIndex = tm->tm_mon;

	http_host = getenv ( "HTTP_HOST" );
	if ( nsStrstr ( http_host, "silverhammersoftware" ) != NULL )
	{
		ImageOffset = IMAGES_DARKEN;
		ImageIndex += IMAGES_DARKEN;
	}

	ptrWebParms = webInitParms ();

	if ( EasterEggImages && UserLoggedIn )
	{
		ClickWidth = 3;
		LeftWidth = 17;
		CenterWidth = 60;
		RightWidth = 17;
	}

    ptrWebParms->WP_Title = Title;
    webStartHead ( ptrWebParms );

	webStartJava ();
	printf ( "var CurrentImage = %d;\n", ImageIndex - ImageOffset );
	printf ( "const ImageArray = [ " );
	for ( ndx = 0; ndx < 12; ndx++ )
	{
		printf ( "'%s'%s", ImageArray[ImageOffset+ndx], ndx < 11 ? ", " : "" );
	}
	printf ( "];\n" );

	webEndJava ();

	if ( WriteMeta )
	{
		AcctMeta ();
	}

#define USE_STYLE_SHEET
#ifdef USE_STYLE_SHEET
	switch ( RunMode )
	{
		case MODE_PAINT_FORGOT:
		case MODE_EXEC_FORGOT:
			AcctStyle ( "" );
			break;
		default:
			AcctStyle ( ImageArray[ImageIndex] );
			break;
	}
#endif

	if ( ClickWidth )
	{
		PaintSlideShow ();
	}

	/*--------------------------------------------------------------
		if on load function or not
	--------------------------------------------------------------*/
	if ( OnLoad == (char *)0 )
	{
		//ptrWebParms->WP_Color = COLOR_BACKGROUND;
		webHeadToBody ( ptrWebParms );
	}
	else
	{
		//ptrWebParms->WP_Color = COLOR_BACKGROUND;
		ptrWebParms->WP_OnLoad = OnLoad;
		webHeadToBody ( ptrWebParms );
	}

	webFreeParms ( ptrWebParms );
}
