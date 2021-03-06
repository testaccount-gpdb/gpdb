#-------------------------------------------------------------------------
#
# Makefile for parser
#
# $PostgreSQL: pgsql/src/backend/parser/Makefile,v 1.46 2008/02/19 10:30:07 petere Exp $
#
#-------------------------------------------------------------------------

subdir = src/backend/parser
top_builddir = ../../..
include $(top_builddir)/src/Makefile.global

override CPPFLAGS := -I$(srcdir) $(CPPFLAGS)

OBJS= analyze.o gram.o keywords.o parser.o parse_agg.o parse_cte.o parse_clause.o \
      parse_expr.o parse_func.o parse_node.o parse_oper.o parse_relation.o \
      parse_type.o parse_coerce.o parse_target.o scansup.o parse_utilcmd.o kwlookup.o \
      parse_partition.o

FLEXFLAGS = -CF

include $(top_srcdir)/src/backend/common.mk


# scan is compiled as part of gram
gram.o: $(srcdir)/scan.c


# There is no correct way to write a rule that generates two files.
# Rules with two targets don't have that meaning, they are merely
# shorthand for two otherwise separate rules.  To be safe for parallel
# make, we must chain the dependencies like this.  The semicolon is
# important, otherwise make will choose the built-in rule for
# gram.y=>gram.c.

$(srcdir)/gram.h: $(srcdir)/gram.c ;

$(srcdir)/gram.c: gram.y
	$(PERL) $(srcdir)/check_keywords.pl $< $(top_srcdir)/src/include/parser/kwlist.h
ifdef BISON
	$(BISON) -d $(BISONFLAGS) -o $@ $<
else
	@$(missing) bison $< $@
endif


$(srcdir)/scan.c: scan.l
ifdef FLEX
	$(FLEX) $(FLEXFLAGS) -o'$@' $<
else
	@$(missing) flex $< $@
endif


# Force these dependencies to be known even without dependency info built:
gram.o keywords.o parser.o: $(srcdir)/gram.h


# gram.c, gram.h, and scan.c are in the distribution tarball, so they
# are not cleaned here.
clean: 
# And the garbage that might have been left behind by partial build:
	@rm -f y.tab.h y.tab.c y.output lex.yy.c gram.tab.c gram.tab.h
