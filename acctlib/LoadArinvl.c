/*----------------------------------------------------------------------------
	Program : LoadArinvl.c
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

#define		ARINVL
#include	"acctprivate.h"

static int Breakout ()
{
	return ( -1 );
}

int LoadArinvl ( char * WhereClause, XARINVL *ptrARINVL, int PrintErrors )
{
	int		NumberOfRows = 0;

	NumberOfRows = LoadArinvlCB ( WhereClause, NULL, ptrARINVL, Breakout, PrintErrors );

	return ( NumberOfRows );
}
