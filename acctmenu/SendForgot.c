/*----------------------------------------------------------------------------
	Program : SendForgot.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Send email to user who forgot their password.
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

int SendForgot ()
{
	char	fn[256];
	FILE	*fp;
	char	Link[256];
	int		rv;
	char	PlainText[256];
	char	*EncodedText;
	long	CurrentTime;

	RunMode = 0;

	if ( nsStrcmp ( SessionRecord.UserName, "demo" ) == 0 )
	{
		SaveError ( "demo user may not change password" );
		return ( -1 );
	}

	snprintf ( WhereClause, sizeof(WhereClause), "Mname = '%s' and Memail = '%s'", SessionRecord.UserName, ForgotEmail );
	if (( rv = LoadMember ( WhereClause, &xmember, 0 )) != 1 )
	{
		sprintf ( msgbuf,  "rv %d unknown email address, please see your administrator.", rv );
		SaveError ( msgbuf );
		return ( -2 );
	}

	sprintf ( fn, "%s/forgot.txt", TEMPDIR );

	if (( fp = fopen ( fn, "w" )) == (FILE *)0 )
	{
		SaveError ( "error creating email" );
		return ( -3 );
	}

	time ( &CurrentTime );
	CurrentTime = CurrentTime + (60*60);

	sprintf ( PlainText, "%s_%s_%ld", SessionRecord.DbName, xmember.xmname, CurrentTime );

	EncodedText = PlainText;
	EncodedText = tmsEncode ( tolower(PlainText[0]), PlainText );

	sprintf ( Link, "https://%s/chpw.cgi?forgot=%s", getenv("HTTP_HOST"), EncodedText );
	fprintf ( fp, "This email is from %s<br>\n\n", getenv("HTTP_HOST") );
	fprintf ( fp, "If you did not request a new password, then please ignore this email.<br>\n" );
	fprintf ( fp, "<p>\n" );
	fprintf ( fp, "Click this link set a new password:\n" );
	fprintf ( fp, "&emsp;<a href='%s'>Click here</a><br>\n", Link );
	fprintf ( fp, "<p>\n" );
	fprintf ( fp, "This link will expire in one hour.\n" );

	nsFclose ( fp );

	SendAttached ( "tms@stevelt.com", ForgotEmail, "", "", "Reset password instructions",
						1, fn,
						0, NULL );

	sprintf ( msgbuf, "new password instructions sent to your email" );
	SaveError ( msgbuf );

	return ( 0 );
}
