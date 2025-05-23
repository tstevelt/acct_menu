PROG = acctmenu
LIB = acctmenu.a

#MYSQL_FLAGS = -lz -lcrypt -lnsl -lm -lssl -lcrypto
MYSQL_DIR = /usr/lib64
MYSQL_FLAGS = -lz -lcrypt -lm -lssl -lcrypto
XLIB = /usr/local/lib64/acctlib.a /usr/local/lib64/weblib.a /usr/local/lib64/dbylib.a /usr/local/lib64/shslib.a $(MYSQL_DIR)/libmysqlclient.so $(MYSQL_FLAGS)
DEF = /usr/local/include
#PRG = /home/httpd/acct/html/$(PROG).cgi
DIR = /var/www/vhosts/acct/html
PRG = $(DIR)/$(PROG).cgi

FILES = \
	$(LIB)(acctmenu.o)		\
	$(LIB)(ChkInput.o)		\
	$(LIB)(ExecLogin.o)		\
	$(LIB)(ExecTwoFactor.o)		\
	$(LIB)(FormEnd.o)		\
	$(LIB)(FormStart.o)		\
	$(LIB)(GetInput.o)		\
	$(LIB)(MenuStartUp.o)		\
	$(LIB)(PaintForgot.o)	\
	$(LIB)(PaintLogin.o)	\
	$(LIB)(PaintMenu.o)		\
	$(LIB)(PaintShowLicense.o)	\
	$(LIB)(PaintSlideShow.o)		\
	$(LIB)(PaintTop.o)		\
	$(LIB)(PaintTwoFactor.o)		\
	$(LIB)(SendForgot.o)	\
	$(LIB)(SendTwoFactor.o)	\
	$(LIB)(UpdateMemberLogin.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)
	cp -pv $(PRG) /var/www/vhosts/shs_acct/html/

$(LIB): $(FILES)

$(FILES): acctmenu.h $(DEF)/acctlib.h $(DEF)/fileacct.h $(DEF)/weblib.h $(DEF)/dbylib.h $(DEF)/shslib.h

js:
	cp -pv acctmenu.js $(DIR)/acctmenu.js
	cp -pv acctmenu.js /var/www/vhosts/shs_acct/html/

html:
	cp -pv todo.html $(DIR)/todo.html
	cp -pv todo.html /var/www/vhosts/shs_acct/html/

clean:
	rm -f $(LIB)

all:
	make clean
	make
	make html
	make js

.PRECIOUS: $(LIB)

