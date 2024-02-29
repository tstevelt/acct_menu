/*----------------------------------------------------------------------------
	Program : CookieFuncs.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Cookie functions.
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

#include	"acctprivate.h"

static COOKIE_RECORD	CookieRecord;

COOKIE_RECORD *acctGetCookie ( char CookieName[], int GlobalDebug, FILE *fpDebug )
{
	char 	*CookieString;
	char	WorkBuffer[1024];
	char	*tokens[24];
	int		tokcnt;

	if (( CookieString = getenv ( "HTTP_COOKIE" )) == NULL )
	{
		if ( GlobalDebug )
		{
			fprintf ( fpDebug, "HTTP_COOKIE is NULL\n" );
			fflush ( fpDebug );
		}
		sprintf ( CookieRecord.CookieName, "%s", CookieName );
		sprintf ( CookieRecord.SessionID, "12345678" );
		acctWriteCookie ( &CookieRecord, GlobalDebug, fpDebug );
	}
	else
	{
		nsStrcpy ( WorkBuffer, CookieString );

		if (( tokcnt = GetTokensStd ( WorkBuffer, "=;", tokens, 24, 0 )) < 2 )
		{
			if ( GlobalDebug )
			{
				fprintf ( fpDebug, "tokcnt %d\n", tokcnt );
				fflush ( fpDebug );
			}
			sprintf ( CookieRecord.CookieName, "%s", CookieName );
			sprintf ( CookieRecord.SessionID, "12345678" );
			acctWriteCookie ( &CookieRecord, GlobalDebug, fpDebug );
		}
		else
		{
			nsStrcpy ( CookieRecord.CookieName, tokens[0] );
			nsStrcpy ( CookieRecord.SessionID,  tokens[1] );
		}
	}

	return ( &CookieRecord );
}

COOKIE_RECORD *acctMakeCookie ( char CookieName[], char SessionID[] )
{
	sprintf ( CookieRecord.CookieName, "%s", CookieName );
	sprintf ( CookieRecord.SessionID, "%s", SessionID );
	return ( &CookieRecord );
}

static	char	CookieString[1024];

void acctWriteCookie ( COOKIE_RECORD *AcctCookie, int GlobalDebug, FILE *fpDebug )
{
	char	DateString[128];
	int			LifeSeconds;
	long		xtime;
	struct tm	*tm;
//	struct timeval	tv;
//	struct timezone	tz;
	char		*Dow[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	char		*Mon[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",  "Dec" };

	sprintf ( CookieString, "%s=%s;", AcctCookie->CookieName, AcctCookie->SessionID );

	/*----------------------------------------------------------
		set to 8 hours
	----------------------------------------------------------*/
	LifeSeconds = 8 * 3600;

	time ( &xtime );
	tm = localtime ( &xtime );
	tm->tm_gmtoff = 0 - tm->tm_gmtoff;
	xtime = xtime + LifeSeconds + (tm->tm_gmtoff);
	tm = localtime ( &xtime );

	snprintf ( DateString, sizeof(DateString), " expires=%s, %d-%s-%d %02d:%02d:%02d GMT;",
					Dow[tm->tm_wday],
					tm->tm_mday,
					Mon[tm->tm_mon],
					tm->tm_year + 1900,
					tm->tm_hour,
					tm->tm_min,
					tm->tm_sec );

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "CookieString %s\n", CookieString );
		fprintf ( fpDebug, "DateString %s\n", DateString );
		fflush ( fpDebug );
	}

	nsStrcat ( CookieString, DateString );

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "Final CookieString %s\n", CookieString );
		fflush ( fpDebug );
	}

	printf ( "Set-Cookie: %s;\n", CookieString );
}
