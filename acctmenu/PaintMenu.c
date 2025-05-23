/*----------------------------------------------------------------------------
	Program : PaintMenu.c
	Author  : Tom Stevelt
	Date    : 2000-2024
	Synopsis: Paint menu options.
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


#include	"acctmenu.h"

extern	LICENSE_RECORD	LicenseInfo;

void PaintMenu ( int MenuNumber )
{
	int		LinkNdx, MenuNdx, RowCount;
	int		PaintIt, HideIt;

	for ( LinkNdx = 0; LinkNdx < MenuCount; LinkNdx++ )
	{
		if ( (MenuArray[LinkNdx].Menu & LINK_MENU) == LINK_MENU )
		{
			break;
		}
	}

	for ( MenuNdx = 0; MenuNdx < MenuCount; MenuNdx++ )
	{
		if ( MenuArray[MenuNdx].Menu == MenuNumber )
		{
			break;
		}
	}

	if ( LinkNdx == MenuCount || MenuNdx == MenuCount )
	{
		printf ( "oops<br>\n" );
		return;
	}

	if ( GlobalDebug )
	{
		fprintf ( fpDebug, "%d %d %d\n", LinkNdx, MenuNdx, MenuCount );
		fprintf ( fpDebug, "%c\n", xmember.xmrole[0] );
		fflush ( fpDebug );
	}

	for ( RowCount = 0; 
		  /* (LinkNdx < MenuCount) && (MenuNdx < MenuCount) && */
		  ((MenuArray[LinkNdx].Menu & LINK_MENU) == LINK_MENU || MenuArray[MenuNdx].Menu == MenuNumber);
		  RowCount++, LinkNdx++, MenuNdx++ )
	{
		printf ( "<tr class='MenuRow'>\n" );

		/*----------------------------------------------------------
			paint menu link in column one.
		----------------------------------------------------------*/
		if ( LinkNdx < MenuCount && (MenuArray[LinkNdx].Menu & LINK_MENU) == LINK_MENU )
		{
			PaintIt = 0;
			HideIt = 0;

			if ( SessionRecord.HasGL == 0 && (MenuArray[LinkNdx].Menu & ALL_MENUS) == GL_MENU )
			{
				HideIt = 1;
			}
			else if ( SessionRecord.HasAR == 0 && (MenuArray[LinkNdx].Menu & ALL_MENUS) == AR_MENU )
			{
				HideIt = 1;
			}
			else if ( SessionRecord.HasAP == 0 && (MenuArray[LinkNdx].Menu & ALL_MENUS) == AP_MENU )
			{
				HideIt = 1;
			}
			else if ( SessionRecord.HasIC == 0 && (MenuArray[LinkNdx].Menu & ALL_MENUS) == IC_MENU )
			{
				HideIt = 1;
			}
			else if ( SessionRecord.HasAM == 0 && (MenuArray[LinkNdx].Menu & ALL_MENUS) == AM_MENU )
			{
				HideIt = 1;
			}

			if ( HideIt == 0 )
			{
				if (( xmember.xmrole[0] == ROLE_DEMO ) && (MenuArray[LinkNdx].Level & MENU_LEVEL_DEMO) == MENU_LEVEL_DEMO )
				{
					PaintIt = 1;
				}
				else if (( xmember.xmrole[0] == ROLE_MEMBER ) && (MenuArray[LinkNdx].Level & MENU_LEVEL_MEMBER) == MENU_LEVEL_MEMBER )
				{
					PaintIt = 1;
				}
				else if ( xmember.xmrole[0] == ROLE_ADMIN)
				{
					PaintIt = 1;
				}

				if  ( PaintIt )
				{
					if ( (MenuArray[LinkNdx].Menu & MenuNumber) == MenuNumber )
					{
						/*----------------------------------------------------------
							current menu has an asterisk, not hyperlinked
						----------------------------------------------------------*/
						printf ( "<td width='25%%'>*&nbsp;%s</td>\n", MenuArray[LinkNdx].Prompt );
					}
					else
					{
						/*----------------------------------------------------------
							other menus are hyperlinked
						----------------------------------------------------------*/
						printf ( "<td width='25%%'><a href='%s'>%s</a></td>\n", 
							MenuArray[LinkNdx].Action, MenuArray[LinkNdx].Prompt );
					}
				}
				else
				{
					printf ( "<td width='25%%'>%s</td>\n", MenuArray[LinkNdx].Prompt );
				}
			}
			else
			{
				printf ( "<td width='25%%'>&nbsp;</td>\n" );
			}
		}
		else
		{
			printf ( "<td width='25%%'>&nbsp;</td>\n" );
		}

		/*----------------------------------------------------------
			paint program link in second column.
		----------------------------------------------------------*/
		if (MenuNdx < MenuCount && MenuArray[MenuNdx].Menu == MenuNumber )
		{
			char	*cp;
			char	ActionBuffer[1024];

			PaintIt = 0;
			if (( xmember.xmrole[0] == ROLE_DEMO ) && (MenuArray[MenuNdx].Level & MENU_LEVEL_DEMO) == MENU_LEVEL_DEMO )
			{
				PaintIt = 1;
			}
			else if (( xmember.xmrole[0] == ROLE_MEMBER ) && (MenuArray[MenuNdx].Level & MENU_LEVEL_MEMBER) == MENU_LEVEL_MEMBER )
			{
				PaintIt = 1;
			}
			else if ( xmember.xmrole[0] == ROLE_ADMIN)
			{
				PaintIt = 1;
			}

			if  ( PaintIt )
			{
				sprintf ( ActionBuffer, "%s", MenuArray[MenuNdx].Action );

				if (( cp = nsStrstr ( ActionBuffer, "{DB}" )) != NULL )
				{
					*cp = '\0';
#ifdef UNIX
					nsStrcat ( ActionBuffer, SessionRecord.DbName );
#else
					char	*DbName;

					if (( cp = getenv ( "REQUEST_URI" )) == NULL )
					{
						SaveError ( "Cannot find REQUEST_URI" );
						return;
					}

					if ( strstr ( cp, "shs" ) != NULL )
					{
						DbName = "shs";
					}
					else if ( strstr ( cp, "acct" ) != NULL )
					{
						DbName = "acct";
					}
					else
					{
						SaveError ( "Unknown db in REQUEST_URI" );
						return;
					}

					nsStrcat ( ActionBuffer, DbName );
#endif
				}
				
				if ( nsStrlen ( MenuArray[MenuNdx].Target ) > 0 )
				{
					printf ( "<td width='35%%'><a target='%s' href='%s'>%s</a></td>\n", 
						MenuArray[MenuNdx].Target, ActionBuffer, MenuArray[MenuNdx].Prompt );
				}
				else
				{
					printf ( "<td width='35%%'><a href='%s'>%s</a></td>\n", 
						ActionBuffer, MenuArray[MenuNdx].Prompt );
				}
			}
			else
			{
				printf ( "<td width='35%%'>%s</td>\n", MenuArray[MenuNdx].Prompt );
			}
		}
		else
		{
			printf ( "<td width='35%%'>&nbsp;</td>\n" );
		}

		printf ( "</tr>\n" );
	}

}
