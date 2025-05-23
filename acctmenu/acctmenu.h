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

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netinet/tcp.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<signal.h>
#include	<time.h>
#include	<errno.h>

#ifdef	APPLE
#include   <mysql.h>
#include   <errmsg.h>
#else
// #include	<crypt.h>
#include   <mysql/mysql.h>
#include   <mysql/errmsg.h>
#endif

#include	"shslib.h"
#include	"shsCarriers.h"
#include	"weblib.h"
#include	"dbylib.h"

#define		SYSTEM
#define		MEMBER
#include	"fileacct.h"
#include	"acctlib.h"

#define		MODE_PAINT_LOGIN		11
#define		MODE_EXEC_LOGIN			12
#define		MODE_PAINT_TWO_FACTOR	13
#define		MODE_EXEC_TWO_FACTOR	14
#define		MODE_PAINT_FORGOT		15
#define		MODE_EXEC_FORGOT		16
#define		MODE_PAINT_MENU			17
#define		MODE_EXEC_LOGOUT		18

TYPE	int		RunMode;
TYPE	int		MenuNumber;

TYPE	char	Buffer[1024];
TYPE	char	FormPassword[MAX_PASSWORD_LENGTH+1];
TYPE	char	TwoFactorCode[10];
TYPE	char	ForgotEmail[60];

TYPE	COOKIE_RECORD	AcctCookie;

TYPE	int			GlobalDebug;
#define		fnDebug "/var/local/webstate/acct/acctmenu.debug"
TYPE	FILE			*fpDebug;

#define		MENU_LEVEL_DEMO		1
#define		MENU_LEVEL_MEMBER	2
#define		MENU_LEVEL_ADMIN	4
#define		MENU_LEVEL_ALL		(MENU_LEVEL_DEMO|MENU_LEVEL_MEMBER|MENU_LEVEL_ADMIN)
#define		MENU_LEVEL_HIGH		(MENU_LEVEL_MEMBER|MENU_LEVEL_ADMIN)

typedef struct
{
	int		Menu;
	char	*Prompt;
	char	*Action;
	char	*Target;
	int		Level;
} MENUREC;

#define		IMAGES_PHOTO	0
#define		IMAGES_ORIGINAL	12
#define		IMAGES_DARKEN	24

#ifdef MAIN
MENUREC		MenuArray [] =
{
	{ LINK_MENU | SYS_MENU, "setup menu", "acctmenu.cgi?menu=setup", "", MENU_LEVEL_ALL },
	{ LINK_MENU | GL_MENU, "general ledger", "acctmenu.cgi?menu=gl", "", MENU_LEVEL_ALL },
	{ LINK_MENU | GL_RPT_MENU, "g/l reports", "acctmenu.cgi?menu=reports", "", MENU_LEVEL_ALL },
	{ LINK_MENU | AR_MENU, "accounts receivable", "acctmenu.cgi?menu=ar", "", MENU_LEVEL_ALL },
	{ LINK_MENU | AP_MENU, "accounts payable", "acctmenu.cgi?menu=ap", "", MENU_LEVEL_ALL },
	{ LINK_MENU | IC_MENU, "inventory control", "acctmenu.cgi?menu=inven", "", MENU_LEVEL_ALL },
	{ LINK_MENU | AM_MENU, "asset management", "acctmenu.cgi?menu=asset", "", MENU_LEVEL_ALL },
	{ LINK_MENU | ADMIN_MENU, "admin menu", "acctmenu.cgi?menu=admin", "", MENU_LEVEL_ADMIN },

	{ GL_MENU, "accounts", "accounts.cgi?ac=a", "", MENU_LEVEL_ALL },
	{ GL_MENU, "categories", "accounts.cgi?ac=c", "", MENU_LEVEL_ALL },
	{ GL_MENU, "import transactions", "import.cgi", "", MENU_LEVEL_ALL },
	{ GL_MENU, "enter/edit transactions", "entry.cgi", "", MENU_LEVEL_ALL },
	{ GL_MENU, "reconcile account", "reconcile.cgi", "", MENU_LEVEL_ALL },
	{ GL_MENU, "close accounting period", "close.cgi", "", MENU_LEVEL_ADMIN },

	{ GL_RPT_MENU, "balance sheet", "rptgl.cgi?type=B", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "income statement", "rptgl.cgi?type=I", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "cash flow", "rptcf.cgi", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "asset report", "rpttrx.cgi?type=A", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "liability report", "rpttrx.cgi?type=L", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "income report", "rpttrx.cgi?type=I", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "expense report", "rpttrx.cgi?type=X", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "transaction list", "rptall.cgi", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "tax forms", "rpttax.cgi", "", MENU_LEVEL_ALL },
	{ GL_RPT_MENU, "chart of accounts", "rptcoa.cgi", "", MENU_LEVEL_ALL },

	{ SYS_MENU, "system setup",             "asetup.cgi",   "", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "member setup",             "member.cgi",  "", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "change password",          "chpw.cgi",    "", MENU_LEVEL_HIGH },
	{ SYS_MENU, "import chart of accounts", "impcoa.cgi",  "", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "change account number",    "chgacct.cgi", "", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "backup",                   "backup.cgi",  "", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "file store",               "{DB}",        "files", MENU_LEVEL_ADMIN },
	{ SYS_MENU, "todo",                     "todo.html",   "todo", MENU_LEVEL_ADMIN },

	{ ADMIN_MENU, "system maintenance",  "dbymaint.cgi?screen=system&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "member maintenance",  "dbymaint.cgi?screen=member&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "account maintenance", "dbymaint.cgi?screen=account&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "import maintenance",  "dbymaint.cgi?screen=import&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "trxh maintenance",    "dbymaint.cgi?screen=trxh&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "trxd maintenance",    "dbymaint.cgi?screen=trxd&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "rpt maintenance",     "dbymaint.cgi?screen=rpt&DB={DB}", "_blank", MENU_LEVEL_ADMIN },
	{ ADMIN_MENU, "rptacct maintenance", "dbymaint.cgi?screen=rptacct&DB={DB}", "_blank", MENU_LEVEL_ADMIN },

	{ AR_MENU, "customer setup", "ar_arcust.cgi", "", MENU_LEVEL_ALL },
	{ AR_MENU, "invoice entry", "ar_entinv.cgi", "", MENU_LEVEL_ALL },
	{ AR_MENU, "invoice print", "ar_prtinv.cgi", "", MENU_LEVEL_ALL },
//	{ AR_MENU, "invoice post", "ar_post.cgi", "", MENU_LEVEL_ALL },
	{ AR_MENU, "statement print", "ar_statement.cgi", "", MENU_LEVEL_ALL },
	{ AR_MENU, "cash receipts", "ar_receipt.cgi", "", MENU_LEVEL_ALL },

	{ AM_MENU, "stub", "#", "", MENU_LEVEL_ALL },

	{ IC_MENU, "stub", "#", "", MENU_LEVEL_ALL },

	{ AP_MENU, "stub", "#", "", MENU_LEVEL_ALL },

};

