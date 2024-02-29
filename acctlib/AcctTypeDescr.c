/*----------------------------------------------------------------------------
	Program : AcctTypeDescr.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Convert AcctType single-letter code to name.
	Return  : char *
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

char *AcctTypeDescr ( char AcctType, int Plural )
{
	if ( Plural == 0 )
	{
		switch ( AcctType )
		{
			case 'A' : return ( "asset" );
			case 'L' : return ( "liabilty" );
			case 'E' : return ( "equity" );
			case 'I' : return ( "income" );
			case 'X' : return ( "expense" );
			default  : return ( "unknown" );
		}
	}
	else
	{
		switch ( AcctType )
		{
			case 'A' : return ( "assets" );
			case 'L' : return ( "liabilties" );
			case 'E' : return ( "equities" );
			case 'I' : return ( "income" );
			case 'X' : return ( "expenses" );
			default  : return ( "unknown" );
		}
	}
}
