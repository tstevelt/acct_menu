/*----------------------------------------------------------------------------
	Program : DeleteImport.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Delete import record
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

static	char		MyStatementOne[4096];

int DeleteImport ( short AccountNumber )
{
	int		rv;

	sprintf ( MyStatementOne, 
		"delete from import where acctnum = %d", AccountNumber );
	
	rv = dbyDelete  ( "import", &MySql, MyStatementOne, 0, LOGFILENAME );
	
	if ( rv == 0 )
	{
		SaveError ( "an error occurred, import not deleted." );
	}
	
	return ( rv );
}
