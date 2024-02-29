/*----------------------------------------------------------------------------
	Program : TimeFrameDates.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: In account setup, user can chooes various time frames for
				number of transaction to display.  This function calculates
				the starting and ending dates.
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

int TimeFrameDates ( int TimeFrame, DATEVAL *StartDate, DATEVAL *EndDate )
{
	DATEVAL		Today;
	int			rv = 0;

	CurrentDateval ( &Today );

	switch ( TimeFrame )
	{
		case TF_CUR_MONTH:
			StartDate->month = Today.month;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4;
			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_CUR_YEAR:
			StartDate->month = 1;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4;
			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_THREE_MONTHS:
			StartDate->month = Today.month - 3;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4;
			if ( StartDate->month < 1 )
			{
				StartDate->month += 12;
				StartDate->year4--;
			}

			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_ONE_YEAR:
			StartDate->month = Today.month;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4 - 1;
			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_TWO_YEARS:
			StartDate->month = Today.month;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4 - 2;
			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_THREE_YEARS:
			StartDate->month = Today.month;
			StartDate->day   = 1;
			StartDate->year4  = Today.year4 - 3;
			EndDate->month   = Today.month;
			EndDate->day     = Today.day;
			EndDate->year4    = Today.year4;
			break;

		case TF_ALL:
			StartDate->month = 1;
			StartDate->day   = 1;
			StartDate->year4  = 1900;
			EndDate->month   = 12;
			EndDate->day     = 31;
			EndDate->year4    = 2999;
			break;

		case TF_CUSTOM_DATES:
			rv = 1;
			break;
	}

	return ( rv );
}
