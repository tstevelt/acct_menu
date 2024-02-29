/*----------------------------------------------------------------------------
	Program : StatusDescr.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Given STATUS #define, return either single letter or description
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

char *StatusDescr ( short Status, int Format )
{
	if ( Format == 1 )
	{
		switch ( Status )
		{
			case 0                : return ( "&nbsp;" );
			case STATUS_PREENT    : return ( "I" );
			case STATUS_ACCEPT    : return ( "N" );
			case STATUS_BALANCE   : return ( "B" );
			case STATUS_OPEN      : return ( "O" );
			case STATUS_RECONCILED: return ( "R" );
			case STATUS_CLOSED    : return ( "C" );
			default               : return ( "?" );
		}
	}
	else
	{
		switch ( Status )
		{
			case 0                : return ( "&nbsp;" );
			case STATUS_PREENT    : return ( "pre entered" );
			case STATUS_ACCEPT    : return ( "new" );
			case STATUS_BALANCE   : return ( "out of balance" );
			case STATUS_OPEN      : return ( "open" );
			case STATUS_RECONCILED: return ( "reconciled" );
			case STATUS_CLOSED    : return ( "closed" );
			default               : return ( "unknown" );
		}
	}
}
