/*--------------------------------------------------------
	filemysql.h for schema acct.schema
--------------------------------------------------------*/
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
#ifndef FILEACCT_H
#define FILEACCT_H

#ifndef TYPE
#ifdef MAIN
#define  TYPE   /* */
#else
#define  TYPE   extern
#endif
#endif

#ifdef ACCOUNT
#define TABLE_account 1
typedef struct
{
	long	xacctnum;
	char 	xaccttype[2];
	char 	xacctname[31];
	char 	xextranum[21];
	char 	xextraline[21];
	long	xopenbal;
	long	xcurrbal;
	DATEVAL 	xrecondate;
	long	xreconbal;
	short	xdaterange;
	long	xinserted;
	long	xupdated;
} XACCOUNT;
TYPE XACCOUNT xaccount;
#define FIELDS_ACCOUNT  "acctnum,accttype,acctname,extranum,extraline,openbal,currbal,recondate,reconbal,daterange,inserted,updated"
#define	ACCOUNT_acctnum	0
#define	ACCOUNT_accttype	1
#define	ACCOUNT_acctname	2
#define	ACCOUNT_extranum	3
#define	ACCOUNT_extraline	4
#define	ACCOUNT_openbal	5
#define	ACCOUNT_currbal	6
#define	ACCOUNT_recondate	7
#define	ACCOUNT_reconbal	8
#define	ACCOUNT_daterange	9
#define	ACCOUNT_inserted	10
#define	ACCOUNT_updated	11
#endif

#ifdef ARCUST
#define TABLE_arcust 2
typedef struct
{
	unsigned long	xid;
	char 	xname[61];
	char 	xaddr1[61];
	char 	xaddr2[61];
	char 	xcity[41];
	char 	xstate[5];
	char 	xzipcode[11];
	char 	xphone[21];
	char 	xcontact[21];
	long	xinserted;
	long	xupdated;
} XARCUST;
TYPE XARCUST xarcust;
#define FIELDS_ARCUST  "id,name,addr1,addr2,city,state,zipcode,phone,contact,inserted,updated"
#define	ARCUST_id	0
#define	ARCUST_name	1
#define	ARCUST_addr1	2
#define	ARCUST_addr2	3
#define	ARCUST_city	4
#define	ARCUST_state	5
#define	ARCUST_zipcode	6
#define	ARCUST_phone	7
#define	ARCUST_contact	8
#define	ARCUST_inserted	9
#define	ARCUST_updated	10
#endif

#ifdef ARINVH
#define TABLE_arinvh 3
typedef struct
{
	unsigned long	xid;
	unsigned long	xcustomer;
	DATEVAL 	xinvdate;
	char 	xterms[21];
	char 	xstatus[2];
	char 	xponum[21];
	long	xdiscount;
	long	xpayment;
	char 	xrefnum[21];
	DATEVAL 	xpaydate;
	long	xinserted;
	long	xupdated;
} XARINVH;
TYPE XARINVH xarinvh;
#define FIELDS_ARINVH  "id,customer,invdate,terms,status,ponum,discount,payment,refnum,paydate,inserted,updated"
#define	ARINVH_id	0
#define	ARINVH_customer	1
#define	ARINVH_invdate	2
#define	ARINVH_terms	3
#define	ARINVH_status	4
#define	ARINVH_ponum	5
#define	ARINVH_discount	6
#define	ARINVH_payment	7
#define	ARINVH_refnum	8
#define	ARINVH_paydate	9
#define	ARINVH_inserted	10
#define	ARINVH_updated	11
#endif

#ifdef ARINVL
#define TABLE_arinvl 4
typedef struct
{
	unsigned long	xid;
	unsigned long	xinvoice;
	char 	xdescr[513];
	long	xamount;
} XARINVL;
TYPE XARINVL xarinvl;
#define FIELDS_ARINVL  "id,invoice,descr,amount"
#define	ARINVL_id	0
#define	ARINVL_invoice	1
#define	ARINVL_descr	2
#define	ARINVL_amount	3
#endif

#ifdef IMPORT
#define TABLE_import 5
typedef struct
{
	long	xacctnum;
	char 	xwebsite[257];
	char 	xlogin[21];
	DATEVAL 	xprevious;
	char 	xpayments[2];
	char 	xautoparse[2];
	char 	xparsefunc[21];
	short	xheadrows;
	short	xcolcount;
	short	xrefnum;
	short	xdate;
	short	xpayee;
	short	xincrease;
	char 	xincsign[2];
	short	xdecrease;
	char 	xdecsign[2];
	char 	xreverse[2];
} XIMPORT;
TYPE XIMPORT ximport;
#define FIELDS_IMPORT  "acctnum,website,login,previous,payments,autoparse,parsefunc,headrows,colcount,refnum,date,payee,increase,incsign,decrease,decsign,reverse"
#define	IMPORT_acctnum	0
#define	IMPORT_website	1
#define	IMPORT_login	2
#define	IMPORT_previous	3
#define	IMPORT_payments	4
#define	IMPORT_autoparse	5
#define	IMPORT_parsefunc	6
#define	IMPORT_headrows	7
#define	IMPORT_colcount	8
#define	IMPORT_refnum	9
#define	IMPORT_date	10
#define	IMPORT_payee	11
#define	IMPORT_increase	12
#define	IMPORT_incsign	13
#define	IMPORT_decrease	14
#define	IMPORT_decsign	15
#define	IMPORT_reverse	16
#endif

