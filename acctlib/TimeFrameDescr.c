/*----------------------------------------------------------------------------
	Program : TimeFrameDescr.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Given time frame #define, return description
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

char *TimeFrameDescr ( int TimeFrame )
{
	switch ( TimeFrame )
	{
		case TF_CUR_MONTH:
			return ( "current month" );

		case TF_CUR_YEAR:
			return ( "current year" );

		case TF_THREE_MONTHS:
			return ( "three months" );

		case TF_ONE_YEAR:
			return ( "one year" );

		case TF_TWO_YEARS:
			return ( "two years" );

		case TF_THREE_YEARS:
			return ( "three years" );

		case TF_CUSTOM_DATES:
			return ( "custom dates" );

		case TF_ALL:
			return ( "all dates" );
	}

	return ( "---" );
}
