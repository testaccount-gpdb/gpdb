/*-------------------------------------------------------------------------
 *
 * pg_namespace.h
 *	  definition of the system "namespace" relation (pg_namespace)
 *	  along with the relation's initial contents.
 *
 *
 * Portions Copyright (c) 1996-2008, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $PostgreSQL: pgsql/src/include/catalog/pg_namespace.h,v 1.24 2008/03/27 03:57:34 tgl Exp $
 *
 * NOTES
 *	  the genbki.sh script reads this file and generates .bki
 *	  information from the DATA() statements.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_NAMESPACE_H
#define PG_NAMESPACE_H

#include "catalog/genbki.h"

/* ----------------------------------------------------------------
 *		pg_namespace definition.
 *
 *		cpp turns this into typedef struct FormData_pg_namespace
 *
 *	nspname				name of the namespace
 *	nspowner			owner (creator) of the namespace
 *	nspacl				access privilege list
 * ----------------------------------------------------------------
 */
#define NamespaceRelationId  2615

CATALOG(pg_namespace,2615)
{
	NameData	nspname;
	Oid			nspowner;
	aclitem		nspacl[1];		/* VARIABLE LENGTH FIELD */
} FormData_pg_namespace;

/* GPDB added foreign key definitions for gpcheckcat. */
FOREIGN_KEY(nspowner REFERENCES pg_authid(oid));

/* ----------------
 *		Form_pg_namespace corresponds to a pointer to a tuple with
 *		the format of pg_namespace relation.
 * ----------------
 */
typedef FormData_pg_namespace *Form_pg_namespace;

/* ----------------
 *		compiler constants for pg_namespace
 * ----------------
 */

#define Natts_pg_namespace				3
#define Anum_pg_namespace_nspname		1
#define Anum_pg_namespace_nspowner		2
#define Anum_pg_namespace_nspacl		3


/* ----------------
 * initial contents of pg_namespace
 * ---------------
 */

DATA(insert OID = 11 ( "pg_catalog" PGUID _null_ ));
DESCR("system catalog schema");
#define PG_CATALOG_NAMESPACE 11
DATA(insert OID = 99 ( "pg_toast" PGUID _null_ ));
DESCR("reserved schema for TOAST tables");
#define PG_TOAST_NAMESPACE 99
DATA(insert OID = 3012  ( "pg_bitmapindex" PGUID _null_ ));
DESCR("Reserved schema for internal relations of bitmap indexes");
#define PG_BITMAPINDEX_NAMESPACE 3012
DATA(insert OID = 2200 ( "public" PGUID _null_ ));
DESCR("standard public schema");
#define PG_PUBLIC_NAMESPACE 2200
DATA(insert OID = 6104 ( "pg_aoseg" PGUID _null_ ));
DESCR("Reserved schema for Append Only segment list and eof tables");
#define PG_AOSEGMENT_NAMESPACE 6104


#define IsBuiltInNameSpace(namespaceId) \
	(namespaceId == PG_CATALOG_NAMESPACE || \
	 namespaceId == PG_TOAST_NAMESPACE || \
	 namespaceId == PG_BITMAPINDEX_NAMESPACE || \
	 namespaceId == PG_PUBLIC_NAMESPACE || \
	 namespaceId == PG_AOSEGMENT_NAMESPACE)

/*
 * prototypes for functions in pg_namespace.c
 */
extern Oid	NamespaceCreate(const char *nspName, Oid ownerId);

#endif   /* PG_NAMESPACE_H */
