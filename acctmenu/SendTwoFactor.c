/*----------------------------------------------------------------------------
	Program : SendTwoFactor.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Send 2FA code
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


CARRIER_RECORD *FindCarrier ( char *Label )
{
	int		ndx;

	for ( ndx = 0; ndx < CarrierCount; ndx++ )
	{
		if ( nsStrcmp ( CarrierArray[ndx].Label, Label ) == 0 )
		{
			return ( &CarrierArray[ndx] );
		}
	}

	return ( NULL );
}

void SendTwoFactor ()
{
	long	SixDigits;
	char	Address[128];
	CARRIER_RECORD	*ptrCarrier;
	long	Timestamp;

	shs_seed_random ();

	SixDigits = random_range ( 123456, 987654 );

	if ( xmember.xmtwopref[0] == 'P' )
	{
		TrimRightAndLeft ( xmember.xmphone );
		Stripper ( xmember.xmphone, "-" );
		TrimRightAndLeft ( xmember.xmcarrier );
		ptrCarrier = FindCarrier ( xmember.xmcarrier );
		sprintf ( Address, "%s@%s", xmember.xmphone, ptrCarrier->Address );
	}
	else
	{
		nsStrcpy ( Address, xmember.xmemail );
	}

	sprintf ( Buffer, "echo '%ld' | mail -s 'login code' %s", SixDigits, Address );
	system ( Buffer );

	Timestamp = 600 + time ( NULL );

	snprintf ( StatementTwo, sizeof(StatementTwo),
		"update member set Mpasstwo = '%ld', updated = %ld where id = %ld",
				SixDigits, Timestamp, xmember.xid );

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "%s<br>\n", StatementTwo );
		fflush ( fpDebug );
	}

	dbyUpdate ( "acctmenu", &MySql, StatementTwo, 0, LOGFILENAME );

}
