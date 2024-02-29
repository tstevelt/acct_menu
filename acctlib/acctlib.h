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

#define		LOGFILENAME		"/var/local/acct.log"
#define     TEMPDIR         "/var/local/tmp"
#define		RW_DIRECTORY	"/var/local/webstate/acct"

#ifdef MAIN
#define		LIBTYPE	/* */
#else
#define		LIBTYPE	extern
#endif


/*----------------------------------------------------------
	this is used for select from joined tables
----------------------------------------------------------*/
#if defined ( TRXH ) || defined ( TRXD )
#define	FLDS_TRXV	"trxh.trxnum,trxh.status,refnum,trxdate,seqnum,trxd.acctnum,payee,amount"
#define	TRXV_trxnum		0
#define	TRXV_status		1
#define	TRXV_refnum		2
#define	TRXV_trxdate	3
#define	TRXV_seqnum		4
#define	TRXV_acctnum	5
#define	TRXV_payee		6
#define	TRXV_amount		7
#endif

/*----------------------------------------------------------
	not sure why, a name conflict?
----------------------------------------------------------*/
#ifdef RPT
#ifdef FIELDS_RPT
#undef FIELDS_RPT
#endif
#define FIELDS_RPT		"rpt.rptname,title,startdate,enddate,rpt.accttype"
#endif

LIBTYPE		MYSQL		MySql;
LIBTYPE		char		StatementOne  [MAXSTATEMENT];
LIBTYPE		char		StatementTwo  [MAXSTATEMENT];
LIBTYPE		char		StatementThree[MAXSTATEMENT];
LIBTYPE		char		WhereClause   [MAXSTATEMENT];
LIBTYPE		char		msgbuf        [MAXSTATEMENT];

#define		MAXERRLEN	80
#define		MAXERRMSGS	25
extern		int			UseErrorSys;
LIBTYPE		char		AcctErrorArray[MAXERRMSGS][MAXERRLEN];
LIBTYPE		int			AcctErrorCount;

#define		MAXSEQNO		25
#define		ACCT_VERBOSE	1

#define		GL_MENU			1
#define		GL_RPT_MENU		2
#define		AR_MENU			4
#define		AP_MENU			8
#define		IC_MENU			16
#define		AM_MENU			32
#define		SYS_MENU		64
#define		ADMIN_MENU		128
#define		ALL_MENUS		1023
#define		LINK_MENU		4096

#ifdef OLD_SKOOL

#define		COLOR_HEADING_BKGD		"#996600"
#define		COLOR_HEADING_TYPE		"#ffffff"
#define		COLOR_BACKGROUND		"#ffff99"
#define		COLOR_FLIP_FLOP_ODD		"#ddffdd"
#define		COLOR_FLIP_FLOP_EVEN	"#ffffdd"
#define		COLOR_BEFORE_START		"#cccccc"
#define		COLOR_AFTER_END			"#ffff66"
#define		COLOR_TAB_SELECTED_BKGD	"#996600"
#define		COLOR_TAB_SELECTED_TYPE	"#ffff66"
#define		COLOR_TAB_OTHER_BKGD	"#ffff99"
#define		COLOR_TAB_OTHER_TYPE	"#000000"

#else

#define		COLOR_HEADING_BKGD		"#c0c0c0"
#define		COLOR_HEADING_TYPE		"#101010"
#define		COLOR_BACKGROUND		"#defdf7"
#define		COLOR_FLIP_FLOP_ODD		"#ddffdd"
#define		COLOR_FLIP_FLOP_EVEN	"#ffffdd"
#define		COLOR_BEFORE_START		"#cccccc"
#define		COLOR_AFTER_END			"#ffff66"
#define		COLOR_TAB_SELECTED_BKGD	"#c0c0c0"
#define		COLOR_TAB_SELECTED_TYPE	"#ffff66"
#define		COLOR_TAB_OTHER_BKGD	"#defdf7"
#define		COLOR_TAB_OTHER_TYPE	"#000000"

#endif

