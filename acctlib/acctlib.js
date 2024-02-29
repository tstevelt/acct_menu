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


function RoundTwoDec ( dblNumber )
{
	var intNumber = 0;
	var intCents = 0;
	var intDollars = 0;
	var strAnswer = '0.0';
	var NegNumber = 0;

	if ( dblNumber < 0.0 )
	{
		NegNumber = 1;
		dblNumber = 0.0 - dblNumber;
	}

	intDollars = Math.floor ( dblNumber );

	dblNumber = dblNumber - intDollars * 1.0;

	intCents   = Math.round ( dblNumber * 100.0 );

	if ( intCents == 100 )
	{
		intCents = 0;
		intDollars++;
	}

	if ( intCents == 0 )
	{
		strAnswer = intDollars + '.00';
	}
	else if ( intCents < 10 )
	{
		strAnswer = intDollars + '.0' + intCents;
	}
	else if ( (intCents % 10) == 0 )
	{
		strAnswer = intDollars + '.' + (intCents / 10) + '0';
	}
	else
	{
		strAnswer = intDollars + '.' + intCents;
	}
	
	if ( NegNumber == 1 )
	{
		strAnswer = '-' + strAnswer;
	}

	return ( strAnswer );
}

