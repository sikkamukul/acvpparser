/*
 * Copyright (C) 2019 - 2023, Stephan Mueller <smueller@chronox.de>
 *
 * License: see LICENSE file
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT KDF_108LL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef _PARSER_TLS12_H
#define _PARSER_TLS12_H

#include "parser.h"
#include "parser_flags.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief TLS PRF testing context
 *
 * @var hashalg [in] Hash algorithm to be used for PRF.
 * @var pre_master_secret_length [in] Length of pre-master secret in bits
 *					(information only as the
 *					@var pre_master_secret contains the
 *					full data).
 * @var key_block_length [in] Length of the key block to be generated in bits.
 * @var session_hash [in] the hash value of the concatenated handshake messages
 * @var client_random [in] Client random number
 * @var server_random [in] Server random number
 * @var pre_master_secret [in] Pre-master secret for the TLS operation.
 * @var master_secret [out] Master secret generated by the PRF -- the length
 *			      is equal to the @var pre_master_secret.
 * @var key_block [out] Generated key block of the length given with
 *			  @var key_block_length.
 */
struct tls12_data {
	uint64_t hashalg;
	uint32_t pre_master_secret_length;
	uint32_t key_block_length;
	struct buffer session_hash;
	struct buffer client_random;
	struct buffer server_random;
	struct buffer pre_master_secret;

	struct buffer master_secret;
	struct buffer key_block;
};

/**
 * @brief Callback data structure that must be implemented by the backend.
 *
 * All functions return 0 on success or != 0 on error.
 *
 * @var tls12 Perform a TLS 1.2 PRF operation
 */
struct tls12_backend {
	int (*tls12)(struct tls12_data *data, flags_t parsed_flags);
};

void register_tls12_impl(struct tls12_backend *implementation);

#ifdef __cplusplus
}
#endif

#endif /* _PARSER_TLS12_H */