/*--------------------------------------------------------------
-- 1 pre-entered		only on account with import routines
-- 2 not accepted		from import.
-- 3 out of balance		when any saving in entry if >= not accepted,
						or utlity acct_chk       if >= open
						tms 12/03/2020 remove test on >= open from acct_chk
-- 4 open				when saving in entry if > pre-entered and in balance
-- 5 cleared			by clearing
-- 6 reconciled			by reconcile
--------------------------------------------------------------*/
#define		STATUS_PREENT		1
#define		STATUS_ACCEPT		2
#define		STATUS_BALANCE		3
#define		STATUS_OPEN			4
#define		STATUS_RECONCILED	5
#define		STATUS_CLOSED		6

#define		COLOR_PREENT		"#9999cc"
#define		COLOR_ACCEPT		"#99cc99"
#define		COLOR_BALANCE		"#cc9999"
#define		COLOR_SOMETHING		"#cccccc"

/*--------------------------------------------------------------
	common time frames
--------------------------------------------------------------*/
#define		TF_CUR_MONTH		1
#define		TF_CUR_YEAR			2
#define		TF_THREE_MONTHS		3
#define		TF_ONE_YEAR			4
#define		TF_TWO_YEARS		5
#define		TF_THREE_YEARS		6
#define		TF_CUSTOM_DATES		7
#define		TF_ALL				8

/*--------------------------------------------------------------
	Cookies and Session
--------------------------------------------------------------*/
#define	COOKIE_NAME				"acctmenu"
#define	COOKIE_FAIL				"acctmenu.cgi"
#define	COOKIENAME_LENGTH		20
#define	SESSION_ID_SIZE			10

//#define	DBNAME_LENGTH		20
//#define	USERNAME_LENGTH		20
//#define	PASSWORD_LENGTH		42

/*----------------------------------------------------------
	this is a different structure than the standard
	cookie from weblib.
----------------------------------------------------------*/
typedef struct
{
	char	CookieName[COOKIENAME_LENGTH+1];
	char	SessionID [SESSION_ID_SIZE+1];
} COOKIE_RECORD;

typedef struct
{
	char	SessionID [SESSION_ID_SIZE+1];
	char	DbName [DBNAME_LENGTH+1];
	char	UserName [USERNAME_LENGTH];
	long	MemberID;
	int		LoggedIn;
	int		CurrentMenu;
	int		HasGL;
	int		HasAR;
	int		HasAP;
	int		HasIC;
	int		HasAM;
} SESSION_RECORD;

LIBTYPE    SESSION_RECORD  SessionRecord;

/*----------------------------------------------------------
	member roles
----------------------------------------------------------*/
#define		ROLE_DEMO			'D'
#define		ROLE_MEMBER			'M'
#define		ROLE_ADMIN			'A'

/*--------------------------------------------------------------
	prototypes
--------------------------------------------------------------*/

#ifdef TRXD
int InsertOneTrxd ( XTRXD *NewTrxd );
#endif

#ifdef MEMBER
/* LoadMember.c */
int LoadMember ( char *WhereClause , XMEMBER *ptrMEMBER , int PrintErrors );
/* LoadMemberCB.c */
int LoadMemberCB ( char *WhereClause , char *OrderByClause , XMEMBER *ptrMEMBER , int (*CallBack )(), int PrintErrors );
#endif

#ifdef ARINVH
/* LoadArinvh.c */
int LoadArinvh ( char *WhereClause , XARINVH *ptrARINVH , int PrintErrors );
/* LoadArinvhCB.c */
int LoadArinvhCB ( char *WhereClause , char *OrderByClause , XARINVH *ptrARINVH , int (*CallBack )(), int PrintErrors );
#endif

#ifdef ARINVL
/* LoadArinvl.c */
int LoadArinvl ( char *WhereClause , XARINVL *ptrARINVL , int PrintErrors );
/* LoadArinvlCB.c */
int LoadArinvlCB ( char *WhereClause , char *OrderByClause , XARINVL *ptrARINVL , int (*CallBack )(), int PrintErrors );
#endif