#ifdef MEMBER
#define TABLE_member 6
typedef struct
{
	unsigned long	xid;
	char 	xmname[31];
	char 	xmemail[81];
	char 	xmphone[13];
	char 	xmcarrier[13];
	char 	xmpassword[43];
	char 	xmpasstwo[11];
	char 	xmtwopref[2];
	char 	xmrole[2];
	char 	xmipaddr[17];
	DATEVAL 	xminsdt;
	DATEVAL 	xmlogdt;
	long	xinserted;
	long	xupdated;
} XMEMBER;
TYPE XMEMBER xmember;
#define FIELDS_MEMBER  "id,Mname,Memail,Mphone,Mcarrier,Mpassword,Mpasstwo,Mtwopref,Mrole,Mipaddr,Minsdt,Mlogdt,inserted,updated"
#define	MEMBER_id	0
#define	MEMBER_Mname	1
#define	MEMBER_Memail	2
#define	MEMBER_Mphone	3
#define	MEMBER_Mcarrier	4
#define	MEMBER_Mpassword	5
#define	MEMBER_Mpasstwo	6
#define	MEMBER_Mtwopref	7
#define	MEMBER_Mrole	8
#define	MEMBER_Mipaddr	9
#define	MEMBER_Minsdt	10
#define	MEMBER_Mlogdt	11
#define	MEMBER_inserted	12
#define	MEMBER_updated	13
#endif

#ifdef RPT
#define TABLE_rpt 7
typedef struct
{
	char 	xrptname[21];
	char 	xtitle[51];
	DATEVAL 	xstartdate;
	DATEVAL 	xenddate;
	char 	xaccttype[2];
} XRPT;
TYPE XRPT xrpt;
#define FIELDS_RPT  "rptname,title,startdate,enddate,accttype"
#define	RPT_rptname	0
#define	RPT_title	1
#define	RPT_startdate	2
#define	RPT_enddate	3
#define	RPT_accttype	4
#endif

#ifdef RPTACCT
#define TABLE_rptacct 8
typedef struct
{
	char 	xrptname[21];
	short	xseqnum;
	long	xacctnum;
} XRPTACCT;
TYPE XRPTACCT xrptacct;
#define FIELDS_RPTACCT  "rptname,seqnum,acctnum"
#define	RPTACCT_rptname	0
#define	RPTACCT_seqnum	1
#define	RPTACCT_acctnum	2
#endif

#ifdef SYSTEM
#define TABLE_system 9
typedef struct
{
	char 	xname[31];
	char 	xaddress[31];
	char 	xcity[31];
	char 	xstate[21];
	char 	xzipcode[21];
	char 	xphone[21];
	short	xassetnext;
	short	xliabnext;
	short	xequitynext;
	short	xincomenext;
	short	xexpensenext;
	long	xtrxnext;
	char 	xshowamts[2];
	DATEVAL 	xclosedate;
	char 	xreconcile[2];
	char 	xprintdest[2];
	short	xnumtrxnew;
	short	xtrxpermonth;
	DATEVAL 	xtrxstartdate;
	long	xtrxstarttrx;
	short	xtrxrollover;
	char 	xclosemethod[2];
	short	xretainequity;
	short	xretainincome;
	short	xnumtrxedit;
	char 	xtwofactor[2];
} XSYSTEM;
TYPE XSYSTEM xsystem;
#define FIELDS_SYSTEM  "name,address,city,state,zipcode,phone,assetnext,liabnext,equitynext,incomenext,expensenext,trxnext,showamts,closedate,reconcile,printdest,numtrxnew,trxpermonth,trxstartdate,trxstarttrx,trxrollover,closemethod,retainequity,retainincome,numtrxedit,twofactor"
#define	SYSTEM_name	0
#define	SYSTEM_address	1
#define	SYSTEM_city	2
#define	SYSTEM_state	3
#define	SYSTEM_zipcode	4
#define	SYSTEM_phone	5
#define	SYSTEM_assetnext	6
#define	SYSTEM_liabnext	7
#define	SYSTEM_equitynext	8
#define	SYSTEM_incomenext	9
#define	SYSTEM_expensenext	10
#define	SYSTEM_trxnext	11
#define	SYSTEM_showamts	12
#define	SYSTEM_closedate	13
#define	SYSTEM_reconcile	14
#define	SYSTEM_printdest	15
#define	SYSTEM_numtrxnew	16
#define	SYSTEM_trxpermonth	17
#define	SYSTEM_trxstartdate	18
#define	SYSTEM_trxstarttrx	19
#define	SYSTEM_trxrollover	20
#define	SYSTEM_closemethod	21
#define	SYSTEM_retainequity	22
#define	SYSTEM_retainincome	23
#define	SYSTEM_numtrxedit	24
#define	SYSTEM_twofactor	25
#endif

#ifdef TRXD
#define TABLE_trxd 10
typedef struct
{
	long	xtrxnum;
	short	xseqnum;
	long	xacctnum;
	char 	xpayee[41];
	long	xamount;
} XTRXD;
TYPE XTRXD xtrxd;
#define FIELDS_TRXD  "trxnum,seqnum,acctnum,payee,amount"
#define	TRXD_trxnum	0
#define	TRXD_seqnum	1
#define	TRXD_acctnum	2
#define	TRXD_payee	3
#define	TRXD_amount	4
#endif

#ifdef TRXH
#define TABLE_trxh 11
typedef struct
{
	long	xtrxnum;
	short	xstatus;
	char 	xrefnum[9];
	DATEVAL 	xtrxdate;
} XTRXH;
TYPE XTRXH xtrxh;
#define FIELDS_TRXH  "trxnum,status,refnum,trxdate"
#define	TRXH_trxnum	0
#define	TRXH_status	1
#define	TRXH_refnum	2
#define	TRXH_trxdate	3
#endif

#endif
