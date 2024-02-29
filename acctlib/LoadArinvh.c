/*----------------------------------------------------------------------------
	Program : LoadArinvh.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Load <table>
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

#define		ARINVH
#include	"acctprivate.h"

static int Breakout ()
{
	return ( -1 );
}

int LoadArinvh ( char * WhereClause, XARINVH *ptrARINVH, int PrintErrors )
{
	int		NumberOfRows = 0;

	NumberOfRows = LoadArinvhCB ( WhereClause, NULL, ptrARINVH, Breakout, PrintErrors );

	return ( NumberOfRows );
}