#ifdef ARCUST
/* LoadArcust.c */
int LoadArcust ( char *WhereClause , XARCUST *ptrARCUST , int PrintErrors );
/* LoadArcustCB.c */
int LoadArcustCB ( char *WhereClause , char *OrderByClause , XARCUST *ptrARCUST , int (*CallBack )(), int PrintErrors );
#endif

/* AcctTypeDescr.c */
char *AcctTypeDescr ( char AcctType , int Plural );

/* AcctMeta.c */
void AcctMeta ( void );

/* AcctStyle.c */
void AcctStyle (  char *ImageFileName );

/* AddDoubleEntryTrx.c */
void AddDoubleEntryTrx ( long AcctOne , double AmtOne , long AcctTwo , double AmtTwo , char *Ref , char *Payee , DATEVAL Date );

/* CalcTrxBalance.c */
long CalcTrxBalance ( long TrxNumber );

/* CompareDateval.c */
int CompareDateval ( DATEVAL *a , DATEVAL *b );

/* CookieFuncs.c */
COOKIE_RECORD *acctGetCookie ( char CookieName [], int GlobalDebug , FILE *fpDebug );
COOKIE_RECORD *acctMakeCookie ( char CookieName [], char SessionID []);
void acctWriteCookie ( COOKIE_RECORD *AcctCookie , int GlobalDebug , FILE *fpDebug );


/* DeleteAccount.c */
int DeleteAccount ( short AccountNumber );

/* DeleteImport.c */
int DeleteImport ( short AccountNumber );

/* ErrorSysLoaded.c */
void ErrorSysLoaded ( char *FunctionName );

/* Fatal.c */
void Fatal ( char *Message );

/* LoadAccounts.c */
void LoadAccounts ( char *AccountTypes );

/* LoadOneAccount.c */
int LoadOneAccount ( int AccountNumber );

/* LoadOneImport.c */
int LoadOneImport ( int AccountNumber );

/* LoadOneRpt.c */
int LoadOneRpt ( char RptName [], char AccountType );

/* LoadOneTrxd.c */
int LoadOneTrxd ( long TrxNumber , int SeqNumber );

/* LoadOneTrxh.c */
int LoadOneTrxh ( long TrxNumber );

/* LoadSystem.c */
int LoadSystem ( void );

/* LoadUser.c */
int LoadUser ( char *LoginName );

/* NextTrxNum.c */
long NextTrxNum ( int UpdateSystem );

/* ReportUp.c */
void ReportUp ( char *Title , char *DbName , char *OnLoad , char ReportFormat , char *ReportName );

/* safe_convert.c */
double safe_amount_to_atof ( char *String );
long safe_atol ( char *String );
int safe_atoi ( char *String );
short safe_atos ( char *String );

/* SaveError.c */
void SaveError ( char *ErrorMessage );

/* StartDb.c */
int StartDb ( char *DbName );

/* StartUp.c */
void StartUp ( char *Title , char *DbName , int InitDB , int PaintHeader , int WriteMeta, char *OnLoad , int Menu );

/* StatusDescr.c */
char *StatusDescr ( short Status , int Format );

/* StringToDateval.c */
int StringToDateval ( char *String , DATEVAL *Date );

/* TimeFrameDates.c */
int TimeFrameDates ( int TimeFrame , DATEVAL *StartDate , DATEVAL *EndDate );

/* TimeFrameDescr.c */
char *TimeFrameDescr ( int TimeFrame );

/* WebFatal.c */
void WebFatal ( char *Message );

/* Copyright.c */
void Copyright ( void );

/* SessionFuncs.c */
int ReadSession ( char SessionID [], SESSION_RECORD *sr );
int WriteSession ( SESSION_RECORD *sr );
void DumpSession ( SESSION_RECORD *sr );
int DeleteSession ( SESSION_RECORD *sr );

/* AcctGetCookieAndSession.c */
void AcctGetCookieAndSession ( SESSION_RECORD *SessionRecord );
