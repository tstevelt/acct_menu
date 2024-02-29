/*----------------------------------------------------------------------------
	Program : AcctMeta.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint META information at HTML <head>
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

void AcctMeta ()
{
	printf ( "<meta name='description' content='Silver Hammer Software LLC, Accounting Software and Custom Programming' lang='en-US'/>\n" );
	printf ( "<meta name='robots' content='noodp,noydir'/>\n" );
	printf ( "<meta name='viewport' content='width=device-width, initial-scale=1'>\n" );
	printf ( "<meta name='keywords' content='accounting,bookkeeping,programming,balance sheet,income statement,retire,retirement,personal finance'/>\n");
	printf ( "<meta property='og:title' content='Silver Hammer Software'/>\n" );
	printf ( "<meta property='og:description' content='Silver Hammer Software, Accounting Software and Custom Programming'/>\n" );
	printf ( "<meta property='og:url' content='https://acct.silverhammersoftware.com'/>\n" );
	printf ( "<meta property='og:type' content='website'/>\n" );
	printf ( "<meta property='og:site_name' content='Silver Hammer Software LLC'/>\n" );
}
