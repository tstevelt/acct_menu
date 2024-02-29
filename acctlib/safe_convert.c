/*----------------------------------------------------------------------------
	Program : safe_convert.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Don't seg fault on null strings
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

double safe_amount_to_atof ( char *String )
{
	double	dblVal = 0.0;

	if ( String != (char *)0 )
	{
		dblVal = (double) ( nsAtol ( String ) / 100.0 );
	}

	return ( dblVal );
}

long safe_atol ( char *String )
{
	long	longVal = 0L;

	if ( String != (char *)0 )
	{
		longVal = (long)  nsAtol ( String );
	}

	return ( longVal );
}

int safe_atoi ( char *String )
{
	int		intVal = 0;

	if ( String != (char *)0 )
	{
		intVal = (int)  nsAtoi ( String );
	}

	return ( intVal );
}

short safe_atos ( char *String )
{
	short	shortVal = 0;

	if ( String != (char *)0 )
	{
		shortVal = (short)  nsAtoi ( String );
	}

	return ( shortVal );
}

