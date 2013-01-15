/*-------------------------------------------------------------------------
 *
 * defrem.h
 *	  POSTGRES define and remove utility definitions.
 *
 *
 * Portions Copyright (c) 1996-2013, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/commands/defrem.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef DEFREM_H
#define DEFREM_H

#include "nodes/parsenodes.h"

/* commands/dropcmds.c */
extern void RemoveObjects(DropStmt *stmt);

/* commands/indexcmds.c */
extern Oid DefineIndex(IndexStmt *stmt,
			Oid indexRelationId,
			bool is_alter_table,
			bool check_rights,
			bool skip_build,
			bool quiet);
extern Oid ReindexIndex(RangeVar *indexRelation, bool concurrent);
extern Oid ReindexTable(RangeVar *relation, bool concurrent);
extern Oid ReindexDatabase(const char *databaseName,
							bool do_system, bool do_user, bool concurrent);
extern bool ReindexRelationsConcurrently(List *relationIds);
extern char *makeObjectName(const char *name1, const char *name2,
			   const char *label);
extern char *ChooseRelationName(const char *name1, const char *name2,
				   const char *label, Oid namespaceid);
extern bool CheckIndexCompatible(Oid oldId,
					 RangeVar *heapRelation,
					 char *accessMethodName,
					 List *attributeList,
					 List *exclusionOpNames);
extern Oid	GetDefaultOpClass(Oid type_id, Oid am_id);

/* commands/functioncmds.c */
extern Oid CreateFunction(CreateFunctionStmt *stmt, const char *queryString);
extern void RemoveFunctionById(Oid funcOid);
extern void SetFunctionReturnType(Oid funcOid, Oid newRetType);
extern void SetFunctionArgType(Oid funcOid, int argIndex, Oid newArgType);
extern Oid RenameFunction(List *name, List *argtypes, const char *newname);
extern Oid AlterFunction(AlterFunctionStmt *stmt);
extern Oid CreateCast(CreateCastStmt *stmt);
extern void DropCastById(Oid castOid);
extern Oid AlterFunctionNamespace(List *name, List *argtypes, bool isagg,
								  const char *newschema);
extern Oid	AlterFunctionNamespace_oid(Oid procOid, Oid nspOid);
extern void ExecuteDoStmt(DoStmt *stmt);
extern Oid	get_cast_oid(Oid sourcetypeid, Oid targettypeid, bool missing_ok);

/* commands/operatorcmds.c */
extern Oid DefineOperator(List *names, List *parameters);
extern void RemoveOperatorById(Oid operOid);

/* commands/aggregatecmds.c */
extern Oid DefineAggregate(List *name, List *args, bool oldstyle,
				List *parameters);
extern Oid RenameAggregate(List *name, List *args, const char *newname);

/* commands/opclasscmds.c */
extern Oid DefineOpClass(CreateOpClassStmt *stmt);
extern Oid DefineOpFamily(CreateOpFamilyStmt *stmt);
extern Oid AlterOpFamily(AlterOpFamilyStmt *stmt);
extern void RemoveOpClassById(Oid opclassOid);
extern void RemoveOpFamilyById(Oid opfamilyOid);
extern void RemoveAmOpEntryById(Oid entryOid);
extern void RemoveAmProcEntryById(Oid entryOid);
extern Oid RenameOpClass(List *name, const char *access_method, const char *newname);
extern Oid RenameOpFamily(List *name, const char *access_method, const char *newname);
extern Oid	get_am_oid(const char *amname, bool missing_ok);
extern Oid	get_opclass_oid(Oid amID, List *opclassname, bool missing_ok);
extern Oid	get_opfamily_oid(Oid amID, List *opfamilyname, bool missing_ok);

/* commands/tsearchcmds.c */
extern Oid DefineTSParser(List *names, List *parameters);
extern Oid RenameTSParser(List *oldname, const char *newname);
extern void RemoveTSParserById(Oid prsId);

extern Oid DefineTSDictionary(List *names, List *parameters);
extern Oid RenameTSDictionary(List *oldname, const char *newname);
extern void RemoveTSDictionaryById(Oid dictId);
extern Oid AlterTSDictionary(AlterTSDictionaryStmt *stmt);

extern Oid DefineTSTemplate(List *names, List *parameters);
extern Oid RenameTSTemplate(List *oldname, const char *newname);
extern void RemoveTSTemplateById(Oid tmplId);

extern Oid DefineTSConfiguration(List *names, List *parameters);
extern Oid RenameTSConfiguration(List *oldname, const char *newname);
extern void RemoveTSConfigurationById(Oid cfgId);
extern Oid AlterTSConfiguration(AlterTSConfigurationStmt *stmt);

extern text *serialize_deflist(List *deflist);
extern List *deserialize_deflist(Datum txt);

/* commands/foreigncmds.c */
extern Oid RenameForeignServer(const char *oldname, const char *newname);
extern Oid RenameForeignDataWrapper(const char *oldname, const char *newname);
extern Oid AlterForeignServerOwner(const char *name, Oid newOwnerId);
extern void AlterForeignServerOwner_oid(Oid, Oid newOwnerId);
extern Oid AlterForeignDataWrapperOwner(const char *name, Oid newOwnerId);
extern void AlterForeignDataWrapperOwner_oid(Oid fwdId, Oid newOwnerId);
extern Oid CreateForeignDataWrapper(CreateFdwStmt *stmt);
extern Oid AlterForeignDataWrapper(AlterFdwStmt *stmt);
extern void RemoveForeignDataWrapperById(Oid fdwId);
extern Oid CreateForeignServer(CreateForeignServerStmt *stmt);
extern Oid AlterForeignServer(AlterForeignServerStmt *stmt);
extern void RemoveForeignServerById(Oid srvId);
extern Oid CreateUserMapping(CreateUserMappingStmt *stmt);
extern Oid AlterUserMapping(AlterUserMappingStmt *stmt);
extern Oid RemoveUserMapping(DropUserMappingStmt *stmt);
extern void RemoveUserMappingById(Oid umId);
extern void CreateForeignTable(CreateForeignTableStmt *stmt, Oid relid);
extern Datum transformGenericOptions(Oid catalogId,
						Datum oldOptions,
						List *options,
						Oid fdwvalidator);

/* support routines in commands/define.c */

extern char *defGetString(DefElem *def);
extern double defGetNumeric(DefElem *def);
extern bool defGetBoolean(DefElem *def);
extern int64 defGetInt64(DefElem *def);
extern List *defGetQualifiedName(DefElem *def);
extern TypeName *defGetTypeName(DefElem *def);
extern int	defGetTypeLength(DefElem *def);
extern DefElem *defWithOids(bool value);

#endif   /* DEFREM_H */
