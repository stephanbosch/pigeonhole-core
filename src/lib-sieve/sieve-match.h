/* Copyright (c) 2002-2010 Dovecot Sieve authors, see the included COPYING file
 */
 
#ifndef __SIEVE_MATCH_H
#define __SIEVE_MATCH_H

#include "sieve-common.h"

/*
 * Matching context
 */
 
struct sieve_match_key_extractor {
	int (*init)(void **context, string_t *raw_key);
	int (*extract_key)(void *context, const char **key, size_t *size);
};

struct sieve_match_context {
	pool_t pool;

	const struct sieve_runtime_env *runenv;
	const struct sieve_match_type *match_type;
	const struct sieve_comparator *comparator;
	const struct sieve_match_key_extractor *kextract;

	struct sieve_coded_stringlist *key_list;


	void *data;
};

/*
 * Matching implementation
 */

struct sieve_match_context *sieve_match_begin
	(const struct sieve_runtime_env *renv,
		const struct sieve_match_type *mtch, 
		const struct sieve_comparator *cmp, 
		const struct sieve_match_key_extractor *kextract,
		struct sieve_coded_stringlist *key_list);
int sieve_match_value
	(struct sieve_match_context *mctx, const char *value, size_t val_size);
int sieve_match_end(struct sieve_match_context **mctx);

/*
 * Read matching operands
 */
 
enum sieve_match_opt_operand {
	SIEVE_MATCH_OPT_END,
	SIEVE_MATCH_OPT_COMPARATOR,
	SIEVE_MATCH_OPT_MATCH_TYPE,
	SIEVE_MATCH_OPT_LAST
};

int sieve_match_opr_optional_dump
	(const struct sieve_dumptime_env *denv, sieve_size_t *addres, int *opt_code);

int sieve_match_opr_optional_read
	(const struct sieve_runtime_env *renv, sieve_size_t *address, int *opt_code,
		struct sieve_comparator *cmp, struct sieve_match_type *mcht);

#endif /* __SIEVE_MATCH_H */