int			MenuCount = sizeof(MenuArray) / sizeof(MENUREC);

char	*ImageArray [] =
{
	/*----------------------------------------------------------
		current set of images for personal web site. IMAGES_PHOTO
	----------------------------------------------------------*/
	"Winter-01.jpg",
	"Winter-02.jpg",
	"Spring-03.jpg",
	"Spring-04.jpg",
	"Spring-05.jpg",
	"Summer-06.jpg",
	"Summer-07.jpg",
	"Summer-08.jpg",
	"Fall-09.jpg",
	"Fall-10.jpg",
	"Fall-11.jpg",
	"Winter-12.jpg",

	/*----------------------------------------------------------
		original set of images for personal web site. IMAGES_ORIGINAL
	----------------------------------------------------------*/
	"pic01.jpg",
	"pic02.jpg",
	"pic03.jpg",
	"pic04.jpg",
	"pic05.jpg",
	"pic06.jpg",
	"pic07.jpg",
	"pic08.jpg",
	"pic09.jpg",
	"pic10.jpg",
	"pic11.jpg",
	"pic12.jpg",

	/*----------------------------------------------------------
		current image set for business web site. IMAGES_DARKEN
	----------------------------------------------------------*/
	"shs01.png",
	"shs02.png",
	"shs03.png",
	"shs04.png",
	"shs05.png",
	"shs06.png",
	"shs07.png",
	"shs08.png",
	"shs09.png",
	"shs10.png",
	"shs11.png",
	"shs12.png",
};

int		ClickWidth = 0;
int		LeftWidth = 20;
int		CenterWidth = 60;
int		RightWidth = 20;
int		EasterEggImages = 1;
int		EasterEggLicense = 1;

#else
extern	MENUREC		MenuArray[];
extern	int			MenuCount;
extern	char		*ImageArray[];
extern	int		ClickWidth;
extern	int		LeftWidth;
extern	int		CenterWidth;
extern	int		RightWidth;
extern	int		EasterEggImages;
extern	int		EasterEggLicense;
#endif

#define		MENU_ROWS			10



/*----------------------------------------------------------
:.,$d
:r! mkproto -p *.c
----------------------------------------------------------*/

/* acctmenu.c */
int main ( int argc , char *argv []);

/* ChkInput.c */
int ChkInput ( void );

/* FormEnd.c */
void FormEnd ( void );

/* FormStart.c */
void FormStart ( void );

/* GetInput.c */
void GetInput ( void );

/* MenuStartUp.c */
void MenuStartUp ( char *Title , int InitDB , int PaintHeader , int WriteMeta , char *OnLoad , int Menu );

/* PaintForgot.c */
void PaintForgot ( void );

/* PaintLogin.c */
void PaintLogin ( void );

/* PaintMenu.c */
void PaintMenu ( int MenuNumber );

/* PaintShowLicense.c */
void PaintShowLicense ( void );

/* PaintSlideShow.c */
void PaintSlideShow ( void );

/* PaintTop.c */
void PaintTop ( char *Title , int RunMode, int UserLoggedIn , int WriteMeta , char *OnLoad );

/* PaintTwoFactor.c */
void PaintTwoFactor ( void );

/* SendForgot.c */
int SendForgot ( void );

/* SendTwoFactor.c */
CARRIER_RECORD *FindCarrier ( char *Label );
void SendTwoFactor ( void );

/* ExecLogin.c */
void ExecLogin ( void );

/* ExecTwoFactor.c */
void ExecTwoFactor ( void );

/* UpdateMemberLogin.c */
void UpdateMemberLogin ( void );
