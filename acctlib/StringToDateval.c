/*----------------------------------------------------------------------------
	Program : StringToDateval.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: convert string containing date to DATEVAL. Supported formats:
				0123456789
				mmddyy		6, all digits
				mmddyyyy	8, all digits
				mm/dd/yy	three numbers, two separators
				m/d/yy
				m/d/yyyy
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

int StringToDateval ( char *String, DATEVAL *Date )
{
	char	WorkBuffer[20];
	int		digits, separators, numbers, length;
	int		xi;
	int		pdigit;
	int		markers[3];
	
	Date->month = 0;
	Date->day   = 0;
	Date->year2  = 0;
	Date->year4  = 0;

	snprintf ( WorkBuffer, sizeof(WorkBuffer), "%s", String );

	numbers = digits = separators = length = 0;
	
	length = nsStrlen ( WorkBuffer );

	pdigit = 0;

	markers [0] = -1;
	markers [1] = -1;
	markers [2] = -1;

	for ( xi = 0; xi < length; xi++ )
	{
		if ( isdigit ( WorkBuffer[xi] ) != 0 )
		{
			digits++;
			if ( pdigit == 0 )
			{
				if ( markers[0] == -1 )
				{
					markers[0] = xi;
				}
				else if ( markers[1] == -1 )
				{
					markers[1] = xi;
				}
				else if ( markers[2] == -1 )
				{
					markers[2] = xi;
				}
			}
			pdigit = 1;
		}
		else
		{
			separators++;
			if ( xi > 0 && pdigit == 1 )
			{
				numbers++;
			}
			pdigit = 0;
			WorkBuffer[xi] = '\0';
		}
	}
	if ( xi > 0 && pdigit == 1 )
	{
		numbers++;
	}

	if ( separators == 0 && digits == 6 )
	{
		WorkBuffer [6] = '\0';
		Date->year2  = nsAtoi ( &WorkBuffer [4] );
		Date->year4  = nsAtoi ( &WorkBuffer [4] ) + 2000;
		WorkBuffer [4] = '\0';
		Date->day   = nsAtoi ( &WorkBuffer [2] );
		WorkBuffer [2] = '\0';
		Date->month = nsAtoi ( &WorkBuffer [0] );
	}
	else if ( separators == 0 && digits == 8 )
	{
		WorkBuffer [8] = '\0';
		Date->year2 = nsAtoi ( &WorkBuffer [4] ) % 100;
		Date->year4 = nsAtoi ( &WorkBuffer [4] );
		WorkBuffer [4] = '\0';
		Date->day   = nsAtoi ( &WorkBuffer [2] );
		WorkBuffer [2] = '\0';
		Date->month = nsAtoi ( &WorkBuffer [0] );
	}
	else if ( separators == 2 && numbers == 3 )
	{
		if ( nsStrlen ( &WorkBuffer [ markers[0] ] ) == 4 )
		{
			Date->year4  = nsAtoi ( &WorkBuffer [ markers[0] ] );
			Date->year2  = Date->year4 % 100;
			Date->month = nsAtoi ( &WorkBuffer [ markers[1] ] );
			Date->day   = nsAtoi ( &WorkBuffer [ markers[2] ] );
		}
		else
		{
			Date->month = nsAtoi ( &WorkBuffer [ markers[0] ] );
			Date->day   = nsAtoi ( &WorkBuffer [ markers[1] ] );
			Date->year2  = nsAtoi ( &WorkBuffer [ markers[2] ] );
			Date->year4  = nsAtoi ( &WorkBuffer [ markers[2] ] ) + 2000;
		}
	}
	else
	{
		return ( -1 );
	}

	if ( Date->month < 1 || Date->month > 12 )
	{
		return ( -2 );
	}

	if ( Date->day < 1 || Date->day > 31 )
	{
		return ( -3 );
	}

	return ( 0 );

}
