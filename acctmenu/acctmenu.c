/*----------------------------------------------------------------------------
	Program : acctmenu.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Accounting website menu.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		2022		Added 2-factor authentication

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

#define		MAIN
#include	"acctmenu.h"

int		UseErrorSys = 1;

static char	SessionID [SESSION_ID_SIZE+1];

int main ( int argc, char *argv[] )
{
	char	Title[40];
	COOKIE_RECORD	*AcctCookie;
	int		DivCount = 2;
	int		PrintCopyright = 1;
	int		DoWriteSession = 1;
	int		DoGetInput = 1;

	UseErrorSys = 1;
	GlobalDebug = 0;
	if ( GlobalDebug )
	{
		fpDebug = fopen ( fnDebug, "w" );
		if ( fpDebug == NULL )
		{
			fpDebug = stderr;
		}
	}

	if ((( AcctCookie = acctGetCookie ( COOKIE_NAME, GlobalDebug, fpDebug )) == (COOKIE_RECORD *) 0 ) ||
		 ( ReadSession ( AcctCookie->SessionID, &SessionRecord ) != 0         ))
	{
		MakeSessionID ( SessionID, SESSION_ID_SIZE, 1 );
		AcctCookie = acctMakeCookie ( COOKIE_NAME, SessionID );

		/*----------------------------------------------------------
			write the cookie, has to be written before content type
		----------------------------------------------------------*/
		acctWriteCookie ( AcctCookie, GlobalDebug, fpDebug );

		memset ( &SessionRecord, '\0', sizeof(SessionRecord) );
		nsStrcpy ( SessionRecord.SessionID, SessionID );
		SessionRecord.LoggedIn = 0;
		WriteSession ( &SessionRecord );
		RunMode = MODE_PAINT_LOGIN;
		DoGetInput = 0;
	}
	else
	{
		sprintf ( SessionID, "%*.*s", SESSION_ID_SIZE, SESSION_ID_SIZE, AcctCookie->SessionID );
	}

	ReadSession ( SessionID, &SessionRecord );

	/*----------------------------------------------------------
		get input and check it. still have not written 
		content type, that happens in PaintTop.  so 
		both get and check can not use printf, use SaveError
	----------------------------------------------------------*/
	if ( DoGetInput )
	{
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "acctmenu 1: RunMode %d\n", RunMode );
			fflush ( fpDebug );
		}
		GetInput();
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "acctmenu 2: RunMode %d\n", RunMode );
			fflush ( fpDebug );
		}
		ChkInput();
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "acctmenu 3: RunMode %d\n", RunMode );
			fflush ( fpDebug );
		}
	}

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "acctmenu 4: RunMode %d\n", RunMode );
		fflush ( fpDebug );
	}

	/*----------------------------------------------------------
		Take action. Some of these routines might set 
		RunMode for subsequent painting of screen.  For intance
		they might set RunMode to a previous level if there
		is an error.  NOTE!! these functions cannot have 
		printf() output!
	----------------------------------------------------------*/
	switch ( RunMode )
	{
		case MODE_EXEC_LOGIN:
			ExecLogin ();
			break;

		case MODE_EXEC_TWO_FACTOR:
			ExecTwoFactor ();
			break;

		case MODE_EXEC_FORGOT:
			break;
			
		case MODE_EXEC_LOGOUT:
//			rv = DeleteSession ( &SessionRecord );
//			if ( rv == 0 )
//			{
//				DoWriteSession = 0;
//			}

			memset ( SessionRecord.DbName, '\0', sizeof(SessionRecord.DbName) );
			memset ( SessionRecord.UserName, '\0', sizeof(SessionRecord.UserName) );
			SessionRecord.LoggedIn = 0;
			SessionRecord.MemberID = 0;
			SessionRecord.HasGL = 0;
			SessionRecord.HasAP = 0;
			SessionRecord.HasAR = 0;
			SessionRecord.HasIC = 0;
			SessionRecord.HasAM = 0;
			RunMode = MODE_PAINT_LOGIN;
			break;
	}

	/*----------------------------------------------------------
		preliminary screen painting
	----------------------------------------------------------*/
	sprintf ( Title, "accounting - %s", SessionRecord.DbName );
	PaintTop ( Title, RunMode, SessionRecord.LoggedIn, 1, "javascript:Loaded();" );
	MenuStartUp ( Title, SessionRecord.LoggedIn, 1, 1, "javascript:Loaded();", 0 );

	if ( GlobalDebug )
	{
		fprintf  ( fpDebug, "run mode before start screen %d\n", RunMode );
		fflush ( fpDebug );
	}

	switch ( RunMode )
	{
		case MODE_PAINT_FORGOT:
			printf ( "<div class='acct-display-topmiddle w3-full w3-padding'>\n" );
			// printf ( "<div class='w3-padding w3-border w3-opacity-min w3-white w3-text-black w3-center'>\n" );
			DivCount = 1;
			FormStart ();
			//printf ( "<table class='AppWide'>\n" );
			printf ( "<table align='center' border='1' cellspacing='0' cellpadding='3' width='92%%'>\n" );
			PrintCopyright = 0;
			break;

		case MODE_PAINT_LOGIN:
		case MODE_PAINT_TWO_FACTOR:
			printf ( "<div class='acct-display-topmiddle w3-full w3-padding'>\n" );
			printf ( "<div class='w3-padding w3-border w3-opacity-min w3-white w3-text-black w3-center'>\n" );
			FormStart ();
			// printf ( "<table class='AppWide'>\n" );
			// PrintCopyright = 0;
			printf ( "<table align='center' border='1' cellspacing='0' cellpadding='3' width='92%%'>\n" );
			break;
		
		default:
			printf ( "<div class='acct-display-topmiddle w3-threequarter w3-padding'>\n" );
			printf ( "<div class='w3-padding w3-border w3-opacity-min w3-white w3-text-black w3-center'>\n" );
			FormStart ();
			// printf ( "<table class='AppMedium'>\n" );
			printf ( "<table align='center' border='1' cellspacing='0' cellpadding='3' width='92%%'>\n" );
			break;
	}

	if ( GlobalDebug )
	{
		fprintf  ( fpDebug, "run mode now %d\n", RunMode );
		fflush ( fpDebug );
	}

	/*----------------------------------------------------------
		actual screen painting
	----------------------------------------------------------*/
	switch ( RunMode )
	{
		case MODE_PAINT_LOGIN:
			PaintLogin ();
			break;
		case MODE_EXEC_LOGIN:
			break;
		case MODE_PAINT_TWO_FACTOR:
			PaintTwoFactor ();
			break;
		case MODE_EXEC_TWO_FACTOR:
			break;
		case MODE_PAINT_FORGOT:
			PaintForgot ();
			break;
		case MODE_EXEC_FORGOT:
			StartDb ( SessionRecord.DbName );
			if ( SendForgot () == 0 )
			{
				printf ( "<p>Password reset instructions sent to your email<br>\n" );
				printf ( "<input type='button' value='close' onclick='javascript:window.close();'>\n" );
			}
			else
			{
				ErrorSysLoaded ( "Loaded" );
			}
			printf ( "</body>\n" );
			printf ( "</html>\n" );
			dbyClose ( &MySql );
			return ( 0 );

		case MODE_PAINT_MENU:
			switch  ( MenuNumber )
			{
				case GL_MENU:
				case GL_RPT_MENU:
				case SYS_MENU:
				case ADMIN_MENU:
				case AR_MENU:
				case AM_MENU:
				case IC_MENU:
				case AP_MENU:
					PaintMenu ( MenuNumber );
					SessionRecord.CurrentMenu = MenuNumber;
					break;
				default:
					sprintf ( msgbuf, "Unknown menu number %d", MenuNumber );
					SaveError ( msgbuf );
					break;
			}
			break;

		case MODE_EXEC_LOGOUT:
			break;
	}
		
	printf ( "</table>\n" );

	FormEnd ();
		
	if ( PrintCopyright )
	{
		Copyright ();
	}

	while ( DivCount > 0 )
	{
		printf ( "</div>\n" );
		DivCount--;
	}

	ErrorSysLoaded ( "Loaded" );

	printf ( "</body>\n" );
	printf ( "</html>\n" );

	if ( GlobalDebug )
	{
		fprintf  ( fpDebug, "before dbyClose\n" );
		fflush ( fpDebug );
	}

	dbyClose ( &MySql );

	if ( DoWriteSession )
	{
		if ( GlobalDebug )
		{
			fprintf  ( fpDebug, "before WriteSession\n" );
			fflush ( fpDebug );
		}

		WriteSession ( &SessionRecord );
	}

	if ( GlobalDebug )
	{
		fprintf  ( fpDebug, "made it to the end\n" );
		fflush ( fpDebug );
	}

	return ( 0 );
}
