/* Copyright (c) 2018 The Johns Hopkins University/Applied Physics Laboratory
 * All Rights Reserved.
 *
 * This file is dual licensed under the terms of the Apache 2.0 License and
 * the BSD 3-Clause License. See the LICENSE file in the root of this
 * repository for more information.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "kmip.h"
#include "kmip_memset.h"

/*
Miscellaneous Utilities
*/

size_t
kmip_strnlen_s(const char *str, size_t strsz)
{
    if(str == NULL)
    {
        return(0);
    }
    
    size_t length = 0;
    for(const char *i = str; *i != 0; i++)
    {
        length++;
        if(length >= strsz)
        {
            return(strsz);
        }
    }
    return(length);
}

LinkedListItem *
kmip_linked_list_pop(LinkedList *list)
{
    if(list == NULL)
    {
        return(NULL);
    }
    
    LinkedListItem *popped = list->head;
    
    if(popped != NULL)
    {
        list->head = popped->next;
        popped->next = NULL;
        popped->prev = NULL;
        
        if(list->head != NULL)
        {
            list->head->prev = NULL;
        }

        if(popped == list->tail)
        {
            list->tail = NULL;
        }
        
        if(list->size > 0)
        {
            list->size -= 1;
        }
    }
    else
    {
        if(list->size != 0)
        {
            list->size = 0;
        }
    }
    
    return(popped);
}

void
kmip_linked_list_push(LinkedList *list, LinkedListItem *item)
{
    if(list != NULL && item != NULL)
    {
        LinkedListItem *head = list->head;
        list->head = item;
        item->next = head;
        item->prev = NULL;
        list->size += 1;
        
        if(head != NULL)
        {
            head->prev = item;
        }

        if(list->tail == NULL)
        {
            list->tail = list->head;
        }
    }
}

void
kmip_linked_list_enqueue(LinkedList *list, LinkedListItem *item)
{
    if(list != NULL && item != NULL)
    {
        LinkedListItem *tail = list->tail;
        list->tail = item;
        item->next = NULL;
        item->prev = tail;
        list->size += 1;

        if(tail != NULL)
        {
            tail->next = item;
        }

        if(list->head == NULL)
        {
            list->head = list->tail;
        }
    }
}

/*
Memory Handlers
*/

void *
kmip_calloc(void *state, size_t num, size_t size)
{
    (void)state;
    return(calloc(num, size));
}

void *
kmip_realloc(void *state, void *ptr, size_t size)
{
    (void)state;
    return(realloc(ptr, size));
}

void
kmip_free(void *state, void *ptr)
{
    (void)state;
    free(ptr);
    return;
}

/* TODO (ph) Consider replacing this with memcpy_s, ala memset_s. */
void *
kmip_memcpy(void *state, void *destination, const void *source, size_t size)
{
    (void)state;
    return(memcpy(destination, source, size));
}

/*
Enumeration Utilities
*/

static const char *kmip_attribute_names[] = {
    "Unique Identifier",
    "Name",
    "Object Type",
    "Cryptographic Algorithm",
    "Cryptographic Length",
    "Cryptographic Parameters",
    "Cryptographic Domain Parameters",
    "Certificate Type",
    "Certificate Length",
    "X.509 Certificate Identifier",
    "X.509 Certificate Subject",
    "X.509 Certificate Issuer",
    "Certificate Identifier",
    "Certificate Subject",
    "Certificate Issuer",
    "Digital Signature Algorithm",
    "Digest",
    "Operation Policy Name",
    "Cryptographic Usage Mask",
    "Lease Time",
    "Usage Limits",
    "State",
    "Initial Date",
    "Activation Date",
    "Process Start Date",
    "Protect Stop Date",
    "Deactivation Date",
    "Destroy Date",
    "Compromise Occurrence Date",
    "Compromise Date",
    "Revocation Reason",
    "Archive Date",
    "Object Group",
    "Fresh",
    "Link",
    "Application Specific Information",
    "Contact Information",
    "Last Change Date",
    "Alternative Name",
    "Key Value Present",
    "Key Value Location",
    "Original Creation Date",
    "Random Number Generator",
    "PKCS#12 Friendly Name",
    "Description",
    "Comment",
    "Sensitive",
    "Always Sensitive",
    "Extractable",
    "Never Extractable",
    "Key Format Type",
    "Unknown" /* Catch all for unsupported enumerations */
};

int
kmip_get_enum_string_index(enum tag t)
{
    switch(t)
    {
        case KMIP_TAG_UNIQUE_IDENTIFIER:
        return(0);
        break;

        case KMIP_TAG_NAME:
        return(1);
        break;

        case KMIP_TAG_OBJECT_TYPE:
        return(2);
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM:
        return(3);
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_LENGTH:
        return(4);
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS:
        return(5);
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:
        return(6);
        break;

        case KMIP_TAG_CERTIFICATE_TYPE:
        return(7);
        break;

        case KMIP_TAG_CERTIFICATE_LENGTH:
        return(8);
        break;

        case KMIP_TAG_X509_CERTIFICATE_IDENTIFIER:
        return(9);
        break;

        case KMIP_TAG_X509_CERTIFICATE_SUBJECT:
        return(10);
        break;

        case KMIP_TAG_X509_CERTIFICATE_ISSUER:
        return(11);
        break;

        case KMIP_TAG_CERTIFICATE_IDENTIFIER:
        return(12);
        break;

        case KMIP_TAG_CERTIFICATE_SUBJECT:
        return(13);
        break;

        case KMIP_TAG_CERTIFICATE_ISSUER:
        return(14);
        break;

        case KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM:
        return(15);
        break;

        case KMIP_TAG_DIGEST:
        return(16);
        break;

        case KMIP_TAG_OPERATION_POLICY_NAME:
        return(17);
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK:
        return(18);
        break;

        case KMIP_TAG_LEASE_TIME:
        return(19);
        break;

        case KMIP_TAG_USAGE_LIMITS:
        return(20);
        break;

        case KMIP_TAG_STATE:
        return(21);
        break;

        case KMIP_TAG_INITIAL_DATE:
        return(22);
        break;

        case KMIP_TAG_ACTIVATION_DATE:
        return(23);
        break;

        case KMIP_TAG_PROCESS_START_DATE:
        return(24);
        break;

        case KMIP_TAG_PROTECT_STOP_DATE:
        return(25);
        break;

        case KMIP_TAG_DEACTIVATION_DATE:
        return(26);
        break;

        case KMIP_TAG_DESTROY_DATE:
        return(27);
        break;

        case KMIP_TAG_COMPROMISE_OCCURRENCE_DATE:
        return(28);
        break;

        case KMIP_TAG_COMPROMISE_DATE:
        return(29);
        break;

        case KMIP_TAG_REVOCATION_REASON:
        return(30);
        break;

        case KMIP_TAG_ARCHIVE_DATE:
        return(31);
        break;

        case KMIP_TAG_OBJECT_GROUP:
        return(32);
        break;

        case KMIP_TAG_FRESH:
        return(33);
        break;

        case KMIP_TAG_LINK:
        return(34);
        break;

        case KMIP_TAG_APPLICATION_SPECIFIC_INFORMATION:
        return(35);
        break;

        case KMIP_TAG_CONTACT_INFORMATION:
        return(36);
        break;

        case KMIP_TAG_LAST_CHANGE_DATE:
        return(37);
        break;

        case KMIP_TAG_ALTERNATIVE_NAME:
        return(38);
        break;

        case KMIP_TAG_KEY_VALUE_PRESENT:
        return(39);
        break;

        case KMIP_TAG_KEY_VALUE_LOCATION:
        return(40);
        break;

        case KMIP_TAG_ORIGINAL_CREATION_DATE:
        return(41);
        break;

        case KMIP_TAG_RANDOM_NUMBER_GENERATOR:
        return(42);
        break;

        case KMIP_TAG_PKCS_12_FRIENDLY_NAME:
        return(43);
        break;

        case KMIP_TAG_DESCRIPTION:
        return(44);
        break;

        case KMIP_TAG_COMMENT:
        return(45);
        break;

        case KMIP_TAG_SENSITIVE:
        return(46);
        break;

        case KMIP_TAG_ALWAYS_SENSITIVE:
        return(47);
        break;

        case KMIP_TAG_EXTRACTABLE:
        return(48);
        break;

        case KMIP_TAG_NEVER_EXTRACTABLE:
        return(49);
        break;

        case KMIP_TAG_KEY_FORMAT_TYPE:
        return(50);
        break;

        default:
        return(51);
        break;
    };
}

int
kmip_check_enum_value(enum kmip_version version, enum tag t, int value)
{
    int m;
    switch(t)
    {
        case KMIP_TAG_ATTESTATION_TYPE:
        switch(value)
        {
            case KMIP_ATTEST_TPM_QUOTE:
            case KMIP_ATTEST_TCG_INTEGRITY_REPORT:
            case KMIP_ATTEST_SAML_ASSERTION:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_BATCH_ERROR_CONTINUATION_OPTION:
        switch(value)
        {
            case KMIP_BATCH_CONTINUE:
            case KMIP_BATCH_STOP:
            case KMIP_BATCH_UNDO:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_BLOCK_CIPHER_MODE:
        switch(value)
        {
            case KMIP_BLOCK_CBC:
            case KMIP_BLOCK_ECB:
            case KMIP_BLOCK_PCBC:
            case KMIP_BLOCK_CFB:
            case KMIP_BLOCK_OFB:
            case KMIP_BLOCK_CTR:
            case KMIP_BLOCK_CMAC:
            case KMIP_BLOCK_CCM:
            case KMIP_BLOCK_GCM:
            case KMIP_BLOCK_CBC_MAC:
            case KMIP_BLOCK_XTS:
            case KMIP_BLOCK_AES_KEY_WRAP_PADDING:
            case KMIP_BLOCK_NIST_KEY_WRAP:
            case KMIP_BLOCK_X9102_AESKW:
            case KMIP_BLOCK_X9102_TDKW:
            case KMIP_BLOCK_X9102_AKW1:
            case KMIP_BLOCK_X9102_AKW2:
            return(KMIP_OK);
            break;
            
            case KMIP_BLOCK_AEAD:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_CREDENTIAL_TYPE:
        switch(value)
        {
            case KMIP_CRED_USERNAME_AND_PASSWORD:
            return(KMIP_OK);
            break;
            
            case KMIP_CRED_DEVICE:
            if(version >= KMIP_1_1)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_CRED_ATTESTATION:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            /* KMIP 2.0 */
            case KMIP_CRED_ONE_TIME_PASSWORD:
            case KMIP_CRED_HASHED_PASSWORD:
            case KMIP_CRED_TICKET:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM:
        switch(value)
        {
            case KMIP_CRYPTOALG_DES:
            case KMIP_CRYPTOALG_TRIPLE_DES:
            case KMIP_CRYPTOALG_AES:
            case KMIP_CRYPTOALG_RSA:
            case KMIP_CRYPTOALG_DSA:
            case KMIP_CRYPTOALG_ECDSA:
            case KMIP_CRYPTOALG_HMAC_SHA1:
            case KMIP_CRYPTOALG_HMAC_SHA224:
            case KMIP_CRYPTOALG_HMAC_SHA256:
            case KMIP_CRYPTOALG_HMAC_SHA384:
            case KMIP_CRYPTOALG_HMAC_SHA512:
            case KMIP_CRYPTOALG_HMAC_MD5:
            case KMIP_CRYPTOALG_DH:
            case KMIP_CRYPTOALG_ECDH:
            case KMIP_CRYPTOALG_ECMQV:
            case KMIP_CRYPTOALG_BLOWFISH:
            case KMIP_CRYPTOALG_CAMELLIA:
            case KMIP_CRYPTOALG_CAST5:
            case KMIP_CRYPTOALG_IDEA:
            case KMIP_CRYPTOALG_MARS:
            case KMIP_CRYPTOALG_RC2:
            case KMIP_CRYPTOALG_RC4:
            case KMIP_CRYPTOALG_RC5:
            case KMIP_CRYPTOALG_SKIPJACK:
            case KMIP_CRYPTOALG_TWOFISH:
            return(KMIP_OK);
            break;
            
            case KMIP_CRYPTOALG_EC:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_CRYPTOALG_ONE_TIME_PAD:
            if(version >= KMIP_1_3)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_CRYPTOALG_CHACHA20:
            case KMIP_CRYPTOALG_POLY1305:
            case KMIP_CRYPTOALG_CHACHA20_POLY1305:
            case KMIP_CRYPTOALG_SHA3_224:
            case KMIP_CRYPTOALG_SHA3_256:
            case KMIP_CRYPTOALG_SHA3_384:
            case KMIP_CRYPTOALG_SHA3_512:
            case KMIP_CRYPTOALG_HMAC_SHA3_224:
            case KMIP_CRYPTOALG_HMAC_SHA3_256:
            case KMIP_CRYPTOALG_HMAC_SHA3_384:
            case KMIP_CRYPTOALG_HMAC_SHA3_512:
            case KMIP_CRYPTOALG_SHAKE_128:
            case KMIP_CRYPTOALG_SHAKE_256:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            /* KMIP 2.0 */
            case KMIP_CRYPTOALG_ARIA:
            case KMIP_CRYPTOALG_SEED:
            case KMIP_CRYPTOALG_SM2:
            case KMIP_CRYPTOALG_SM3:
            case KMIP_CRYPTOALG_SM4:
            case KMIP_CRYPTOALG_GOST_R_34_10_2012:
            case KMIP_CRYPTOALG_GOST_R_34_11_2012:
            case KMIP_CRYPTOALG_GOST_R_34_13_2015:
            case KMIP_CRYPTOALG_GOST_28147_89:
            case KMIP_CRYPTOALG_XMSS:
            case KMIP_CRYPTOALG_SPHINCS_256:
            case KMIP_CRYPTOALG_MCELIECE:
            case KMIP_CRYPTOALG_MCELIECE_6960119:
            case KMIP_CRYPTOALG_MCELIECE_8192128:
            case KMIP_CRYPTOALG_ED25519:
            case KMIP_CRYPTOALG_ED448:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK:
        switch(value)
        {
            case KMIP_CRYPTOMASK_SIGN:
            case KMIP_CRYPTOMASK_VERIFY:
            case KMIP_CRYPTOMASK_ENCRYPT:
            case KMIP_CRYPTOMASK_DECRYPT:
            case KMIP_CRYPTOMASK_WRAP_KEY:
            case KMIP_CRYPTOMASK_UNWRAP_KEY:
            case KMIP_CRYPTOMASK_EXPORT:
            case KMIP_CRYPTOMASK_MAC_GENERATE:
            case KMIP_CRYPTOMASK_MAC_VERIFY:
            case KMIP_CRYPTOMASK_DERIVE_KEY:
            case KMIP_CRYPTOMASK_CONTENT_COMMITMENT:
            case KMIP_CRYPTOMASK_KEY_AGREEMENT:
            case KMIP_CRYPTOMASK_CERTIFICATE_SIGN:
            case KMIP_CRYPTOMASK_CRL_SIGN:
            case KMIP_CRYPTOMASK_GENERATE_CRYPTOGRAM:
            case KMIP_CRYPTOMASK_VALIDATE_CRYPTOGRAM:
            case KMIP_CRYPTOMASK_TRANSLATE_ENCRYPT:
            case KMIP_CRYPTOMASK_TRANSLATE_DECRYPT:
            case KMIP_CRYPTOMASK_TRANSLATE_WRAP:
            case KMIP_CRYPTOMASK_TRANSLATE_UNWRAP:
            return(KMIP_OK);
            break;

            /* KMIP 2.0 */
            case KMIP_CRYPTOMASK_AUTHENTICATE:
            case KMIP_CRYPTOMASK_UNRESTRICTED:
            case KMIP_CRYPTOMASK_FPE_ENCRYPT:
            case KMIP_CRYPTOMASK_FPE_DECRYPT:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM:
        switch(value)
        {
            case KMIP_DIGITAL_MD2_WITH_RSA:
            case KMIP_DIGITAL_MD5_WITH_RSA:
            case KMIP_DIGITAL_SHA1_WITH_RSA:
            case KMIP_DIGITAL_SHA224_WITH_RSA:
            case KMIP_DIGITAL_SHA256_WITH_RSA:
            case KMIP_DIGITAL_SHA384_WITH_RSA:
            case KMIP_DIGITAL_SHA512_WITH_RSA:
            case KMIP_DIGITAL_RSASSA_PSS:
            case KMIP_DIGITAL_DSA_WITH_SHA1:
            case KMIP_DIGITAL_DSA_WITH_SHA224:
            case KMIP_DIGITAL_DSA_WITH_SHA256:
            case KMIP_DIGITAL_ECDSA_WITH_SHA1:
            case KMIP_DIGITAL_ECDSA_WITH_SHA224:
            case KMIP_DIGITAL_ECDSA_WITH_SHA256:
            case KMIP_DIGITAL_ECDSA_WITH_SHA384:
            case KMIP_DIGITAL_ECDSA_WITH_SHA512:
            if(version >= KMIP_1_1)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_DIGITAL_SHA3_256_WITH_RSA:
            case KMIP_DIGITAL_SHA3_384_WITH_RSA:
            case KMIP_DIGITAL_SHA3_512_WITH_RSA:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_ENCODING_OPTION:
        switch(value)
        {
            case KMIP_ENCODE_NO_ENCODING:
            case KMIP_ENCODE_TTLV_ENCODING:
            if(version >= KMIP_1_1)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;

        case KMIP_TAG_HASHING_ALGORITHM:
        switch(value)
        {
            case KMIP_HASH_MD2:
            case KMIP_HASH_MD4:
            case KMIP_HASH_MD5:
            case KMIP_HASH_SHA1:
            case KMIP_HASH_SHA224:
            case KMIP_HASH_SHA256:
            case KMIP_HASH_SHA384:
            case KMIP_HASH_SHA512:
            case KMIP_HASH_RIPEMD160:
            case KMIP_HASH_TIGER:
            case KMIP_HASH_WHIRLPOOL:
            return(KMIP_OK);
            break;
            
            case KMIP_HASH_SHA512_224:
            case KMIP_HASH_SHA512_256:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_HASH_SHA3_224:
            case KMIP_HASH_SHA3_256:
            case KMIP_HASH_SHA3_384:
            case KMIP_HASH_SHA3_512:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_KEY_COMPRESSION_TYPE:
        switch(value)
        {
            case KMIP_KEYCOMP_EC_PUB_UNCOMPRESSED:
            case KMIP_KEYCOMP_EC_PUB_X962_COMPRESSED_PRIME:
            case KMIP_KEYCOMP_EC_PUB_X962_COMPRESSED_CHAR2:
            case KMIP_KEYCOMP_EC_PUB_X962_HYBRID:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_KEY_FORMAT_TYPE:
        switch(value)
        {
            case KMIP_KEYFORMAT_RAW:
            case KMIP_KEYFORMAT_OPAQUE:
            case KMIP_KEYFORMAT_PKCS1:
            case KMIP_KEYFORMAT_PKCS8:
            case KMIP_KEYFORMAT_X509:
            case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
            case KMIP_KEYFORMAT_TRANS_DSA_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_DSA_PUBLIC_KEY:
            case KMIP_KEYFORMAT_TRANS_RSA_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_RSA_PUBLIC_KEY:
            case KMIP_KEYFORMAT_TRANS_DH_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_DH_PUBLIC_KEY:
            return(KMIP_OK);
            break;
            
            /* The following set is deprecated as of KMIP 1.3 */
            case KMIP_KEYFORMAT_TRANS_ECDSA_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_ECDSA_PUBLIC_KEY:
            case KMIP_KEYFORMAT_TRANS_ECDH_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_ECDH_PUBLIC_KEY:
            case KMIP_KEYFORMAT_TRANS_ECMQV_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_ECMQV_PUBLIC_KEY:
            /* TODO (ph) What should happen if version >= 1.3? */
            return(KMIP_OK);
            break;
            
            case KMIP_KEYFORMAT_TRANS_EC_PRIVATE_KEY:
            case KMIP_KEYFORMAT_TRANS_EC_PUBLIC_KEY:
            if(version >= KMIP_1_3)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            case KMIP_KEYFORMAT_PKCS12:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            /* KMIP 2.0 */
            case KMIP_KEYFORMAT_PKCS10:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_KEY_ROLE_TYPE:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_ROLE_BDK:
            case KMIP_ROLE_CVK:
            case KMIP_ROLE_DEK:
            case KMIP_ROLE_MKAC:
            case KMIP_ROLE_MKSMC:
            case KMIP_ROLE_MKSMI:
            case KMIP_ROLE_MKDAC:
            case KMIP_ROLE_MKDN:
            case KMIP_ROLE_MKCP:
            case KMIP_ROLE_MKOTH:
            case KMIP_ROLE_KEK:
            case KMIP_ROLE_MAC16609:
            case KMIP_ROLE_MAC97971:
            case KMIP_ROLE_MAC97972:
            case KMIP_ROLE_MAC97973:
            case KMIP_ROLE_MAC97974:
            case KMIP_ROLE_MAC97975:
            case KMIP_ROLE_ZPK:
            case KMIP_ROLE_PVKIBM:
            case KMIP_ROLE_PVKPVV:
            case KMIP_ROLE_PVKOTH:
            return(KMIP_OK);
            break;
            
            /* KMIP 1.4 */
            case KMIP_ROLE_DUKPT:
            case KMIP_ROLE_IV:
            case KMIP_ROLE_TRKBK:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_KEY_WRAP_TYPE:
        switch(value)
        {
            /* KMIP 1.4 */
            case KMIP_WRAPTYPE_NOT_WRAPPED:
            case KMIP_WRAPTYPE_AS_REGISTERED:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_MASK_GENERATOR:
        switch(value)
        {
            /* KMIP 1.4 */
            case KMIP_MASKGEN_MGF1:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_NAME_TYPE:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_NAME_UNINTERPRETED_TEXT_STRING:
            case KMIP_NAME_URI:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_OBJECT_TYPE:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_OBJTYPE_CERTIFICATE:
            case KMIP_OBJTYPE_SYMMETRIC_KEY:
            case KMIP_OBJTYPE_PUBLIC_KEY:
            case KMIP_OBJTYPE_PRIVATE_KEY:
            case KMIP_OBJTYPE_SPLIT_KEY:
            case KMIP_OBJTYPE_SECRET_DATA:
            case KMIP_OBJTYPE_OPAQUE_OBJECT:
            return(KMIP_OK);
            break;
            
            /* The following set is deprecated as of KMIP 1.3 */
            case KMIP_OBJTYPE_TEMPLATE:
            /* TODO (ph) What should happen if version >= 1.3? */
            return(KMIP_OK);
            break;
            
            /* KMIP 1.2 */
            case KMIP_OBJTYPE_PGP_KEY:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            /* KMIP 2.0 */
            case KMIP_OBJTYPE_CERTIFICATE_REQUEST:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_OPERATION:
        switch(value)
        {
	    case KMIP_OP_EXPORT:
	    case KMIP_OP_IMPORT:
            if(version < KMIP_1_4)
                return(KMIP_INVALID_FOR_VERSION);
            else return(KMIP_OK);

	    case KMIP_OP_JOIN_SPLIT_KEY:
	    case KMIP_OP_CREATE_SPLIT_KEY:
	    case KMIP_OP_HASH:
	    case KMIP_OP_RNG_SEED:
	    case KMIP_OP_RNG_RETRIEVE:
	    case KMIP_OP_MAC_VERIFY:
	    case KMIP_OP_MAC:
	    case KMIP_OP_SIGNATURE_VERIFY:
	    case KMIP_OP_SIGN:
	    case KMIP_OP_DECRYPT:
	    case KMIP_OP_ENCRYPT:
            if(version < KMIP_1_2)
                return(KMIP_INVALID_FOR_VERSION);
            else return(KMIP_OK);

	    case KMIP_OP_DISCOVER_VERSIONS:
	    case KMIP_OP_REKEY_KEY_PAIR:
            if(version < KMIP_1_1)
                return(KMIP_INVALID_FOR_VERSION);
            else return(KMIP_OK);

            /* KMIP 1.0 */
	    case KMIP_OP_PUT:
	    case KMIP_OP_NOTIFY:
	    case KMIP_OP_POLL:
	    case KMIP_OP_CANCEL:
	    case KMIP_OP_QUERY:
	    case KMIP_OP_VALIDATE:
	    case KMIP_OP_RECOVER:
	    case KMIP_OP_ARCHIVE:
	    case KMIP_OP_DESTROY:
	    case KMIP_OP_REVOKE:
	    case KMIP_OP_ACTIVATE:
	    case KMIP_OP_GET_USAGE_ALLOCATION:
	    case KMIP_OP_OBTAIN_LEASE:
	    case KMIP_OP_DELETE_ATTRIBUTE:
	    case KMIP_OP_MODIFY_ATTRIBUTE:
	    case KMIP_OP_ADD_ATTRIBUTE:
	    case KMIP_OP_GET_ATTRIBUTE_LIST:
	    case KMIP_OP_GET_ATTRIBUTES:
	    case KMIP_OP_GET:
	    case KMIP_OP_CHECK:
	    case KMIP_OP_LOCATE:
	    case KMIP_OP_RECERTIFY:
	    case KMIP_OP_CERTIFY:
	    case KMIP_OP_DERIVE_KEY:
	    case KMIP_OP_REKEY:
	    case KMIP_OP_REGISTER:
	    case KMIP_OP_CREATE_KEY_PAIR:
	    case KMIP_OP_CREATE:
            return(KMIP_OK);
            
            default:
            return(KMIP_ENUM_MISMATCH);
        };
        break;
        
        case KMIP_TAG_PADDING_METHOD:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_PAD_NONE:
            case KMIP_PAD_OAEP:
            case KMIP_PAD_PKCS5:
            case KMIP_PAD_SSL3:
            case KMIP_PAD_ZEROS:
            case KMIP_PAD_ANSI_X923:
            case KMIP_PAD_ISO_10126:
            case KMIP_PAD_PKCS1v15:
            case KMIP_PAD_X931:
            case KMIP_PAD_PSS:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;

        case KMIP_TAG_PROTECTION_STORAGE_MASK:
        {
            switch(value)
            {
                /* KMIP 2.0 */
                case KMIP_PROTECT_SOFTWARE:
                case KMIP_PROTECT_HARDWARE:
                case KMIP_PROTECT_ON_PROCESSOR:
                case KMIP_PROTECT_ON_SYSTEM:
                case KMIP_PROTECT_OFF_SYSTEM:
                case KMIP_PROTECT_HYPERVISOR:
                case KMIP_PROTECT_OPERATING_SYSTEM:
                case KMIP_PROTECT_CONTAINER:
                case KMIP_PROTECT_ON_PREMISES:
                case KMIP_PROTECT_OFF_PREMISES:
                case KMIP_PROTECT_SELF_MANAGED:
                case KMIP_PROTECT_OUTSOURCED:
                case KMIP_PROTECT_VALIDATED:
                case KMIP_PROTECT_SAME_JURISDICTION:
                if(version >= KMIP_2_0)
                    return(KMIP_OK);
                else
                    return(KMIP_INVALID_FOR_VERSION);
                break;

                default:
                return(KMIP_ENUM_MISMATCH);
                break;
            };
        };
        break;
        
        case KMIP_TAG_RESULT_REASON:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_REASON_GENERAL_FAILURE:
            case KMIP_REASON_ITEM_NOT_FOUND:
            case KMIP_REASON_RESPONSE_TOO_LARGE:
            case KMIP_REASON_AUTHENTICATION_NOT_SUCCESSFUL:
            case KMIP_REASON_INVALID_MESSAGE:
            case KMIP_REASON_OPERATION_NOT_SUPPORTED:
            case KMIP_REASON_MISSING_DATA:
            case KMIP_REASON_INVALID_FIELD:
            case KMIP_REASON_FEATURE_NOT_SUPPORTED:
            case KMIP_REASON_OPERATION_CANCELED_BY_REQUESTER:
            case KMIP_REASON_CRYPTOGRAPHIC_FAILURE:
            case KMIP_REASON_ILLEGAL_OPERATION:
            case KMIP_REASON_PERMISSION_DENIED:
            case KMIP_REASON_OBJECT_ARCHIVED:
            case KMIP_REASON_INDEX_OUT_OF_BOUNDS:
            case KMIP_REASON_APPLICATION_NAMESPACE_NOT_SUPPORTED:
            case KMIP_REASON_KEY_FORMAT_TYPE_NOT_SUPPORTED:
            case KMIP_REASON_KEY_COMPRESSION_TYPE_NOT_SUPPORTED:
            return(KMIP_OK);
            break;
            
            /* KMIP 1.1 */
            case KMIP_REASON_ENCODING_OPTION_FAILURE:
            if(version >= KMIP_1_1)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            /* KMIP 1.2 */
            case KMIP_REASON_KEY_VALUE_NOT_PRESENT:
            case KMIP_REASON_ATTESTATION_REQUIRED:
            case KMIP_REASON_ATTESTATION_FAILED:
            if(version >= KMIP_1_2)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            /* KMIP 1.4 */
            case KMIP_REASON_SENSITIVE:
            case KMIP_REASON_NOT_EXTRACTABLE:
            case KMIP_REASON_OBJECT_ALREADY_EXISTS:
            if(version >= KMIP_1_4)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;
            
            /* KMIP 2.0 */
            case KMIP_REASON_INVALID_TICKET:
            case KMIP_REASON_USAGE_LIMIT_EXCEEDED:
            case KMIP_REASON_NUMERIC_RANGE:
            case KMIP_REASON_INVALID_DATA_TYPE:
            case KMIP_REASON_READ_ONLY_ATTRIBUTE:
            case KMIP_REASON_MULTI_VALUED_ATTRIBUTE:
            case KMIP_REASON_UNSUPPORTED_ATTRIBUTE:
            case KMIP_REASON_ATTRIBUTE_INSTANCE_NOT_FOUND:
            case KMIP_REASON_ATTRIBUTE_NOT_FOUND:
            case KMIP_REASON_ATTRIBUTE_READ_ONLY:
            case KMIP_REASON_ATTRIBUTE_SINGLE_VALUED:
            case KMIP_REASON_BAD_CRYPTOGRAPHIC_PARAMETERS:
            case KMIP_REASON_BAD_PASSWORD:
            case KMIP_REASON_CODEC_ERROR:
            case KMIP_REASON_ILLEGAL_OBJECT_TYPE:
            case KMIP_REASON_INCOMPATIBLE_CRYPTOGRAPHIC_USAGE_MASK:
            case KMIP_REASON_INTERNAL_SERVER_ERROR:
            case KMIP_REASON_INVALID_ASYNCHRONOUS_CORRELATION_VALUE:
            case KMIP_REASON_INVALID_ATTRIBUTE:
            case KMIP_REASON_INVALID_ATTRIBUTE_VALUE:
            case KMIP_REASON_INVALID_CORRELATION_VALUE:
            case KMIP_REASON_INVALID_CSR:
            case KMIP_REASON_INVALID_OBJECT_TYPE:
            case KMIP_REASON_KEY_WRAP_TYPE_NOT_SUPPORTED:
            case KMIP_REASON_MISSING_INITIALIZATION_VECTOR:
            case KMIP_REASON_NON_UNIQUE_NAME_ATTRIBUTE:
            case KMIP_REASON_OBJECT_DESTROYED:
            case KMIP_REASON_OBJECT_NOT_FOUND:
            case KMIP_REASON_NOT_AUTHORISED:
            case KMIP_REASON_SERVER_LIMIT_EXCEEDED:
            case KMIP_REASON_UNKNOWN_ENUMERATION:
            case KMIP_REASON_UNKNOWN_MESSAGE_EXTENSION:
            case KMIP_REASON_UNKNOWN_TAG:
            case KMIP_REASON_UNSUPPORTED_CRYPTOGRAPHIC_PARAMETERS:
            case KMIP_REASON_UNSUPPORTED_PROTOCOL_VERSION:
            case KMIP_REASON_WRAPPING_OBJECT_ARCHIVED:
            case KMIP_REASON_WRAPPING_OBJECT_DESTROYED:
            case KMIP_REASON_WRAPPING_OBJECT_NOT_FOUND:
            case KMIP_REASON_WRONG_KEY_LIFECYCLE_STATE:
            case KMIP_REASON_PROTECTION_STORAGE_UNAVAILABLE:
            case KMIP_REASON_PKCS11_CODEC_ERROR:
            case KMIP_REASON_PKCS11_INVALID_FUNCTION:
            case KMIP_REASON_PKCS11_INVALID_INTERFACE:
            case KMIP_REASON_PRIVATE_PROTECTION_STORAGE_UNAVAILABLE:
            case KMIP_REASON_PUBLIC_PROTECTION_STORAGE_UNAVAILABLE:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_RESULT_STATUS:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_STATUS_SUCCESS:
            case KMIP_STATUS_OPERATION_FAILED:
            case KMIP_STATUS_OPERATION_PENDING:
            case KMIP_STATUS_OPERATION_UNDONE:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_STATE:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_STATE_PRE_ACTIVE:
            case KMIP_STATE_ACTIVE:
            case KMIP_STATE_DEACTIVATED:
            case KMIP_STATE_COMPROMISED:
            case KMIP_STATE_DESTROYED:
            case KMIP_STATE_DESTROYED_COMPROMISED:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_TAG:
        return(KMIP_OK);
        break;
        
        case KMIP_TAG_TYPE:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_TYPE_STRUCTURE:
            case KMIP_TYPE_INTEGER:
            case KMIP_TYPE_LONG_INTEGER:
            case KMIP_TYPE_BIG_INTEGER:
            case KMIP_TYPE_ENUMERATION:
            case KMIP_TYPE_BOOLEAN:
            case KMIP_TYPE_TEXT_STRING:
            case KMIP_TYPE_BYTE_STRING:
            case KMIP_TYPE_DATE_TIME:
            case KMIP_TYPE_INTERVAL:
            return(KMIP_OK);
            break;
            
            /* KMIP 2.0 */
            case KMIP_TYPE_DATE_TIME_EXTENDED:
            if(version >= KMIP_2_0)
                return(KMIP_OK);
            else
                return(KMIP_INVALID_FOR_VERSION);
            break;

            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;
        
        case KMIP_TAG_WRAPPING_METHOD:
        switch(value)
        {
            /* KMIP 1.0 */
            case KMIP_WRAP_ENCRYPT:
            case KMIP_WRAP_MAC_SIGN:
            case KMIP_WRAP_ENCRYPT_MAC_SIGN:
            case KMIP_WRAP_MAC_SIGN_ENCRYPT:
            case KMIP_WRAP_TR31:
            return(KMIP_OK);
            break;
            
            default:
            return(KMIP_ENUM_MISMATCH);
            break;
        };
        break;

        case KMIP_TAG_STORAGE_STATUS_MASK:
	if ((value & ~(KMIP_OGM_GROUP_MEMBER_FRESH|KMIP_OGM_GROUP_MEMBER_DEFAULT)))
	    return KMIP_ENUM_MISMATCH;
	return KMIP_OK;

        case KMIP_TAG_OBJECT_GROUP_MEMBER:
	m = KMIP_SSM_ONLINE_STORAGE | KMIP_SSM_ARCHIVAL_STORAGE;
	if(version >= KMIP_2_0) {
	    m |= KMIP_SSM_DESTROYED_STORAGE;
	}
	if (value & ~m)
	    return KMIP_ENUM_MISMATCH;
	return KMIP_OK;
	break;
        
        default:
        return(KMIP_ENUM_UNSUPPORTED);
        break;
    };
}

/*
Context Utilities
*/

void
kmip_clear_errors(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    for(size_t i = 0; i < ARRAY_LENGTH(ctx->errors); i++)
    {
        ctx->errors[i] = (ErrorFrame){{0},0};
    }
    ctx->frame_index = ctx->errors;
    
    if(ctx->error_message != NULL)
    {
        ctx->free_func(ctx->state, ctx->error_message);
        ctx->error_message = NULL;
    }
}

void
kmip_init(KMIP *ctx, void *buffer, size_t buffer_size, enum kmip_version v)
{
    if(ctx == NULL)
    {
        return;
    }
    
    ctx->buffer = (uint8 *)buffer;
    ctx->index = ctx->buffer;
    ctx->size = buffer_size;
    ctx->version = v;
    
    if(ctx->calloc_func == NULL)
    {
        ctx->calloc_func = &kmip_calloc;
    }
    if(ctx->realloc_func == NULL)
    {
        ctx->realloc_func = &kmip_realloc;
    }
    if(ctx->memset_func == NULL)
    {
        ctx->memset_func = &kmip_memset;
    }
    if(ctx->free_func == NULL)
    {
        ctx->free_func = &kmip_free;
    }
    if(ctx->memcpy_func == NULL)
        ctx->memcpy_func = &kmip_memcpy;
    
    ctx->max_message_size = 8192;
    ctx->error_message_size = 200;
    ctx->error_message = NULL;
    
    ctx->error_frame_count = 20;
    
    ctx->credential_list = ctx->calloc_func(ctx->state, 1, sizeof(LinkedList));
    
    kmip_clear_errors(ctx);
}

void
kmip_init_error_message(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    if(ctx->error_message == NULL)
    {
        ctx->error_message = ctx->calloc_func(ctx->state, ctx->error_message_size, sizeof(char));
    }
}

int
kmip_add_credential(KMIP *ctx, Credential *cred)
{
    if(ctx == NULL || cred == NULL)
    {
        return(KMIP_UNSET);
    }
    
    LinkedListItem *item = ctx->calloc_func(ctx->state, 1, sizeof(LinkedListItem));
    if(item != NULL)
    {
        item->data = cred;
        kmip_linked_list_push(ctx->credential_list, item);
        return(KMIP_OK);
    }
    
    return(KMIP_UNSET);
}

void
kmip_remove_credentials(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    LinkedListItem *item = kmip_linked_list_pop(ctx->credential_list);
    while(item != NULL)
    {
        ctx->memset_func(item, 0, sizeof(LinkedListItem));
        ctx->free_func(ctx->state, item);
        
        item = kmip_linked_list_pop(ctx->credential_list);
    }
}

void
kmip_reset(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    if(ctx->buffer != NULL)
    {
        kmip_memset(ctx->buffer, 0, ctx->size);
    }
    ctx->index = ctx->buffer;
    
    kmip_clear_errors(ctx);
}

void
kmip_rewind(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    ctx->index = ctx->buffer;
    
    kmip_clear_errors(ctx);
}

void
kmip_set_buffer(KMIP *ctx, void *buffer, size_t buffer_size)
{
    if(ctx == NULL)
    {
        return;
    }
    
    /* TODO (ph) Add own_buffer if buffer == NULL? */
    ctx->buffer = (uint8 *)buffer;
    ctx->index = ctx->buffer;
    ctx->size = buffer_size;
}

void
kmip_destroy(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    kmip_reset(ctx);
    kmip_set_buffer(ctx, NULL, 0);

    kmip_remove_credentials(ctx);
    ctx->memset_func(ctx->credential_list, 0, sizeof(LinkedList));
    ctx->free_func(ctx->state, ctx->credential_list);
    
    ctx->calloc_func = NULL;
    ctx->realloc_func = NULL;
    ctx->memset_func = NULL;
    ctx->free_func = NULL;
    ctx->memcpy_func = NULL;
    ctx->state = NULL;
}

void
kmip_push_error_frame(KMIP *ctx, const char *function, const int line)
{
    if(ctx == NULL)
    {
        return;
    }
    
    for(size_t i = 0; i < 20; i++)
    {
        ErrorFrame *frame = &ctx->errors[i];
        if(frame->line == 0)
        {
            ctx->frame_index = frame;
            strncpy(frame->function, function, sizeof(frame->function) - 1);
            frame->line = line;
            break;
        }
    }
}

void
kmip_set_enum_error_message(KMIP *ctx, enum tag t, int value, int result)
{
    if(ctx == NULL)
    {
        return;
    }
    
    switch(result)
    {
        /* TODO (ph) Update error message for KMIP version 2.0+ */
        case KMIP_INVALID_FOR_VERSION:
        kmip_init_error_message(ctx);
        snprintf(ctx->error_message, ctx->error_message_size, "KMIP 1.%d does not support %s enumeration value (%d)", ctx->version, kmip_attribute_names[kmip_get_enum_string_index(t)], value);
        break;
        
        default: /* KMIP_ENUM_MISMATCH */
        kmip_init_error_message(ctx);
        snprintf(ctx->error_message, ctx->error_message_size, "Invalid %s enumeration value (%d)", kmip_attribute_names[kmip_get_enum_string_index(t)], value);
        break;
    };
}

void
kmip_set_alloc_error_message(KMIP *ctx, size_t size, const char *type)
{
    if(ctx == NULL)
    {
        return;
    }
    
    kmip_init_error_message(ctx);
    snprintf(ctx->error_message, ctx->error_message_size, "Could not allocate %zd bytes for a %s", size, type);
}

void
kmip_set_error_message(KMIP *ctx, const char *message)
{
    if(ctx == NULL)
    {
        return;
    }
    
    kmip_init_error_message(ctx);
    snprintf(ctx->error_message, ctx->error_message_size, "%s", message);
}

int
kmip_is_tag_next(const KMIP *ctx, enum tag t)
{
    if(ctx == NULL)
    {
        return(KMIP_FALSE);
    }
    
    uint8 *index = ctx->index;
    
    if((ctx->size - (index - ctx->buffer)) < 3)
    {
        return(KMIP_FALSE);
    }
    
    uint32 tag = 0;
    
    tag |= ((uint32)*index++ << 16);
    tag |= ((uint32)*index++ << 8);
    tag |= ((uint32)*index++ << 0);
    
    if(tag != t)
    {
        return(KMIP_FALSE);
    }
    
    return(KMIP_TRUE);
}

int
kmip_is_tag_type_next(const KMIP *ctx, enum tag t, enum type s)
{
    if(ctx == NULL)
    {
        return(KMIP_FALSE);
    }
    
    uint8 *index = ctx->index;
    
    if((ctx->size - (index - ctx->buffer)) < 4)
    {
        return(KMIP_FALSE);
    }
    
    uint32 tag_type = 0;
    
    tag_type |= ((uint32)*index++ << 24);
    tag_type |= ((uint32)*index++ << 16);
    tag_type |= ((uint32)*index++ << 8);
    tag_type |= ((uint32)*index++ << 0);
    
    if(tag_type != TAG_TYPE(t, s))
    {
        return(KMIP_FALSE);
    }
    
    return(KMIP_TRUE);
}

int
kmip_get_num_items_next(KMIP *ctx, enum tag t)
{
    if(ctx == NULL)
    {
        return(0);
    }
    
    int count = 0;
    
    uint8 *index = ctx->index;
    uint32 length = 0;
    
    while((ctx->size - (ctx->index - ctx->buffer)) > 8)
    {
        if(kmip_is_tag_next(ctx, t))
        {
            ctx->index += 4;
            
            length = 0;
            length |= ((int32)*ctx->index++ << 24);
            length |= ((int32)*ctx->index++ << 16);
            length |= ((int32)*ctx->index++ << 8);
            length |= ((int32)*ctx->index++ << 0);
            length += CALCULATE_PADDING(length);
            
            if((ctx->size - (ctx->index - ctx->buffer)) >= length)
            {
                ctx->index += length;
                count++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    
    ctx->index = index;
    return(count);
}

uint32
kmip_peek_tag(KMIP *ctx)
{
    if(BUFFER_BYTES_LEFT(ctx) < 3)
    {
        return(0);
    }

    uint8 *index = ctx->index;
    uint32 tag = 0;

    tag |= ((int32)*index++ << 16);
    tag |= ((int32)*index++ << 8);
    tag |= ((int32)*index++ << 0);

    return(tag);
}

int
kmip_is_attribute_tag(uint32 value)
{
    enum tag attribute_tags[] = {
        KMIP_TAG_UNIQUE_IDENTIFIER,
        KMIP_TAG_NAME,
        KMIP_TAG_OBJECT_TYPE,
        KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM,
        KMIP_TAG_CRYPTOGRAPHIC_LENGTH,
        KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS,
        KMIP_TAG_CRYPTOGRAPHIC_DOMAIN_PARAMETERS,
        KMIP_TAG_CERTIFICATE_TYPE,
        KMIP_TAG_CERTIFICATE_LENGTH,
        KMIP_TAG_X509_CERTIFICATE_IDENTIFIER,
        KMIP_TAG_X509_CERTIFICATE_SUBJECT,
        KMIP_TAG_X509_CERTIFICATE_ISSUER,
        KMIP_TAG_CERTIFICATE_IDENTIFIER,
        KMIP_TAG_CERTIFICATE_SUBJECT,
        KMIP_TAG_CERTIFICATE_ISSUER,
        KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM,
        KMIP_TAG_DIGEST,
        KMIP_TAG_OPERATION_POLICY_NAME,
        KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK,
        KMIP_TAG_LEASE_TIME,
        KMIP_TAG_USAGE_LIMITS,
        KMIP_TAG_STATE,
        KMIP_TAG_INITIAL_DATE,
        KMIP_TAG_ACTIVATION_DATE,
        KMIP_TAG_PROCESS_START_DATE,
        KMIP_TAG_PROTECT_STOP_DATE,
        KMIP_TAG_DEACTIVATION_DATE,
        KMIP_TAG_DESTROY_DATE,
        KMIP_TAG_COMPROMISE_OCCURRENCE_DATE,
        KMIP_TAG_COMPROMISE_DATE,
        KMIP_TAG_REVOCATION_REASON,
        KMIP_TAG_ARCHIVE_DATE,
        KMIP_TAG_OBJECT_GROUP,
        KMIP_TAG_FRESH,
        KMIP_TAG_LINK,
        KMIP_TAG_APPLICATION_SPECIFIC_INFORMATION,
        KMIP_TAG_CONTACT_INFORMATION,
        KMIP_TAG_LAST_CHANGE_DATE,
        KMIP_TAG_ALTERNATIVE_NAME,
        KMIP_TAG_KEY_VALUE_PRESENT,
        KMIP_TAG_KEY_VALUE_LOCATION,
        KMIP_TAG_ORIGINAL_CREATION_DATE,
        KMIP_TAG_RANDOM_NUMBER_GENERATOR,
        KMIP_TAG_PKCS_12_FRIENDLY_NAME,
        KMIP_TAG_DESCRIPTION,
        KMIP_TAG_COMMENT,
        KMIP_TAG_SENSITIVE,
        KMIP_TAG_ALWAYS_SENSITIVE,
        KMIP_TAG_EXTRACTABLE,
        KMIP_TAG_NEVER_EXTRACTABLE,
        KMIP_TAG_KEY_FORMAT_TYPE
    };

    for(size_t i = 0; i < ARRAY_LENGTH(attribute_tags); i++)
    {
        if(attribute_tags[i] == value)
        {
            return(KMIP_TRUE);
        }
    }

    return(KMIP_FALSE);
}

/*
Initialization Functions
*/

void
kmip_init_protocol_version(ProtocolVersion *value, enum kmip_version kmip_version)
{
    if(value == NULL)
    {
        return;
    }
    
    switch(kmip_version)
    {
        case KMIP_2_0:
        {
            value->major = 2;
            value->minor = 0;
        };
        break;

        case KMIP_1_4:
        {
            value->major = 1;
            value->minor = 4;
        };
        break;
        
        case KMIP_1_3:
        {
            value->major = 1;
            value->minor = 3;
        };
        break;
        
        case KMIP_1_2:
        {
            value->major = 1;
            value->minor = 2;
        };
        break;
        
        case KMIP_1_1:
        {
            value->major = 1;
            value->minor = 1;
        };
        break;
        
        case KMIP_1_0:
        default:
        {
            value->major = 1;
            value->minor = 0;
        };
        break;
    };
}

void
kmip_init_attribute(Attribute *value)
{
    if(value == NULL)
    {
        return;
    }
    
    value->type = 0;
    value->index = KMIP_UNSET;
    value->value = NULL;
}

void
kmip_init_cryptographic_parameters(CryptographicParameters *value)
{
    if(value == NULL)
    {
        return;
    }
    
    value->block_cipher_mode = 0;
    value->padding_method = 0;
    value->hashing_algorithm = 0;
    value->key_role_type = 0;
    
    value->digital_signature_algorithm = 0;
    value->cryptographic_algorithm = 0;
    value->random_iv = KMIP_UNSET;
    value->iv_length = KMIP_UNSET;
    value->tag_length = KMIP_UNSET;
    value->fixed_field_length = KMIP_UNSET;
    value->invocation_field_length = KMIP_UNSET;
    value->counter_length = KMIP_UNSET;
    value->initial_counter_value = KMIP_UNSET;
    
    value->salt_length = KMIP_UNSET;
    value->mask_generator = 0;
    value->mask_generator_hashing_algorithm = 0;
    value->p_source = NULL;
    value->trailer_field = KMIP_UNSET;
}

void
kmip_init_key_block(KeyBlock *value)
{
    if(value == NULL)
    {
        return;
    }
    
    value->key_format_type = 0;
    value->key_compression_type = 0;
    value->key_value = NULL;
    value->key_value_type = 0;
    value->cryptographic_algorithm = 0;
    value->cryptographic_length = KMIP_UNSET;
    value->key_wrapping_data = NULL;
}

void
kmip_init_request_header(RequestHeader *value)
{
    if(value == NULL)
    {
        return;
    }
    
    value->protocol_version = NULL;
    value->maximum_response_size = KMIP_UNSET;
    value->asynchronous_indicator = KMIP_UNSET;
    value->authentication = NULL;
    value->batch_error_continuation_option = 0;
    value->batch_order_option = KMIP_UNSET;
    value->time_stamp = 0;
    value->batch_count = KMIP_UNSET;
    
    value->attestation_capable_indicator = KMIP_UNSET;
    value->attestation_types = NULL;
    value->attestation_type_count = 0;
    
    value->client_correlation_value = NULL;
    value->server_correlation_value = NULL;
}

void
kmip_init_response_header(ResponseHeader *value)
{
    if(value == NULL)
    {
        return;
    }
    
    value->protocol_version = NULL;
    value->time_stamp = 0;
    value->batch_count = KMIP_UNSET;
    
    value->nonce = NULL;
    value->attestation_types = NULL;
    value->attestation_type_count = 0;
    
    value->client_correlation_value = NULL;
    value->server_correlation_value = NULL;

    value->server_hashed_password = NULL;
}

void
kmip_init_request_batch_item(RequestBatchItem *value)
{
    if(value == NULL)
    {
        return;
    }

    value->operation = 0;
    value->unique_batch_item_id = NULL;
    value->request_payload = NULL;

    value->ephemeral = KMIP_UNSET;
}

/*
Printing Functions
*/

void
kmip_print_buffer(void *buffer, int size)
{
    if(buffer == NULL)
    {
        return;
    }
    
    uint8 *index = (uint8 *)buffer;
    for(int i = 0; i < size; i++)
    {
        if(i % 16 == 0)
        {
            printf("\n0x");
        }
        printf("%02X", index[i]);
    }
}

void
kmip_print_stack_trace(KMIP *ctx)
{
    if(ctx == NULL)
    {
        return;
    }
    
    ErrorFrame *index = ctx->frame_index;
    do
    {
        printf("- %s @ line: %d\n", index->function, index->line);
    } while(index-- != ctx->errors);
}

void
kmip_print_error_string(int value)
{
    /* TODO (ph) Move this to a static string array. */
    switch(value)
    {
        case 0:
        {
            printf("KMIP_OK");
        } break;
        
        case -1:
        {
            printf("KMIP_NOT_IMPLEMENTED");
        } break;
        
        case -2:
        {
            printf("KMIP_ERROR_BUFFER_FULL");
        } break;
        
        case -3:
        {
            printf("KMIP_ERROR_ATTR_UNSUPPORTED");
        } break;
        
        case -4:
        {
            printf("KMIP_TAG_MISMATCH");
        } break;
        
        case -5:
        {
            printf("KMIP_TYPE_MISMATCH");
        } break;
        
        case -6:
        {
            printf("KMIP_LENGTH_MISMATCH");
        } break;
        
        case -7:
        {
            printf("KMIP_PADDING_MISMATCH");
        } break;
        
        case -8:
        {
            printf("KMIP_BOOLEAN_MISMATCH");
        } break;
        
        case -9:
        {
            printf("KMIP_ENUM_MISMATCH");
        } break;
        
        case -10:
        {
            printf("KMIP_ENUM_UNSUPPORTED");
        } break;
        
        case -11:
        {
            printf("KMIP_INVALID_FOR_VERSION");
        } break;
        
        case -12:
        {
            printf("KMIP_MEMORY_ALLOC_FAILED");
        } break;

        case -13:
        {
            printf("KMIP_IO_FAILURE");
        } break;

        case -14:
        {
            printf("KMIP_EXCEED_MAX_MESSAGE_SIZE");
        } break;

        case -15:
        {
            printf("KMIP_MALFORMED_RESPONSE");
        } break;

        case -16:
        {
            printf("KMIP_OBJECT_MISMATCH");
        } break;

        case -17:
        {
            printf("KMIP_ARG_INVALID");
        } break;

        case -18:
        {
            printf("KMIP_ERROR_BUFFER_UNDERFULL");
        } break;

        default:
        {
            printf("Unrecognized Error Code");
        } break;
    };
    
    return;
}

void
kmip_print_attestation_type_enum(enum attestation_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_ATTEST_TPM_QUOTE:
        printf("TPM Quote");
        break;
        
        case KMIP_ATTEST_TCG_INTEGRITY_REPORT:
        printf("TCG Integrity Report");
        break;
        
        case KMIP_ATTEST_SAML_ASSERTION:
        printf("SAML Assertion");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_batch_error_continuation_option(enum batch_error_continuation_option value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_BATCH_CONTINUE:
        printf("Continue");
        break;
        
        case KMIP_BATCH_STOP:
        printf("Stop");
        break;
        
        case KMIP_BATCH_UNDO:
        printf("Undo");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_operation_enum(enum operation value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_OP_CREATE:
        printf("Create");
        break;
        
        case KMIP_OP_GET:
        printf("Get");
        break;
        
        case KMIP_OP_DESTROY:
        printf("Destroy");
        break;

        case KMIP_OP_CREATE_KEY_PAIR: printf ("Create Key Pair"); break;
        case KMIP_OP_REGISTER: printf ("Register"); break;
        case KMIP_OP_REKEY: printf ("Re-key"); break;
        case KMIP_OP_DERIVE_KEY: printf ("Derive Key"); break;
        case KMIP_OP_CERTIFY: printf ("Certify"); break;
        case KMIP_OP_RECERTIFY: printf ("Recertify"); break;
        case KMIP_OP_LOCATE: printf ("Locate"); break;
        case KMIP_OP_CHECK: printf ("Check"); break;
        case KMIP_OP_GET_ATTRIBUTES: printf ("Get Attributes"); break;
        case KMIP_OP_GET_ATTRIBUTE_LIST: printf ("Get Attribute List"); break;
        case KMIP_OP_ADD_ATTRIBUTE: printf ("Add Attribute"); break;
        case KMIP_OP_MODIFY_ATTRIBUTE: printf ("Modify Attribute"); break;
        case KMIP_OP_DELETE_ATTRIBUTE: printf ("Delete Attribute"); break;
        case KMIP_OP_OBTAIN_LEASE: printf ("Obtain Lease"); break;
        case KMIP_OP_GET_USAGE_ALLOCATION: printf ("Get Usage Allocation"); break;
        case KMIP_OP_ACTIVATE: printf ("Activate"); break;
        case KMIP_OP_REVOKE: printf ("Revoke"); break;
        case KMIP_OP_ARCHIVE: printf ("Archive"); break;
        case KMIP_OP_RECOVER: printf ("Recover"); break;
        case KMIP_OP_VALIDATE: printf ("Validate"); break;
        case KMIP_OP_QUERY: printf ("Query"); break;
        case KMIP_OP_CANCEL: printf ("Cancel"); break;
        case KMIP_OP_POLL: printf ("Poll"); break;
        case KMIP_OP_NOTIFY: printf ("Notify"); break;
        case KMIP_OP_PUT: printf ("Put"); break;
        case KMIP_OP_REKEY_KEY_PAIR: printf ("Rekey Key Pair"); break;
        case KMIP_OP_DISCOVER_VERSIONS: printf ("Discover Versions"); break;
        case KMIP_OP_ENCRYPT: printf ("Encrypt"); break;
        case KMIP_OP_DECRYPT: printf ("Decrypt"); break;
        case KMIP_OP_SIGN: printf ("Sign"); break;
        case KMIP_OP_SIGNATURE_VERIFY: printf ("Signature Verify"); break;
        case KMIP_OP_MAC: printf ("MAC"); break;
        case KMIP_OP_MAC_VERIFY: printf ("MAC Verify"); break;
        case KMIP_OP_RNG_RETRIEVE: printf ("RNG Retrieve"); break;
        case KMIP_OP_RNG_SEED: printf ("RNG Seed"); break;
        case KMIP_OP_HASH: printf ("Hash"); break;
        case KMIP_OP_CREATE_SPLIT_KEY: printf ("Create Split Key"); break;
        case KMIP_OP_JOIN_SPLIT_KEY: printf ("Join Split Key"); break;
        case KMIP_OP_IMPORT: printf ("Import"); break;
        case KMIP_OP_EXPORT: printf ("Export"); break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_result_status_enum(enum result_status value)
{
    switch(value)
    {
        case KMIP_STATUS_SUCCESS:
        printf("Success");
        break;
        
        case KMIP_STATUS_OPERATION_FAILED:
        printf("Operation Failed");
        break;
        
        case KMIP_STATUS_OPERATION_PENDING:
        printf("Operation Pending");
        break;
        
        case KMIP_STATUS_OPERATION_UNDONE:
        printf("Operation Undone");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_result_reason_enum(enum result_reason value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_REASON_GENERAL_FAILURE:
        printf("General Failure");
        break;
        
        case KMIP_REASON_ITEM_NOT_FOUND:
        printf("Item Not Found");
        break;
        
        case KMIP_REASON_RESPONSE_TOO_LARGE:
        printf("Response Too Large");
        break;
        
        case KMIP_REASON_AUTHENTICATION_NOT_SUCCESSFUL:
        printf("Authentication Not Successful");
        break;
        
        case KMIP_REASON_INVALID_MESSAGE:
        printf("Invalid Message");
        break;
        
        case KMIP_REASON_OPERATION_NOT_SUPPORTED:
        printf("Operation Not Supported");
        break;
        
        case KMIP_REASON_MISSING_DATA:
        printf("Missing Data");
        break;
        
        case KMIP_REASON_INVALID_FIELD:
        printf("Invalid Field");
        break;
        
        case KMIP_REASON_FEATURE_NOT_SUPPORTED:
        printf("Feature Not Supported");
        break;
        
        case KMIP_REASON_OPERATION_CANCELED_BY_REQUESTER:
        printf("Operation Canceled By Requester");
        break;
        
        case KMIP_REASON_CRYPTOGRAPHIC_FAILURE:
        printf("Cryptographic Failure");
        break;
        
        case KMIP_REASON_ILLEGAL_OPERATION:
        printf("Illegal Operation");
        break;
        
        case KMIP_REASON_PERMISSION_DENIED:
        printf("Permission Denied");
        break;
        
        case KMIP_REASON_OBJECT_ARCHIVED:
        printf("Object Archived");
        break;
        
        case KMIP_REASON_INDEX_OUT_OF_BOUNDS:
        printf("Index Out Of Bounds");
        break;
        
        case KMIP_REASON_APPLICATION_NAMESPACE_NOT_SUPPORTED:
        printf("Application Namespace Not Supported");
        break;
        
        case KMIP_REASON_KEY_FORMAT_TYPE_NOT_SUPPORTED:
        printf("Key Format Type Not Supported");
        break;
        
        case KMIP_REASON_KEY_COMPRESSION_TYPE_NOT_SUPPORTED:
        printf("Key Compression Type Not Supported");
        break;
        
        case KMIP_REASON_ENCODING_OPTION_FAILURE:
        printf("Encoding Option Failure");
        break;
        
        case KMIP_REASON_KEY_VALUE_NOT_PRESENT:
        printf("Key Value Not Present");
        break;
        
        case KMIP_REASON_ATTESTATION_REQUIRED:
        printf("Attestation Required");
        break;
        
        case KMIP_REASON_ATTESTATION_FAILED:
        printf("Attestation Failed");
        break;
        
        case KMIP_REASON_SENSITIVE:
        printf("Sensitive");
        break;
        
        case KMIP_REASON_NOT_EXTRACTABLE:
        printf("Not Extractable");
        break;
        
        case KMIP_REASON_OBJECT_ALREADY_EXISTS:
        printf("Object Already Exists");
        break;
        
        case KMIP_REASON_INVALID_TICKET:
        printf("Invalid Ticket");
        break;

        case KMIP_REASON_USAGE_LIMIT_EXCEEDED:
        printf("Usage Limit Exceeded");
        break;

        case KMIP_REASON_NUMERIC_RANGE:
        printf("Numeric Range");
        break;

        case KMIP_REASON_INVALID_DATA_TYPE:
        printf("Invalid Data Type");
        break;

        case KMIP_REASON_READ_ONLY_ATTRIBUTE:
        printf("Read Only Attribute");
        break;

        case KMIP_REASON_MULTI_VALUED_ATTRIBUTE:
        printf("Multi Valued Attribute");
        break;

        case KMIP_REASON_UNSUPPORTED_ATTRIBUTE:
        printf("Unsupported Attribute");
        break;

        case KMIP_REASON_ATTRIBUTE_INSTANCE_NOT_FOUND:
        printf("Attribute Instance Not Found");
        break;

        case KMIP_REASON_ATTRIBUTE_NOT_FOUND:
        printf("Attribute Not Found");
        break;

        case KMIP_REASON_ATTRIBUTE_READ_ONLY:
        printf("Attribute Read Only");
        break;

        case KMIP_REASON_ATTRIBUTE_SINGLE_VALUED:
        printf("Attribute Single Valued");
        break;

        case KMIP_REASON_BAD_CRYPTOGRAPHIC_PARAMETERS:
        printf("Bad Cryptographic Parameters");
        break;

        case KMIP_REASON_BAD_PASSWORD:
        printf("Bad Password");
        break;

        case KMIP_REASON_CODEC_ERROR:
        printf("Codec Error");
        break;

        case KMIP_REASON_ILLEGAL_OBJECT_TYPE:
        printf("Illegal Object Type");
        break;

        case KMIP_REASON_INCOMPATIBLE_CRYPTOGRAPHIC_USAGE_MASK:
        printf("Incompatible Cryptographic Usage Mask");
        break;

        case KMIP_REASON_INTERNAL_SERVER_ERROR:
        printf("Internal Server Error");
        break;

        case KMIP_REASON_INVALID_ASYNCHRONOUS_CORRELATION_VALUE:
        printf("Invalid Asynchronous Correlation Value");
        break;

        case KMIP_REASON_INVALID_ATTRIBUTE:
        printf("Invalid Attribute");
        break;

        case KMIP_REASON_INVALID_ATTRIBUTE_VALUE:
        printf("Invalid Attribute Value");
        break;

        case KMIP_REASON_INVALID_CORRELATION_VALUE:
        printf("Invalid Correlation Value");
        break;

        case KMIP_REASON_INVALID_CSR:
        printf("Invalid CSR");
        break;

        case KMIP_REASON_INVALID_OBJECT_TYPE:
        printf("Invalid Object Type");
        break;

        case KMIP_REASON_KEY_WRAP_TYPE_NOT_SUPPORTED:
        printf("Key Wrap Type Not Supported");
        break;

        case KMIP_REASON_MISSING_INITIALIZATION_VECTOR:
        printf("Missing Initialization Vector");
        break;

        case KMIP_REASON_NON_UNIQUE_NAME_ATTRIBUTE:
        printf("Non Unique Name Attribute");
        break;

        case KMIP_REASON_OBJECT_DESTROYED:
        printf("Object Destroyed");
        break;

        case KMIP_REASON_OBJECT_NOT_FOUND:
        printf("Object Not Found");
        break;

        case KMIP_REASON_NOT_AUTHORISED:
        printf("Not Authorised");
        break;

        case KMIP_REASON_SERVER_LIMIT_EXCEEDED:
        printf("Server Limit Exceeded");
        break;

        case KMIP_REASON_UNKNOWN_ENUMERATION:
        printf("Unknown Enumeration");
        break;

        case KMIP_REASON_UNKNOWN_MESSAGE_EXTENSION:
        printf("Unknown Message Extension");
        break;

        case KMIP_REASON_UNKNOWN_TAG:
        printf("Unknown Tag");
        break;

        case KMIP_REASON_UNSUPPORTED_CRYPTOGRAPHIC_PARAMETERS:
        printf("Unsupported Cryptographic Parameters");
        break;

        case KMIP_REASON_UNSUPPORTED_PROTOCOL_VERSION:
        printf("Unsupported Protocol Version");
        break;

        case KMIP_REASON_WRAPPING_OBJECT_ARCHIVED:
        printf("Wrapping Object Archived");
        break;

        case KMIP_REASON_WRAPPING_OBJECT_DESTROYED:
        printf("Wrapping Object Destroyed");
        break;

        case KMIP_REASON_WRAPPING_OBJECT_NOT_FOUND:
        printf("Wrapping Object Not Found");
        break;

        case KMIP_REASON_WRONG_KEY_LIFECYCLE_STATE:
        printf("Wrong Key Lifecycle State");
        break;

        case KMIP_REASON_PROTECTION_STORAGE_UNAVAILABLE:
        printf("Protection Storage Unavailable");
        break;

        case KMIP_REASON_PKCS11_CODEC_ERROR:
        printf("PKCS#11 Codec Error");
        break;

        case KMIP_REASON_PKCS11_INVALID_FUNCTION:
        printf("PKCS#11 Invalid Function");
        break;

        case KMIP_REASON_PKCS11_INVALID_INTERFACE:
        printf("PKCS#11 Invalid Interface");
        break;

        case KMIP_REASON_PRIVATE_PROTECTION_STORAGE_UNAVAILABLE:
        printf("Private Protection Storage Unavailable");
        break;

        case KMIP_REASON_PUBLIC_PROTECTION_STORAGE_UNAVAILABLE:
        printf("Public Protection Storage Unavailable");
        break;

        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_object_type_enum(enum object_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_OBJTYPE_CERTIFICATE:
        printf("Certificate");
        break;
        
        case KMIP_OBJTYPE_SYMMETRIC_KEY:
        printf("Symmetric Key");
        break;
        
        case KMIP_OBJTYPE_PUBLIC_KEY:
        printf("Public Key");
        break;
        
        case KMIP_OBJTYPE_PRIVATE_KEY:
        printf("Private Key");
        break;
        
        case KMIP_OBJTYPE_SPLIT_KEY:
        printf("Split Key");
        break;
        
        case KMIP_OBJTYPE_TEMPLATE:
        printf("Template");
        break;
        
        case KMIP_OBJTYPE_SECRET_DATA:
        printf("Secret Data");
        break;
        
        case KMIP_OBJTYPE_OPAQUE_OBJECT:
        printf("Opaque Object");
        break;
        
        case KMIP_OBJTYPE_PGP_KEY:
        printf("PGP Key");
        break;

        case KMIP_OBJTYPE_CERTIFICATE_REQUEST:
        printf("Certificate Request");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_key_format_type_enum(enum key_format_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_KEYFORMAT_RAW:
        printf("Raw");
        break;
        
        case KMIP_KEYFORMAT_OPAQUE:
        printf("Opaque");
        break;
        
        case KMIP_KEYFORMAT_PKCS1:
        printf("PKCS1");
        break;
        
        case KMIP_KEYFORMAT_PKCS8:
        printf("PKCS8");
        break;
        
        case KMIP_KEYFORMAT_X509:
        printf("X509");
        break;
        
        case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
        printf("EC Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
        printf("Transparent Symmetric Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_DSA_PRIVATE_KEY:
        printf("Transparent DSA Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_DSA_PUBLIC_KEY:
        printf("Transparent DSA Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_RSA_PRIVATE_KEY:
        printf("Transparent RSA Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_RSA_PUBLIC_KEY:
        printf("Transparent RSA Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_DH_PRIVATE_KEY:
        printf("Transparent DH Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_DH_PUBLIC_KEY:
        printf("Transparent DH Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDSA_PRIVATE_KEY:
        printf("Transparent ECDSA Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDSA_PUBLIC_KEY:
        printf("Transparent ECDSA Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDH_PRIVATE_KEY:
        printf("Transparent ECDH Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDH_PUBLIC_KEY:
        printf("Transparent ECDH Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECMQV_PRIVATE_KEY:
        printf("Transparent ECMQV Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECMQV_PUBLIC_KEY:
        printf("Transparent ECMQV Public Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_EC_PRIVATE_KEY:
        printf("Transparent EC Private Key");
        break;
        
        case KMIP_KEYFORMAT_TRANS_EC_PUBLIC_KEY:
        printf("Transparent EC Public Key");
        break;
        
        case KMIP_KEYFORMAT_PKCS12:
        printf("PKCS#12");
        break;
        
        case KMIP_KEYFORMAT_PKCS10:
        printf("PKCS#10");
        break;

        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_key_compression_type_enum(enum key_compression_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_KEYCOMP_EC_PUB_UNCOMPRESSED:
        printf("EC Public Key Type Uncompressed");
        break;
        
        case KMIP_KEYCOMP_EC_PUB_X962_COMPRESSED_PRIME:
        printf("EC Public Key Type X9.62 Compressed Prime");
        break;
        
        case KMIP_KEYCOMP_EC_PUB_X962_COMPRESSED_CHAR2:
        printf("EC Public Key Type X9.62 Compressed Char2");
        break;
        
        case KMIP_KEYCOMP_EC_PUB_X962_HYBRID:
        printf("EC Public Key Type X9.62 Hybrid");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_cryptographic_algorithm_enum(enum cryptographic_algorithm value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_CRYPTOALG_DES:
        printf("DES");
        break;
        
        case KMIP_CRYPTOALG_TRIPLE_DES:
        printf("3DES");
        break;
        
        case KMIP_CRYPTOALG_AES:
        printf("AES");
        break;
        
        case KMIP_CRYPTOALG_RSA:
        printf("RSA");
        break;
        
        case KMIP_CRYPTOALG_DSA:
        printf("DSA");
        break;
        
        case KMIP_CRYPTOALG_ECDSA:
        printf("ECDSA");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA1:
        printf("SHA1");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA224:
        printf("SHA224");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA256:
        printf("SHA256");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA384:
        printf("SHA384");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA512:
        printf("SHA512");
        break;
        
        case KMIP_CRYPTOALG_HMAC_MD5:
        printf("MD5");
        break;
        
        case KMIP_CRYPTOALG_DH:
        printf("DH");
        break;
        
        case KMIP_CRYPTOALG_ECDH:
        printf("ECDH");
        break;
        
        case KMIP_CRYPTOALG_ECMQV:
        printf("ECMQV");
        break;
        
        case KMIP_CRYPTOALG_BLOWFISH:
        printf("Blowfish");
        break;
        
        case KMIP_CRYPTOALG_CAMELLIA:
        printf("Camellia");
        break;
        
        case KMIP_CRYPTOALG_CAST5:
        printf("CAST5");
        break;
        
        case KMIP_CRYPTOALG_IDEA:
        printf("IDEA");
        break;
        
        case KMIP_CRYPTOALG_MARS:
        printf("MARS");
        break;
        
        case KMIP_CRYPTOALG_RC2:
        printf("RC2");
        break;
        
        case KMIP_CRYPTOALG_RC4:
        printf("RC4");
        break;
        
        case KMIP_CRYPTOALG_RC5:
        printf("RC5");
        break;
        
        case KMIP_CRYPTOALG_SKIPJACK:
        printf("Skipjack");
        break;
        
        case KMIP_CRYPTOALG_TWOFISH:
        printf("Twofish");
        break;
        
        case KMIP_CRYPTOALG_EC:
        printf("EC");
        break;
        
        case KMIP_CRYPTOALG_ONE_TIME_PAD:
        printf("One Time Pad");
        break;
        
        case KMIP_CRYPTOALG_CHACHA20:
        printf("ChaCha20");
        break;
        
        case KMIP_CRYPTOALG_POLY1305:
        printf("Poly1305");
        break;
        
        case KMIP_CRYPTOALG_CHACHA20_POLY1305:
        printf("ChaCha20 Poly1305");
        break;
        
        case KMIP_CRYPTOALG_SHA3_224:
        printf("SHA3-224");
        break;
        
        case KMIP_CRYPTOALG_SHA3_256:
        printf("SHA3-256");
        break;
        
        case KMIP_CRYPTOALG_SHA3_384:
        printf("SHA3-384");
        break;
        
        case KMIP_CRYPTOALG_SHA3_512:
        printf("SHA3-512");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA3_224:
        printf("HMAC SHA3-224");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA3_256:
        printf("HMAC SHA3-256");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA3_384:
        printf("HMAC SHA3-384");
        break;
        
        case KMIP_CRYPTOALG_HMAC_SHA3_512:
        printf("HMAC SHA3-512");
        break;
        
        case KMIP_CRYPTOALG_SHAKE_128:
        printf("SHAKE-128");
        break;
        
        case KMIP_CRYPTOALG_SHAKE_256:
        printf("SHAKE-256");
        break;
        
        case KMIP_CRYPTOALG_ARIA:
        printf("ARIA");
        break;

        case KMIP_CRYPTOALG_SEED:
        printf("SEED");
        break;

        case KMIP_CRYPTOALG_SM2:
        printf("SM2");
        break;

        case KMIP_CRYPTOALG_SM3:
        printf("SM3");
        break;

        case KMIP_CRYPTOALG_SM4:
        printf("SM4");
        break;

        case KMIP_CRYPTOALG_GOST_R_34_10_2012:
        printf("GOST R 34.10-2012");
        break;

        case KMIP_CRYPTOALG_GOST_R_34_11_2012:
        printf("GOST R 34.11-2012");
        break;

        case KMIP_CRYPTOALG_GOST_R_34_13_2015:
        printf("GOST R 34.13-2015");
        break;

        case KMIP_CRYPTOALG_GOST_28147_89:
        printf("GOST 28147-89");
        break;

        case KMIP_CRYPTOALG_XMSS:
        printf("XMSS");
        break;

        case KMIP_CRYPTOALG_SPHINCS_256:
        printf("SPHINCS-256");
        break;

        case KMIP_CRYPTOALG_MCELIECE:
        printf("McEliece");
        break;

        case KMIP_CRYPTOALG_MCELIECE_6960119:
        printf("McEliece 6960119");
        break;

        case KMIP_CRYPTOALG_MCELIECE_8192128:
        printf("McEliece 8192128");
        break;

        case KMIP_CRYPTOALG_ED25519:
        printf("Ed25519");
        break;

        case KMIP_CRYPTOALG_ED448:
        printf("Ed448");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_name_type_enum(enum name_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_NAME_UNINTERPRETED_TEXT_STRING:
        printf("Uninterpreted Text String");
        break;
        
        case KMIP_NAME_URI:
        printf("URI");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_attribute_type_enum(enum attribute_type value)
{
    if((int)value == KMIP_UNSET)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        printf("Unique Identifier");
        break;

        case KMIP_ATTR_NAME:
        printf("Name");
        break;

        case KMIP_ATTR_OBJECT_TYPE:
        printf("Object Type");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        printf("Cryptographic Algorithm");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        printf("Cryptographic Length");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:
        printf("Cryptographic Parameters");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:
        printf("Cryptographic Domain Parameters");
        break;

        case KMIP_ATTR_CERTIFICATE_TYPE:
        printf("Certificate Type");
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        printf("Certificate Length");
        break;

        case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:
        printf("X.509 Certificate Identifier");
        break;

        case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:
        printf("X.509 Certificate Subject");
        break;

        case KMIP_ATTR_X509_CERTIFICATE_ISSUER:
        printf("X.509 Certificate Issuer");
        break;

        case KMIP_ATTR_CERTIFICATE_IDENTIFIER:
        printf("Certificate Identifier");
        break;

        case KMIP_ATTR_CERTIFICATE_SUBJECT:
        printf("Certificate Subject");
        break;

        case KMIP_ATTR_CERTIFICATE_ISSUER:
        printf("Certificate Issuer");
        break;

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        printf("Digital Signature Algorithm");
        break;

        case KMIP_ATTR_DIGEST:
        printf("Digest");
        break;

        case KMIP_ATTR_OPERATION_POLICY_NAME:
        printf("Operation Policy Name");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        printf("Cryptographic Usage Mask");
        break;

        case KMIP_ATTR_LEASE_TIME:
        printf("Lease Time");
        break;

        case KMIP_ATTR_USAGE_LIMITS:
        printf("Usage Limits");
        break;

        case KMIP_ATTR_STATE:
        printf("State");
        break;

        case KMIP_ATTR_INITIAL_DATE:
        printf("Initial Date");
        break;

        case KMIP_ATTR_ACTIVATION_DATE:
        printf("Activation Date");
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        printf("Process Start Date");
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        printf("Protect Stop Date");
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        printf("Deactivation Date");
        break;

        case KMIP_ATTR_DESTROY_DATE:
        printf("Destroy Date");
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        printf("Compromise Occurrence Date");
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        printf("Compromise Date");
        break;

        case KMIP_ATTR_REVOCATION_REASON:
        printf("Revocation Reason");
        break;

        case KMIP_ATTR_ARCHIVE_DATE:
        printf("Archive Date");
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        printf("Object Group");
        break;

        case KMIP_ATTR_FRESH:
        printf("Fresh");
        break;

        case KMIP_ATTR_LINK:
        printf("Link");
        break;

        case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:
        printf("Application Specific Information");
        break;

        case KMIP_ATTR_CONTACT_INFORMATION:
        printf("Contact Information");
        break;

        case KMIP_ATTR_LAST_CHANGE_DATE:
        printf("Last Change Date");
        break;

        case KMIP_ATTR_CUSTOM_ATTRIBUTE:
        printf("* X-* Y-* Custom Attribute");
        break;

        case KMIP_ATTR_ALTERNATIVE_NAME:
        printf("Alternative Name");
        break;

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        printf("Key Value Present");
        break;

        case KMIP_ATTR_KEY_VALUE_LOCATION:
        printf("Key Value Location");
        break;

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        printf("Original Creation Date");
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        printf("Random Number Generator");
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        printf("PKCS#12 Friendly Name");
        break;

        case KMIP_ATTR_DESCRIPTION:
        printf("Description");
        break;

        case KMIP_ATTR_COMMENT:
        printf("Comment");
        break;

        case KMIP_ATTR_SENSITIVE:
        printf("Sensitive");
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        printf("Always Sensitive");
        break;

        case KMIP_ATTR_EXTRACTABLE:
        printf("Extractable");
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        printf("Never Extractable");
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        printf("Key Format Type");
        break;

        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_state_enum(enum state value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_STATE_PRE_ACTIVE:
        printf("Pre-Active");
        break;
        
        case KMIP_STATE_ACTIVE:
        printf("Active");
        break;
        
        case KMIP_STATE_DEACTIVATED:
        printf("Deactivated");
        break;
        
        case KMIP_STATE_COMPROMISED:
        printf("Compromised");
        break;
        
        case KMIP_STATE_DESTROYED:
        printf("Destroyed");
        break;
        
        case KMIP_STATE_DESTROYED_COMPROMISED:
        printf("Destroyed Compromised");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_block_cipher_mode_enum(enum block_cipher_mode value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_BLOCK_CBC:
        printf("CBC");
        break;
        
        case KMIP_BLOCK_ECB:
        printf("ECB");
        break;
        
        case KMIP_BLOCK_PCBC:
        printf("PCBC");
        break;
        
        case KMIP_BLOCK_CFB:
        printf("CFB");
        break;
        
        case KMIP_BLOCK_OFB:
        printf("OFB");
        break;
        
        case KMIP_BLOCK_CTR:
        printf("CTR");
        break;
        
        case KMIP_BLOCK_CMAC:
        printf("CMAC");
        break;
        
        case KMIP_BLOCK_CCM:
        printf("CCM");
        break;
        
        case KMIP_BLOCK_GCM:
        printf("GCM");
        break;
        
        case KMIP_BLOCK_CBC_MAC:
        printf("CBC-MAC");
        break;
        
        case KMIP_BLOCK_XTS:
        printf("XTS");
        break;
        
        case KMIP_BLOCK_AES_KEY_WRAP_PADDING:
        printf("AESKeyWrapPadding");
        break;
        
        case KMIP_BLOCK_NIST_KEY_WRAP:
        printf("NISTKeyWrap");
        break;
        
        case KMIP_BLOCK_X9102_AESKW:
        printf("X9.102 AESKW");
        break;
        
        case KMIP_BLOCK_X9102_TDKW:
        printf("X9.102 TDKW");
        break;
        
        case KMIP_BLOCK_X9102_AKW1:
        printf("X9.102 AKW1");
        break;
        
        case KMIP_BLOCK_X9102_AKW2:
        printf("X9.102 AKW2");
        break;
        
        case KMIP_BLOCK_AEAD:
        printf("AEAD");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_certificate_type_enum(enum certificate_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_CERT_X509:
        printf("X.509");
        break;
        
        case KMIP_CERT_PGP:
        printf("PGP");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_padding_method_enum(enum padding_method value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_PAD_NONE:
        printf("None");
        break;
        
        case KMIP_PAD_OAEP:
        printf("OAEP");
        break;
        
        case KMIP_PAD_PKCS5:
        printf("PKCS5");
        break;
        
        case KMIP_PAD_SSL3:
        printf("SSL3");
        break;
        
        case KMIP_PAD_ZEROS:
        printf("Zeros");
        break;
        
        case KMIP_PAD_ANSI_X923:
        printf("ANSI X9.23");
        break;
        
        case KMIP_PAD_ISO_10126:
        printf("ISO 10126");
        break;
        
        case KMIP_PAD_PKCS1v15:
        printf("PKCS1 v1.5");
        break;
        
        case KMIP_PAD_X931:
        printf("X9.31");
        break;
        
        case KMIP_PAD_PSS:
        printf("PSS");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_hashing_algorithm_enum(enum hashing_algorithm value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_HASH_MD2:
        printf("MD2");
        break;
        
        case KMIP_HASH_MD4:
        printf("MD4");
        break;
        
        case KMIP_HASH_MD5:
        printf("MD5");
        break;
        
        case KMIP_HASH_SHA1:
        printf("SHA-1");
        break;
        
        case KMIP_HASH_SHA224:
        printf("SHA-224");
        break;
        
        case KMIP_HASH_SHA256:
        printf("SHA-256");
        break;
        
        case KMIP_HASH_SHA384:
        printf("SHA-384");
        break;
        
        case KMIP_HASH_SHA512:
        printf("SHA-512");
        break;
        
        case KMIP_HASH_RIPEMD160:
        printf("RIPEMD-160");
        break;
        
        case KMIP_HASH_TIGER:
        printf("Tiger");
        break;
        
        case KMIP_HASH_WHIRLPOOL:
        printf("Whirlpool");
        break;
        
        case KMIP_HASH_SHA512_224:
        printf("SHA-512/224");
        break;
        
        case KMIP_HASH_SHA512_256:
        printf("SHA-512/256");
        break;
        
        case KMIP_HASH_SHA3_224:
        printf("SHA-3-224");
        break;
        
        case KMIP_HASH_SHA3_256:
        printf("SHA-3-256");
        break;
        
        case KMIP_HASH_SHA3_384:
        printf("SHA-3-384");
        break;
        
        case KMIP_HASH_SHA3_512:
        printf("SHA-3-512");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_key_role_type_enum(enum key_role_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_ROLE_BDK:
        printf("BDK");
        break;
        
        case KMIP_ROLE_CVK:
        printf("CVK");
        break;
        
        case KMIP_ROLE_DEK:
        printf("DEK");
        break;
        
        case KMIP_ROLE_MKAC:
        printf("MKAC");
        break;
        
        case KMIP_ROLE_MKSMC:
        printf("MKSMC");
        break;
        
        case KMIP_ROLE_MKSMI:
        printf("MKSMI");
        break;
        
        case KMIP_ROLE_MKDAC:
        printf("MKDAC");
        break;
        
        case KMIP_ROLE_MKDN:
        printf("MKDN");
        break;
        
        case KMIP_ROLE_MKCP:
        printf("MKCP");
        break;
        
        case KMIP_ROLE_MKOTH:
        printf("MKOTH");
        break;
        
        case KMIP_ROLE_KEK:
        printf("KEK");
        break;
        
        case KMIP_ROLE_MAC16609:
        printf("MAC16609");
        break;
        
        case KMIP_ROLE_MAC97971:
        printf("MAC97971");
        break;
        
        case KMIP_ROLE_MAC97972:
        printf("MAC97972");
        break;
        
        case KMIP_ROLE_MAC97973:
        printf("MAC97973");
        break;
        
        case KMIP_ROLE_MAC97974:
        printf("MAC97974");
        break;
        
        case KMIP_ROLE_MAC97975:
        printf("MAC97975");
        break;
        
        case KMIP_ROLE_ZPK:
        printf("ZPK");
        break;
        
        case KMIP_ROLE_PVKIBM:
        printf("PVKIBM");
        break;
        
        case KMIP_ROLE_PVKPVV:
        printf("PVKPVV");
        break;
        
        case KMIP_ROLE_PVKOTH:
        printf("PVKOTH");
        break;
        
        case KMIP_ROLE_DUKPT:
        printf("DUKPT");
        break;
        
        case KMIP_ROLE_IV:
        printf("IV");
        break;
        
        case KMIP_ROLE_TRKBK:
        printf("TRKBK");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_digital_signature_algorithm_enum(enum digital_signature_algorithm value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_DIGITAL_MD2_WITH_RSA:
        printf("MD2 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_MD5_WITH_RSA:
        printf("MD5 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_SHA1_WITH_RSA:
        printf("SHA-1 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_SHA224_WITH_RSA:
        printf("SHA-224 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_SHA256_WITH_RSA:
        printf("SHA-256 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_SHA384_WITH_RSA:
        printf("SHA-384 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_SHA512_WITH_RSA:
        printf("SHA-512 with RSA Encryption (PKCS#1 v1.5)");
        break;
        
        case KMIP_DIGITAL_RSASSA_PSS:
        printf("RSASSA-PSS (PKCS#1 v2.1)");
        break;
        
        case KMIP_DIGITAL_DSA_WITH_SHA1:
        printf("DSA with SHA-1");
        break;
        
        case KMIP_DIGITAL_DSA_WITH_SHA224:
        printf("DSA with SHA224");
        break;
        
        case KMIP_DIGITAL_DSA_WITH_SHA256:
        printf("DSA with SHA256");
        break;
        
        case KMIP_DIGITAL_ECDSA_WITH_SHA1:
        printf("ECDSA with SHA-1");
        break;
        
        case KMIP_DIGITAL_ECDSA_WITH_SHA224:
        printf("ECDSA with SHA224");
        break;
        
        case KMIP_DIGITAL_ECDSA_WITH_SHA256:
        printf("ECDSA with SHA256");
        break;
        
        case KMIP_DIGITAL_ECDSA_WITH_SHA384:
        printf("ECDSA with SHA384");
        break;
        
        case KMIP_DIGITAL_ECDSA_WITH_SHA512:
        printf("ECDSA with SHA512");
        break;
        
        case KMIP_DIGITAL_SHA3_256_WITH_RSA:
        printf("SHA3-256 with RSA Encryption");
        break;
        
        case KMIP_DIGITAL_SHA3_384_WITH_RSA:
        printf("SHA3-384 with RSA Encryption");
        break;
        
        case KMIP_DIGITAL_SHA3_512_WITH_RSA:
        printf("SHA3-512 with RSA Encryption");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_date_time(int64 value)
{
	time_t t = value;
	struct tm tm[1];
	char decoded_time[64];
	gmtime_r(&t, tm);
	strftime(decoded_time, sizeof decoded_time, "%F %T", tm);
	printf ("%s (%" PRId64 ")", decoded_time, value);
}

void
kmip_print_mask_generator_enum(enum mask_generator value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_MASKGEN_MGF1:
        printf("MGF1");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_wrapping_method_enum(enum wrapping_method value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_WRAP_ENCRYPT:
        printf("Encrypt");
        break;
        
        case KMIP_WRAP_MAC_SIGN:
        printf("MAC/sign");
        break;
        
        case KMIP_WRAP_ENCRYPT_MAC_SIGN:
        printf("Encrypt then MAC/sign");
        break;
        
        case KMIP_WRAP_MAC_SIGN_ENCRYPT:
        printf("MAC/sign then encrypt");
        break;
        
        case KMIP_WRAP_TR31:
        printf("TR-31");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_encoding_option_enum(enum encoding_option value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_ENCODE_NO_ENCODING:
        printf("No Encoding");
        break;
        
        case KMIP_ENCODE_TTLV_ENCODING:
        printf("TTLV Encoding");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_key_wrap_type_enum(enum key_wrap_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_WRAPTYPE_NOT_WRAPPED:
        printf("Not Wrapped");
        break;
        
        case KMIP_WRAPTYPE_AS_REGISTERED:
        printf("As Registered");
        break;
        
        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_credential_type_enum(enum credential_type value)
{
    if(value == 0)
    {
        printf("-");
        return;
    }
    
    switch(value)
    {
        case KMIP_CRED_USERNAME_AND_PASSWORD:
        printf("Username and Password");
        break;
        
        case KMIP_CRED_DEVICE:
        printf("Device");
        break;
        
        case KMIP_CRED_ATTESTATION:
        printf("Attestation");
        break;

        case KMIP_CRED_ONE_TIME_PASSWORD:
        printf("One Time Password");
        break;

        case KMIP_CRED_HASHED_PASSWORD:
        printf("Hashed Password");
        break;

        case KMIP_CRED_TICKET:
        printf("Ticket");
        break;

        default:
        printf("Unknown");
        break;
    };
}

void
kmip_print_cryptographic_usage_mask_enums(int indent, int32 value)
{
    printf("\n");
    
    if((value & KMIP_CRYPTOMASK_SIGN) == KMIP_CRYPTOMASK_SIGN)
    {
        printf("%*sSign\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_VERIFY) == KMIP_CRYPTOMASK_VERIFY)
    {
        printf("%*sVerify\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_ENCRYPT) == KMIP_CRYPTOMASK_ENCRYPT)
    {
        printf("%*sEncrypt\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_DECRYPT) == KMIP_CRYPTOMASK_DECRYPT)
    {
        printf("%*sDecrypt\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_WRAP_KEY) == KMIP_CRYPTOMASK_WRAP_KEY)
    {
        printf("%*sWrap Key\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_UNWRAP_KEY) == KMIP_CRYPTOMASK_UNWRAP_KEY)
    {
        printf("%*sUnwrap Key\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_EXPORT) == KMIP_CRYPTOMASK_EXPORT)
    {
        printf("%*sExport\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_MAC_GENERATE) == KMIP_CRYPTOMASK_MAC_GENERATE)
    {
        printf("%*sMAC Generate\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_MAC_VERIFY) == KMIP_CRYPTOMASK_MAC_VERIFY)
    {
        printf("%*sMAC Verify\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_DERIVE_KEY) == KMIP_CRYPTOMASK_DERIVE_KEY)
    {
        printf("%*sDerive Key\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_CONTENT_COMMITMENT) == KMIP_CRYPTOMASK_CONTENT_COMMITMENT)
    {
        printf("%*sContent Commitment\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_KEY_AGREEMENT) == KMIP_CRYPTOMASK_KEY_AGREEMENT)
    {
        printf("%*sKey Agreement\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_CERTIFICATE_SIGN) == KMIP_CRYPTOMASK_CERTIFICATE_SIGN)
    {
        printf("%*sCertificate Sign\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_CRL_SIGN) == KMIP_CRYPTOMASK_CRL_SIGN)
    {
        printf("%*sCRL Sign\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_GENERATE_CRYPTOGRAM) == KMIP_CRYPTOMASK_GENERATE_CRYPTOGRAM)
    {
        printf("%*sGenerate Cryptogram\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_VALIDATE_CRYPTOGRAM) == KMIP_CRYPTOMASK_VALIDATE_CRYPTOGRAM)
    {
        printf("%*sValidate Cryptogram\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_TRANSLATE_ENCRYPT) == KMIP_CRYPTOMASK_TRANSLATE_ENCRYPT)
    {
        printf("%*sTranslate Encrypt\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_TRANSLATE_DECRYPT) == KMIP_CRYPTOMASK_TRANSLATE_DECRYPT)
    {
        printf("%*sTranslate Decrypt\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_TRANSLATE_WRAP) == KMIP_CRYPTOMASK_TRANSLATE_WRAP)
    {
        printf("%*sTranslate Wrap\n", indent, "");
    }
    
    if((value & KMIP_CRYPTOMASK_TRANSLATE_UNWRAP) == KMIP_CRYPTOMASK_TRANSLATE_UNWRAP)
    {
        printf("%*sTranslate Unwrap\n", indent, "");
    }

    if((value & KMIP_CRYPTOMASK_AUTHENTICATE) == KMIP_CRYPTOMASK_AUTHENTICATE)
    {
        printf("%*sAuthenticate\n", indent, "");
    }

    if((value & KMIP_CRYPTOMASK_UNRESTRICTED) == KMIP_CRYPTOMASK_UNRESTRICTED)
    {
        printf("%*sUnrestricted\n", indent, "");
    }

    if((value & KMIP_CRYPTOMASK_FPE_ENCRYPT) == KMIP_CRYPTOMASK_FPE_ENCRYPT)
    {
        printf("%*sFPE Encrypt\n", indent, "");
    }

    if((value & KMIP_CRYPTOMASK_FPE_DECRYPT) == KMIP_CRYPTOMASK_FPE_DECRYPT)
    {
        printf("%*sFPE Decrypt\n", indent, "");
    }
}

void
kmip_print_protection_storage_mask_enum(int indent, int32 value)
{
    printf("\n");

    if((value & KMIP_PROTECT_SOFTWARE) == KMIP_PROTECT_SOFTWARE)
    {
        printf("%*sSoftware\n", indent, "");
    }

    if((value & KMIP_PROTECT_HARDWARE) == KMIP_PROTECT_HARDWARE)
    {
        printf("%*sHardware\n", indent, "");
    }

    if((value & KMIP_PROTECT_ON_PROCESSOR) == KMIP_PROTECT_ON_PROCESSOR)
    {
        printf("%*sOn Processor\n", indent, "");
    }

    if((value & KMIP_PROTECT_ON_SYSTEM) == KMIP_PROTECT_ON_SYSTEM)
    {
        printf("%*sOn System\n", indent, "");
    }

    if((value & KMIP_PROTECT_OFF_SYSTEM) == KMIP_PROTECT_OFF_SYSTEM)
    {
        printf("%*sOff System\n", indent, "");
    }

    if((value & KMIP_PROTECT_HYPERVISOR) == KMIP_PROTECT_HYPERVISOR)
    {
        printf("%*sHypervisor\n", indent, "");
    }

    if((value & KMIP_PROTECT_OPERATING_SYSTEM) == KMIP_PROTECT_OPERATING_SYSTEM)
    {
        printf("%*sOperating System\n", indent, "");
    }

    if((value & KMIP_PROTECT_CONTAINER) == KMIP_PROTECT_CONTAINER)
    {
        printf("%*sContainer\n", indent, "");
    }

    if((value & KMIP_PROTECT_ON_PREMISES) == KMIP_PROTECT_ON_PREMISES)
    {
        printf("%*sOn Premises\n", indent, "");
    }

    if((value & KMIP_PROTECT_OFF_PREMISES) == KMIP_PROTECT_OFF_PREMISES)
    {
        printf("%*sOff Premises\n", indent, "");
    }

    if((value & KMIP_PROTECT_SELF_MANAGED) == KMIP_PROTECT_SELF_MANAGED)
    {
        printf("%*sSelf Managed\n", indent, "");
    }

    if((value & KMIP_PROTECT_OUTSOURCED) == KMIP_PROTECT_OUTSOURCED)
    {
        printf("%*sOutsourced\n", indent, "");
    }

    if((value & KMIP_PROTECT_VALIDATED) == KMIP_PROTECT_VALIDATED)
    {
        printf("%*sValidated\n", indent, "");
    }

    if((value & KMIP_PROTECT_SAME_JURISDICTION) == KMIP_PROTECT_SAME_JURISDICTION)
    {
        printf("%*sSame Jurisdiction\n", indent, "");
    }
}

void
kmip_print_storage_status_mask_enum(enum storage_status_mask value)
{
    char *sep = "";
    if((value & KMIP_SSM_ONLINE_STORAGE))
    {
        printf("%sonline", sep); sep = " ";
    }
    if((value & KMIP_SSM_ARCHIVAL_STORAGE))
    {
        printf("%sarchived", sep); sep = " ";
    }
    if((value & KMIP_SSM_DESTROYED_STORAGE))
    {
        printf("%sdestroyed", sep); sep = " ";
    }
}

void
kmip_print_object_group_member_enum(enum object_group_member value)
{
    char *sep = "";
    if((value & KMIP_OGM_GROUP_MEMBER_FRESH))
    {
        printf("%sfresh", sep); sep = " ";
    }
    if((value & KMIP_OGM_GROUP_MEMBER_DEFAULT))
    {
        printf("%sdefault", sep); sep = " ";
    }
}

void
kmip_print_protection_storage_masks(int indent, ProtectionStorageMasks *value)
{
    printf("%*sProtection Storage Masks @ %p\n", indent, "", (void *)value);

    if(value != NULL)
    {
        printf("%*sMasks: %zu\n", indent + 2, "", value->masks->size);
        LinkedListItem *curr = value->masks->head;
        size_t count = 1;
        while(curr != NULL)
        {
            printf("%*sMask: %zu", indent + 4, "", count);
            int32 mask = *(int32 *)curr->data;
            kmip_print_protection_storage_mask_enum(indent + 6, mask);

            curr = curr->next;
            count++;
        }
    }
}

void
kmip_print_integer(int32 value)
{
    switch(value)
    {
        case KMIP_UNSET:
        printf("-");
        break;
        
        default:
        printf("%d", value);
        break;
    };
}

void
kmip_print_bool(int32 value)
{
    switch(value)
    {
        case KMIP_TRUE:
        printf("True");
        break;
        
        case KMIP_FALSE:
        printf("False");
        break;
        
        default:
        printf("-");
        break;
    };
}

void
kmip_print_text_string(int indent, const char *name, TextString *value)
{
    printf("%*s%s @ %p\n", indent, "", name, (void *)value);
    
    if(value != NULL)
    {
        printf("%*sValue: %.*s\n", indent + 2, "", (int)value->size, value->value);
    }
    
    return;
}

void
kmip_print_byte_string(int indent, const char *name, ByteString *value)
{
    printf("%*s%s @ %p\n", indent, "", name, (void *)value);
    
    if(value != NULL)
    {
        printf("%*sValue:", indent + 2, "");
        for(size_t i = 0; i < value->size; i++)
        {
            if(i % 16 == 0)
            {
                printf("\n%*s0x", indent + 4, "");
            }
            printf("%02X", value->value[i]);
        }
        printf("\n");
    }
    
    return;
}

void
kmip_print_protocol_version(int indent, ProtocolVersion *value)
{
    printf("%*sProtocol Version @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sMajor: %d\n", indent + 2, "", value->major);
        printf("%*sMinor: %d\n", indent + 2, "", value->minor);
    }
    
    return;
}

void
kmip_print_name(int indent, Name *value)
{
    printf("%*sName @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(indent + 2, "Name Value", value->value);
        
        printf("%*sName Type: ", indent + 2, "");
        kmip_print_name_type_enum(value->type);
        printf("\n");
    }
}

void
kmip_print_nonce(int indent, Nonce *value)
{
    printf("%*sNonce @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_byte_string(indent + 2, "Nonce ID", value->nonce_id);
        kmip_print_byte_string(indent + 2, "Nonce Value", value->nonce_value);
    }
    
    return;
}

void
kmip_print_cryptographic_parameters(int indent, CryptographicParameters *value)
{
    printf("%*sCryptographic Parameters @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sBlock Cipher Mode: ", indent + 2, "");
        kmip_print_block_cipher_mode_enum(value->block_cipher_mode);
        printf("\n");
        
        printf("%*sPadding Method: ", indent + 2, "");
        kmip_print_padding_method_enum(value->padding_method);
        printf("\n");
        
        printf("%*sHashing Algorithm: ", indent + 2, "");
        kmip_print_hashing_algorithm_enum(value->hashing_algorithm);
        printf("\n");
        
        printf("%*sKey Role Type: ", indent + 2, "");
        kmip_print_key_role_type_enum(value->key_role_type);
        printf("\n");
        
        printf("%*sDigital Signature Algorithm: ", indent + 2, "");
        kmip_print_digital_signature_algorithm_enum(value->digital_signature_algorithm);
        printf("\n");
        
        printf("%*sCryptographic Algorithm: ", indent + 2, "");
        kmip_print_cryptographic_algorithm_enum(value->cryptographic_algorithm);
        printf("\n");
        
        printf("%*sRandom IV: ", indent + 2, "");
        kmip_print_bool(value->random_iv);
        printf("\n");
        
        printf("%*sIV Length: ", indent + 2, "");
        kmip_print_integer(value->iv_length);
        printf("\n");
        
        printf("%*sTag Length: ", indent + 2, "");
        kmip_print_integer(value->tag_length);
        printf("\n");
        
        printf("%*sFixed Field Length: ", indent + 2, "");
        kmip_print_integer(value->fixed_field_length);
        printf("\n");
        
        printf("%*sInvocation Field Length: ", indent + 2, "");
        kmip_print_integer(value->invocation_field_length);
        printf("\n");
        
        printf("%*sCounter Length: ", indent + 2, "");
        kmip_print_integer(value->counter_length);
        printf("\n");
        
        printf("%*sInitial Counter Value: ", indent + 2, "");
        kmip_print_integer(value->initial_counter_value);
        printf("\n");
        
        printf("%*sSalt Length: ", indent + 2, "");
        kmip_print_integer(value->salt_length);
        printf("\n");
        
        printf("%*sMask Generator: ", indent + 2, "");
        kmip_print_mask_generator_enum(value->mask_generator);
        printf("\n");
        
        printf("%*sMask Generator Hashing Algorithm: ", indent + 2, "");
        kmip_print_hashing_algorithm_enum(value->mask_generator_hashing_algorithm);
        printf("\n");
        
        kmip_print_byte_string(indent + 2, "P Source", value->p_source);
        
        printf("%*sTrailer Field: ", indent + 2, "");
        kmip_print_integer(value->trailer_field);
        printf("\n");
    }
}

void
kmip_print_encryption_key_information(int indent, EncryptionKeyInformation *value)
{
    printf("%*sEncryption Key Information @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(indent + 2, "Unique Identifier", value->unique_identifier);
        
        kmip_print_cryptographic_parameters(indent + 2, value->cryptographic_parameters);
    }
}

void
kmip_print_mac_signature_key_information(int indent, MACSignatureKeyInformation *value)
{
    printf("%*sMAC/Signature Key Information @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(indent + 2, "Unique Identifier", value->unique_identifier);
        
        kmip_print_cryptographic_parameters(indent + 2, value->cryptographic_parameters);
    }
}

void
kmip_print_key_wrapping_data(int indent, KeyWrappingData *value)
{
    printf("%*sKey Wrapping Data @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sWrapping Method: ", indent + 2, "");
        kmip_print_wrapping_method_enum(value->wrapping_method);
        printf("\n");
        
        kmip_print_encryption_key_information(indent + 2, value->encryption_key_info);
        
        kmip_print_mac_signature_key_information(indent + 2, value->mac_signature_key_info);
        
        kmip_print_byte_string(indent + 2, "MAC/Signature", value->mac_signature);
        
        kmip_print_byte_string(indent + 2, "IV/Counter/Nonce", value->iv_counter_nonce);
        
        printf("%*sEncoding Option: ", indent + 2, "");
        kmip_print_encoding_option_enum(value->encoding_option);
        printf("\n");
    }
    
    return;
}

void
kmip_print_attribute_value(int indent, enum attribute_type type, void *value)
{
    printf("%*sAttribute Value: ", indent, "");
    
    switch(type)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        printf("\n");
        kmip_print_text_string(indent + 2, "Unique Identifier", value);
        break;

        case KMIP_ATTR_NAME:
        printf("\n");
        kmip_print_name(indent + 2, value);
        break;

        case KMIP_ATTR_OBJECT_TYPE:
        kmip_print_object_type_enum(*(enum object_type *)value);
        printf("\n");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        kmip_print_cryptographic_algorithm_enum(*(enum cryptographic_algorithm *)value);
        printf("\n");
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        printf("%d\n", *(int32 *)value);
        break;

        // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:	XXX how to hack struct?
        // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:	XXX how to hack struct?

        case KMIP_ATTR_CERTIFICATE_TYPE:
        kmip_print_certificate_type_enum(*(enum certificate_type *)value);
        printf("\n");
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        printf("%d\n", *(int32 *)value);
        break;

        // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_ISSUER:	XXX how to hack struct?

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        kmip_print_digital_signature_algorithm_enum(*(enum digital_signature_algorithm *)value);
        printf("\n");
        break;

        // case KMIP_ATTR_DIGEST:	XXX how to hack struct?

        case KMIP_ATTR_OPERATION_POLICY_NAME:
        printf("\n");
        kmip_print_text_string(indent + 2, "Operation Policy Name", value);
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        kmip_print_cryptographic_usage_mask_enums(indent + 2, *(int32 *)value);
        break;

        case KMIP_ATTR_LEASE_TIME:
        printf("%u\n", *(uint32 *)value);
        break;

        // case KMIP_ATTR_USAGE_LIMITS:	XXX how to hack struct?

        case KMIP_ATTR_STATE:
        kmip_print_state_enum(*(enum state *)value);
        printf("\n");
        break;

        case KMIP_ATTR_INITIAL_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_ACTIVATION_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_DESTROY_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        // case KMIP_ATTR_REVOCATION_REASON:	XXX how to hack struct?

        case KMIP_ATTR_ARCHIVE_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        printf("\n");
        kmip_print_text_string(indent + 2, "Object Group", value);
        break;

        case KMIP_ATTR_FRESH:
        printf("%d\n", *(bool32 *)value);
        break;

        // case KMIP_ATTR_LINK:	XXX how to hack struct?
        // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:	XXX how to hack struct?
        // case KMIP_ATTR_CONTACT_INFORMATION:	XXX how to hack struct?

        case KMIP_ATTR_LAST_CHANGE_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        // case KMIP_ATTR_CUSTOM_ATTRIBUTE:	XXX how to hack custom?
        // case KMIP_ATTR_ALTERNATIVE_NAME:	XXX how to hack struct?

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        printf("%d\n", *(bool32 *)value);
        break;

        // case KMIP_ATTR_KEY_VALUE_LOCATION:	XXX how to hack struct?

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        kmip_print_date_time(*(int64*)value);
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        printf("\n");
        kmip_print_text_string(indent + 2, "Random Number Generator", value);
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        printf("\n");
        kmip_print_text_string(indent + 2, "PKCS#12 Friendly Name", value);
        break;

        case KMIP_ATTR_DESCRIPTION:
        printf("\n");
        kmip_print_text_string(indent + 2, "Description", value);
        break;

        case KMIP_ATTR_COMMENT:
        printf("\n");
        kmip_print_text_string(indent + 2, "Comment", value);
        break;


        case KMIP_ATTR_SENSITIVE:
        printf("%d\n", *(bool32 *)value);
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        printf("%d\n", *(bool32 *)value);
        break;

        case KMIP_ATTR_EXTRACTABLE:
        printf("%d\n", *(bool32 *)value);
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        printf("%d\n", *(bool32 *)value);
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        kmip_print_key_format_type_enum(*(enum key_format_type *)value);
        printf("\n");
        break;
        
        default:
        printf("Unknown\n");
        break;
    };
}

void
kmip_print_attribute(int indent, Attribute *value)
{
    printf("%*sAttribute @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sAttribute Name: ", indent + 2, "");
        kmip_print_attribute_type_enum(value->type);
        printf("\n");
        
        printf("%*sAttribute Index: ", indent + 2, "");
        kmip_print_integer(value->index);
        printf("\n");
        
        kmip_print_attribute_value(indent + 2, value->type, value->value);
    }
    
    return;
}

void
kmip_print_key_material(int indent, enum key_format_type format, void *value)
{
    switch(format)
    {
        case KMIP_KEYFORMAT_RAW:
        case KMIP_KEYFORMAT_OPAQUE:
        case KMIP_KEYFORMAT_PKCS1:
        case KMIP_KEYFORMAT_PKCS8:
        case KMIP_KEYFORMAT_X509:
        case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
        kmip_print_byte_string(indent, "Key Material", (ByteString *)value);
        break;
        
        default:
        printf("%*sUnknown Key Material @ %p\n", indent, "", value);
        break;
    };
}

void
kmip_print_key_value(int indent, enum type type, enum key_format_type format, void *value)
{
    switch(type)
    {
        case KMIP_TYPE_BYTE_STRING:
        kmip_print_byte_string(indent, "Key Value", (ByteString *)value);
        break;
        
        case KMIP_TYPE_STRUCTURE:
        printf("%*sKey Value @ %p\n", indent, "", value);
        
        if(value != NULL)
        {
            KeyValue key_value = *(KeyValue *)value;
            kmip_print_key_material(indent + 2, format, key_value.key_material);
            printf("%*sAttributes: %zu\n", indent + 2, "", key_value.attribute_count);
            for(size_t i = 0; i < key_value.attribute_count; i++)
            {
                kmip_print_attribute(indent + 2, &key_value.attributes[i]);
            }
        }
        break;
        
        default:
        printf("%*sUnknown Key Value @ %p\n", indent, "", value);
        break;
    };
}

void
kmip_print_key_block(int indent, KeyBlock *value)
{
    printf("%*sKey Block @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sKey Format Type: ", indent + 2, "");
        kmip_print_key_format_type_enum(value->key_format_type);
        printf("\n");
        
        printf("%*sKey Compression Type: ", indent + 2, "");
        kmip_print_key_compression_type_enum(value->key_compression_type);
        printf("\n");
        
        kmip_print_key_value(indent + 2, value->key_value_type, value->key_format_type, value->key_value);
        
        printf("%*sCryptographic Algorithm: ", indent + 2, "");
        kmip_print_cryptographic_algorithm_enum(value->cryptographic_algorithm);
        printf("\n");
        
        printf("%*sCryptographic Length: %d\n", indent + 2, "", value->cryptographic_length);
        
        kmip_print_key_wrapping_data(indent + 2, value->key_wrapping_data);
    }
    
    return;
}

void
kmip_print_symmetric_key(int indent, SymmetricKey *value)
{
    printf("%*sSymmetric Key @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_key_block(indent + 2, value->key_block);
    }
    
    return;
}

void
kmip_print_object(int indent, enum object_type type, void *value)
{
    switch(type)
    {
        case KMIP_OBJTYPE_SYMMETRIC_KEY:
        kmip_print_symmetric_key(indent, (SymmetricKey *)value);
        break;
        
        default:
        printf("%*sUnknown Object @ %p\n", indent, "", value);
        break;
    };
}

void
kmip_print_key_wrapping_specification(int indent, KeyWrappingSpecification *value)
{
    printf("%*sKey Wrapping Specification @ %p\n", indent, "", (void *)value);
}

void
kmip_print_attributes(int indent, Attributes *value)
{
    printf("%*sAttributes @ %p\n", indent, "", (void *)value);

    if(value != NULL)
    {
        printf("%*sAttributes: %zu\n", indent + 2, "", value->attribute_list->size);
        LinkedListItem *curr = value->attribute_list->head;
        while(curr != NULL)
        {
            Attribute *attribute = (Attribute *)curr->data;
            kmip_print_attribute(indent + 4, attribute);

            curr = curr->next;
        }
    }
}

void
kmip_print_template_attribute(int indent, TemplateAttribute *value)
{
    printf("%*sTemplate Attribute @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sNames: %zu\n", indent + 2, "", value->name_count);
        for(size_t i = 0; i < value->name_count; i++)
        {
            kmip_print_name(indent + 4, &value->names[i]);
        }
        
        printf("%*sAttributes: %zu\n", indent + 2, "", value->attribute_count);
        for(size_t i = 0; i< value->attribute_count; i++)
        {
            kmip_print_attribute(indent + 4, &value->attributes[i]);
        }
    }
}

void
kmip_print_create_request_payload(int indent, CreateRequestPayload *value)
{
    printf("%*sCreate Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sObject Type: ", indent + 2, "");
        kmip_print_object_type_enum(value->object_type);
        printf("\n");
        
        kmip_print_template_attribute(indent + 2, value->template_attribute);
        kmip_print_attributes(indent + 2, value->attributes);
        kmip_print_protection_storage_masks(indent + 2, value->protection_storage_masks);
    }
}

void
kmip_print_create_response_payload(int indent, CreateResponsePayload *value)
{
    printf("%*sCreate Response Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sObject Type: ", indent + 2, "");
        kmip_print_object_type_enum(value->object_type);
        printf("\n");
        
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);
        
        kmip_print_template_attribute(indent + 2, value->template_attribute);
    }
}

void
kmip_print_locate_request_payload(int indent, LocateRequestPayload *value)
{
    printf("%*sLocate Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sMaximum Items: ", indent + 2, "");
        kmip_print_integer(value->maximum_items);
        printf("\n");

        printf("%*sOffset Items: ", indent + 2, "");
        kmip_print_integer(value->offset_items);
        printf("\n");
 
        printf("%*sStorage Status Mask: ", indent + 2, "");
        kmip_print_storage_status_mask_enum(value->storage_status_mask);
        printf("\n");
 
        printf("%*sObject Group Member: ", indent + 2, "");
        kmip_print_object_group_member_enum(value->object_group_member);
        printf("\n");

	printf("%*sAttributes: %d\n", indent + 2, "", value->attribute_count);
	for(int i = 0; i < value->attribute_count; ++i)
	{
	    kmip_print_attribute(indent + 4, value->attributes + i);
	}
    }
}

void
kmip_print_locate_response_payload(int indent, LocateResponsePayload *value)
{
    printf("%*sLocate Response Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sLocated Items: ", indent + 2, "");
        kmip_print_integer(value->located_items);
        printf("\n");

	printf("%*sUnique Identifiers: %d\n", indent + 2, "", value->unique_identifiers_count);
	for(int i = 0; i < value->unique_identifiers_count; ++i)
	{
	    printf("%*s%.*s\n", indent + 4, "",
		(int)value->unique_identifiers[i].size,
		value->unique_identifiers[i].value);
	}
    }
}

void
kmip_print_get_request_payload(int indent, GetRequestPayload *value)
{
    printf("%*sGet Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);
        
        printf("%*sKey Format Type: ", indent + 2, "");
        kmip_print_key_format_type_enum(value->key_format_type);
        printf("\n");
        
        printf("%*sKey Wrap Type: ", indent + 2, "");
        kmip_print_key_wrap_type_enum(value->key_wrap_type);
        printf("\n");
        
        printf("%*sKey Compression Type: ", indent + 2, "");
        kmip_print_key_compression_type_enum(value->key_compression_type);
        printf("\n");
        
        kmip_print_key_wrapping_specification(indent + 2, value->key_wrapping_spec);
    }
}

void
kmip_print_get_response_payload(int indent, GetResponsePayload *value)
{
    printf("%*sGet Response Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sObject Type: ", indent + 2, "");
        kmip_print_object_type_enum(value->object_type);
        printf("\n");
        
        kmip_print_text_string(indent + 2, "Unique Identifier", value->unique_identifier);
        kmip_print_object(indent + 2, value->object_type, value->object);
    }
    
    return;
}

void
kmip_print_get_attributes_request_payload(int indent, GetAttributesRequestPayload *value)
{
    printf("%*sGet Attributes Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);

	printf("%*sAttribute Names: %d\n", indent + 2, "", value->attribute_count);
	for(int i = 0; i < value->attribute_count; ++i)
	{
	    printf("%*s", indent + 4, "");
	    kmip_print_attribute_type_enum(value->attribute_names[i]);
	    printf ("\n");
	}
    }
}

void
kmip_print_get_attributes_response_payload(int indent, GetAttributesResponsePayload *value)
{
    printf("%*sGet Attributes Response Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);

	printf("%*sAttributes: %d\n", indent + 2, "", value->attribute_count);
	for(int i = 0; i < value->attribute_count; ++i)
	{
	    kmip_print_attribute(indent + 4, value->attributes + i);
	}
    }
    
    return;
}

void
kmip_print_get_attribute_list_request_payload(int indent, GetAttributeListRequestPayload *value)
{
    printf("%*sGet Attribute List Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);
    }
}

void
kmip_print_get_attribute_list_response_payload(int indent, GetAttributeListResponsePayload *value)
{
    printf("%*sGet Attribute List Response Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);

	printf("%*sAttribute Names: %d\n", indent + 2, "", value->attribute_names_count);
	for(int i = 0; i < value->attribute_names_count; ++i)
	{
	    printf("%*s", indent + 4, "");
	    kmip_print_attribute_type_enum(value->attribute_names[i]);
	    printf ("\n");
	}
    }
    
    return;
}

void
kmip_print_destroy_request_payload(int indent, DestroyRequestPayload *value)
{
    printf("%*sDestroy Request Payload @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);
    }
}

void
kmip_print_destroy_response_payload(int indent, DestroyResponsePayload *value)
{
    printf("%*sDestroy Response Payload @ %p\n", indent, "", (void *)value);

    if(value != NULL)
    {
        kmip_print_text_string(
            indent + 2,
            "Unique Identifier",
            value->unique_identifier);
    }
}

void
kmip_print_request_payload(int indent, enum operation type, void *value)
{
    switch(type)
    {
        case KMIP_OP_CREATE:
        kmip_print_create_request_payload(indent, value);
        break;
        
        case KMIP_OP_LOCATE:
        kmip_print_locate_request_payload(indent, (LocateRequestPayload *)value);
        break;
        
        case KMIP_OP_GET:
        kmip_print_get_request_payload(indent, (GetRequestPayload *)value);
        break;
        
        case KMIP_OP_GET_ATTRIBUTES:
        kmip_print_get_attributes_request_payload(indent, (GetAttributesRequestPayload *)value);
        break;
        
        case KMIP_OP_GET_ATTRIBUTE_LIST:
        kmip_print_get_attribute_list_request_payload(indent, (GetAttributeListRequestPayload *)value);
        break;
        
        case KMIP_OP_DESTROY:
        kmip_print_destroy_request_payload(indent, value);
        break;
        
        default:
        printf("%*sUnknown Payload @ %p\n", indent, "", value);
        break;
    };
}

void
kmip_print_response_payload(int indent, enum operation type, void *value)
{
    switch(type)
    {
        case KMIP_OP_CREATE:
        kmip_print_create_response_payload(indent, value);
        break;
        
        case KMIP_OP_LOCATE:
        kmip_print_locate_response_payload(indent, (LocateResponsePayload *)value);
        break;
        
        case KMIP_OP_GET:
        kmip_print_get_response_payload(indent, (GetResponsePayload *)value);
        break;
        
        case KMIP_OP_GET_ATTRIBUTES:
        kmip_print_get_attributes_response_payload(indent, (GetAttributesResponsePayload *)value);
        break;
        
        case KMIP_OP_GET_ATTRIBUTE_LIST:
        kmip_print_get_attribute_list_response_payload(indent, (GetAttributeListResponsePayload *)value);
        break;
        
        case KMIP_OP_DESTROY:
        kmip_print_destroy_response_payload(indent, value);
        break;
        
        default:
        printf("%*sUnknown Payload @ %p\n", indent, "", value);
        break;
    };
}

void
kmip_print_username_password_credential(int indent, UsernamePasswordCredential *value)
{
    printf("%*sUsername/Password Credential @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_text_string(indent + 2, "Username", value->username);
        kmip_print_text_string(indent + 2, "Password", value->password);
    }
}

void
kmip_print_device_credential(int indent, DeviceCredential *value)
{
    printf("%*sDevice Credential @ %p\n", indent, "", (void *)value);

    if(value != NULL)
    {
        kmip_print_text_string(indent + 2, "Device Serial Number", value->device_serial_number);
        kmip_print_text_string(indent + 2, "Password", value->password);
        kmip_print_text_string(indent + 2, "Device Identifier", value->device_identifier);
        kmip_print_text_string(indent + 2, "Network Identifier", value->network_identifier);
        kmip_print_text_string(indent + 2, "Machine Identifier", value->machine_identifier);
        kmip_print_text_string(indent + 2, "Media Identifier", value->media_identifier);
    }
}

void
kmip_print_attestation_credential(int indent, AttestationCredential *value)
{
    printf("%*sAttestation Credential @ %p\n", indent, "", (void *)value);

    if(value != NULL)
    {
        kmip_print_nonce(indent + 2, value->nonce);
        printf("%*sAttestation Type: ", indent + 2, "");
        kmip_print_attestation_type_enum(value->attestation_type);
        printf("\n");
        kmip_print_byte_string(indent + 2, "Attestation Measurement", value->attestation_measurement);
        kmip_print_byte_string(indent + 2, "Attestation Assertion", value->attestation_assertion);
    }
}

void
kmip_print_credential_value(int indent, enum credential_type type, void *value)
{
    printf("%*sCredential Value @ %p\n", indent, "", value);
    
    if(value != NULL)
    {
        switch(type)
        {
            case KMIP_CRED_USERNAME_AND_PASSWORD:
            kmip_print_username_password_credential(indent + 2, value);
            break;
            
            case KMIP_CRED_DEVICE:
            kmip_print_device_credential(indent + 2, value);
            break;
            
            case KMIP_CRED_ATTESTATION:
            kmip_print_attestation_credential(indent + 2, value);
            break;
            
            default:
            printf("%*sUnknown Credential @ %p\n", indent + 2, "", value);
            break;
        };
    }
}

void
kmip_print_credential(int indent, Credential *value)
{
    printf("%*sCredential @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sCredential Type: ", indent + 2, "");
        kmip_print_credential_type_enum(value->credential_type);
        printf("\n");
        
        kmip_print_credential_value(
            indent + 2,
            value->credential_type,
            value->credential_value);
    }
}

void
kmip_print_authentication(int indent, Authentication *value)
{
    printf("%*sAuthentication @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_credential(indent + 2, value->credential);
    }
}

void
kmip_print_request_batch_item(int indent, RequestBatchItem *value)
{
    printf("%*sRequest Batch Item @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sOperation: ", indent + 2, "");
        kmip_print_operation_enum(value->operation);
        printf("\n");

        printf("%*sEphemeral: ", indent + 2, "");
        kmip_print_bool(value->ephemeral);
        printf("\n");

        kmip_print_byte_string(
            indent + 2,
            "Unique Batch Item ID",
            value->unique_batch_item_id);
        
        kmip_print_request_payload(
            indent + 2,
            value->operation,
            value->request_payload);
    }
}

void
kmip_print_response_batch_item(int indent, ResponseBatchItem *value)
{
    printf("%*sResponse Batch Item @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        printf("%*sOperation: ", indent + 2, "");
        kmip_print_operation_enum(value->operation);
        printf("\n");
        
        kmip_print_byte_string(
            indent + 2,
            "Unique Batch Item ID",
            value->unique_batch_item_id);
        
        printf("%*sResult Status: ", indent + 2, "");
        kmip_print_result_status_enum(value->result_status);
        printf("\n");
        
        printf("%*sResult Reason: ", indent + 2, "");
        kmip_print_result_reason_enum(value->result_reason);
        printf("\n");
        
        kmip_print_text_string(indent + 2, "Result Message", value->result_message);
        kmip_print_byte_string(
            indent + 2,
            "Asynchronous Correlation Value",
            value->asynchronous_correlation_value);
        
        kmip_print_response_payload(
            indent + 2,
            value->operation,
            value->response_payload);
    }
    
    return;
}

void
kmip_print_request_header(int indent, RequestHeader *value)
{
    printf("%*sRequest Header @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_protocol_version(indent + 2, value->protocol_version);
        
        printf("%*sMaximum Response Size: ", indent + 2, "");
        kmip_print_integer(value->maximum_response_size);
        printf("\n");
        
        kmip_print_text_string(
            indent + 2,
            "Client Correlation Value",
            value->client_correlation_value);
        kmip_print_text_string(
            indent + 2,
            "Server Correlation Value",
            value->server_correlation_value);
        printf("%*sAsynchronous Indicator: ", indent + 2, "");
        kmip_print_bool(value->asynchronous_indicator);
        printf("\n");
        printf("%*sAttestation Capable Indicator: ", indent + 2, "");
        kmip_print_bool(value->attestation_capable_indicator);
        printf("\n");
        printf(
            "%*sAttestation Types: %zu\n",
            indent + 2,
            "",
            value->attestation_type_count);
        for(size_t i = 0; i < value->attestation_type_count; i++)
        {
            /* TODO (ph) Add enum value -> string functionality. */
            printf("%*sAttestation Type: %s\n", indent + 4, "", "???");
        }
        kmip_print_authentication(indent + 2, value->authentication);
        printf("%*sBatch Error Continuation Option: ", indent + 2, "");
        kmip_print_batch_error_continuation_option(
            value->batch_error_continuation_option);
        printf("\n");
        printf("%*sBatch Order Option: ", indent + 2, "");
        kmip_print_bool(value->batch_order_option);
        printf("\n");
        printf("%*sTime Stamp: %" PRIu64 "\n", indent + 2, "", value->time_stamp);
        printf("%*sBatch Count: %d\n", indent + 2, "", value->batch_count);
    }
}

void
kmip_print_response_header(int indent, ResponseHeader *value)
{
    printf("%*sResponse Header @ %p\n", indent, "", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_protocol_version(indent + 2, value->protocol_version);
        printf("%*sTime Stamp: %" PRIu64 "\n", indent + 2, "", value->time_stamp);
        kmip_print_nonce(indent + 2, value->nonce);

        kmip_print_byte_string(indent + 2, "Server Hashed Password", value->server_hashed_password);

        printf(
            "%*sAttestation Types: %zu\n",
            indent + 2,
            "",
            value->attestation_type_count);
        for(size_t i = 0; i < value->attestation_type_count; i++)
        {
            /* TODO (ph) Add enum value -> string functionality. */
            printf("%*sAttestation Type: %s\n", indent + 4, "", "???");
        }
        kmip_print_text_string(
            indent + 2,
            "Client Correlation Value",
            value->client_correlation_value);
        kmip_print_text_string(
            indent + 2,
            "Server Correlation Value",
            value->server_correlation_value);
        printf("%*sBatch Count: %d\n", indent + 2, "", value->batch_count);
    }
}

void
kmip_print_request_message(RequestMessage *value)
{
    printf("Request Message @ %p\n", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_request_header(2, value->request_header);
        printf("%*sBatch Items: %zu\n", 2, "", value->batch_count);
        
        for(size_t i = 0; i < value->batch_count; i++)
        {
            kmip_print_request_batch_item(4, &value->batch_items[i]);
        }
    }
    
    return;
}

void
kmip_print_response_message(ResponseMessage *value)
{
    printf("Response Message @ %p\n", (void *)value);
    
    if(value != NULL)
    {
        kmip_print_response_header(2, value->response_header);
        printf("  Batch Items: %zu\n", value->batch_count);
        
        for(size_t i = 0; i < value->batch_count; i++)
        {
            kmip_print_response_batch_item(4, &value->batch_items[i]);
        }
    }
    
    return;
}

/*
Freeing Functions
*/

void
kmip_free_buffer(KMIP *ctx, void *buffer, size_t size)
{
    if(ctx == NULL)
    {
        return;
    }
    
    ctx->memset_func(buffer, 0, size);
    ctx->free_func(ctx->state, buffer);
}

void
kmip_free_text_string(KMIP *ctx, TextString *value)
{
    if(ctx == NULL)
    {
        return;
    }
    
    if(value != NULL)
    {
        if(value->value != NULL)
        {
            ctx->memset_func(value->value, 0, value->size);
            ctx->free_func(ctx->state, value->value);
            
            value->value = NULL;
        }
        
        value->size = 0;
    }
    
    return;
}

void
kmip_free_byte_string(KMIP *ctx, ByteString *value)
{
    if(value != NULL)
    {
        if(value->value != NULL)
        {
            ctx->memset_func(value->value, 0, value->size);
            ctx->free_func(ctx->state, value->value);
            
            value->value = NULL;
        }
        
        value->size = 0;
    }
    
    return;
}

void
kmip_free_name(KMIP *ctx, Name *value)
{
    if(value != NULL)
    {
        if(value->value != NULL)
        {
            kmip_free_text_string(ctx, value->value);
            ctx->free_func(ctx->state, value->value);
            
            value->value = NULL;
        }
        
        value->type = 0;
    }
    
    return;
}

void
kmip_free_protection_storage_masks(KMIP *ctx, ProtectionStorageMasks *value)
{
    if(value != NULL)
    {
        if(value->masks != NULL)
        {
            LinkedListItem *curr = kmip_linked_list_pop(value->masks);
            while(curr != NULL)
            {
                ctx->free_func(ctx->state, curr->data);
                curr->data = NULL;
                ctx->free_func(ctx->state, curr);
                curr = kmip_linked_list_pop(value->masks);
            }
            ctx->free_func(ctx->state, value->masks);
            value->masks = NULL;
        }
    }

    return;
}

void
kmip_free_digest(KMIP *ctx, Digest *value)
{
    if(value != NULL)
    {
        if(value->digest_value != NULL)
        {
            kmip_free_byte_string(ctx, value->digest_value);
            value->digest_value = NULL;
        }
	value->hashing_algorithm = 0;
	value->key_format_type = 0;
    }

    return;
}

void
kmip_free_attribute(KMIP *ctx, Attribute *value)
{
    if(value != NULL)
    {
        if(value->value != NULL)
        {
            switch(value->type)
            {
                case KMIP_ATTR_UNIQUE_IDENTIFIER:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_NAME:
                kmip_free_name(ctx, value->value);
                break;

                case KMIP_ATTR_OBJECT_TYPE:
                *(int32*)value->value = 0;
                break;

                case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
                *(int32*)value->value = 0;
                break;

                case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
                *(int32 *)value->value = KMIP_UNSET;
                break;

                // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:	XXX how to hack struct?
                // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:	XXX how to hack struct?

                case KMIP_ATTR_CERTIFICATE_TYPE:
                *(int32*)value->value = 0;
                break;

                case KMIP_ATTR_CERTIFICATE_LENGTH:
                *(int32 *)value->value = 0;
                break;

                // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
                // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:	XXX how to hack struct?
                // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:	XXX how to hack struct?
                // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
                // case KMIP_ATTR_CERTIFICATE_SUBJECT:	XXX how to hack struct?
                // case KMIP_ATTR_CERTIFICATE_ISSUER:	XXX how to hack struct?

                case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
                *(int32*)value->value = 0;
                break;

                case KMIP_ATTR_DIGEST:
                kmip_free_digest(ctx, value->value);
                break;

                case KMIP_ATTR_OPERATION_POLICY_NAME:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
                *(int32 *)value->value = KMIP_UNSET;
                break;

                case KMIP_ATTR_LEASE_TIME:
                *(uint32 *)value->value = 0;
                break;

                // case KMIP_ATTR_USAGE_LIMITS:	XXX how to hack struct?

                case KMIP_ATTR_STATE:
                *(uint32*)value->value = 0;
                break;

                case KMIP_ATTR_INITIAL_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_ACTIVATION_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_PROCESS_START_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_PROTECT_STOP_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_DEACTIVATION_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_DESTROY_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_COMPROMISE_DATE:
                *(int64*)value->value = 0;
                break;

                // case KMIP_ATTR_REVOCATION_REASON:	XXX how to hack struct?

                case KMIP_ATTR_ARCHIVE_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_OBJECT_GROUP:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_FRESH:
                *(bool32 *)value->value = 0;
                break;

                // case KMIP_ATTR_LINK:	XXX how to hack struct?
                // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:	XXX how to hack struct?
                // case KMIP_ATTR_CONTACT_INFORMATION:	XXX how to hack struct?

                case KMIP_ATTR_LAST_CHANGE_DATE:
                *(int64*)value->value = 0;
                break;

                // case KMIP_ATTR_CUSTOM_ATTRIBUTE:	XXX how to hack custom?
                // case KMIP_ATTR_ALTERNATIVE_NAME:	XXX how to hack struct?

                case KMIP_ATTR_KEY_VALUE_PRESENT:
                *(bool32 *)value->value = 0;
                break;

                // case KMIP_ATTR_KEY_VALUE_LOCATION:	XXX how to hack struct?

                case KMIP_ATTR_ORIGINAL_CREATION_DATE:
                *(int64*)value->value = 0;
                break;

                case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_DESCRIPTION:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_COMMENT:
                kmip_free_text_string(ctx, value->value);
                break;

                case KMIP_ATTR_SENSITIVE:
                *(bool32 *)value->value = 0;
                break;

                case KMIP_ATTR_ALWAYS_SENSITIVE:
                *(bool32 *)value->value = 0;
                break;

                case KMIP_ATTR_EXTRACTABLE:
                *(bool32 *)value->value = 0;
                break;

                case KMIP_ATTR_NEVER_EXTRACTABLE:
                *(bool32 *)value->value = 0;
                break;

                case KMIP_ATTR_KEY_FORMAT_TYPE:
                *(int32*)value->value = 0;
                break;

                default:
                /* NOTE (ph) Hitting this case means that we don't know what the */
                /*      actual type, size, or value of value->value is. We can   */
                /*      still free it but we cannot securely zero the memory. We */
                /*      also do not know how to free any possible substructures  */
                /*      pointed to within value->value.                          */
                /*                                                               */
                /*      Avoid hitting this case at all costs.                    */
                break;
            };
            
            ctx->free_func(ctx->state, value->value);
            value->value = NULL;
        }
        
        value->type = 0;
        value->index = KMIP_UNSET;
    }
    
    return;
}

void
kmip_free_attributes(KMIP *ctx, Attributes *value)
{
    if(value != NULL)
    {
        if(value->attribute_list != NULL)
        {
            LinkedListItem *curr = kmip_linked_list_pop(value->attribute_list);
            while(curr != NULL)
            {
                Attribute *attribute = (Attribute *)curr->data;
                kmip_free_attribute(ctx, attribute);
                ctx->free_func(ctx->state, attribute);
                ctx->free_func(ctx->state, curr);
                curr = kmip_linked_list_pop(value->attribute_list);
            }
            ctx->free_func(ctx->state, value->attribute_list);

            value->attribute_list = NULL;
        }
    }

    return;
}

void
kmip_free_attributes_2(KMIP *ctx, Attribute *value, int count)
{
    if(value != NULL)
    {
	for(int i = 0; i < count; i++)
	{
	    kmip_free_attribute(ctx, &value[i]);
	}
	ctx->free_func(ctx->state, value);
    }

    return;
}

void
kmip_free_template_attribute(KMIP *ctx, TemplateAttribute *value)
{
    if(value != NULL)
    {
        if(value->names != NULL)
        {
            for(size_t i = 0; i < value->name_count; i++)
            {
                kmip_free_name(ctx, &value->names[i]);
            }
            ctx->free_func(ctx->state, value->names);
            
            value->names = NULL;
        }
        
        value->name_count = 0;
        
        if(value->attributes != NULL)
        {
            for(size_t i = 0; i < value->attribute_count; i++)
            {
                kmip_free_attribute(ctx, &value->attributes[i]);
            }
            ctx->free_func(ctx->state, value->attributes);
            
            value->attributes = NULL;
        }
        
        value->attribute_count = 0;
    }
    
    return;
}

void
kmip_free_transparent_symmetric_key(KMIP *ctx, TransparentSymmetricKey *value)
{
    if(value != NULL)
    {
        if(value->key != NULL)
        {
            kmip_free_byte_string(ctx, value->key);
            
            ctx->free_func(ctx->state, value->key);
            value->key = NULL;
        }
    }
    
    return;
}

void
kmip_free_key_material(KMIP *ctx, enum key_format_type format, void **value)
{
    if(value != NULL)
    {
        if(*value != NULL)
        {
            switch(format)
            {
                case KMIP_KEYFORMAT_RAW:
                case KMIP_KEYFORMAT_OPAQUE:
                case KMIP_KEYFORMAT_PKCS1:
                case KMIP_KEYFORMAT_PKCS8:
                case KMIP_KEYFORMAT_X509:
                case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
                kmip_free_byte_string(ctx, *value);
                break;
                
                case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
                kmip_free_transparent_symmetric_key(ctx, *value);
                break;
                
                default:
                /* NOTE (ph) Hitting this case means that we don't know   */
                /*      what the actual type, size, or value of value is. */
                /*      We can still free it but we cannot securely zero  */
                /*      the memory. We also do not know how to free any   */
                /*      possible substructures pointed to within value.   */
                /*                                                        */
                /*      Avoid hitting this case at all costs.             */
                break;
            };
            
            ctx->free_func(ctx->state, *value);
            *value = NULL;
        }
    }
    
    return;
}

void
kmip_free_key_value(KMIP *ctx, enum key_format_type format, KeyValue *value)
{
    if(value != NULL)
    {
        if(value->key_material != NULL)
        {
            kmip_free_key_material(ctx, format, &value->key_material);
            value->key_material = NULL;
        }
        
        if(value->attributes != NULL)
        {
            for(size_t i = 0; i < value->attribute_count; i++)
            {
                kmip_free_attribute(ctx, &value->attributes[i]);
            }
            ctx->free_func(ctx->state, value->attributes);
            
            value->attributes = NULL;
        }
        
        value->attribute_count = 0;
    }
    
    return;
}

void
kmip_free_cryptographic_parameters(KMIP *ctx, CryptographicParameters *value)
{
    if(value != NULL)
    {
        if(value->p_source != NULL)
        {
            kmip_free_byte_string(ctx, value->p_source);
            
            ctx->free_func(ctx->state, value->p_source);
            value->p_source = NULL;
        }
        
        kmip_init_cryptographic_parameters(value);
    }
    
    return;
}

void
kmip_free_encryption_key_information(KMIP *ctx, EncryptionKeyInformation *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
        
        if(value->cryptographic_parameters != NULL)
        {
            kmip_free_cryptographic_parameters(ctx, value->cryptographic_parameters);
            
            ctx->free_func(ctx->state, value->cryptographic_parameters);
            value->cryptographic_parameters = NULL;
        }
    }
    
    return;
}

void
kmip_free_mac_signature_key_information(KMIP *ctx, MACSignatureKeyInformation *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
        
        if(value->cryptographic_parameters != NULL)
        {
            kmip_free_cryptographic_parameters(ctx, value->cryptographic_parameters);
            
            ctx->free_func(ctx->state, value->cryptographic_parameters);
            value->cryptographic_parameters = NULL;
        }
    }
    
    return;
}

void
kmip_free_key_wrapping_data(KMIP *ctx, KeyWrappingData *value)
{
    if(value != NULL)
    {
        if(value->encryption_key_info != NULL)
        {
            kmip_free_encryption_key_information(ctx, value->encryption_key_info);
            
            ctx->free_func(ctx->state, value->encryption_key_info);
            value->encryption_key_info = NULL;
        }
        
        if(value->mac_signature_key_info != NULL)
        {
            kmip_free_mac_signature_key_information(ctx, value->mac_signature_key_info);
            
            ctx->free_func(ctx->state, value->mac_signature_key_info);
            value->mac_signature_key_info = NULL;
        }
        
        if(value->mac_signature != NULL)
        {
            kmip_free_byte_string(ctx, value->mac_signature);
            
            ctx->free_func(ctx->state, value->mac_signature);
            value->mac_signature = NULL;
        }
        
        if(value->iv_counter_nonce != NULL)
        {
            kmip_free_byte_string(ctx, value->iv_counter_nonce);
            
            ctx->free_func(ctx->state, value->iv_counter_nonce);
            value->iv_counter_nonce = NULL;
        }
        
        value->wrapping_method = 0;
        value->encoding_option = 0;
    }
    
    return;
}

void
kmip_free_key_block(KMIP *ctx, KeyBlock *value)
{
    if(value != NULL)
    {
        if(value->key_value != NULL)
        {
            if(value->key_value_type == KMIP_TYPE_BYTE_STRING)
            {
                kmip_free_byte_string(ctx, value->key_value);
                ctx->free_func(ctx->state, value->key_value);
            }
            else
            {
                kmip_free_key_value(ctx, value->key_format_type, value->key_value);
                ctx->free_func(ctx->state, value->key_value);
            }
            value->key_value = NULL;
        }
        
        if(value->key_wrapping_data != NULL)
        {
            kmip_free_key_wrapping_data(ctx, value->key_wrapping_data);
            ctx->free_func(ctx->state, value->key_wrapping_data);
            value->key_wrapping_data = NULL;
        }
        
        kmip_init_key_block(value);
    }
    
    return;
}

void
kmip_free_symmetric_key(KMIP *ctx, SymmetricKey *value)
{
    if(value != NULL)
    {
        if(value->key_block != NULL)
        {
            kmip_free_key_block(ctx, value->key_block);
            ctx->free_func(ctx->state, value->key_block);
            value->key_block = NULL;
        }
    }
    
    return;
}

void
kmip_free_public_key(KMIP *ctx, PublicKey *value)
{
    if(value != NULL)
    {
        if(value->key_block != NULL)
        {
            kmip_free_key_block(ctx, value->key_block);
            ctx->free_func(ctx->state, value->key_block);
            value->key_block = NULL;
        }
    }
    
    return;
}

void
kmip_free_private_key(KMIP *ctx, PrivateKey *value)
{
    if(value != NULL)
    {
        if(value->key_block != NULL)
        {
            kmip_free_key_block(ctx, value->key_block);
            ctx->free_func(ctx->state, value->key_block);
            value->key_block = NULL;
        }
    }
    
    return;
}

void
kmip_free_key_wrapping_specification(KMIP *ctx, KeyWrappingSpecification *value)
{
    if(value != NULL)
    {
        if(value->encryption_key_info != NULL)
        {
            kmip_free_encryption_key_information(ctx, value->encryption_key_info);
            ctx->free_func(ctx->state, value->encryption_key_info);
            value->encryption_key_info = NULL;
        }
        
        if(value->mac_signature_key_info != NULL)
        {
            kmip_free_mac_signature_key_information(ctx, value->mac_signature_key_info);
            ctx->free_func(ctx->state, value->mac_signature_key_info);
            value->mac_signature_key_info = NULL;
        }
        
        if(value->attribute_names != NULL)
        {
            for(size_t i = 0; i < value->attribute_name_count; i++)
            {
                kmip_free_text_string(ctx, &value->attribute_names[i]);
            }
            ctx->free_func(ctx->state, value->attribute_names);
            value->attribute_names = NULL;
        }
        value->attribute_name_count = 0;
        
        value->wrapping_method = 0;
        value->encoding_option = 0;
    }
    
    return;
}

void
kmip_free_create_request_payload(KMIP *ctx, CreateRequestPayload *value)
{
    if(value != NULL)
    {
        if(value->template_attribute != NULL)
        {
            kmip_free_template_attribute(ctx, value->template_attribute);
            ctx->free_func(ctx->state, value->template_attribute);
            value->template_attribute = NULL;
        }

        if(value->attributes != NULL)
        {
            kmip_free_attributes(ctx, value->attributes);
            ctx->free_func(ctx->state, value->attributes);
            value->attributes = NULL;
        }

        if(value->protection_storage_masks != NULL)
        {
            kmip_free_protection_storage_masks(ctx, value->protection_storage_masks);
            ctx->free_func(ctx->state, value->protection_storage_masks);
            value->protection_storage_masks = NULL;
        }
        
        value->object_type = 0;
    }
    
    return;
}

void
kmip_free_create_response_payload(KMIP *ctx, CreateResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
        
        if(value->template_attribute != NULL)
        {
            kmip_free_template_attribute(ctx, value->template_attribute);
            ctx->free_func(ctx->state, value->template_attribute);
            value->template_attribute = NULL;
        }
        
        value->object_type = 0;
    }
    
    return;
}

void
kmip_free_locate_request_payload(KMIP *ctx, LocateRequestPayload *value)
{
    if(value != NULL)
    {
	kmip_free_attributes_2(ctx, value->attributes, value->attribute_count);
	memset(value, 0, sizeof *value);
    }
    
    return;
}

void
kmip_free_locate_response_payload(KMIP *ctx, LocateResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifiers != NULL)
        {
            for(int i = 0; i < value->unique_identifiers_count; i++)
            {
                kmip_free_text_string(ctx, &value->unique_identifiers[i]);
            }
            ctx->free_func(ctx->state, value->unique_identifiers);
        }
	memset(value, 0, sizeof *value);
    }
    
    return;
}

void
kmip_free_get_request_payload(KMIP *ctx, GetRequestPayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
        
        if(value->key_wrapping_spec != NULL)
        {
            kmip_free_key_wrapping_specification(ctx, value->key_wrapping_spec);
            ctx->free_func(ctx->state, value->key_wrapping_spec);
            value->key_wrapping_spec = NULL;
        }
        
        value->key_format_type = 0;
        value->key_compression_type = 0;
        value->key_wrap_type = 0;
    }
    
    return;
}

void
kmip_free_get_response_payload(KMIP *ctx, GetResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
        
        if(value->object != NULL)
        {
            switch(value->object_type)
            {
                case KMIP_OBJTYPE_SYMMETRIC_KEY:
                kmip_free_symmetric_key(ctx, (SymmetricKey *)value->object);
                break;
                
                case KMIP_OBJTYPE_PUBLIC_KEY:
                kmip_free_public_key(ctx, (PublicKey *)value->object);
                break;
                
                case KMIP_OBJTYPE_PRIVATE_KEY:
                kmip_free_private_key(ctx, (PrivateKey *)value->object);
                break;
                
                default:
                /* NOTE (ph) Hitting this case means that we don't know */
                /*      what the actual type, size, or value of         */
                /*      value->object is. We can still free it but we   */
                /*      cannot securely zero the memory. We also do not */
                /*      know how to free any possible substructures     */
                /*      pointed to within value->object.                */
                /*                                                      */
                /*      Avoid hitting this case at all costs.           */
                break;
            };
            
            ctx->free_func(ctx->state, value->object);
            value->object = NULL;
        }
        
        value->object_type = 0;
    }
    
    return;
}

void
kmip_free_get_attributes_request_payload(KMIP *ctx, GetAttributesRequestPayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }

        if(value->attribute_names != NULL)
        {
            ctx->free_func(ctx->state, value->attribute_names);
            value->attribute_names = NULL;
        }
    }
    
    return;
}

void
kmip_free_get_attributes_response_payload(KMIP *ctx, GetAttributesResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
	kmip_free_attributes_2(ctx, value->attributes, value->attribute_count);
    }
    
    return;
}

void
kmip_free_get_attribute_list_request_payload(KMIP *ctx, GetAttributeListRequestPayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
    }
    
    return;
}

void
kmip_free_get_attribute_list_response_payload(KMIP *ctx, GetAttributeListResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }

        if(value->attribute_names != NULL)
        {
            ctx->free_func(ctx->state, value->attribute_names);
            value->attribute_names = NULL;
        }
    }
    
    return;
}

void
kmip_free_destroy_request_payload(KMIP *ctx, DestroyRequestPayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
    }
    
    return;
}

void
kmip_free_destroy_response_payload(KMIP *ctx, DestroyResponsePayload *value)
{
    if(value != NULL)
    {
        if(value->unique_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->unique_identifier);
            ctx->free_func(ctx->state, value->unique_identifier);
            value->unique_identifier = NULL;
        }
    }
    
    return;
}

void
kmip_free_request_batch_item(KMIP *ctx, RequestBatchItem *value)
{
    if(value != NULL)
    {
        if(value->unique_batch_item_id != NULL)
        {
            kmip_free_byte_string(ctx, value->unique_batch_item_id);
            ctx->free_func(ctx->state, value->unique_batch_item_id);
            value->unique_batch_item_id = NULL;
        }
        
        if(value->request_payload != NULL)
        {
            switch(value->operation)
            {
                case KMIP_OP_CREATE:
                kmip_free_create_request_payload(ctx, (CreateRequestPayload *)value->request_payload);
                break;
                
                case KMIP_OP_LOCATE:
                kmip_free_locate_request_payload(ctx, (LocateRequestPayload *)value->request_payload);
                break;
                
                case KMIP_OP_GET:
                kmip_free_get_request_payload(ctx, (GetRequestPayload *)value->request_payload);
                break;
                
                case KMIP_OP_GET_ATTRIBUTES:
                kmip_free_get_attributes_request_payload(ctx, (GetAttributesRequestPayload *)value->request_payload);
                break;
                
                case KMIP_OP_GET_ATTRIBUTE_LIST:
                kmip_free_get_attribute_list_request_payload(ctx, (GetAttributeListRequestPayload *)value->request_payload);
                break;
                
                case KMIP_OP_DESTROY:
                kmip_free_destroy_request_payload(ctx, (DestroyRequestPayload *)value->request_payload);
                break;
                
                default:
                /* NOTE (ph) Hitting this case means that we don't know    */
                /*      what the actual type, size, or value of            */
                /*      value->request_payload is. We can still free it    */
                /*      but we cannot securely zero the memory. We also    */
                /*      do not know how to free any possible substructures */
                /*      pointed to within value->request_payload.          */
                /*                                                         */
                /*      Avoid hitting this case at all costs.              */
                break;
            };
            
            ctx->free_func(ctx->state, value->request_payload);
            value->request_payload = NULL;
        }
        
        value->operation = 0;
        value->ephemeral = 0;
    }
    
    return;
}

void
kmip_free_response_batch_item(KMIP *ctx, ResponseBatchItem *value)
{
    if(value != NULL)
    {
        if(value->unique_batch_item_id != NULL)
        {
            kmip_free_byte_string(ctx, value->unique_batch_item_id);
            ctx->free_func(ctx->state, value->unique_batch_item_id);
            value->unique_batch_item_id = NULL;
        }
        
        if(value->result_message != NULL)
        {
            kmip_free_text_string(ctx, value->result_message);
            ctx->free_func(ctx->state, value->result_message);
            value->result_message = NULL;
        }
        
        if(value->asynchronous_correlation_value != NULL)
        {
            kmip_free_byte_string(ctx, value->asynchronous_correlation_value);
            ctx->free_func(ctx->state, value->asynchronous_correlation_value);
            value->asynchronous_correlation_value = NULL;
        }
        
        if(value->response_payload != NULL)
        {
            switch(value->operation)
            {
                case KMIP_OP_CREATE:
                kmip_free_create_response_payload(ctx, (CreateResponsePayload *)value->response_payload);
                break;
                
                case KMIP_OP_LOCATE:
                kmip_free_locate_response_payload(ctx, (LocateResponsePayload *)value->response_payload);
                break;
                
                case KMIP_OP_GET:
                kmip_free_get_response_payload(ctx, (GetResponsePayload *)value->response_payload);
                break;
                
                case KMIP_OP_GET_ATTRIBUTES:
                kmip_free_get_attributes_response_payload(ctx, (GetAttributesResponsePayload *)value->response_payload);
                break;
                
                case KMIP_OP_GET_ATTRIBUTE_LIST:
                kmip_free_get_attribute_list_response_payload(ctx, (GetAttributeListResponsePayload *)value->response_payload);
                break;
                
                case KMIP_OP_DESTROY:
                kmip_free_destroy_response_payload(ctx, (DestroyResponsePayload *)value->response_payload);
                break;
                
                default:
                /* NOTE (ph) Hitting this case means that we don't know    */
                /*      what the actual type, size, or value of            */
                /*      value->response_payload is. We can still free it   */
                /*      but we cannot securely zero the memory. We also    */
                /*      do not know how to free any possible substructures */
                /*      pointed to within value->response_payload.         */
                /*                                                         */
                /*      Avoid hitting this case at all costs.              */
                break;
            };
            
            ctx->free_func(ctx->state, value->response_payload);
            value->response_payload = NULL;
        }
        
        value->operation = 0;
        value->result_status = 0;
        value->result_reason = 0;
    }
    
    return;
}

void
kmip_free_nonce(KMIP *ctx, Nonce *value)
{
    if(value != NULL)
    {
        if(value->nonce_id != NULL)
        {
            kmip_free_byte_string(ctx, value->nonce_id);
            ctx->free_func(ctx->state, value->nonce_id);
            value->nonce_id = NULL;
        }
        
        if(value->nonce_value != NULL)
        {
            kmip_free_byte_string(ctx, value->nonce_value);
            ctx->free_func(ctx->state, value->nonce_value);
            value->nonce_value = NULL;
        }
    }
    
    return;
}

void
kmip_free_username_password_credential(KMIP *ctx, UsernamePasswordCredential *value)
{
    if(value != NULL)
    {
        if(value->username != NULL)
        {
            kmip_free_text_string(ctx, value->username);
            ctx->free_func(ctx->state, value->username);
            value->username = NULL;
        }
        
        if(value->password != NULL)
        {
            kmip_free_text_string(ctx, value->password);
            ctx->free_func(ctx->state, value->password);
            value->password = NULL;
        }
    }
    
    return;
}

void
kmip_free_device_credential(KMIP *ctx, DeviceCredential *value)
{
    if(value != NULL)
    {
        if(value->device_serial_number != NULL)
        {
            kmip_free_text_string(ctx, value->device_serial_number);
            ctx->free_func(ctx->state, value->device_serial_number);
            value->device_serial_number = NULL;
        }
        
        if(value->password != NULL)
        {
            kmip_free_text_string(ctx, value->password);
            ctx->free_func(ctx->state, value->password);
            value->password = NULL;
        }
        
        if(value->device_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->device_identifier);
            ctx->free_func(ctx->state, value->device_identifier);
            value->device_identifier = NULL;
        }
        
        if(value->network_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->network_identifier);
            ctx->free_func(ctx->state, value->network_identifier);
            value->network_identifier = NULL;
        }
        
        if(value->machine_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->machine_identifier);
            ctx->free_func(ctx->state, value->machine_identifier);
            value->machine_identifier = NULL;
        }
        
        if(value->media_identifier != NULL)
        {
            kmip_free_text_string(ctx, value->media_identifier);
            ctx->free_func(ctx->state, value->media_identifier);
            value->media_identifier = NULL;
        }
    }
    
    return;
}

void
kmip_free_attestation_credential(KMIP *ctx, AttestationCredential *value)
{
    if(value != NULL)
    {
        if(value->nonce != NULL)
        {
            kmip_free_nonce(ctx, value->nonce);
            ctx->free_func(ctx->state, value->nonce);
            value->nonce = NULL;
        }
        
        if(value->attestation_measurement != NULL)
        {
            kmip_free_byte_string(ctx, value->attestation_measurement);
            ctx->free_func(ctx->state, value->attestation_measurement);
            value->attestation_measurement = NULL;
        }
        
        if(value->attestation_assertion != NULL)
        {
            kmip_free_byte_string(ctx, value->attestation_assertion);
            ctx->free_func(ctx->state, value->attestation_assertion);
            value->attestation_assertion = NULL;
        }
        
        value->attestation_type = 0;
    }
    
    return;
}

void
kmip_free_credential_value(KMIP *ctx, enum credential_type type, void **value)
{
    if(value != NULL)
    {
        if(*value != NULL)
        {
            switch(type)
            {
                case KMIP_CRED_USERNAME_AND_PASSWORD:
                kmip_free_username_password_credential(ctx, (UsernamePasswordCredential *)*value);
                break;
                
                case KMIP_CRED_DEVICE:
                kmip_free_device_credential(ctx, (DeviceCredential *)*value);
                break;
                
                case KMIP_CRED_ATTESTATION:
                kmip_free_attestation_credential(ctx, (AttestationCredential *)*value);
                break;
                
                default:
                /* NOTE (ph) Hitting this case means that we don't know   */
                /*      what the actual type, size, or value of value is. */
                /*      We can still free it but we cannot securely zero  */
                /*      the memory. We also do not know how to free any   */
                /*      possible substructures pointed to within value.   */
                /*                                                        */
                /*      Avoid hitting this case at all costs.             */
                break;
            };
        
            ctx->free_func(ctx->state, *value);
            *value = NULL;
        }    
    }
    
    return;
}

void
kmip_free_credential(KMIP *ctx, Credential *value)
{
    if(value != NULL)
    {
        if(value->credential_value != NULL)
        {
            kmip_free_credential_value(ctx, value->credential_type, &value->credential_value);
            value->credential_value = NULL;
        }
        
        value->credential_type = 0;
    }
    
    return;
}

void
kmip_free_authentication(KMIP *ctx, Authentication *value)
{
    if(value != NULL)
    {
        if(value->credential != NULL)
        {
            kmip_free_credential(ctx, value->credential);
            ctx->free_func(ctx->state, value->credential);
            value->credential = NULL;
        }
    }
    
    return;
}

void
kmip_free_request_header(KMIP *ctx, RequestHeader *value)
{
    if(value != NULL)
    {
        if(value->protocol_version != NULL)
        {
            ctx->memset_func(
                value->protocol_version,
                0,
                sizeof(ProtocolVersion));
            ctx->free_func(ctx->state, value->protocol_version);
            value->protocol_version = NULL;
        }
        
        if(value->authentication != NULL)
        {
            kmip_free_authentication(ctx, value->authentication);
            ctx->free_func(ctx->state, value->authentication);
            value->authentication = NULL;
        }
        
        if(value->attestation_types != NULL)
        {
            ctx->memset_func(
                value->attestation_types,
                0,
                value->attestation_type_count * sizeof(enum attestation_type));
            ctx->free_func(ctx->state, value->attestation_types);
            value->attestation_types = NULL;
            value->attestation_type_count = 0;
        }
        
        if(value->client_correlation_value != NULL)
        {
            kmip_free_text_string(ctx, value->client_correlation_value);
            ctx->free_func(ctx->state, value->client_correlation_value);
            value->client_correlation_value = NULL;
        }
        
        if(value->server_correlation_value != NULL)
        {
            kmip_free_text_string(ctx, value->server_correlation_value);
            ctx->free_func(ctx->state, value->server_correlation_value);
            value->server_correlation_value = NULL;
        }
        
        kmip_init_request_header(value);
    }
    
    return;
}

void
kmip_free_response_header(KMIP *ctx, ResponseHeader *value)
{
    if(value != NULL)
    {
        if(value->protocol_version != NULL)
        {
            ctx->memset_func(
                value->protocol_version,
                0,
                sizeof(ProtocolVersion));
            ctx->free_func(ctx->state, value->protocol_version);
            value->protocol_version = NULL;
        }
        
        if(value->nonce != NULL)
        {
            kmip_free_nonce(ctx, value->nonce);
            ctx->free_func(ctx->state, value->nonce);
            value->nonce = NULL;
        }

        if(value->server_hashed_password != NULL)
        {
            kmip_free_byte_string(ctx, value->server_hashed_password);
            ctx->free_func(ctx->state, value->server_hashed_password);
            value->server_hashed_password = NULL;
        }

        if(value->attestation_types != NULL)
        {
            ctx->memset_func(
                value->attestation_types,
                0,
                value->attestation_type_count * sizeof(enum attestation_type));
            ctx->free_func(ctx->state, value->attestation_types);
            value->attestation_types = NULL;
        }
        
        value->attestation_type_count = 0;
        
        if(value->client_correlation_value != NULL)
        {
            kmip_free_text_string(ctx, value->client_correlation_value);
            ctx->free_func(ctx->state, value->client_correlation_value);
            value->client_correlation_value = NULL;
        }
        
        if(value->server_correlation_value != NULL)
        {
            kmip_free_text_string(ctx, value->server_correlation_value);
            ctx->free_func(ctx->state, value->server_correlation_value);
            value->server_correlation_value = NULL;
        }
        
        kmip_init_response_header(value);
    }
    
    return;
}

void
kmip_free_request_message(KMIP *ctx, RequestMessage *value)
{
    if(value != NULL)
    {
        if(value->request_header != NULL)
        {
            kmip_free_request_header(ctx, value->request_header);
            ctx->free_func(ctx->state, value->request_header);
            value->request_header = NULL;
        }
        
        if(value->batch_items != NULL)
        {
            for(size_t i = 0; i < value->batch_count; i++)
            {
                kmip_free_request_batch_item(ctx, &value->batch_items[i]);
            }
            ctx->free_func(ctx, value->batch_items);
            value->batch_items = NULL;
        }
        
        value->batch_count = 0;
    }
    
    return;
}

void
kmip_free_response_message(KMIP *ctx, ResponseMessage *value)
{
    if(value != NULL)
    {
        if(value->response_header != NULL)
        {
            kmip_free_response_header(ctx, value->response_header);
            ctx->free_func(ctx->state, value->response_header);
            value->response_header = NULL;
        }
        
        if(value->batch_items != NULL)
        {
            for(size_t i = 0; i < value->batch_count; i++)
            {
                kmip_free_response_batch_item(ctx, &value->batch_items[i]);
            }
            ctx->free_func(ctx, value->batch_items);
            value->batch_items = NULL;
        }
        
        value->batch_count = 0;
    }
    
    return;
}

/*
Copying Functions
*/

int32 *
kmip_deep_copy_int32(KMIP *ctx, const int32 *value)
{
    if(ctx == NULL || value == NULL)
        return(NULL);

    int32 *copy = ctx->calloc_func(ctx, 1, sizeof(int32));
    if(copy == NULL)
        return(NULL);

    copy = ctx->memcpy_func(ctx->state, copy, value, sizeof(int32));

    return(copy);
}

int64 *
kmip_deep_copy_int64(KMIP *ctx, const int64 *value)
{
    if(ctx == NULL || value == NULL)
        return(NULL);

    int64 *copy = ctx->calloc_func(ctx, 1, sizeof(int64));
    if(copy == NULL)
        return(NULL);

    copy = ctx->memcpy_func(ctx->state, copy, value, sizeof(int64));

    return(copy);
}

TextString *
kmip_deep_copy_text_string(KMIP *ctx, const TextString *value)
{
    if(ctx == NULL || value == NULL)
        return(NULL);

    TextString *copy = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    if(copy == NULL)
        return(NULL);

    copy->size = value->size;
    if(value->value != NULL)
    {
        copy->value = ctx->calloc_func(ctx->state, 1, value->size);
        if(copy->value == NULL && value->value != NULL)
        {
            ctx->free_func(ctx->state, copy);
            return(NULL);
        }
        copy->value = ctx->memcpy_func(ctx->state, copy->value, value->value, value->size);
    }
    else
        copy->value = NULL;

    return(copy);
}

Name *
kmip_deep_copy_name(KMIP *ctx, const Name *value)
{
    if(ctx == NULL || value == NULL)
        return(NULL);

    Name *copy = ctx->calloc_func(ctx->state, 1, sizeof(Name));
    if(copy == NULL)
        return(NULL);

    copy->type = value->type;
    if(value->value != NULL)
    {
        copy->value = kmip_deep_copy_text_string(ctx, value->value);
        if(copy->value == NULL)
        {
            ctx->free_func(ctx->state, copy);
            return(NULL);
        }
    }
    else
        copy->value = NULL;

    return(copy);
}

Attribute *
kmip_deep_copy_attribute(KMIP *ctx, const Attribute *value)
{
    if(ctx == NULL || value == NULL)
        return(NULL);

    Attribute *copy = ctx->calloc_func(ctx->state, 1, sizeof(Attribute));
    if(copy == NULL)
        return(NULL);

    copy->type = value->type;
    copy->index = value->index;

    if(value->value == NULL)
    {
        copy->value = NULL;
        return(copy);
    }

    switch(value->type)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        case KMIP_ATTR_OPERATION_POLICY_NAME:
        case KMIP_ATTR_OBJECT_GROUP:
        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        case KMIP_ATTR_DESCRIPTION:
        case KMIP_ATTR_COMMENT:
        {
            copy->value = kmip_deep_copy_text_string(ctx, (TextString *)value->value);
            if(copy->value == NULL)
            {
                ctx->free_func(ctx->state, copy);
                return(NULL);
            }
        } break;

        case KMIP_ATTR_NAME:
        {
            copy->value = kmip_deep_copy_name(ctx, (Name *)value->value);
            if(copy->value == NULL)
            {
                ctx->free_func(ctx->state, copy);
                return(NULL);
            }
        } break;

        case KMIP_ATTR_OBJECT_TYPE:
        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        case KMIP_ATTR_CERTIFICATE_TYPE:
        case KMIP_ATTR_CERTIFICATE_LENGTH:
        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        case KMIP_ATTR_LEASE_TIME:
        case KMIP_ATTR_STATE:
        case KMIP_ATTR_FRESH:
        case KMIP_ATTR_KEY_VALUE_PRESENT:
        case KMIP_ATTR_SENSITIVE:
        case KMIP_ATTR_ALWAYS_SENSITIVE:
        case KMIP_ATTR_EXTRACTABLE:
        case KMIP_ATTR_NEVER_EXTRACTABLE:
        case KMIP_ATTR_KEY_FORMAT_TYPE:
        {
            copy->value = kmip_deep_copy_int32(ctx, (int32 *)value->value);
            if(copy->value == NULL)
            {
                ctx->free_func(ctx->state, copy);
                return(NULL);
            }
        } break;

        case KMIP_ATTR_INITIAL_DATE:
        case KMIP_ATTR_ACTIVATION_DATE:
        case KMIP_ATTR_PROCESS_START_DATE:
        case KMIP_ATTR_PROTECT_STOP_DATE:
        case KMIP_ATTR_DEACTIVATION_DATE:
        case KMIP_ATTR_DESTROY_DATE:
        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        case KMIP_ATTR_COMPROMISE_DATE:
        case KMIP_ATTR_ARCHIVE_DATE:
        case KMIP_ATTR_LAST_CHANGE_DATE:
        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        {
            copy->value = kmip_deep_copy_int64(ctx, (int64 *)value->value);
            if(copy->value == NULL)
            {
                ctx->free_func(ctx->state, copy);
                return(NULL);
            }
        } break;

        // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:
        // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:
        // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:
        // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:
        // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:
        // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:
        // case KMIP_ATTR_CERTIFICATE_SUBJECT:
        // case KMIP_ATTR_CERTIFICATE_ISSUER:
        // case KMIP_ATTR_DIGEST:
        // case KMIP_ATTR_USAGE_LIMITS:
        // case KMIP_ATTR_REVOCATION_REASON:
        // case KMIP_ATTR_LINK:
        // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:
        // case KMIP_ATTR_CONTACT_INFORMATION:
        // case KMIP_ATTR_CUSTOM_ATTRIBUTE:
        // case KMIP_ATTR_ALTERNATIVE_NAME:
        // case KMIP_ATTR_KEY_VALUE_LOCATION:

        default:
        {
            ctx->free_func(ctx->state, copy);
            return(NULL);
        } break;
    };

    return(copy);
}

/*
Comparison Functions
*/

int
kmip_compare_text_string(const TextString *a, const TextString *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->size != b->size)
        {
            return(KMIP_FALSE);
        }
        
        if(a->value != b->value)
        {
            if((a->value == NULL) || (b->value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->size; i++)
            {
                if(a->value[i] != b->value[i])
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_byte_string(const ByteString *a, const ByteString *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->size != b->size)
        {
            return(KMIP_FALSE);
        }
        
        if(a->value != b->value)
        {
            if((a->value == NULL) || (b->value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->size; i++)
            {
                if(a->value[i] != b->value[i])
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_name(const Name *a, const Name *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->type != b->type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->value != b->value)
        {
            if((a->value == NULL) || (b->value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->value, b->value) != KMIP_TRUE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_protection_storage_masks(const ProtectionStorageMasks *a, const ProtectionStorageMasks *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }

        if((a->masks != b->masks))
        {
            if((a->masks == NULL) || (b->masks == NULL))
            {
                return(KMIP_FALSE);
            }

            if((a->masks->size != b->masks->size))
            {
                return(KMIP_FALSE);
            }

            LinkedListItem *a_item = a->masks->head;
            LinkedListItem *b_item = b->masks->head;
            while((a_item != NULL) || (b_item != NULL))
            {
                if(a_item != b_item)
                {
                    int32 a_data = *(int32 *)a_item->data;
                    int32 b_data = *(int32 *)b_item->data;
                    if(a_data != b_data)
                    {
                        return(KMIP_FALSE);
                    }
                }

                a_item = a_item->next;
                b_item = b_item->next;
            }

            if(a_item != b_item)
            {
                return(KMIP_FALSE);
            }
        }
    }

    return(KMIP_TRUE);
}

int
kmip_compare_attribute(const Attribute *a, const Attribute *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->type != b->type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->index != b->index)
        {
            return(KMIP_FALSE);
        }
        
        if(a->value != b->value)
        {
            if((a->value == NULL) || (b->value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            switch(a->type)
            {
                case KMIP_ATTR_UNIQUE_IDENTIFIER:
                case KMIP_ATTR_OPERATION_POLICY_NAME:
                case KMIP_ATTR_OBJECT_GROUP:
                case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
                case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
                case KMIP_ATTR_DESCRIPTION:
                case KMIP_ATTR_COMMENT:
                return(kmip_compare_text_string((TextString *)a->value, (TextString *)b->value));
                break;
                
                case KMIP_ATTR_NAME:
                return(kmip_compare_name((Name *)a->value, (Name *)b->value));
                break;
                
                case KMIP_ATTR_OBJECT_TYPE:
                case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
                case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
                case KMIP_ATTR_CERTIFICATE_TYPE:
                case KMIP_ATTR_CERTIFICATE_LENGTH:
                case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
                case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
                case KMIP_ATTR_LEASE_TIME:
                case KMIP_ATTR_STATE:
                case KMIP_ATTR_FRESH:
                case KMIP_ATTR_KEY_VALUE_PRESENT:
                case KMIP_ATTR_SENSITIVE:
                case KMIP_ATTR_ALWAYS_SENSITIVE:
                case KMIP_ATTR_EXTRACTABLE:
                case KMIP_ATTR_NEVER_EXTRACTABLE:
                case KMIP_ATTR_KEY_FORMAT_TYPE:
                if(*(int32*)a->value != *(int32*)b->value)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_ATTR_INITIAL_DATE:
                case KMIP_ATTR_ACTIVATION_DATE:
                case KMIP_ATTR_PROCESS_START_DATE:
                case KMIP_ATTR_PROTECT_STOP_DATE:
                case KMIP_ATTR_DEACTIVATION_DATE:
                case KMIP_ATTR_DESTROY_DATE:
                case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
                case KMIP_ATTR_COMPROMISE_DATE:
                case KMIP_ATTR_ARCHIVE_DATE:
                case KMIP_ATTR_LAST_CHANGE_DATE:
                case KMIP_ATTR_ORIGINAL_CREATION_DATE:
                if(*(int64*)a->value != *(int64*)b->value)
                {
                    return(KMIP_FALSE);
                }
                break;

                // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:
                // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:
                // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:
                // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:
                // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:
                // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:
                // case KMIP_ATTR_CERTIFICATE_SUBJECT:
                // case KMIP_ATTR_CERTIFICATE_ISSUER:
                // case KMIP_ATTR_DIGEST:
                // case KMIP_ATTR_USAGE_LIMITS:
                // case KMIP_ATTR_REVOCATION_REASON:
                // case KMIP_ATTR_LINK:
                // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:
                // case KMIP_ATTR_CONTACT_INFORMATION:
                // case KMIP_ATTR_CUSTOM_ATTRIBUTE:
                // case KMIP_ATTR_ALTERNATIVE_NAME:
                // case KMIP_ATTR_KEY_VALUE_LOCATION:

                default:
                /* NOTE (ph) Unsupported types can't be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_attributes(const Attributes *a, const Attributes *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }

        if((a->attribute_list != b->attribute_list))
        {
            if((a->attribute_list == NULL) || (b->attribute_list == NULL))
            {
                return(KMIP_FALSE);
            }

            if((a->attribute_list->size != b->attribute_list->size))
            {
                return(KMIP_FALSE);
            }

            LinkedListItem *a_item = a->attribute_list->head;
            LinkedListItem *b_item = b->attribute_list->head;
            while((a_item != NULL) || (b_item != NULL))
            {
                if(a_item != b_item)
                {
                    Attribute *a_data = (Attribute *)a_item->data;
                    Attribute *b_data = (Attribute *)b_item->data;
                    if(kmip_compare_attribute(a_data, b_data) == KMIP_FALSE)
                    {
                        return(KMIP_FALSE);
                    }
                }

                a_item = a_item->next;
                b_item = b_item->next;
            }

            if(a_item != b_item)
            {
                return(KMIP_FALSE);
            }
        }
    }

    return(KMIP_TRUE);
}

int
kmip_compare_template_attribute(const TemplateAttribute *a, const TemplateAttribute *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->name_count != b->name_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attribute_count != b->attribute_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->names != b->names)
        {
            if((a->names == NULL) || (b->names == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->name_count; i++)
            {
                if(kmip_compare_name(&a->names[i], &b->names[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
        
        if(a->attributes != b->attributes)
        {
            if((a->attributes == NULL) || (b->attributes == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->attribute_count; i++)
            {
                if(kmip_compare_attribute(&a->attributes[i], &b->attributes[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_protocol_version(const ProtocolVersion *a, const ProtocolVersion *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->major != b->major)
        {
            return(KMIP_FALSE);
        }
        
        if(a->minor != b->minor)
        {
            return(KMIP_FALSE);
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_transparent_symmetric_key(const TransparentSymmetricKey *a, const TransparentSymmetricKey *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key != b->key)
        {
            if((a->key == NULL) || (b->key == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->key, b->key) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_key_material(enum key_format_type format, void **a, void **b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(*a != *b)
        {
            if((*a == NULL) || (*b == NULL))
            {
                return(KMIP_FALSE);
            }
            
            switch(format)
            {
                case KMIP_KEYFORMAT_RAW:
                case KMIP_KEYFORMAT_OPAQUE:
                case KMIP_KEYFORMAT_PKCS1:
                case KMIP_KEYFORMAT_PKCS8:
                case KMIP_KEYFORMAT_X509:
                case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
                if(kmip_compare_byte_string(*a, *b) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
                if(kmip_compare_transparent_symmetric_key(*a, *b) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                default:
                /* NOTE (ph) Unsupported types cannot be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_key_value(enum key_format_type format, const KeyValue *a, const KeyValue *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_material != b->key_material)
        {
            if((a->key_material == NULL) || (b->key_material == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_material(format, (void**)&a->key_material, (void**)&b->key_material) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attributes != b->attributes)
        {
            if((a->attributes == NULL) || (b->attributes == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->attribute_count; i++)
            {
                if(kmip_compare_attribute(&a->attributes[i], &b->attributes[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_cryptographic_parameters(const CryptographicParameters *a, const CryptographicParameters *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->block_cipher_mode != b->block_cipher_mode)
        {
            return(KMIP_FALSE);
        }
        
        if(a->padding_method != b->padding_method)
        {
            return(KMIP_FALSE);
        }
        
        if(a->hashing_algorithm != b->hashing_algorithm)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_role_type != b->key_role_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->digital_signature_algorithm != b->digital_signature_algorithm)
        {
            return(KMIP_FALSE);
        }
        
        if(a->cryptographic_algorithm != b->cryptographic_algorithm)
        {
            return(KMIP_FALSE);
        }
        
        if(a->random_iv != b->random_iv)
        {
            return(KMIP_FALSE);
        }
        
        if(a->iv_length != b->iv_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->tag_length != b->tag_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->fixed_field_length != b->fixed_field_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->invocation_field_length != b->invocation_field_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->counter_length != b->counter_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->initial_counter_value != b->initial_counter_value)
        {
            return(KMIP_FALSE);
        }
        
        if(a->salt_length != b->salt_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->mask_generator != b->mask_generator)
        {
            return(KMIP_FALSE);
        }
        
        if(a->mask_generator_hashing_algorithm != 
           b->mask_generator_hashing_algorithm)
        {
            return(KMIP_FALSE);
        }
        
        if(a->trailer_field != b->trailer_field)
        {
            return(KMIP_FALSE);
        }
        
        if(a->p_source != b->p_source)
        {
            if((a->p_source == NULL) || (b->p_source == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->p_source, b->p_source) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_encryption_key_information(const EncryptionKeyInformation *a, const EncryptionKeyInformation *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->cryptographic_parameters != b->cryptographic_parameters)
        {
            if((a->cryptographic_parameters == NULL) ||
               (b->cryptographic_parameters == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_cryptographic_parameters(a->cryptographic_parameters, b->cryptographic_parameters) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_mac_signature_key_information(const MACSignatureKeyInformation *a, const MACSignatureKeyInformation *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->cryptographic_parameters != b->cryptographic_parameters)
        {
            if((a->cryptographic_parameters == NULL) || (b->cryptographic_parameters == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_cryptographic_parameters(a->cryptographic_parameters, b->cryptographic_parameters) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_key_wrapping_data(const KeyWrappingData *a, const KeyWrappingData *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->wrapping_method != b->wrapping_method)
        {
            return(KMIP_FALSE);
        }
        
        if(a->encoding_option != b->encoding_option)
        {
            return(KMIP_FALSE);
        }
        
        if(a->mac_signature != b->mac_signature)
        {
            if((a->mac_signature == NULL) || (b->mac_signature == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->mac_signature, b->mac_signature) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->iv_counter_nonce != b->iv_counter_nonce)
        {
            if((a->iv_counter_nonce == NULL) || (b->iv_counter_nonce == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->iv_counter_nonce, b->iv_counter_nonce) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->encryption_key_info != b->encryption_key_info)
        {
            if((a->encryption_key_info == NULL) || (b->encryption_key_info == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_encryption_key_information(a->encryption_key_info, b->encryption_key_info) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->mac_signature_key_info != b->mac_signature_key_info)
        {
            if((a->mac_signature_key_info == NULL) || (b->mac_signature_key_info == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_mac_signature_key_information(a->mac_signature_key_info, b->mac_signature_key_info) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_key_block(const KeyBlock *a, const KeyBlock *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_format_type != b->key_format_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_compression_type != b->key_compression_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->cryptographic_algorithm != b->cryptographic_algorithm)
        {
            return(KMIP_FALSE);
        }
        
        if(a->cryptographic_length != b->cryptographic_length)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_value_type != b->key_value_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_value != b->key_value)
        {
            if((a->key_value == NULL) || (b->key_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(a->key_value_type == KMIP_TYPE_BYTE_STRING)
            {
                if(kmip_compare_byte_string((ByteString *)a->key_value, (ByteString *)b->key_value) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
            else
            {
                if(kmip_compare_key_value(a->key_format_type, (KeyValue *)a->key_value, (KeyValue *)b->key_value) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
        
        if(a->key_wrapping_data != b->key_wrapping_data)
        {
            if((a->key_wrapping_data == NULL) || (b->key_wrapping_data == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_wrapping_data(a->key_wrapping_data, b->key_wrapping_data) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_symmetric_key(const SymmetricKey *a, const SymmetricKey *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_block != b->key_block)
        {
            if((a->key_block == NULL) || (b->key_block == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_block(a->key_block, b->key_block) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_public_key(const PublicKey *a, const PublicKey *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_block != b->key_block)
        {
            if((a->key_block == NULL) || (b->key_block == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_block(a->key_block, b->key_block) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_private_key(const PrivateKey *a, const PrivateKey *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_block != b->key_block)
        {
            if((a->key_block == NULL) || (b->key_block == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_block(a->key_block, b->key_block) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_key_wrapping_specification(const KeyWrappingSpecification *a, const KeyWrappingSpecification *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->wrapping_method != b->wrapping_method)
        {
            return(KMIP_FALSE);
        }
        
        if(a->encoding_option != b->encoding_option)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attribute_name_count != b->attribute_name_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->encryption_key_info != b->encryption_key_info)
        {
            if((a->encryption_key_info == NULL) || (b->encryption_key_info == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_encryption_key_information(a->encryption_key_info, b->encryption_key_info) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->mac_signature_key_info != b->mac_signature_key_info)
        {
            if((a->mac_signature_key_info == NULL) || (b->mac_signature_key_info == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_mac_signature_key_information(a->mac_signature_key_info, b->mac_signature_key_info) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attribute_names != b->attribute_names)
        {
            if((a->attribute_names == NULL) || (b->attribute_names == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->attribute_name_count; i++)
            {
                if(kmip_compare_text_string(&a->attribute_names[i], &b->attribute_names[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_create_request_payload(const CreateRequestPayload *a, const CreateRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->object_type != b->object_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->template_attribute != b->template_attribute)
        {
            if((a->template_attribute == NULL) || (b->template_attribute == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_template_attribute(a->template_attribute, b->template_attribute) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }

        if(a->attributes != b->attributes)
        {
            if((a->attributes == NULL) || (b->attributes == NULL))
            {
                return(KMIP_FALSE);
            }

            if(kmip_compare_attributes(a->attributes, b->attributes) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }

        if(a->protection_storage_masks != b->protection_storage_masks)
        {
            if((a->protection_storage_masks == NULL) || (b->protection_storage_masks == NULL))
            {
                return(KMIP_FALSE);
            }

            if(kmip_compare_protection_storage_masks(a->protection_storage_masks, b->protection_storage_masks) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_create_response_payload(const CreateResponsePayload *a, const CreateResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->object_type != b->object_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->template_attribute != b->template_attribute)
        {
            if((a->template_attribute == NULL) || (b->template_attribute == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_template_attribute(a->template_attribute, b->template_attribute) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_locate_request_payload(const LocateRequestPayload *a, const LocateRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->maximum_items != b->maximum_items)
        {
            return(KMIP_FALSE);
        }
        
        if(a->offset_items != b->offset_items)
        {
            return(KMIP_FALSE);
        }
        
        if(a->storage_status_mask != b->storage_status_mask)
        {
            return(KMIP_FALSE);
        }
        
        if(a->object_group_member != b->object_group_member)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attribute_count != b->attribute_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attributes != b->attributes)
        {
            if((a->attributes == NULL) || (b->attributes == NULL))
            {
                return(KMIP_FALSE);
            }
            for(int i = 0; i < a->attribute_count; ++i)
            {
                if(kmip_compare_attribute(a->attributes + i, b->attributes + i) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_locate_response_payload(const LocateResponsePayload *a, const LocateResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->located_items != b->located_items)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifiers_count != b->unique_identifiers_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifiers != b->unique_identifiers)
        {
            for(int i = 0; i < a->unique_identifiers_count; ++i)
            {
                if(kmip_compare_text_string(a->unique_identifiers + i, b->unique_identifiers + i) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_request_payload(const GetRequestPayload *a, const GetRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_format_type != b->key_format_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_compression_type != b->key_compression_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->key_wrap_type != b->key_wrap_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->key_wrapping_spec != b->key_wrapping_spec)
        {
            if((a->key_wrapping_spec == NULL) || (b->key_wrapping_spec == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_key_wrapping_specification(a->key_wrapping_spec, b->key_wrapping_spec) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_response_payload(const GetResponsePayload *a, const GetResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->object_type != b->object_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->object != b->object)
        {
            switch(a->object_type)
            {
                case KMIP_OBJTYPE_SYMMETRIC_KEY:
                if(kmip_compare_symmetric_key((SymmetricKey *)a->object, (SymmetricKey *)b->object) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OBJTYPE_PUBLIC_KEY:
                if(kmip_compare_public_key((PublicKey *)a->object, (PublicKey *)b->object) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OBJTYPE_PRIVATE_KEY:
                if(kmip_compare_private_key((PrivateKey *)a->object, (PrivateKey *)b->object) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                default:
                /* NOTE (ph) Unsupported types cannot be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_attributes_request_payload(const GetAttributesRequestPayload *a, const GetAttributesRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attribute_count != b->attribute_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attribute_names != b->attribute_names)
        {
            if((a->attribute_names == NULL) || (b->attribute_names == NULL))
            {
                return(KMIP_FALSE);
            }
            for(int i = 0; i < a->attribute_count; ++i)
            {
		if (a->attribute_names[i] != b->attribute_names[i])
		return KMIP_FALSE;
	    }
	}
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_attributes_response_payload(const GetAttributesResponsePayload *a, const GetAttributesResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attributes != b->attributes)
        {
            if((a->attributes == NULL) || (b->attributes == NULL))
            {
                return(KMIP_FALSE);
            }
            for(int i = 0; i < a->attribute_count; ++i)
            {
                if(kmip_compare_attribute(a->attributes + i, b->attributes + i) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_attribute_list_request_payload(const GetAttributeListRequestPayload *a, const GetAttributeListRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_get_attribute_list_response_payload(const GetAttributeListResponsePayload *a, const GetAttributeListResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attribute_names_count != b->attribute_names_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attribute_names != b->attribute_names)
        {
            if((a->attribute_names == NULL) || (b->attribute_names == NULL))
            {
                return(KMIP_FALSE);
            }
            for(int i = 0; i < a->attribute_names_count; ++i)
            {
		if (a->attribute_names[i] != b->attribute_names[i])
		return KMIP_FALSE;
	    }
	}
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_destroy_request_payload(const DestroyRequestPayload *a, const DestroyRequestPayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_destroy_response_payload(const DestroyResponsePayload *a, const DestroyResponsePayload *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_identifier != b->unique_identifier)
        {
            if((a->unique_identifier == NULL) || (b->unique_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->unique_identifier, b->unique_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_request_batch_item(const RequestBatchItem *a, const RequestBatchItem *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->operation != b->operation)
        {
            return(KMIP_FALSE);
        }

        if(a->ephemeral != b->ephemeral)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_batch_item_id != b->unique_batch_item_id)
        {
            if((a->unique_batch_item_id == NULL) || (b->unique_batch_item_id == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->unique_batch_item_id, b->unique_batch_item_id) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->request_payload != b->request_payload)
        {
            if((a->request_payload == NULL) || (b->request_payload == NULL))
            {
                return(KMIP_FALSE);
            }
            
            switch(a->operation)
            {
                case KMIP_OP_CREATE:
                if(kmip_compare_create_request_payload((CreateRequestPayload *)a->request_payload, (CreateRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_LOCATE:
                if(kmip_compare_locate_request_payload((LocateRequestPayload *)a->request_payload, (LocateRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET:
                if(kmip_compare_get_request_payload((GetRequestPayload *)a->request_payload, (GetRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET_ATTRIBUTES:
                if(kmip_compare_get_attributes_request_payload((GetAttributesRequestPayload *)a->request_payload, (GetAttributesRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET_ATTRIBUTE_LIST:
                if(kmip_compare_get_attribute_list_request_payload((GetAttributeListRequestPayload *)a->request_payload, (GetAttributeListRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_DESTROY:
                if(kmip_compare_destroy_request_payload((DestroyRequestPayload *)a->request_payload, (DestroyRequestPayload *)b->request_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                default:
                /* NOTE (ph) Unsupported payloads cannot be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_response_batch_item(const ResponseBatchItem *a, const ResponseBatchItem *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->operation != b->operation)
        {
            return(KMIP_FALSE);
        }
        
        if(a->result_status != b->result_status)
        {
            return(KMIP_FALSE);
        }
        
        if(a->result_reason != b->result_reason)
        {
            return(KMIP_FALSE);
        }
        
        if(a->unique_batch_item_id != b->unique_batch_item_id)
        {
            if((a->unique_batch_item_id == NULL) || (b->unique_batch_item_id == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->unique_batch_item_id, b->unique_batch_item_id) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->result_message != b->result_message)
        {
            if((a->result_message == NULL) || (b->result_message == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->result_message, b->result_message) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->asynchronous_correlation_value != b->asynchronous_correlation_value)
        {
            if((a->asynchronous_correlation_value == NULL) || (b->asynchronous_correlation_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->asynchronous_correlation_value, b->asynchronous_correlation_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->response_payload != b->response_payload)
        {
            if((a->response_payload == NULL) || (b->response_payload == NULL))
            {
                return(KMIP_FALSE);
            }
            
            switch(a->operation)
            {
                case KMIP_OP_CREATE:
                if(kmip_compare_create_response_payload((CreateResponsePayload *)a->response_payload, (CreateResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_LOCATE:
                if(kmip_compare_locate_response_payload((LocateResponsePayload *)a->response_payload, (LocateResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET:
                if(kmip_compare_get_response_payload((GetResponsePayload *)a->response_payload, (GetResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET_ATTRIBUTES:
                if(kmip_compare_get_attributes_response_payload((GetAttributesResponsePayload *)a->response_payload, (GetAttributesResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_GET_ATTRIBUTE_LIST:
                if(kmip_compare_get_attribute_list_response_payload((GetAttributeListResponsePayload *)a->response_payload, (GetAttributeListResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_OP_DESTROY:
                if(kmip_compare_destroy_response_payload((DestroyResponsePayload *)a->response_payload, (DestroyResponsePayload *)b->response_payload) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                default:
                /* NOTE (ph) Unsupported payloads cannot be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_nonce(const Nonce *a, const Nonce *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->nonce_id != b->nonce_id)
        {
            if((a->nonce_id == NULL) || (b->nonce_id == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->nonce_id, b->nonce_id) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->nonce_value != b->nonce_value)
        {
            if((a->nonce_value == NULL) || (b->nonce_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->nonce_value, b->nonce_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_username_password_credential(const UsernamePasswordCredential *a, const UsernamePasswordCredential *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->username != b->username)
        {
            if((a->username == NULL) || (b->username == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->username, b->username) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->password != b->password)
        {
            if((a->password == NULL) || (b->password == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->password, b->password) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_device_credential(const DeviceCredential *a, const DeviceCredential *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->device_serial_number != b->device_serial_number)
        {
            if((a->device_serial_number == NULL) || (b->device_serial_number == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->device_serial_number, b->device_serial_number) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->password != b->password)
        {
            if((a->password == NULL) || (b->password == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->password, b->password) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->device_identifier != b->device_identifier)
        {
            if((a->device_identifier == NULL) || (b->device_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->device_identifier, b->device_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->network_identifier != b->network_identifier)
        {
            if((a->network_identifier == NULL) || (b->network_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->network_identifier, b->network_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->machine_identifier != b->machine_identifier)
        {
            if((a->machine_identifier == NULL) || (b->machine_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->machine_identifier, b->machine_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->media_identifier != b->media_identifier)
        {
            if((a->media_identifier == NULL) || (b->media_identifier == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->media_identifier, b->media_identifier) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_attestation_credential(const AttestationCredential *a, const AttestationCredential *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->attestation_type != b->attestation_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->nonce != b->nonce)
        {
            if((a->nonce == NULL) || (b->nonce == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_nonce(a->nonce, b->nonce) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attestation_measurement != b->attestation_measurement)
        {
            if((a->attestation_measurement == NULL) || (b->attestation_measurement == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->attestation_measurement, b->attestation_measurement) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attestation_assertion != b->attestation_assertion)
        {
            if((a->attestation_assertion == NULL) || (b->attestation_assertion == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_byte_string(a->attestation_assertion, b->attestation_assertion) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_credential_value(enum credential_type type, void **a, void **b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(*a != *b)
        {
            if((*a == NULL) || (*b == NULL))
            {
                return(KMIP_FALSE);
            }
            
            switch(type)
            {
                case KMIP_CRED_USERNAME_AND_PASSWORD:
                if(kmip_compare_username_password_credential(*a, *b) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_CRED_DEVICE:
                if(kmip_compare_device_credential(*a, *b) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                case KMIP_CRED_ATTESTATION:
                if(kmip_compare_attestation_credential(*a, *b) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
                break;
                
                default:
                /* NOTE (ph) Unsupported types cannot be compared. */
                return(KMIP_FALSE);
                break;
            };
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_credential(const Credential *a, const Credential *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->credential_type != b->credential_type)
        {
            return(KMIP_FALSE);
        }
        
        if(a->credential_value != b->credential_value)
        {
            if((a->credential_value == NULL) || (b->credential_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_credential_value(a->credential_type, (void**)&a->credential_value, (void**)&b->credential_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_authentication(const Authentication *a, const Authentication *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->credential != b->credential)
        {
            if((a->credential == NULL) || (b->credential == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_credential(a->credential, b->credential) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_request_header(const RequestHeader *a, const RequestHeader *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->maximum_response_size != b->maximum_response_size)
        {
            return(KMIP_FALSE);
        }
        
        if(a->asynchronous_indicator != b->asynchronous_indicator)
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_error_continuation_option != b->batch_error_continuation_option)
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_order_option != b->batch_order_option)
        {
            return(KMIP_FALSE);
        }
        
        if(a->time_stamp != b->time_stamp)
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_count != b->batch_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attestation_capable_indicator != b->attestation_capable_indicator)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attestation_type_count != b->attestation_type_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->protocol_version != b->protocol_version)
        {
            if((a->protocol_version == NULL) || (b->protocol_version == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_protocol_version(a->protocol_version, b->protocol_version) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->authentication != b->authentication)
        {
            if((a->authentication == NULL) || (b->authentication == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_authentication(a->authentication, b->authentication) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->attestation_types != b->attestation_types)
        {
            if((a->attestation_types == NULL) || (b->attestation_types == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->attestation_type_count; i++)
            {
                if(a->attestation_types[i] != b->attestation_types[i])
                {
                    return(KMIP_FALSE);
                }
            }
        }
        
        if(a->client_correlation_value != b->client_correlation_value)
        {
            if((a->client_correlation_value == NULL) || (b->client_correlation_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->client_correlation_value, b->client_correlation_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->server_correlation_value != b->server_correlation_value)
        {
            if((a->server_correlation_value == NULL) || (b->server_correlation_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->server_correlation_value, b->server_correlation_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_response_header(const ResponseHeader *a, const ResponseHeader *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->time_stamp != b->time_stamp)
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_count != b->batch_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->attestation_type_count != b->attestation_type_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->protocol_version != b->protocol_version)
        {
            if((a->protocol_version == NULL) || (b->protocol_version == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_protocol_version(a->protocol_version, b->protocol_version) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->nonce != b->nonce)
        {
            if((a->nonce == NULL) || (b->nonce == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_nonce(a->nonce, b->nonce) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }

        if(a->server_hashed_password != b->server_hashed_password)
        {
            if((a->server_hashed_password == NULL) || (b->server_hashed_password == NULL))
                return(KMIP_FALSE);

            if(kmip_compare_byte_string(a->server_hashed_password, b->server_hashed_password) == KMIP_FALSE)
                return(KMIP_FALSE);
        }

        if(a->attestation_types != b->attestation_types)
        {
            if((a->attestation_types == NULL) || (b->attestation_types == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->attestation_type_count; i++)
            {
                if(a->attestation_types[i] != b->attestation_types[i])
                {
                    return(KMIP_FALSE);
                }
            }
        }
        
        if(a->client_correlation_value != b->client_correlation_value)
        {
            if((a->client_correlation_value == NULL) || (b->client_correlation_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->client_correlation_value, b->client_correlation_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->server_correlation_value != b->server_correlation_value)
        {
            if((a->server_correlation_value == NULL) || (b->server_correlation_value == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_text_string(a->server_correlation_value, b->server_correlation_value) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_request_message(const RequestMessage *a, const RequestMessage *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_count != b->batch_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->request_header != b->request_header)
        {
            if((a->request_header == NULL) || (b->request_header == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_request_header(a->request_header, b->request_header) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->batch_items != b->batch_items)
        {
            if((a->batch_items == NULL) || (b->batch_items == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->batch_count; i++)
            {
                if(kmip_compare_request_batch_item(&a->batch_items[i], &b->batch_items[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

int
kmip_compare_response_message(const ResponseMessage *a, const ResponseMessage *b)
{
    if(a != b)
    {
        if((a == NULL) || (b == NULL))
        {
            return(KMIP_FALSE);
        }
        
        if(a->batch_count != b->batch_count)
        {
            return(KMIP_FALSE);
        }
        
        if(a->response_header != b->response_header)
        {
            if((a->response_header == NULL) || (b->response_header == NULL))
            {
                return(KMIP_FALSE);
            }
            
            if(kmip_compare_response_header(a->response_header, b->response_header) == KMIP_FALSE)
            {
                return(KMIP_FALSE);
            }
        }
        
        if(a->batch_items != b->batch_items)
        {
            if((a->batch_items == NULL) || (b->batch_items == NULL))
            {
                return(KMIP_FALSE);
            }
            
            for(size_t i = 0; i < a->batch_count; i++)
            {
                if(kmip_compare_response_batch_item(&a->batch_items[i], &b->batch_items[i]) == KMIP_FALSE)
                {
                    return(KMIP_FALSE);
                }
            }
        }
    }
    
    return(KMIP_TRUE);
}

/*
Encoding Functions
*/

int
kmip_encode_int8_be(KMIP *ctx, int8 value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int8));
    
    *ctx->index++ = value;
    
    return(KMIP_OK);
}

int
kmip_encode_int32_be(KMIP *ctx, int32 value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int32));
    
    *ctx->index++ = (value << 0) >> 24;
    *ctx->index++ = (value << 8) >> 24;
    *ctx->index++ = (value << 16) >> 24;
    *ctx->index++ = (value << 24) >> 24;
    
    return(KMIP_OK);
}

int
kmip_encode_int64_be(KMIP *ctx, int64 value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int64));
    
    *ctx->index++ = (value << 0) >> 56;
    *ctx->index++ = (value << 8) >> 56;
    *ctx->index++ = (value << 16) >> 56;
    *ctx->index++ = (value << 24) >> 56;
    *ctx->index++ = (value << 32) >> 56;
    *ctx->index++ = (value << 40) >> 56;
    *ctx->index++ = (value << 48) >> 56;
    *ctx->index++ = (value << 56) >> 56;
    
    return(KMIP_OK);
}

int
kmip_encode_integer(KMIP *ctx, enum tag t, int32 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_INTEGER));
    kmip_encode_int32_be(ctx, 4);
    kmip_encode_int32_be(ctx, value);
    kmip_encode_int32_be(ctx, 0);
    
    return(KMIP_OK);
}

int
kmip_encode_long(KMIP *ctx, enum tag t, int64 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_LONG_INTEGER));
    kmip_encode_int32_be(ctx, 8);
    kmip_encode_int64_be(ctx, value);
    
    return(KMIP_OK);
}

int
kmip_encode_enum(KMIP *ctx, enum tag t, int32 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_ENUMERATION));
    kmip_encode_int32_be(ctx, 4);
    kmip_encode_int32_be(ctx, value);
    kmip_encode_int32_be(ctx, 0);
    
    return(KMIP_OK);
}

int
kmip_encode_bool(KMIP *ctx, enum tag t, bool32 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_BOOLEAN));
    kmip_encode_int32_be(ctx, 8);
    kmip_encode_int32_be(ctx, 0);
    kmip_encode_int32_be(ctx, value);
    
    return(KMIP_OK);
}

int
kmip_encode_text_string(KMIP *ctx, enum tag t, const TextString *value)
{
    /* TODO (ph) What if value is NULL? */
    uint8 padding = (8 - (value->size % 8)) % 8;
    CHECK_BUFFER_FULL(ctx, 8 + value->size + padding);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_TEXT_STRING));
    kmip_encode_int32_be(ctx, value->size);
    
    for(uint32 i = 0; i < value->size; i++)
    {
        kmip_encode_int8_be(ctx, value->value[i]);
    }
    for(uint8 i = 0; i < padding; i++)
    {
        kmip_encode_int8_be(ctx, 0);
    }
    
    return(KMIP_OK);
}

int
kmip_encode_byte_string(KMIP *ctx, enum tag t, const ByteString *value)
{
    uint8 padding = (8 - (value->size % 8)) % 8;
    CHECK_BUFFER_FULL(ctx, 8 + value->size + padding);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_BYTE_STRING));
    kmip_encode_int32_be(ctx, value->size);
    
    for(uint32 i = 0; i < value->size; i++)
    {
        kmip_encode_int8_be(ctx, value->value[i]);
    }
    for(uint8 i = 0; i < padding; i++)
    {
        kmip_encode_int8_be(ctx, 0);
    }
    
    return(KMIP_OK);
}

int
kmip_encode_date_time(KMIP *ctx, enum tag t, uint64 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_DATE_TIME));
    kmip_encode_int32_be(ctx, 8);
    kmip_encode_int64_be(ctx, value);
    
    return(KMIP_OK);
}

int
kmip_encode_interval(KMIP *ctx, enum tag t, uint32 value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(t, KMIP_TYPE_INTERVAL));
    kmip_encode_int32_be(ctx, 4);
    kmip_encode_int32_be(ctx, value);
    kmip_encode_int32_be(ctx, 0);
    
    return(KMIP_OK);
}

int
kmip_encode_digest(KMIP *ctx, const Digest *value)
{
    int result = 0;

    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_DIGEST, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    result = kmip_encode_enum(ctx, KMIP_TAG_HASHING_ALGORITHM, value->hashing_algorithm);
    CHECK_RESULT(ctx, result);

    if(value->digest_value != NULL)
    {
	result = kmip_encode_byte_string(ctx, KMIP_TAG_DIGEST_VALUE, value->digest_value);
	CHECK_RESULT(ctx, result);
    }

    if(value->key_format_type != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
        CHECK_RESULT(ctx, result);
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    kmip_encode_int32_be(ctx, curr_index - value_index);

    ctx->index = curr_index;

    return(KMIP_OK);
}

int
kmip_encode_name(KMIP *ctx, const Name *value)
{
    /* TODO (ph) Check for value == NULL? */
    
    int result = 0;
    
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_NAME, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_NAME_VALUE, value->value);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_enum(ctx, KMIP_TAG_NAME_TYPE, value->type);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_protection_storage_masks(KMIP *ctx, const ProtectionStorageMasks *value)
{
    CHECK_ENCODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);

    int result = 0;

    result = kmip_encode_int32_be(
        ctx,
        TAG_TYPE(KMIP_TAG_PROTECTION_STORAGE_MASKS, KMIP_TYPE_STRUCTURE)
    );
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    if(value->masks != NULL)
    {
        LinkedListItem *curr = value->masks->head;
        while(curr != NULL)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_PROTECTION_STORAGE_MASK, *(int32 *)curr->data);
            CHECK_RESULT(ctx, result);

            curr = curr->next;
        }
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);

    ctx->index = curr_index;

    return(KMIP_OK);
}

int
kmip_encode_attribute_name(KMIP *ctx, enum attribute_type value)
{
    int result = 0;
    enum tag t = KMIP_TAG_ATTRIBUTE_NAME;
    TextString attribute_name = {0};
    
    switch(value)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        attribute_name.value = "Unique Identifier";
        attribute_name.size = 17;
        break;
        
        case KMIP_ATTR_NAME:
        attribute_name.value = "Name";
        attribute_name.size = 4;
        break;
        
        case KMIP_ATTR_OBJECT_TYPE:
        attribute_name.value = "Object Type";
        attribute_name.size = 11;
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        attribute_name.value = "Cryptographic Algorithm";
        attribute_name.size = 23;
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        attribute_name.value = "Cryptographic Length";
        attribute_name.size = 20;
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:
        attribute_name.value = "Cryptographic Parameters";
        attribute_name.size = 24;
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:
        attribute_name.value = "Cryptographic Domain Parameters";
        attribute_name.size = 31;
        break;

        case KMIP_ATTR_CERTIFICATE_TYPE:
        attribute_name.value = "Certificate Type";
        attribute_name.size = 16;
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        attribute_name.value = "Certificate Length";
        attribute_name.size = 18;
        break;

        case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:
        attribute_name.value = "X.509 Certificate Identifier";
        attribute_name.size = 28;
        break;

        case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:
        attribute_name.value = "X.509 Certificate Subject";
        attribute_name.size = 25;
        break;

        case KMIP_ATTR_X509_CERTIFICATE_ISSUER:
        attribute_name.value = "X.509 Certificate Issuer";
        attribute_name.size = 24;
        break;

        case KMIP_ATTR_CERTIFICATE_IDENTIFIER:
        attribute_name.value = "Certificate Identifier";
        attribute_name.size = 22;
        break;

        case KMIP_ATTR_CERTIFICATE_SUBJECT:
        attribute_name.value = "Certificate Subject";
        attribute_name.size = 19;
        break;

        case KMIP_ATTR_CERTIFICATE_ISSUER:
        attribute_name.value = "Certificate Issuer";
        attribute_name.size = 18;
        break;

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        attribute_name.value = "Digital Signature Algorithm";
        attribute_name.size = 27;
        break;

        case KMIP_ATTR_DIGEST:
        attribute_name.value = "Digest";
        attribute_name.size = 6;
        break;
        
        case KMIP_ATTR_OPERATION_POLICY_NAME:
        attribute_name.value = "Operation Policy Name";
        attribute_name.size = 21;
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        attribute_name.value = "Cryptographic Usage Mask";
        attribute_name.size = 24;
        break;

        case KMIP_ATTR_LEASE_TIME:
        attribute_name.value = "Lease Time";
        attribute_name.size = 10;
        break;

        case KMIP_ATTR_USAGE_LIMITS:
        attribute_name.value = "Usage Limits";
        attribute_name.size = 12;
        break;
        
        case KMIP_ATTR_STATE:
        attribute_name.value = "State";
        attribute_name.size = 5;
        break;
        
        case KMIP_ATTR_INITIAL_DATE:
        attribute_name.value = "Initial Date";
        attribute_name.size = 12;
        break;
        case KMIP_ATTR_ACTIVATION_DATE:
        attribute_name.value = "Activation Date";
        attribute_name.size = 15;
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        attribute_name.value = "Process Start Date";
        attribute_name.size = 18;
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        attribute_name.value = "Protect Stop Date";
        attribute_name.size = 17;
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        attribute_name.value = "Deactivation Date";
        attribute_name.size = 17;
        break;

        case KMIP_ATTR_DESTROY_DATE:
        attribute_name.value = "Destroy Date";
        attribute_name.size = 12;
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        attribute_name.value = "Compromise Occurrence Date";
        attribute_name.size = 26;
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        attribute_name.value = "Compromise Date";
        attribute_name.size = 15;
        break;

        case KMIP_ATTR_REVOCATION_REASON:
        attribute_name.value = "Revocation Reason";
        attribute_name.size = 17;
        break;

        case KMIP_ATTR_ARCHIVE_DATE:
        attribute_name.value = "Archive Date";
        attribute_name.size = 12;
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        attribute_name.value = "Object Group";
        attribute_name.size = 12;
        break;

        case KMIP_ATTR_FRESH:
        attribute_name.value = "Fresh";
        attribute_name.size = 5;
        break;

        case KMIP_ATTR_LINK:
        attribute_name.value = "Link";
        attribute_name.size = 4;
        break;

        case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:
        attribute_name.value = "Application Specific Information";
        attribute_name.size = 32;
        break;

        case KMIP_ATTR_CONTACT_INFORMATION:
        attribute_name.value = "Contact Information";
        attribute_name.size = 19;
        break;

        case KMIP_ATTR_LAST_CHANGE_DATE:
        attribute_name.value = "Last Change Date";
        attribute_name.size = 16;
        break;

        case KMIP_ATTR_ALTERNATIVE_NAME:
        attribute_name.value = "Alternative Name";
        attribute_name.size = 16;
        break;

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        attribute_name.value = "Key Value Present";
        attribute_name.size = 17;
        break;

        case KMIP_ATTR_KEY_VALUE_LOCATION:
        attribute_name.value = "Key Value Location";
        attribute_name.size = 18;
        break;

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        attribute_name.value = "Original Creation Date";
        attribute_name.size = 22;
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        attribute_name.value = "Random Number Generator";
        attribute_name.size = 23;
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        attribute_name.value = "PKCS#12 Friendly Name";
        attribute_name.size = 21;
        break;

        case KMIP_ATTR_DESCRIPTION:
        attribute_name.value = "Description";
        attribute_name.size = 11;
        break;

        case KMIP_ATTR_COMMENT:
        attribute_name.value = "Comment";
        attribute_name.size = 7;
        break;

        case KMIP_ATTR_SENSITIVE:
        attribute_name.value = "Sensitive";
        attribute_name.size = 9;
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        attribute_name.value = "Always Sensitive";
        attribute_name.size = 16;
        break;

        case KMIP_ATTR_EXTRACTABLE:
        attribute_name.value = "Extractable";
        attribute_name.size = 11;
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        attribute_name.value = "Never Extractable";
        attribute_name.size = 17;
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        attribute_name.value = "Key Format Type";
        attribute_name.size = 15;
        break;

        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_ERROR_ATTR_UNSUPPORTED);
        break;
    };
    
    result = kmip_encode_text_string(ctx, t, &attribute_name);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_encode_attribute_v1(KMIP *ctx, const Attribute *value)
{
    /* TODO (ph) Add CryptographicParameters support? */
    CHECK_ENCODE_ARGS(ctx, value);

    int result = 0;
    
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ATTRIBUTE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_attribute_name(ctx, value->type);
    CHECK_RESULT(ctx, result);
    
    if(value->index != KMIP_UNSET)
    {
        result = kmip_encode_integer(ctx, KMIP_TAG_ATTRIBUTE_INDEX, value->index);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    uint8 *tag_index = ctx->index;
    enum tag t = KMIP_TAG_ATTRIBUTE_VALUE;
    
    switch(value->type)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;
        
        case KMIP_ATTR_NAME:
        /* TODO (ph) This is messy. Clean it up? */
        result = kmip_encode_name(ctx, (Name*)value->value);
        CHECK_RESULT(ctx, result);
        
        curr_index = ctx->index;
        ctx->index = tag_index;
        
        result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE));
        
        ctx->index = curr_index;
        break;
        
        case KMIP_ATTR_OBJECT_TYPE:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        result = kmip_encode_integer(ctx, t, *(int32 *)value->value);
        break;

        // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:     XXX how to hack struct?
        // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:      XXX how to hack struct?

        case KMIP_ATTR_CERTIFICATE_TYPE:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        result = kmip_encode_integer(ctx, t, *(int32 *)value->value);
        break;

        // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:  XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:     XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:      XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:       XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_SUBJECT:  XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_ISSUER:   XXX how to hack struct?

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;

        case KMIP_ATTR_DIGEST:
	// messy...
        result = kmip_encode_digest(ctx, (const Digest*)value->value);
        CHECK_RESULT(ctx, result);
        
        curr_index = ctx->index;
        ctx->index = tag_index;
        
        result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE));
        
        ctx->index = curr_index;
	break;

        case KMIP_ATTR_OPERATION_POLICY_NAME:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        result = kmip_encode_integer(ctx, t, *(int32 *)value->value);
        break;

        case KMIP_ATTR_LEASE_TIME:
        result = kmip_encode_interval(ctx, t, *(uint32 *)value->value);
        break;

        // case KMIP_ATTR_USAGE_LIMITS: XXX how to hack struct?
        
        case KMIP_ATTR_STATE:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_INITIAL_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;
       case KMIP_ATTR_ACTIVATION_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_DESTROY_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        // case KMIP_ATTR_REVOCATION_REASON:    XXX how to hack struct?

        case KMIP_ATTR_ARCHIVE_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;

        case KMIP_ATTR_FRESH:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        // case KMIP_ATTR_LINK: XXX how to hack struct?
        // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:     XXX how to hack struct?
        // case KMIP_ATTR_CONTACT_INFORMATION:  XXX how to hack struct?

        case KMIP_ATTR_LAST_CHANGE_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        // case KMIP_ATTR_CUSTOM_ATTRIBUTE:     XXX how to hack custom?
        // case KMIP_ATTR_ALTERNATIVE_NAME:     XXX how to hack struct?

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        // case KMIP_ATTR_KEY_VALUE_LOCATION:   XXX how to hack struct?

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        result = kmip_encode_date_time(ctx, t, *(uint64 *)value->value);
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;

        case KMIP_ATTR_DESCRIPTION:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;

        case KMIP_ATTR_COMMENT:
        result = kmip_encode_text_string(ctx, t, (TextString*)value->value);
        break;

        case KMIP_ATTR_SENSITIVE:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        case KMIP_ATTR_EXTRACTABLE:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        result = kmip_encode_bool(ctx, t, *(bool32 *)value->value);
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        result = kmip_encode_enum(ctx, t, *(int32 *)value->value);
        break;

        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_ERROR_ATTR_UNSUPPORTED);
        break;
    };
    CHECK_RESULT(ctx, result);
    
    curr_index = ctx->index;
    ctx->index = length_index;
    
    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_attribute_v2(KMIP *ctx, const Attribute *value)
{
    /* TODO (ph) Add CryptographicParameters support? */
    CHECK_ENCODE_ARGS(ctx, value);

    int result = 0;

    switch(value->type)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_UNIQUE_IDENTIFIER,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_NAME:
        {
            result = kmip_encode_name(ctx, (Name*)value->value);
        }
        break;

        case KMIP_ATTR_OBJECT_TYPE:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_OBJECT_TYPE,
                *(int32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM,
                *(int32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        {
            result = kmip_encode_integer(
                ctx,
                KMIP_TAG_CRYPTOGRAPHIC_LENGTH,
                *(int32 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:	XXX how to hack struct?
        // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:	XXX how to hack struct?

        case KMIP_ATTR_CERTIFICATE_TYPE:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_CERTIFICATE_TYPE,
                *(int32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        {
            result = kmip_encode_integer(
                ctx,
                KMIP_TAG_CERTIFICATE_LENGTH,
                *(int32 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_ISSUER:	XXX how to hack struct?

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM,
                *(int32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_DIGEST:
        {
            result = kmip_encode_digest(ctx, (Digest*)value->value);
        }
        break;

        case KMIP_ATTR_OPERATION_POLICY_NAME:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_OPERATION_POLICY_NAME,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        {
            result = kmip_encode_integer(
                ctx,
                KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK,
                *(int32 *)value->value)
            ;
        }
        break;

        case KMIP_ATTR_LEASE_TIME:
        {
            result = kmip_encode_interval(
                ctx,
                KMIP_TAG_LEASE_TIME,
                *(uint32 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_USAGE_LIMITS: XXX how to hack struct?

        case KMIP_ATTR_STATE:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_STATE,
                *(int32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_INITIAL_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_INITIAL_DATE,
                *(uint64 *)value->value)
            ;
        }
        break;

        case KMIP_ATTR_ACTIVATION_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_ACTIVATION_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_PROCESS_START_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_PROTECT_STOP_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_DEACTIVATION_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_DESTROY_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_DESTROY_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_COMPROMISE_OCCURRENCE_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_COMPROMISE_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_REVOCATION_REASON:	XXX how to hack struct?

        case KMIP_ATTR_ARCHIVE_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_ARCHIVE_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_OBJECT_GROUP,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_FRESH:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_FRESH,
                *(bool32 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_LINK:	XXX how to hack struct?
        // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:	XXX how to hack struct?
        // case KMIP_ATTR_CONTACT_INFORMATION:	XXX how to hack struct?

        case KMIP_ATTR_LAST_CHANGE_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_LAST_CHANGE_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_CUSTOM_ATTRIBUTE:	XXX how to hack custom?
        // case KMIP_ATTR_ALTERNATIVE_NAME:	XXX how to hack struct?

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_KEY_VALUE_PRESENT,
                *(bool32 *)value->value
            );
        }
        break;

        // case KMIP_ATTR_KEY_VALUE_LOCATION:	XXX how to hack struct?

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        {
            result = kmip_encode_date_time(
                ctx,
                KMIP_TAG_ORIGINAL_CREATION_DATE,
                *(uint64 *)value->value
            );
        }
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_RANDOM_NUMBER_GENERATOR,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_PKCS_12_FRIENDLY_NAME,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_DESCRIPTION:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_DESCRIPTION,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_COMMENT:
        {
            result = kmip_encode_text_string(
                ctx,
                KMIP_TAG_COMMENT,
                (TextString*)value->value
            );
        }
        break;

        case KMIP_ATTR_SENSITIVE:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_SENSITIVE,
                *(bool32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_ALWAYS_SENSITIVE,
                *(bool32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_EXTRACTABLE:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_EXTRACTABLE,
                *(bool32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        {
            result = kmip_encode_bool(
                ctx,
                KMIP_TAG_NEVER_EXTRACTABLE,
                *(bool32 *)value->value
            );
        }
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        {
            result = kmip_encode_enum(
                ctx,
                KMIP_TAG_KEY_FORMAT_TYPE,
                *(int32 *)value->value
            );
        }
        break;

        default:
        {
            kmip_push_error_frame(ctx, __func__, __LINE__);
            return(KMIP_ERROR_ATTR_UNSUPPORTED);
        }
        break;
    };
    CHECK_RESULT(ctx, result);

    return(KMIP_OK);
}

int
kmip_encode_attribute(KMIP *ctx, const Attribute *value)
{
    CHECK_ENCODE_ARGS(ctx, value);

    if(ctx->version < KMIP_2_0)
    {
        return(kmip_encode_attribute_v1(ctx, value));
    }
    else
    {
        return(kmip_encode_attribute_v2(ctx, value));
    }
}

int
kmip_encode_attributes(KMIP *ctx, const Attributes *value)
{
    CHECK_ENCODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);

    int result = 0;

    result = kmip_encode_int32_be(
        ctx,
        TAG_TYPE(KMIP_TAG_ATTRIBUTES, KMIP_TYPE_STRUCTURE)
    );
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    if(value->attribute_list != NULL)
    {
        LinkedListItem *curr = value->attribute_list->head;
        while(curr != NULL)
        {
            Attribute *attribute = (Attribute *)curr->data;
            result = kmip_encode_attribute(ctx, attribute);
            CHECK_RESULT(ctx, result);

            curr = curr->next;
        }
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);

    ctx->index = curr_index;

    return(KMIP_OK);
}

int
kmip_encode_attributes_2(KMIP *ctx, const Attribute *value, int count)
{
    CHECK_ENCODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);

    int result = 0;

    result = kmip_encode_int32_be(
        ctx,
        TAG_TYPE(KMIP_TAG_ATTRIBUTES, KMIP_TYPE_STRUCTURE)
    );
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    if(value) {
	for (int i = 0; i < count; ++i)
	{
	    result = kmip_encode_attribute(ctx, value + i);
	    CHECK_RESULT(ctx, result);
	}
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);

    ctx->index = curr_index;

    return(KMIP_OK);
}

int
kmip_encode_template_attribute(KMIP *ctx, const TemplateAttribute *value)
{
    int result = 0;
    
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_TEMPLATE_ATTRIBUTE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    for(size_t i = 0; i < value->name_count; i++)
    {
        result = kmip_encode_name(ctx, &value->names[i]);
        CHECK_RESULT(ctx, result);
    }
    
    for(size_t i = 0; i <value->attribute_count; i++)
    {
        result = kmip_encode_attribute(ctx, &value->attributes[i]);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    result = kmip_encode_int32_be(ctx, curr_index - value_index);
    CHECK_RESULT(ctx, result);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_protocol_version(KMIP *ctx, const ProtocolVersion *value)
{
    CHECK_BUFFER_FULL(ctx, 40);
    
    kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_PROTOCOL_VERSION, KMIP_TYPE_STRUCTURE));
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    kmip_encode_integer(ctx, KMIP_TAG_PROTOCOL_VERSION_MAJOR, value->major);
    kmip_encode_integer(ctx, KMIP_TAG_PROTOCOL_VERSION_MINOR, value->minor);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_cryptographic_parameters(KMIP *ctx, const CryptographicParameters *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->block_cipher_mode != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_BLOCK_CIPHER_MODE, value->block_cipher_mode);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->padding_method != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_PADDING_METHOD, value->padding_method);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->hashing_algorithm != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_HASHING_ALGORITHM, value->hashing_algorithm);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->key_role_type != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_KEY_ROLE_TYPE, value->key_role_type);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_2)
    {
        if(value->digital_signature_algorithm != 0)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, value->digital_signature_algorithm);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->cryptographic_algorithm != 0)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, value->cryptographic_algorithm);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->random_iv != KMIP_UNSET)
        {
            result = kmip_encode_bool(ctx, KMIP_TAG_RANDOM_IV, value->random_iv);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->iv_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_IV_LENGTH, value->iv_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->tag_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_TAG_LENGTH, value->tag_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->fixed_field_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_FIXED_FIELD_LENGTH, value->fixed_field_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->invocation_field_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_INVOCATION_FIELD_LENGTH, value->invocation_field_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->counter_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_COUNTER_LENGTH, value->counter_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->initial_counter_value != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_INITIAL_COUNTER_VALUE, value->initial_counter_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(value->salt_length != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_SALT_LENGTH, value->salt_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->mask_generator != 0)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_MASK_GENERATOR, value->mask_generator);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->mask_generator_hashing_algorithm != 0)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_MASK_GENERATOR_HASHING_ALGORITHM, value->mask_generator_hashing_algorithm);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->p_source != NULL)
        {
            result = kmip_encode_byte_string(ctx, KMIP_TAG_P_SOURCE, value->p_source);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->trailer_field != KMIP_UNSET)
        {
            result = kmip_encode_integer(ctx, KMIP_TAG_TRAILER_FIELD, value->trailer_field);
            CHECK_RESULT(ctx, result);
        }
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_encryption_key_information(KMIP *ctx, const EncryptionKeyInformation *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ENCRYPTION_KEY_INFORMATION, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    if(value->cryptographic_parameters != 0)
    {
        result = kmip_encode_cryptographic_parameters(ctx, value->cryptographic_parameters);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_mac_signature_key_information(KMIP *ctx, const MACSignatureKeyInformation *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_MAC_SIGNATURE_KEY_INFORMATION, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    if(value->cryptographic_parameters != 0)
    {
        result = kmip_encode_cryptographic_parameters(ctx, value->cryptographic_parameters);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_key_wrapping_data(KMIP *ctx, const KeyWrappingData *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_KEY_WRAPPING_DATA, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_WRAPPING_METHOD, value->wrapping_method);
    CHECK_RESULT(ctx, result);
    
    if(value->encryption_key_info != NULL)
    {
        result = kmip_encode_encryption_key_information(ctx, value->encryption_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->mac_signature_key_info != NULL)
    {
        result = kmip_encode_mac_signature_key_information(ctx, value->mac_signature_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->mac_signature != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_MAC_SIGNATURE, value->mac_signature);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->iv_counter_nonce != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_IV_COUNTER_NONCE, value->iv_counter_nonce);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_1)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_ENCODING_OPTION, value->encoding_option);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_transparent_symmetric_key(KMIP *ctx, const TransparentSymmetricKey *value)
{
    int result = 0;
    
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_KEY_MATERIAL, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_byte_string(ctx, KMIP_TAG_KEY, value->key);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_key_material(KMIP *ctx, enum key_format_type format, const void *value)
{
    int result = 0;
    
    switch(format)
    {
        case KMIP_KEYFORMAT_RAW:
        case KMIP_KEYFORMAT_OPAQUE:
        case KMIP_KEYFORMAT_PKCS1:
        case KMIP_KEYFORMAT_PKCS8:
        case KMIP_KEYFORMAT_X509:
        case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
        result = kmip_encode_byte_string(ctx, KMIP_TAG_KEY_MATERIAL, (ByteString*)value);
        CHECK_RESULT(ctx, result);
        return(KMIP_OK);
        break;
        
        default:
        break;
    };
    
    switch(format)
    {
        case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
        result = kmip_encode_transparent_symmetric_key(ctx, (TransparentSymmetricKey*)value);
        CHECK_RESULT(ctx, result);
        break;
        
        /* TODO (ph) The rest require BigInteger support. */
        
        case KMIP_KEYFORMAT_TRANS_DSA_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_DSA_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_RSA_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_RSA_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_DH_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_DH_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDSA_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDSA_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDH_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECDH_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECMQV_PRIVATE_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        case KMIP_KEYFORMAT_TRANS_ECMQV_PUBLIC_KEY:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    
    return(KMIP_OK);
}

int
kmip_encode_key_value(KMIP *ctx, enum key_format_type format, const KeyValue *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_KEY_VALUE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_key_material(ctx, format, value->key_material);
    CHECK_RESULT(ctx, result);
    
    for(size_t i = 0; i < value->attribute_count; i++)
    {
        result = kmip_encode_attribute(ctx, &value->attributes[i]);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_key_block(KMIP *ctx, const KeyBlock *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_KEY_BLOCK, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
    CHECK_RESULT(ctx, result);
    
    if(value->key_compression_type != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, value->key_compression_type);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->key_wrapping_data != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_KEY_VALUE, (ByteString*)value->key_value);
    }
    else
    {
        result = kmip_encode_key_value(ctx, value->key_format_type, (KeyValue*)value->key_value);
    }
    CHECK_RESULT(ctx, result);
    
    if(value->cryptographic_algorithm != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, value->cryptographic_algorithm);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->cryptographic_length != KMIP_UNSET)
    {
        result = kmip_encode_integer(ctx, KMIP_TAG_CRYPTOGRAPHIC_LENGTH, value->cryptographic_length);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->key_wrapping_data != NULL)
    {
        result = kmip_encode_key_wrapping_data(ctx, value->key_wrapping_data);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_symmetric_key(KMIP *ctx, const SymmetricKey *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_SYMMETRIC_KEY, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_public_key(KMIP *ctx, const PublicKey *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_PUBLIC_KEY, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_private_key(KMIP *ctx, const PrivateKey *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_PRIVATE_KEY, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_key_wrapping_specification(KMIP *ctx, const KeyWrappingSpecification *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_KEY_WRAPPING_SPECIFICATION, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_WRAPPING_METHOD, value->wrapping_method);
    CHECK_RESULT(ctx, result);
    
    if(value->encryption_key_info != NULL)
    {
        result = kmip_encode_encryption_key_information(ctx, value->encryption_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->mac_signature_key_info != NULL)
    {
        result = kmip_encode_mac_signature_key_information(ctx, value->mac_signature_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    for(size_t i = 0; i < value->attribute_name_count; i++)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_ATTRIBUTE_NAME, &value->attribute_names[i]);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_1)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_ENCODING_OPTION, value->encoding_option);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_create_request_payload(KMIP *ctx, const CreateRequestPayload *value)
{
    CHECK_ENCODE_ARGS(ctx, value);

    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);
    CHECK_RESULT(ctx, result);

    if(ctx->version < KMIP_2_0)
    {
        result = kmip_encode_template_attribute(ctx, value->template_attribute);
        CHECK_RESULT(ctx, result);
    }
    else
    {
        if(value->attributes)
        {
            result = kmip_encode_attributes(ctx, value->attributes);
            CHECK_RESULT(ctx, result);
        }
        else if(value->template_attribute)
        {
            Attributes *attributes = ctx->calloc_func(ctx->state, 1, sizeof(Attributes));
            LinkedList *list = ctx->calloc_func(ctx->state, 1, sizeof(LinkedList));
            attributes->attribute_list = list;
            for(size_t i = 0; i < value->template_attribute->attribute_count; i++)
            {
                LinkedListItem *item = ctx->calloc_func(ctx->state, 1, sizeof(LinkedListItem));
                item->data = kmip_deep_copy_attribute(ctx, &value->template_attribute->attributes[i]);
                kmip_linked_list_enqueue(list, item);
            }

            result = kmip_encode_attributes(ctx, attributes);

            kmip_free_attributes(ctx, attributes);
            ctx->free_func(ctx->state, attributes);

            CHECK_RESULT(ctx, result);
        }

        if(value->protection_storage_masks != NULL)
        {
            result = kmip_encode_protection_storage_masks(ctx, value->protection_storage_masks);
            CHECK_RESULT(ctx, result);
        }
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_create_response_payload(KMIP *ctx, const CreateResponsePayload *value)
{
    CHECK_ENCODE_ARGS(ctx, value);

    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);

    if(ctx->version < KMIP_2_0)
    {
        if(value->template_attribute != NULL)
        {
            result = kmip_encode_template_attribute(ctx, value->template_attribute);
            CHECK_RESULT(ctx, result);
        }
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
     
    return(KMIP_OK);
}

int
kmip_encode_locate_request_payload(KMIP *ctx, const LocateRequestPayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    if(value->maximum_items != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_MAXIMUM_ITEMS, value->maximum_items);
        CHECK_RESULT(ctx, result);
    }

    if(value->offset_items != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_OFFSET_ITEMS, value->offset_items);
        CHECK_RESULT(ctx, result);
    }

    if(value->storage_status_mask != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_STORAGE_STATUS_MASK, value->storage_status_mask);
        CHECK_RESULT(ctx, result);
    }

    if(value->object_group_member != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_OBJECT_GROUP_MEMBER, value->object_group_member);
        CHECK_RESULT(ctx, result);
    }

    if (value->attributes)
    {
	if(ctx->version < KMIP_2_0)
	{
	    for(int i = 0; i < value->attribute_count; ++i)
	    {
		result = kmip_encode_attribute(ctx, value->attributes + i);
		CHECK_RESULT(ctx, result);
	    }
	} else {
	    result = kmip_encode_attributes_2(ctx, value->attributes, value->attribute_count);
	    CHECK_RESULT(ctx, result);
	}
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    kmip_encode_int32_be(ctx, curr_index - value_index);

    ctx->index = curr_index;

    return(KMIP_OK);
}


int
kmip_encode_locate_response_payload(KMIP *ctx, const LocateResponsePayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);

    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;

    if(value->located_items != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_LOCATED_ITEMS, value->located_items);
        CHECK_RESULT(ctx, result);
    }

    if (value->unique_identifiers) {
	for(int i = 0; i < value->unique_identifiers_count; ++i)
	{
	    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifiers + i);
	    CHECK_RESULT(ctx, result);
	}
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;

    kmip_encode_int32_be(ctx, curr_index - value_index);

    ctx->index = curr_index;

    return(KMIP_OK);
}


int
kmip_encode_get_request_payload(KMIP *ctx, const GetRequestPayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->unique_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->key_format_type != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(value->key_wrap_type != 0)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_KEY_WRAP_TYPE, value->key_wrap_type);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(value->key_compression_type != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, value->key_compression_type);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->key_wrapping_spec != NULL)
    {
        result = kmip_encode_key_wrapping_specification(ctx, value->key_wrapping_spec);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_get_response_payload(KMIP *ctx, const GetResponsePayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    switch(value->object_type)
    {
        case KMIP_OBJTYPE_SYMMETRIC_KEY:
        result = kmip_encode_symmetric_key(ctx, (const SymmetricKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_OBJTYPE_PUBLIC_KEY:
        result = kmip_encode_public_key(ctx, (const PublicKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_OBJTYPE_PRIVATE_KEY:
        result = kmip_encode_private_key(ctx, (const PrivateKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}


int
kmip_encode_get_attributes_request_payload(KMIP *ctx, const GetAttributesRequestPayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->unique_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }

    if (value->attribute_names) {
	for(int i = 0; i < value->attribute_count; ++i)
	{
	    result = kmip_encode_attribute_name(ctx, value->attribute_names[i]);
	    CHECK_RESULT(ctx, result);
	}
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_get_attributes_response_payload(KMIP *ctx, const GetAttributesResponsePayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);

    if (value->attributes)
    {
	if(ctx->version < KMIP_2_0)
	{
	    for(int i = 0; i < value->attribute_count; ++i)
	    {
		result = kmip_encode_attribute(ctx, value->attributes + i);
		CHECK_RESULT(ctx, result);
	    }
	} else {
	    result = kmip_encode_attributes_2(ctx, value->attributes, value->attribute_count);
	    CHECK_RESULT(ctx, result);
	}
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}


int
kmip_encode_get_attribute_list_request_payload(KMIP *ctx, const GetAttributeListRequestPayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->unique_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_get_attribute_list_response_payload(KMIP *ctx, const GetAttributeListResponsePayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);

    if (value->attribute_names) {
	for(int i = 0; i < value->attribute_names_count; ++i)
	{
	    result = kmip_encode_attribute_name(ctx, value->attribute_names[i]);
	    CHECK_RESULT(ctx, result);
	}
    }

    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_destroy_request_payload(KMIP *ctx, const DestroyRequestPayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->unique_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_destroy_response_payload(KMIP *ctx, const DestroyResponsePayload *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_nonce(KMIP *ctx, const Nonce *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_NONCE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_byte_string(ctx, KMIP_TAG_NONCE_ID, value->nonce_id);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_byte_string(ctx, KMIP_TAG_NONCE_VALUE, value->nonce_value);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_username_password_credential(KMIP *ctx, const UsernamePasswordCredential *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_text_string(ctx, KMIP_TAG_USERNAME, value->username);
    CHECK_RESULT(ctx, result);
    
    if(value->password != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_PASSWORD, value->password);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_device_credential(KMIP *ctx, const DeviceCredential *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    if(value->device_serial_number != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_DEVICE_SERIAL_NUMBER, value->device_serial_number);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->password != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_PASSWORD, value->password);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->device_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_DEVICE_IDENTIFIER, value->device_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->network_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_NETWORK_IDENTIFIER, value->network_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->machine_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_MACHINE_IDENTIFIER, value->machine_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->media_identifier != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_MEDIA_IDENTIFIER, value->media_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_attestation_credential(KMIP *ctx, const AttestationCredential *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_nonce(ctx, value->nonce);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_type);
    CHECK_RESULT(ctx, result);
    
    if(value->attestation_measurement != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_ATTESTATION_MEASUREMENT, value->attestation_measurement);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->attestation_assertion != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_ATTESTATION_ASSERTION, value->attestation_assertion);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_credential_value(KMIP *ctx, enum credential_type type, void *value)
{
    int result = 0;
    
    switch(type)
    {
        case KMIP_CRED_USERNAME_AND_PASSWORD:
        result = kmip_encode_username_password_credential(ctx, (UsernamePasswordCredential*)value);
        break;
        
        case KMIP_CRED_DEVICE:
        result = kmip_encode_device_credential(ctx, (DeviceCredential*)value);
        break;
        
        case KMIP_CRED_ATTESTATION:
        result = kmip_encode_attestation_credential(ctx, (AttestationCredential*)value);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    }
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_encode_credential(KMIP *ctx, const Credential *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_CREDENTIAL, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_CREDENTIAL_TYPE, value->credential_type);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_credential_value(ctx, value->credential_type, value->credential_value);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_authentication(KMIP *ctx, const Authentication *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_AUTHENTICATION, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_credential(ctx, value->credential);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_request_header(KMIP *ctx, const RequestHeader *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_HEADER, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_protocol_version(ctx, value->protocol_version);
    CHECK_RESULT(ctx, result);
    
    /* HERE (ph) Stopped working here after bug with 0 vs KMIP_UNSET */
    if(value->maximum_response_size != KMIP_UNSET)
    {
        result = kmip_encode_integer(ctx, KMIP_TAG_MAXIMUM_RESPONSE_SIZE, value->maximum_response_size);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(value->client_correlation_value != NULL)
        {
            result = kmip_encode_text_string(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE, value->client_correlation_value);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->server_correlation_value != NULL)
        {
            result = kmip_encode_text_string(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE, value->server_correlation_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(value->asynchronous_indicator != KMIP_UNSET)
    {
        result = kmip_encode_bool(ctx, KMIP_TAG_ASYNCHRONOUS_INDICATOR, value->asynchronous_indicator);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_2)
    {
        if(value->attestation_capable_indicator != KMIP_UNSET)
        {
            result = kmip_encode_bool(ctx, KMIP_TAG_ATTESTATION_CAPABLE_INDICATOR, value->attestation_capable_indicator);
            CHECK_RESULT(ctx, result);
        }
        
        for(size_t i = 0; i < value->attestation_type_count; i++)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_types[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(value->authentication != NULL)
    {
        result = kmip_encode_authentication(ctx, value->authentication);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->batch_error_continuation_option != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_BATCH_ERROR_CONTINUATION_OPTION, value->batch_error_continuation_option);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->batch_order_option != KMIP_UNSET)
    {
        result = kmip_encode_bool(ctx, KMIP_TAG_BATCH_ORDER_OPTION, value->batch_order_option);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->time_stamp != 0)
    {
        result = kmip_encode_date_time(ctx, KMIP_TAG_TIME_STAMP, value->time_stamp);
        CHECK_RESULT(ctx, result);
    }
    
    result = kmip_encode_integer(ctx, KMIP_TAG_BATCH_COUNT, value->batch_count);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_response_header(KMIP *ctx, const ResponseHeader *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_HEADER, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_protocol_version(ctx, value->protocol_version);
    CHECK_RESULT(ctx, result);
    
    result = kmip_encode_date_time(ctx, KMIP_TAG_TIME_STAMP, value->time_stamp);
    CHECK_RESULT(ctx, result);
    
    if(ctx->version >= KMIP_1_2)
    {
        if(value->nonce != NULL)
        {
            result = kmip_encode_nonce(ctx, value->nonce);
            CHECK_RESULT(ctx, result);
        }

        if(ctx->version >= KMIP_2_0)
        {
            if(value->server_hashed_password != NULL)
            {
                result = kmip_encode_byte_string(ctx, KMIP_TAG_SERVER_HASHED_PASSWORD, value->server_hashed_password);
                CHECK_RESULT(ctx, result);
            }
        }

        for(size_t i = 0; i < value->attestation_type_count; i++)
        {
            result = kmip_encode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_types[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(value->client_correlation_value != NULL)
        {
            result = kmip_encode_text_string(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE, value->client_correlation_value);
            CHECK_RESULT(ctx, result);
        }
        
        if(value->server_correlation_value != NULL)
        {
            result = kmip_encode_text_string(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE, value->server_correlation_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    result = kmip_encode_integer(ctx, KMIP_TAG_BATCH_COUNT, value->batch_count);
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_request_batch_item(KMIP *ctx, const RequestBatchItem *value)
{
    CHECK_ENCODE_ARGS(ctx, value);

    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_BATCH_ITEM, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_OPERATION, value->operation);
    CHECK_RESULT(ctx, result);

    if(ctx->version >= KMIP_2_0)
    {
        if(value->ephemeral != KMIP_UNSET)
        {
            result=kmip_encode_bool(ctx, KMIP_TAG_EPHEMERAL, value->ephemeral);
            CHECK_RESULT(ctx, result);
        }
    }

    if(value->unique_batch_item_id != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID, value->unique_batch_item_id);
        CHECK_RESULT(ctx, result);
    }
    
    switch(value->operation)
    {
        case KMIP_OP_CREATE:
        result = kmip_encode_create_request_payload(ctx, (CreateRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_LOCATE:
        result = kmip_encode_locate_request_payload(ctx, (LocateRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET:
        result = kmip_encode_get_request_payload(ctx, (GetRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTES:
        result = kmip_encode_get_attributes_request_payload(ctx, (GetAttributesRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTE_LIST:
        result = kmip_encode_get_attribute_list_request_payload(ctx, (GetAttributeListRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_DESTROY:
        result = kmip_encode_destroy_request_payload(ctx, (DestroyRequestPayload*)value->request_payload);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_response_batch_item(KMIP *ctx, const ResponseBatchItem *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_BATCH_ITEM, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_enum(ctx, KMIP_TAG_OPERATION, value->operation);
    CHECK_RESULT(ctx, result);
    
    if(value->unique_batch_item_id != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID, value->unique_batch_item_id);
        CHECK_RESULT(ctx, result);
    }
    
    result = kmip_encode_enum(ctx, KMIP_TAG_RESULT_STATUS, value->result_status);
    CHECK_RESULT(ctx, result);
    
    if(value->result_reason != 0)
    {
        result = kmip_encode_enum(ctx, KMIP_TAG_RESULT_REASON, value->result_reason);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->result_message != NULL)
    {
        result = kmip_encode_text_string(ctx, KMIP_TAG_RESULT_MESSAGE, value->result_message);
        CHECK_RESULT(ctx, result);
    }
    
    if(value->asynchronous_correlation_value != NULL)
    {
        result = kmip_encode_byte_string(ctx, KMIP_TAG_ASYNCHRONOUS_CORRELATION_VALUE, value->asynchronous_correlation_value);
        CHECK_RESULT(ctx, result);
    }
    
    switch(value->operation)
    {
        case KMIP_OP_CREATE:
        result = kmip_encode_create_response_payload(ctx, (CreateResponsePayload*)value->response_payload);
        break;
        
        case KMIP_OP_LOCATE:
        result = kmip_encode_locate_response_payload(ctx, (LocateResponsePayload*)value->response_payload);
        break;
        
        case KMIP_OP_GET:
        result = kmip_encode_get_response_payload(ctx, (GetResponsePayload*)value->response_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTES:
        result = kmip_encode_get_attributes_response_payload(ctx, (GetAttributesResponsePayload*)value->response_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTE_LIST:
        result = kmip_encode_get_attribute_list_response_payload(ctx, (GetAttributeListResponsePayload*)value->response_payload);
        break;
        
        case KMIP_OP_DESTROY:
        result = kmip_encode_destroy_response_payload(ctx, (DestroyResponsePayload*)value->response_payload);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    CHECK_RESULT(ctx, result);
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_request_message(KMIP *ctx, const RequestMessage *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_REQUEST_MESSAGE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_request_header(ctx, value->request_header);
    CHECK_RESULT(ctx, result);
    
    for(size_t i = 0; i < value->batch_count; i++)
    {
        result = kmip_encode_request_batch_item(ctx, &value->batch_items[i]);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

int
kmip_encode_response_message(KMIP *ctx, const ResponseMessage *value)
{
    int result = 0;
    result = kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_RESPONSE_MESSAGE, KMIP_TYPE_STRUCTURE));
    CHECK_RESULT(ctx, result);
    
    uint8 *length_index = ctx->index;
    uint8 *value_index = ctx->index += 4;
    
    result = kmip_encode_response_header(ctx, value->response_header);
    CHECK_RESULT(ctx, result);
    
    for(size_t i = 0; i < value->batch_count; i++)
    {
        result = kmip_encode_response_batch_item(ctx, &value->batch_items[i]);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    ctx->index = length_index;
    
    kmip_encode_int32_be(ctx, curr_index - value_index);
    
    ctx->index = curr_index;
    
    return(KMIP_OK);
}

/*
Decoding Functions
*/

int
kmip_decode_int8_be(KMIP *ctx, void *value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int8));
    
    int8 *i = (int8*)value;
    
    *i = 0;
    *i = *ctx->index++;
    
    return(KMIP_OK);
}

int
kmip_decode_int32_be(KMIP *ctx, void *value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int32));
    
    int32 *i = (int32*)value;
    
    *i = 0;
    *i |= ((int32)*ctx->index++ << 24);
    *i |= ((int32)*ctx->index++ << 16);
    *i |= ((int32)*ctx->index++ << 8);
    *i |= ((int32)*ctx->index++ << 0);
    
    return(KMIP_OK);
}

int
kmip_decode_int64_be(KMIP *ctx, void *value)
{
    CHECK_BUFFER_FULL(ctx, sizeof(int64));
    
    int64 *i = (int64*)value;
    
    *i = 0;
    *i |= ((int64)*ctx->index++ << 56);
    *i |= ((int64)*ctx->index++ << 48);
    *i |= ((int64)*ctx->index++ << 40);
    *i |= ((int64)*ctx->index++ << 32);
    *i |= ((int64)*ctx->index++ << 24);
    *i |= ((int64)*ctx->index++ << 16);
    *i |= ((int64)*ctx->index++ << 8);
    *i |= ((int64)*ctx->index++ << 0);
    
    return(KMIP_OK);
}

int
kmip_decode_integer(KMIP *ctx, enum tag t, int32 *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 padding = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_INTEGER);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 4);
    
    kmip_decode_int32_be(ctx, value);
    
    kmip_decode_int32_be(ctx, &padding);
    CHECK_PADDING(ctx, padding);
    
    return(KMIP_OK);
}

int
kmip_decode_long(KMIP *ctx, enum tag t, int64 *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_LONG_INTEGER);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 8);
    
    kmip_decode_int64_be(ctx, value);
    
    return(KMIP_OK);
}

int
kmip_decode_enum(KMIP *ctx, enum tag t, void *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 *v = (int32*)value;
    int32 padding = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_ENUMERATION);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 4);
    
    kmip_decode_int32_be(ctx, v);
    
    kmip_decode_int32_be(ctx, &padding);
    CHECK_PADDING(ctx, padding);
    
    return(KMIP_OK);
}

int
kmip_decode_bool(KMIP *ctx, enum tag t, bool32 *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 padding = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_BOOLEAN);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 8);
    
    kmip_decode_int32_be(ctx, &padding);
    CHECK_PADDING(ctx, padding);
    
    kmip_decode_int32_be(ctx, value);
    CHECK_BOOLEAN(ctx, *value);
    
    return(KMIP_OK);
}

int
kmip_decode_text_string(KMIP *ctx, enum tag t, TextString *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 padding = 0;
    int8 spacer = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_TEXT_STRING);
    
    kmip_decode_int32_be(ctx, &length);
    padding = (8 - (length % 8)) % 8;
    CHECK_BUFFER_FULL(ctx, (uint32)(length + padding));
    
    value->value = ctx->calloc_func(ctx->state, 1, length);
    value->size = length;
    
    char *index = value->value;
    
    for(int32 i = 0; i < length; i++)
    {
        kmip_decode_int8_be(ctx, (int8*)index++);
    }
    for(int32 i = 0; i < padding; i++)
    {
        kmip_decode_int8_be(ctx, &spacer);
        CHECK_PADDING(ctx, spacer);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_byte_string(KMIP *ctx, enum tag t, ByteString *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 padding = 0;
    int8 spacer = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_BYTE_STRING);
    
    kmip_decode_int32_be(ctx, &length);
    padding = (8 - (length % 8)) % 8;
    CHECK_BUFFER_FULL(ctx, (uint32)(length + padding));
    
    value->value = ctx->calloc_func(ctx->state, 1, length);
    value->size = length;
    
    uint8 *index = value->value;
    
    for(int32 i = 0; i < length; i++)
    {
        kmip_decode_int8_be(ctx, index++);
    }
    for(int32 i = 0; i < padding; i++)
    {
        kmip_decode_int8_be(ctx, &spacer);
        CHECK_PADDING(ctx, spacer);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_date_time(KMIP *ctx, enum tag t, uint64 *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_DATE_TIME);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 8);
    
    kmip_decode_int64_be(ctx, value);
    
    return(KMIP_OK);
}

int
kmip_decode_digest(KMIP *ctx, Digest *value)
{
    CHECK_BUFFER_FULL(ctx, 8);

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;

    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_DIGEST, KMIP_TYPE_STRUCTURE);

    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    result = kmip_decode_enum(ctx, KMIP_TAG_HASHING_ALGORITHM, &value->hashing_algorithm);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_HASHING_ALGORITHM, value->hashing_algorithm);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_DIGEST_VALUE))
    {
	value->digest_value = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
	CHECK_NEW_MEMORY(ctx, value->digest_value, sizeof(ByteString), "Digest byte string");
	result = kmip_decode_byte_string(ctx, KMIP_TAG_DIGEST_VALUE, value->digest_value);
	CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_FORMAT_TYPE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, &value->key_format_type);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
    }

    return(KMIP_OK);
}

int
kmip_decode_interval(KMIP *ctx, enum tag t, uint32 *value)
{
    CHECK_BUFFER_FULL(ctx, 16);
    
    int32 tag_type = 0;
    int32 length = 0;
    int32 padding = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, t, KMIP_TYPE_INTERVAL);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 4);
    
    kmip_decode_int32_be(ctx, value);
    
    kmip_decode_int32_be(ctx, &padding);
    CHECK_PADDING(ctx, padding);
    
    return(KMIP_OK);
}

int
kmip_decode_name(KMIP *ctx, Name *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_NAME, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_NAME_VALUE, value->value);
    CHECK_RESULT(ctx, result);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_NAME_TYPE, (int32*)&value->type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_NAME_TYPE, value->type);
    
    return(KMIP_OK);
}

int
kmip_decode_attribute_name(KMIP *ctx, enum attribute_type *value)
{
    int result = 0;
    enum tag t = KMIP_TAG_ATTRIBUTE_NAME;
    TextString n = {0};
    
    result = kmip_decode_text_string(ctx, t, &n);
    CHECK_RESULT(ctx, result);
    
    if((n.size == 17) && (strncmp(n.value, "Unique Identifier", 17) == 0))
    {
        *value = KMIP_ATTR_UNIQUE_IDENTIFIER;
    }
    else if((n.size == 4) && (strncmp(n.value, "Name", 4) == 0))
    {
        *value = KMIP_ATTR_NAME;
    }
    else if((n.size == 11) && (strncmp(n.value, "Object Type", 11) == 0))
    {
        *value = KMIP_ATTR_OBJECT_TYPE;
    }
    else if((n.size == 23) && (strncmp(n.value, "Cryptographic Algorithm", 23) == 0))
    {
        *value = KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM;
    }
    else if((n.size == 20) && (strncmp(n.value, "Cryptographic Length", 20) == 0))
    {
        *value = KMIP_ATTR_CRYPTOGRAPHIC_LENGTH;
    }
    else if((n.size == 24) && (strncmp(n.value, "Cryptographic Parameters", 24) == 0))
    {
        *value = KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS;
    }
    else if((n.size == 31) && (strncmp(n.value, "Cryptographic Domain Parameters", 31) == 0))
    {
        *value = KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS;
    }
    else if((n.size == 16) && (strncmp(n.value, "Certificate Type", 16) == 0))
    {
        *value = KMIP_ATTR_CERTIFICATE_TYPE;
    }
    else if((n.size == 18) && (strncmp(n.value, "Certificate Length", 18) == 0))
    {
        *value = KMIP_ATTR_CERTIFICATE_LENGTH;
    }
    else if((n.size == 28) && (strncmp(n.value, "X.509 Certificate Identifier", 28) == 0))
    {
        *value = KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER;
    }
    else if((n.size == 25) && (strncmp(n.value, "X.509 Certificate Subject", 25) == 0))
    {
        *value = KMIP_ATTR_X509_CERTIFICATE_SUBJECT;
    }
    else if((n.size == 24) && (strncmp(n.value, "X.509 Certificate Issuer", 24) == 0))
    {
        *value = KMIP_ATTR_X509_CERTIFICATE_ISSUER;
    }
    else if((n.size == 22) && (strncmp(n.value, "Certificate Identifier", 22) == 0))
    {
        *value = KMIP_ATTR_CERTIFICATE_IDENTIFIER;
    }
    else if((n.size == 19) && (strncmp(n.value, "Certificate Subject", 19) == 0))
    {
        *value = KMIP_ATTR_CERTIFICATE_SUBJECT;
    }
    else if((n.size == 18) && (strncmp(n.value, "Certificate Issuer", 18) == 0))
    {
        *value = KMIP_ATTR_CERTIFICATE_ISSUER;
    }
    else if((n.size == 27) && (strncmp(n.value, "Digital Signature Algorithm", 27) == 0))
    {
        *value = KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM;
    }
    else if((n.size == 6) && (strncmp(n.value, "Digest", 6) == 0))
    {
        *value = KMIP_ATTR_DIGEST;
    }
    else if((n.size == 21) && (strncmp(n.value, "Operation Policy Name", 21) == 0))
    {
        *value = KMIP_ATTR_OPERATION_POLICY_NAME;
    }
    else if((n.size == 24) && (strncmp(n.value, "Cryptographic Usage Mask", 24) == 0))
    {
        *value = KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK;
    }
    else if((n.size == 10) && (strncmp(n.value, "Lease Time", 10) == 0))
    {
        *value = KMIP_ATTR_LEASE_TIME;
    }
    else if((n.size == 12) && (strncmp(n.value, "Usage Limits", 12) == 0))
    {
        *value = KMIP_ATTR_USAGE_LIMITS;
    }
    else if((n.size == 5) && (strncmp(n.value, "State", 5) == 0))
    {
        *value = KMIP_ATTR_STATE;
    }
    else if((n.size == 12) && (strncmp(n.value, "Initial Date", 12) == 0))
    {
        *value = KMIP_ATTR_INITIAL_DATE;
    }
    else if((n.size == 15) && (strncmp(n.value, "Activation Date", 15) == 0))
    {
        *value = KMIP_ATTR_ACTIVATION_DATE;
    }
    else if((n.size == 18) && (strncmp(n.value, "Process Start Date", 18) == 0))
    {
        *value = KMIP_ATTR_PROCESS_START_DATE;
    }
    else if((n.size == 17) && (strncmp(n.value, "Protect Stop Date", 17) == 0))
    {
        *value = KMIP_ATTR_PROTECT_STOP_DATE;
    }
    else if((n.size == 17) && (strncmp(n.value, "Deactivation Date", 17) == 0))
    {
        *value = KMIP_ATTR_DEACTIVATION_DATE;
    }
    else if((n.size == 12) && (strncmp(n.value, "Destroy Date", 12) == 0))
    {
        *value = KMIP_ATTR_DESTROY_DATE;
    }
    else if((n.size == 26) && (strncmp(n.value, "Compromise Occurrence Date", 26) == 0))
    {
        *value = KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE;
    }
    else if((n.size == 15) && (strncmp(n.value, "Compromise Date", 15) == 0))
    {
        *value = KMIP_ATTR_COMPROMISE_DATE;
    }
    else if((n.size == 17) && (strncmp(n.value, "Revocation Reason", 17) == 0))
    {
        *value = KMIP_ATTR_REVOCATION_REASON;
    }
    else if((n.size == 12) && (strncmp(n.value, "Archive Date", 12) == 0))
    {
        *value = KMIP_ATTR_ARCHIVE_DATE;
    }
    else if((n.size == 12) && (strncmp(n.value, "Object Group", 12) == 0))
    {
        *value = KMIP_ATTR_OBJECT_GROUP;
    }
    else if((n.size == 5) && (strncmp(n.value, "Fresh", 5) == 0))
    {
        *value = KMIP_ATTR_FRESH;
    }
    else if((n.size == 4) && (strncmp(n.value, "Link", 4) == 0))
    {
        *value = KMIP_ATTR_LINK;
    }
    else if((n.size == 32) && (strncmp(n.value, "Application Specific Information", 32) == 0))
    {
        *value = KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION;
    }
    else if((n.size == 19) && (strncmp(n.value, "Contact Information", 19) == 0))
    {
        *value = KMIP_ATTR_CONTACT_INFORMATION;
    }
    else if((n.size == 16) && (strncmp(n.value, "Last Change Date", 16) == 0))
    {
        *value = KMIP_ATTR_LAST_CHANGE_DATE;
    }
    else if((n.size == 16) && (strncmp(n.value, "Alternative Name", 16) == 0))
    {
        *value = KMIP_ATTR_ALTERNATIVE_NAME;
    }
    else if((n.size == 17) && (strncmp(n.value, "Key Value Present", 17) == 0))
    {
        *value = KMIP_ATTR_KEY_VALUE_PRESENT;
    }
    else if((n.size == 18) && (strncmp(n.value, "Key Value Location", 18) == 0))
    {
        *value = KMIP_ATTR_KEY_VALUE_LOCATION;
    }
    else if((n.size == 22) && (strncmp(n.value, "Original Creation Date", 22) == 0))
    {
        *value = KMIP_ATTR_ORIGINAL_CREATION_DATE;
    }
    else if((n.size == 23) && (strncmp(n.value, "Random Number Generator", 23) == 0))
    {
        *value = KMIP_ATTR_RANDOM_NUMBER_GENERATOR;
    }
    else if((n.size == 21) && (strncmp(n.value, "PKCS#12 Friendly Name", 21) == 0))
    {
        *value = KMIP_ATTR_PKCS_12_FRIENDLY_NAME;
    }
    else if((n.size == 11) && (strncmp(n.value, "Description", 11) == 0))
    {
        *value = KMIP_ATTR_DESCRIPTION;
    }
    else if((n.size == 7) && (strncmp(n.value, "Comment", 7) == 0))
    {
        *value = KMIP_ATTR_COMMENT;
    }
    else if((n.size == 9) && (strncmp(n.value, "Sensitive", 9) == 0))
    {
        *value = KMIP_ATTR_SENSITIVE;
    }
    else if((n.size == 16) && (strncmp(n.value, "Always Sensitive", 16) == 0))
    {
        *value = KMIP_ATTR_ALWAYS_SENSITIVE;
    }
    else if((n.size == 11) && (strncmp(n.value, "Extractable", 11) == 0))
    {
        *value = KMIP_ATTR_EXTRACTABLE;
    }
    else if((n.size == 17) && (strncmp(n.value, "Never Extractable", 17) == 0))
    {
        *value = KMIP_ATTR_NEVER_EXTRACTABLE;
    }
    else if((n.size == 15) && (strncmp(n.value, "Key Format Type", 15) == 0))
    {
        *value = KMIP_ATTR_KEY_FORMAT_TYPE;
    }

    /* TODO (ph) Add all remaining attributes here. */
    else
    {
        kmip_push_error_frame(ctx, __func__, __LINE__);
        kmip_free_text_string(ctx, &n);
        return(KMIP_ERROR_ATTR_UNSUPPORTED);
    }
    
    kmip_free_text_string(ctx, &n);
    return(KMIP_OK);
}

int
kmip_decode_protection_storage_masks(KMIP *ctx, ProtectionStorageMasks *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);
    CHECK_BUFFER_FULL(ctx, 8);

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;

    result = kmip_decode_int32_be(ctx, &tag_type);
    CHECK_RESULT(ctx, result);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_PROTECTION_STORAGE_MASKS, KMIP_TYPE_STRUCTURE);

    result = kmip_decode_int32_be(ctx, &length);
    CHECK_RESULT(ctx, result);
    CHECK_BUFFER_FULL(ctx, length);

    value->masks = ctx->calloc_func(ctx->state, 1, sizeof(LinkedList));
    CHECK_NEW_MEMORY(ctx, value->masks, sizeof(LinkedList), "LinkedList");

    uint32 tag = kmip_peek_tag(ctx);
    while(tag == KMIP_TAG_PROTECTION_STORAGE_MASK)
    {
        LinkedListItem *item = ctx->calloc_func(ctx->state, 1, sizeof(LinkedListItem));
        CHECK_NEW_MEMORY(ctx, item, sizeof(LinkedListItem), "LinkedListItem");
        kmip_linked_list_enqueue(value->masks, item);

        item->data = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, item->data, sizeof(int32), "Protection Storage Mask");

        result = kmip_decode_integer(ctx, KMIP_TAG_PROTECTION_STORAGE_MASK, (int32 *)item->data);
        CHECK_RESULT(ctx, result);

        tag = kmip_peek_tag(ctx);
    }

    return(KMIP_OK);
}

int
kmip_decode_attribute_v1(KMIP *ctx, Attribute *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    kmip_init_attribute(value);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_ATTRIBUTE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_attribute_name(ctx, &value->type);
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ATTRIBUTE_INDEX))
    {
        result = kmip_decode_integer(ctx, KMIP_TAG_ATTRIBUTE_INDEX, &value->index);
        CHECK_RESULT(ctx, result);
    }
    
    uint8 *curr_index = ctx->index;
    uint8 *tag_index = ctx->index;
    enum tag t = KMIP_TAG_ATTRIBUTE_VALUE;
    
    switch(value->type)
    {
        case KMIP_ATTR_UNIQUE_IDENTIFIER:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "UniqueIdentifier text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_ATTR_NAME:
        /* TODO (ph) Like encoding, this is messy. Better solution? */
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(Name));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(Name), "Name structure");
        
        if(kmip_is_tag_type_next(ctx, KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE))
        {
            /* NOTE (ph) Decoding name structures will fail if the name tag */
            /* is not present in the encoding. Temporarily swap the tags, */
            /* decode the name structure, and then swap the tags back to */
            /* preserve the encoding. The tag/type check above guarantees */
            /* space exists for this to succeed. */
            kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_NAME, KMIP_TYPE_STRUCTURE));
            ctx->index = tag_index;
            
            result = kmip_decode_name(ctx, (Name*)value->value);
            
            curr_index = ctx->index;
            ctx->index = tag_index;
            
            kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE));
            ctx->index = curr_index;
        }
        else
        {
            result = KMIP_TAG_MISMATCH;
        }
        
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_ATTR_OBJECT_TYPE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "ObjectType enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_OBJECT_TYPE, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CryptographicAlgorithm enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_LENGTH:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CryptographicLength integer");
        result = kmip_decode_integer(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_CRYPTOGRAPHIC_PARAMETERS:	XXX how to hack struct?
        // case KMIP_ATTR_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:	XXX how to hack struct?

        case KMIP_ATTR_CERTIFICATE_TYPE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CertificateType enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_CERTIFICATE_TYPE, *(int32 *)value->value);
        break;

        case KMIP_ATTR_CERTIFICATE_LENGTH:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CertificateLength integer");
        result = kmip_decode_integer(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_X509_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_X509_CERTIFICATE_ISSUER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_ATTR_CERTIFICATE_ISSUER:	XXX how to hack struct?

        case KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "DigitalSignatureAlgorithm enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_DIGEST:
	// same issues as Name above, all the same uglies.
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(Digest));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(Digest), "Digest structure");
        if(kmip_is_tag_type_next(ctx, KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE))
        {
            kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_DIGEST, KMIP_TYPE_STRUCTURE));
            ctx->index = tag_index;
            
            result = kmip_decode_digest(ctx, (Digest*)value->value);
            
            curr_index = ctx->index;
            ctx->index = tag_index;
            
            kmip_encode_int32_be(ctx, TAG_TYPE(KMIP_TAG_ATTRIBUTE_VALUE, KMIP_TYPE_STRUCTURE));
            ctx->index = curr_index;
	} else {
            result = KMIP_TAG_MISMATCH;
	}
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_ATTR_OPERATION_POLICY_NAME:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "OperationPolicyName text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CryptographicUsageMask integer");
        result = kmip_decode_integer(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_LEASE_TIME:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(uint32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(uint32), "LeaseTime interval");
        result = kmip_decode_interval(ctx, t, (uint32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_USAGE_LIMITS: XXX how to hack struct?
        
        case KMIP_ATTR_STATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "State enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_STATE, *(int32 *)value->value);
        break;
        
        case KMIP_ATTR_INITIAL_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "InitialDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_ACTIVATION_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ActivationDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_PROCESS_START_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ProcessStartDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_PROTECT_STOP_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ProtectStopDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_DEACTIVATION_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "DeactivationDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_DESTROY_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "DestroyDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "CompromiseOccurrenceDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_COMPROMISE_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "CompromiseDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_REVOCATION_REASON:	XXX how to hack struct?

        case KMIP_ATTR_ARCHIVE_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ArchiveDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_OBJECT_GROUP:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "ObjectGroup text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_FRESH:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Fresh boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_LINK:	XXX how to hack struct?
        // case KMIP_ATTR_APPLICATION_SPECIFIC_INFORMATION:	XXX how to hack struct?
        // case KMIP_ATTR_CONTACT_INFORMATION:	XXX how to hack struct?

        case KMIP_ATTR_LAST_CHANGE_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "LastChangeDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_CUSTOM_ATTRIBUTE:	XXX how to hack custom?
        // case KMIP_ATTR_ALTERNATIVE_NAME:	XXX how to hack struct?

        case KMIP_ATTR_KEY_VALUE_PRESENT:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "KeyValuePresent boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        // case KMIP_ATTR_KEY_VALUE_LOCATION:	XXX how to hack struct?

        case KMIP_ATTR_ORIGINAL_CREATION_DATE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "OriginalCreationDate datetime");
        result = kmip_decode_date_time(ctx, t, (uint64 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_RANDOM_NUMBER_GENERATOR:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "RandomNumberGenerator text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_PKCS_12_FRIENDLY_NAME:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Pkcs12FriendlyName text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_DESCRIPTION:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Description text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_COMMENT:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Comment text string");
        result = kmip_decode_text_string(ctx, t, (TextString*)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_SENSITIVE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Sensitive boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_ALWAYS_SENSITIVE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "AlwaysSensitive boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_EXTRACTABLE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Extractable boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_NEVER_EXTRACTABLE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "NeverExtractable boolean");
        result = kmip_decode_bool(ctx, t, (bool32 *)value->value);
        CHECK_RESULT(ctx, result);
        break;

        case KMIP_ATTR_KEY_FORMAT_TYPE:
        value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
        CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "KeyFormatType enumeration");
        result = kmip_decode_enum(ctx, t, (int32 *)value->value);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_FORMAT_TYPE, *(int32 *)value->value);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_ERROR_ATTR_UNSUPPORTED);
        break;
    };
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_attribute_v2(KMIP *ctx, Attribute *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);

    kmip_init_attribute(value);

    int result = 0;
    uint32 tag = kmip_peek_tag(ctx);
    if(tag == 0)
    {
        /* Record an error for an underfull buffer here and return. */
    }

    CHECK_RESULT(ctx, result);

    switch(tag)
    {
        case KMIP_TAG_UNIQUE_IDENTIFIER:
        {
            value->type = KMIP_ATTR_UNIQUE_IDENTIFIER;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "UniqueIdentifier text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_NAME:
        {
            value->type = KMIP_ATTR_NAME;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(Name));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(Name), "Name structure");

            result = kmip_decode_name(ctx, (Name *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_OBJECT_TYPE:
        {
            value->type = KMIP_ATTR_OBJECT_TYPE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "ObjectType enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_OBJECT_TYPE, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_OBJECT_TYPE, *(int32 *)value->value);
        }
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM:
        {
            value->type = KMIP_ATTR_CRYPTOGRAPHIC_ALGORITHM;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CrypographicAlgorithm enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, *(int32 *)value->value);
        }
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_LENGTH:
        {
            value->type = KMIP_ATTR_CRYPTOGRAPHIC_LENGTH;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CryptographicLength integer");

            result = kmip_decode_integer(ctx, KMIP_TAG_CRYPTOGRAPHIC_LENGTH, (int32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS:	XXX how to hack struct?
        // case KMIP_TAG_CRYPTOGRAPHIC_DOMAIN_PARAMETERS:	XXX how to hack struct?

        case KMIP_TAG_CERTIFICATE_TYPE:
        {
            value->type = KMIP_ATTR_CERTIFICATE_TYPE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CertificateType enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_CERTIFICATE_TYPE, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_CERTIFICATE_TYPE, *(int32 *)value->value);
        }
        break;

        case KMIP_TAG_CERTIFICATE_LENGTH:
        {
            value->type = KMIP_ATTR_CERTIFICATE_LENGTH;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CertificateLength integer");

            result = kmip_decode_integer(ctx, KMIP_TAG_CERTIFICATE_LENGTH, (int32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_X509_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_TAG_X509_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_TAG_X509_CERTIFICATE_ISSUER:	XXX how to hack struct?
        // case KMIP_TAG_CERTIFICATE_IDENTIFIER:	XXX how to hack struct?
        // case KMIP_TAG_CERTIFICATE_SUBJECT:	XXX how to hack struct?
        // case KMIP_TAG_CERTIFICATE_ISSUER:	XXX how to hack struct?

        case KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM:
        {
            value->type = KMIP_ATTR_DIGITAL_SIGNATURE_ALGORITHM;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "DigitalSignatureAlgorithm enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, *(int32 *)value->value);
        }
        break;

        case KMIP_TAG_DIGEST:
        {
            value->type = KMIP_ATTR_DIGEST;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(Digest));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(Digest), "Digest structure");

            result = kmip_decode_digest(ctx, (Digest *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_OPERATION_POLICY_NAME:
        {
            value->type = KMIP_ATTR_OPERATION_POLICY_NAME;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "OperationPolicyName text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_OPERATION_POLICY_NAME, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK:
        {
            value->type = KMIP_ATTR_CRYPTOGRAPHIC_USAGE_MASK;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "CryptographicUsageMask integer");

            result = kmip_decode_integer(ctx, KMIP_TAG_CRYPTOGRAPHIC_USAGE_MASK, (int32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_LEASE_TIME:
        {
            value->type = KMIP_ATTR_LEASE_TIME;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(uint32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(uint32), "LeaseTime interval");

            result = kmip_decode_interval(ctx, KMIP_TAG_LEASE_TIME, (uint32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_USAGE_LIMITS:  XXX how to hack struct?

        case KMIP_TAG_STATE:
        {
            value->type = KMIP_ATTR_STATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "State enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_STATE, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_STATE, *(int32 *)value->value);
        }
        break;

        case KMIP_TAG_INITIAL_DATE:
        {
            value->type = KMIP_ATTR_INITIAL_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "InitialDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_INITIAL_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_ACTIVATION_DATE:
        {
            value->type = KMIP_ATTR_ACTIVATION_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ActivationDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_ACTIVATION_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_PROCESS_START_DATE:
        {
            value->type = KMIP_ATTR_PROCESS_START_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ProcessStartDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_PROCESS_START_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_PROTECT_STOP_DATE:
        {
            value->type = KMIP_ATTR_PROTECT_STOP_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ProtectStopDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_PROTECT_STOP_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_DEACTIVATION_DATE:
        {
            value->type = KMIP_ATTR_DEACTIVATION_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "DeactivationDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_DEACTIVATION_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_DESTROY_DATE:
        {
            value->type = KMIP_ATTR_DESTROY_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "DestroyDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_DESTROY_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_COMPROMISE_OCCURRENCE_DATE:
        {
            value->type = KMIP_ATTR_COMPROMISE_OCCURRENCE_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "CompromiseOccurrenceDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_COMPROMISE_OCCURRENCE_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_COMPROMISE_DATE:
        {
            value->type = KMIP_ATTR_COMPROMISE_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "CompromiseDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_COMPROMISE_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_REVOCATION_REASON:	XXX how to hack struct?

        case KMIP_TAG_ARCHIVE_DATE:
        {
            value->type = KMIP_ATTR_ARCHIVE_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "ArchiveDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_ARCHIVE_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_OBJECT_GROUP:
        {
            value->type = KMIP_ATTR_OBJECT_GROUP;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "ObjectGroup text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_OBJECT_GROUP, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_FRESH:
        {
            value->type = KMIP_ATTR_FRESH;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Fresh boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_FRESH, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_LINK:	XXX how to hack struct?
        // case KMIP_TAG_APPLICATION_SPECIFIC_INFORMATION:	XXX how to hack struct?
        // case KMIP_TAG_CONTACT_INFORMATION:	XXX how to hack struct?

        case KMIP_TAG_LAST_CHANGE_DATE:
        {
            value->type = KMIP_ATTR_LAST_CHANGE_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "LastChangeDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_LAST_CHANGE_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_CUSTOM_ATTRIBUTE:	XXX how to hack custom?
        // case KMIP_TAG_ALTERNATIVE_NAME:	XXX how to hack struct?

        case KMIP_TAG_KEY_VALUE_PRESENT:
        {
            value->type = KMIP_ATTR_KEY_VALUE_PRESENT;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "KeyValuePresent boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_KEY_VALUE_PRESENT, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        // case KMIP_TAG_KEY_VALUE_LOCATION:	XXX how to hack struct?

        case KMIP_TAG_ORIGINAL_CREATION_DATE:
        {
            value->type = KMIP_ATTR_ORIGINAL_CREATION_DATE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int64));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int64), "OriginalCreationDate integer");

            result = kmip_decode_date_time(ctx, KMIP_TAG_ORIGINAL_CREATION_DATE, (uint64 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_RANDOM_NUMBER_GENERATOR:
        {
            value->type = KMIP_ATTR_RANDOM_NUMBER_GENERATOR;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "RandomNumberGenerator text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_RANDOM_NUMBER_GENERATOR, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_PKCS_12_FRIENDLY_NAME:
        {
            value->type = KMIP_ATTR_PKCS_12_FRIENDLY_NAME;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Pkcs12FriendlyName text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_PKCS_12_FRIENDLY_NAME, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_DESCRIPTION:
        {
            value->type = KMIP_ATTR_DESCRIPTION;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Description text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_DESCRIPTION, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_COMMENT:
        {
            value->type = KMIP_ATTR_COMMENT;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(TextString), "Comment text string");

            result = kmip_decode_text_string(ctx, KMIP_TAG_COMMENT, (TextString *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_SENSITIVE:
        {
            value->type = KMIP_ATTR_SENSITIVE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Sensitive boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_SENSITIVE, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_ALWAYS_SENSITIVE:
        {
            value->type = KMIP_ATTR_ALWAYS_SENSITIVE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "AlwaysSensitive boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_ALWAYS_SENSITIVE, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_EXTRACTABLE:
        {
            value->type = KMIP_ATTR_EXTRACTABLE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "Extractable boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_EXTRACTABLE, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_NEVER_EXTRACTABLE:
        {
            value->type = KMIP_ATTR_NEVER_EXTRACTABLE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(bool32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(bool32), "NeverExtractable boolean");

            result = kmip_decode_bool(ctx, KMIP_TAG_NEVER_EXTRACTABLE, (bool32 *)value->value);
            CHECK_RESULT(ctx, result);
        }
        break;

        case KMIP_TAG_KEY_FORMAT_TYPE:
        {
            value->type = KMIP_ATTR_KEY_FORMAT_TYPE;
            value->value = ctx->calloc_func(ctx->state, 1, sizeof(int32));
            CHECK_NEW_MEMORY(ctx, value->value, sizeof(int32), "KeyFormatType enumeration");

            result = kmip_decode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, (int32 *)value->value);
            CHECK_RESULT(ctx, result);

            CHECK_ENUM(ctx, KMIP_TAG_KEY_FORMAT_TYPE, *(int32 *)value->value);
        }
        break;

        default:
        {
            kmip_push_error_frame(ctx, __func__, __LINE__);
            return(KMIP_ERROR_ATTR_UNSUPPORTED);
        }
        break;
    };

    return(KMIP_OK);
}

int
kmip_decode_attribute(KMIP *ctx, Attribute *value)
{
    CHECK_DECODE_ARGS(ctx, value);

    if(ctx->version < KMIP_2_0)
    {
        return(kmip_decode_attribute_v1(ctx, value));
    }
    else
    {
        return(kmip_decode_attribute_v2(ctx, value));
    }
}

int
kmip_decode_attributes(KMIP *ctx, Attributes *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);
    CHECK_BUFFER_FULL(ctx, 8);

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;

    result = kmip_decode_int32_be(ctx, &tag_type);
    CHECK_RESULT(ctx, result);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_ATTRIBUTES, KMIP_TYPE_STRUCTURE);

    result = kmip_decode_int32_be(ctx, &length);
    CHECK_RESULT(ctx, result);
    CHECK_BUFFER_FULL(ctx, length);

    value->attribute_list = ctx->calloc_func(ctx->state, 1, sizeof(LinkedList));
    CHECK_NEW_MEMORY(ctx, value->attribute_list, sizeof(LinkedList), "LinkedList");

    uint32 tag = kmip_peek_tag(ctx);
    while(tag != 0 && kmip_is_attribute_tag(tag))
    {
        LinkedListItem *item = ctx->calloc_func(ctx->state, 1, sizeof(LinkedListItem));
        CHECK_NEW_MEMORY(ctx, item, sizeof(LinkedListItem), "LinkedListItem");
        kmip_linked_list_enqueue(value->attribute_list, item);

        item->data = ctx->calloc_func(ctx->state, 1, sizeof(Attribute));
        CHECK_NEW_MEMORY(ctx, item->data, sizeof(Attribute), "Attribute");

        result = kmip_decode_attribute(ctx, (Attribute *)item->data);
        CHECK_RESULT(ctx, result);

        tag = kmip_peek_tag(ctx);
    }

    return(KMIP_OK);
}

int
kmip_decode_attributes_2(KMIP *ctx, Attribute **valuep, int *countp)
{
    CHECK_KMIP_VERSION(ctx, KMIP_2_0);
    CHECK_BUFFER_FULL(ctx, 8);
    uint8 *backup, *lim;
    int i, count;
    Attribute *attribute_list;

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0, sublen;

    *valuep = 0;
    *countp = 0;
    result = kmip_decode_int32_be(ctx, &tag_type);
    CHECK_RESULT(ctx, result);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_ATTRIBUTES, KMIP_TYPE_STRUCTURE);

    result = kmip_decode_int32_be(ctx, &length);
    CHECK_RESULT(ctx, result);
    CHECK_BUFFER_FULL(ctx, length);

    backup = ctx->index;
    lim = backup + length;
    count = 0;
    while (ctx->index < lim-8)
    {
	ctx->index += 4;
	result = kmip_decode_int32_be(ctx, &sublen);
	if (result != KMIP_OK)
	{
	    break;
	}
	sublen += CALCULATE_PADDING(length);
	if (ctx->index + sublen > lim)
	{
	    break;
	}
	++count;
    }
    ctx->index = backup;
    attribute_list = ctx->calloc_func(ctx->state, count, sizeof(Attribute*));
    CHECK_NEW_MEMORY(ctx, attribute_list, count*sizeof(Attribute*), "Attribute List");
    *valuep = attribute_list;
    *countp = count;
    for (i = 0; i < count; ++i)
    {
        result = kmip_decode_attribute(ctx, attribute_list + i);
        CHECK_RESULT(ctx, result);
    }

    return(KMIP_OK);
}

int
kmip_decode_template_attribute(KMIP *ctx, TemplateAttribute *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_TEMPLATE_ATTRIBUTE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->name_count = kmip_get_num_items_next(ctx, KMIP_TAG_NAME);
    if(value->name_count > 0)
    {
        value->names = ctx->calloc_func(ctx->state, value->name_count, sizeof(Name));
        CHECK_NEW_MEMORY(ctx, value->names, value->name_count * sizeof(Name), "sequence of Name structures");
        
        for(size_t i = 0; i < value->name_count; i++)
        {
            result = kmip_decode_name(ctx, &value->names[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    value->attribute_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE);
    if(value->attribute_count > 0)
    {
        value->attributes = ctx->calloc_func(ctx->state, value->attribute_count, sizeof(Attribute));
        CHECK_NEW_MEMORY(ctx, value->attributes, value->attribute_count * sizeof(Attribute), "sequence of Attribute structures");
        
        for(size_t i = 0; i < value->attribute_count; i++)
        {
            result = kmip_decode_attribute(ctx, &value->attributes[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_protocol_version(KMIP *ctx, ProtocolVersion *value)
{
    CHECK_BUFFER_FULL(ctx, 40);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_PROTOCOL_VERSION, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_LENGTH(ctx, length, 32);
    
    result = kmip_decode_integer(ctx, KMIP_TAG_PROTOCOL_VERSION_MAJOR, &value->major);
    CHECK_RESULT(ctx, result);
    
    result = kmip_decode_integer(ctx, KMIP_TAG_PROTOCOL_VERSION_MINOR, &value->minor);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_transparent_symmetric_key(KMIP *ctx, TransparentSymmetricKey *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_KEY_MATERIAL, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->key = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
    CHECK_NEW_MEMORY(ctx, value->key, sizeof(ByteString), "Key byte string");
    
    result = kmip_decode_byte_string(ctx, KMIP_TAG_KEY, value->key);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_key_material(KMIP *ctx, enum key_format_type format, void **value)
{
    int result = 0;
    
    switch(format)
    {
        case KMIP_KEYFORMAT_RAW:
        case KMIP_KEYFORMAT_OPAQUE:
        case KMIP_KEYFORMAT_PKCS1:
        case KMIP_KEYFORMAT_PKCS8:
        case KMIP_KEYFORMAT_X509:
        case KMIP_KEYFORMAT_EC_PRIVATE_KEY:
        *value = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, *value, sizeof(ByteString), "KeyMaterial byte string");
        result = kmip_decode_byte_string(ctx, KMIP_TAG_KEY_MATERIAL, (ByteString*)*value);
        CHECK_RESULT(ctx, result);
        return(KMIP_OK);
        break;
        
        default:
        break;
    };
    
    switch(format)
    {
        case KMIP_KEYFORMAT_TRANS_SYMMETRIC_KEY:
        *value = ctx->calloc_func(ctx->state, 1, sizeof(TransparentSymmetricKey));
        CHECK_NEW_MEMORY(ctx, *value, sizeof(TransparentSymmetricKey), "TransparentSymmetricKey structure");
        result = kmip_decode_transparent_symmetric_key(ctx, (TransparentSymmetricKey*)*value);
        CHECK_RESULT(ctx, result);
        break;
        
        /* TODO (ph) The rest require BigInteger support. */
        
        case KMIP_KEYFORMAT_TRANS_DSA_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_DSA_PUBLIC_KEY:
        case KMIP_KEYFORMAT_TRANS_RSA_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_RSA_PUBLIC_KEY:
        case KMIP_KEYFORMAT_TRANS_DH_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_DH_PUBLIC_KEY:
        case KMIP_KEYFORMAT_TRANS_ECDSA_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_ECDSA_PUBLIC_KEY:
        case KMIP_KEYFORMAT_TRANS_ECDH_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_ECDH_PUBLIC_KEY:
        case KMIP_KEYFORMAT_TRANS_ECMQV_PRIVATE_KEY:
        case KMIP_KEYFORMAT_TRANS_ECMQV_PUBLIC_KEY:
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    
    return(KMIP_OK);
}

int
kmip_decode_key_value(KMIP *ctx, enum key_format_type format, KeyValue *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_KEY_VALUE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_key_material(ctx, format, &value->key_material);
    CHECK_RESULT(ctx, result);
    
    value->attribute_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE);
    if(value->attribute_count > 0)
    {
        value->attributes = ctx->calloc_func(ctx->state, value->attribute_count, sizeof(Attribute));
        CHECK_NEW_MEMORY(ctx, value->attributes, value->attribute_count * sizeof(Attribute), "sequence of Attribute structures");
        
        for(size_t i = 0; i < value->attribute_count; i++)
        {
            result = kmip_decode_attribute(ctx, &value->attributes[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_cryptographic_parameters(KMIP *ctx, CryptographicParameters *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    kmip_init_cryptographic_parameters(value);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_BLOCK_CIPHER_MODE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_BLOCK_CIPHER_MODE, &value->block_cipher_mode);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_BLOCK_CIPHER_MODE, value->block_cipher_mode);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_PADDING_METHOD))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_PADDING_METHOD, &value->padding_method);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_PADDING_METHOD, value->padding_method);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_HASHING_ALGORITHM))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_HASHING_ALGORITHM, &value->hashing_algorithm);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_HASHING_ALGORITHM, value->hashing_algorithm);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_ROLE_TYPE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_KEY_ROLE_TYPE, &value->key_role_type);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_ROLE_TYPE, value->key_role_type);
    }
    
    if(ctx->version >= KMIP_1_2)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, &value->digital_signature_algorithm);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_DIGITAL_SIGNATURE_ALGORITHM, value->digital_signature_algorithm);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, &value->cryptographic_algorithm);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, value->cryptographic_algorithm);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_RANDOM_IV))
        {
            result = kmip_decode_bool(ctx, KMIP_TAG_RANDOM_IV, &value->random_iv);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_IV_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_IV_LENGTH, &value->iv_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_TAG_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_TAG_LENGTH, &value->tag_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_FIXED_FIELD_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_FIXED_FIELD_LENGTH, &value->fixed_field_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_INVOCATION_FIELD_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_INVOCATION_FIELD_LENGTH, &value->invocation_field_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_COUNTER_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_COUNTER_LENGTH, &value->counter_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_INITIAL_COUNTER_VALUE))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_INITIAL_COUNTER_VALUE, &value->initial_counter_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_SALT_LENGTH))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_SALT_LENGTH, &value->salt_length);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_MASK_GENERATOR))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_MASK_GENERATOR, &value->mask_generator);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_MASK_GENERATOR, value->mask_generator);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_MASK_GENERATOR_HASHING_ALGORITHM))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_MASK_GENERATOR_HASHING_ALGORITHM, &value->mask_generator_hashing_algorithm);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_HASHING_ALGORITHM, value->mask_generator_hashing_algorithm);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_P_SOURCE))
        {
            value->p_source = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
            CHECK_NEW_MEMORY(ctx, value->p_source, sizeof(ByteString), "P Source byte string");
            
            result = kmip_decode_byte_string(ctx, KMIP_TAG_P_SOURCE, value->p_source);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_TRAILER_FIELD))
        {
            result = kmip_decode_integer(ctx, KMIP_TAG_TRAILER_FIELD, &value->trailer_field);
            CHECK_RESULT(ctx, result);
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_encryption_key_information(KMIP *ctx, EncryptionKeyInformation *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_ENCRYPTION_KEY_INFORMATION, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS))
    {
        value->cryptographic_parameters = ctx->calloc_func(ctx->state, 1, sizeof(CryptographicParameters));
        CHECK_NEW_MEMORY(ctx, value->cryptographic_parameters, sizeof(CryptographicParameters), "CryptographicParameters structure");
        
        result = kmip_decode_cryptographic_parameters(ctx, value->cryptographic_parameters);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_mac_signature_key_information(KMIP *ctx, MACSignatureKeyInformation *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_MAC_SIGNATURE_KEY_INFORMATION, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_CRYPTOGRAPHIC_PARAMETERS))
    {
        value->cryptographic_parameters = ctx->calloc_func(ctx->state, 1, sizeof(CryptographicParameters));
        CHECK_NEW_MEMORY(ctx, value->cryptographic_parameters, sizeof(CryptographicParameters), "CryptographicParameters structure");
        
        result = kmip_decode_cryptographic_parameters(ctx, value->cryptographic_parameters);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}


int
kmip_decode_key_wrapping_data(KMIP *ctx, KeyWrappingData *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_KEY_WRAPPING_DATA, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_WRAPPING_METHOD, &value->wrapping_method);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_WRAPPING_METHOD, value->wrapping_method);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ENCRYPTION_KEY_INFORMATION))
    {
        value->encryption_key_info = ctx->calloc_func(ctx->state, 1, sizeof(EncryptionKeyInformation));
        CHECK_NEW_MEMORY(ctx, value->encryption_key_info, sizeof(EncryptionKeyInformation), "EncryptionKeyInformation structure");
        
        result = kmip_decode_encryption_key_information(ctx, value->encryption_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MAC_SIGNATURE_KEY_INFORMATION))
    {
        value->mac_signature_key_info = ctx->calloc_func(ctx->state, 1, sizeof(MACSignatureKeyInformation));
        CHECK_NEW_MEMORY(ctx, value->mac_signature_key_info, sizeof(MACSignatureKeyInformation), "MAC/SignatureKeyInformation structure");
        
        result = kmip_decode_mac_signature_key_information(ctx, value->mac_signature_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MAC_SIGNATURE))
    {
        value->mac_signature = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->mac_signature, sizeof(ByteString), "MAC/Signature byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_MAC_SIGNATURE, value->mac_signature);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_IV_COUNTER_NONCE))
    {
        value->iv_counter_nonce = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->iv_counter_nonce, sizeof(ByteString), "IV/Counter/Nonce byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_IV_COUNTER_NONCE, value->iv_counter_nonce);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_1)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_ENCODING_OPTION))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_ENCODING_OPTION, &value->encoding_option);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_ENCODING_OPTION, value->encoding_option);
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_key_block(KMIP *ctx, KeyBlock *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_KEY_BLOCK, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, &value->key_format_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, &value->key_compression_type);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, value->key_compression_type);
    }
    
    if(kmip_is_tag_type_next(ctx, KMIP_TAG_KEY_VALUE, KMIP_TYPE_BYTE_STRING))
    {
        value->key_value_type = KMIP_TYPE_BYTE_STRING;
        value->key_value = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->key_value, sizeof(ByteString), "KeyValue byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_KEY_VALUE, (ByteString *)value->key_value);
    }
    else
    {
        value->key_value_type = KMIP_TYPE_STRUCTURE;
        value->key_value = ctx->calloc_func(ctx->state, 1, sizeof(KeyValue));
        CHECK_NEW_MEMORY(ctx, value->key_value, sizeof(KeyValue), "KeyValue structure");
        
        result = kmip_decode_key_value(ctx, value->key_format_type, (KeyValue *)value->key_value);
    }
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, &value->cryptographic_algorithm);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_CRYPTOGRAPHIC_ALGORITHM, value->cryptographic_algorithm);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_CRYPTOGRAPHIC_LENGTH))
    {
        result = kmip_decode_integer(ctx, KMIP_TAG_CRYPTOGRAPHIC_LENGTH, &value->cryptographic_length);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_WRAPPING_DATA))
    {
        value->key_wrapping_data = ctx->calloc_func(ctx->state, 1, sizeof(KeyWrappingData));
        CHECK_NEW_MEMORY(ctx, value->key_wrapping_data, sizeof(KeyWrappingData), "KeyWrappingData structure");
        
        result = kmip_decode_key_wrapping_data(ctx, value->key_wrapping_data);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_symmetric_key(KMIP *ctx, SymmetricKey *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_SYMMETRIC_KEY, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->key_block = ctx->calloc_func(ctx->state, 1, sizeof(KeyBlock));
    CHECK_NEW_MEMORY(ctx, value->key_block, sizeof(KeyBlock), "KeyBlock structure");
    
    result = kmip_decode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_public_key(KMIP *ctx, PublicKey *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_PUBLIC_KEY, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->key_block = ctx->calloc_func(ctx->state, 1, sizeof(KeyBlock));
    CHECK_NEW_MEMORY(ctx, value->key_block, sizeof(KeyBlock), "KeyBlock structure");
    
    result = kmip_decode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_private_key(KMIP *ctx, PrivateKey *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_PRIVATE_KEY, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->key_block = ctx->calloc_func(ctx->state, 1, sizeof(KeyBlock));
    CHECK_NEW_MEMORY(ctx, value->key_block, sizeof(KeyBlock), "KeyBlock structure");
    
    result = kmip_decode_key_block(ctx, value->key_block);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_key_wrapping_specification(KMIP *ctx, KeyWrappingSpecification *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_KEY_WRAPPING_SPECIFICATION, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_WRAPPING_METHOD, &value->wrapping_method);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_WRAPPING_METHOD, value->wrapping_method);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ENCRYPTION_KEY_INFORMATION))
    {
        value->encryption_key_info = ctx->calloc_func(ctx->state, 1, sizeof(EncryptionKeyInformation));
        CHECK_NEW_MEMORY(ctx, value->encryption_key_info, sizeof(EncryptionKeyInformation), "EncryptionKeyInformation structure");
        result = kmip_decode_encryption_key_information(ctx, value->encryption_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MAC_SIGNATURE_KEY_INFORMATION))
    {
        value->mac_signature_key_info = ctx->calloc_func(ctx->state, 1, sizeof(MACSignatureKeyInformation));
        CHECK_NEW_MEMORY(ctx, value->mac_signature_key_info, sizeof(MACSignatureKeyInformation), "MACSignatureKeyInformation structure");
        result = kmip_decode_mac_signature_key_information(ctx, value->mac_signature_key_info);
        CHECK_RESULT(ctx, result);
    }
    
    value->attribute_name_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE_NAME);
    if(value->attribute_name_count > 0)
    {
        value->attribute_names = ctx->calloc_func(ctx->state, value->attribute_name_count, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->attribute_names, value->attribute_name_count * sizeof(TextString), "sequence of AttributeName text strings");
        
        for(size_t i = 0; i < value->attribute_name_count; i++)
        {
            result = kmip_decode_text_string(ctx, KMIP_TAG_ATTRIBUTE_NAME, &value->attribute_names[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(ctx->version >= KMIP_1_1)
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_ENCODING_OPTION, &value->encoding_option);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_ENCODING_OPTION, value->encoding_option);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_create_request_payload(KMIP *ctx, CreateRequestPayload *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_OBJECT_TYPE, &value->object_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);

    if(ctx->version < KMIP_2_0)
    {
        value->template_attribute = ctx->calloc_func(ctx->state, 1, sizeof(TemplateAttribute));
        if(value->template_attribute == NULL)
        {
            HANDLE_FAILED_ALLOC(ctx, sizeof(TemplateAttribute), "TemplateAttribute");
        }
        result = kmip_decode_template_attribute(ctx, value->template_attribute);
        if(result != KMIP_OK)
        {
            kmip_free_template_attribute(ctx, value->template_attribute);
            ctx->free_func(ctx, value->template_attribute);
            value->template_attribute = NULL;
            HANDLE_FAILURE(ctx, result);
        }
    }
    else
    {
        value->attributes = ctx->calloc_func(ctx->state, 1, sizeof(Attributes));
        if(value->attributes == NULL)
        {
            HANDLE_FAILED_ALLOC(ctx, sizeof(Attributes), "Attributes");
        }
        result = kmip_decode_attributes(ctx, value->attributes);
        if(result != KMIP_OK)
        {
            kmip_free_attributes(ctx, value->attributes);
            ctx->free_func(ctx, value->attributes);
            value->attributes = NULL;

            HANDLE_FAILURE(ctx, result);
        }

        if(kmip_is_tag_next(ctx, KMIP_TAG_PROTECTION_STORAGE_MASKS))
        {
            value->protection_storage_masks = ctx->calloc_func(ctx->state, 1, sizeof(ProtectionStorageMasks));
            if(value->protection_storage_masks == NULL)
            {
                kmip_free_attributes(ctx, value->attributes);
                ctx->free_func(ctx, value->attributes);
                value->attributes = NULL;

                HANDLE_FAILED_ALLOC(ctx, sizeof(ProtectionStorageMasks), "ProtectionStorageMasks");
            }
            result = kmip_decode_protection_storage_masks(ctx, value->protection_storage_masks);
            if(result != KMIP_OK)
            {
                kmip_free_attributes(ctx, value->attributes);
                kmip_free_protection_storage_masks(ctx, value->protection_storage_masks);
                ctx->free_func(ctx, value->attributes);
                ctx->free_func(ctx, value->protection_storage_masks);
                value->attributes = NULL;
                value->protection_storage_masks = NULL;

                HANDLE_FAILURE(ctx, result);
            }
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_create_response_payload(KMIP *ctx, CreateResponsePayload *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_OBJECT_TYPE, &value->object_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    if(ctx->version < KMIP_2_0)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_TEMPLATE_ATTRIBUTE))
        {
            value->template_attribute = ctx->calloc_func(ctx->state, 1, sizeof(TemplateAttribute));
            CHECK_NEW_MEMORY(ctx, value->template_attribute, sizeof(TemplateAttribute), "TemplateAttribute structure");
            
            result = kmip_decode_template_attribute(ctx, value->template_attribute);
            CHECK_RESULT(ctx, result);
        }
    }

    return(KMIP_OK);
}

int
kmip_decode_locate_request_payload(KMIP *ctx, LocateRequestPayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    int i;

    value->attributes = 0;
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);

    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    if(kmip_is_tag_next(ctx, KMIP_TAG_MAXIMUM_ITEMS))
    {
	result = kmip_decode_enum(ctx, KMIP_TAG_MAXIMUM_ITEMS, &value->maximum_items);
	CHECK_RESULT(ctx, result);
    }

    if(kmip_is_tag_next(ctx, KMIP_TAG_OFFSET_ITEMS))
    {
	result = kmip_decode_enum(ctx, KMIP_TAG_OFFSET_ITEMS, &value->offset_items);
	CHECK_RESULT(ctx, result);
    }

    if(kmip_is_tag_next(ctx, KMIP_TAG_STORAGE_STATUS_MASK))
    {
	result = kmip_decode_enum(ctx, KMIP_TAG_STORAGE_STATUS_MASK, &value->storage_status_mask);
	CHECK_RESULT(ctx, result);
    }

    if(kmip_is_tag_next(ctx, KMIP_TAG_OBJECT_GROUP_MEMBER))
    {
	result = kmip_decode_enum(ctx, KMIP_TAG_OBJECT_GROUP_MEMBER, &value->object_group_member);
	CHECK_RESULT(ctx, result);
    }

    if(ctx->version < KMIP_2_0)
    {
	value->attribute_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE);

	value->attributes = ctx->calloc_func(ctx->state, value->attribute_count, sizeof(Attributes));
	CHECK_NEW_MEMORY(ctx, value->attributes,
		value->attribute_count*sizeof(Attributes), "Attributes list");
	for (i = 0; i < value->attribute_count; ++i)
	{
	    result = kmip_decode_attribute(ctx, value->attributes + i);
	    CHECK_RESULT(ctx, result);
	}
    } else {
        if(kmip_is_tag_next(ctx, KMIP_TAG_ATTRIBUTES))
	{
	    result = kmip_decode_attributes_2(ctx, &value->attributes, &value->attribute_count);
	    if (result != KMIP_OK)
	    {
		kmip_free_attributes_2(ctx, value->attributes, value->attribute_count);
		value->attributes = 0;
		value->attribute_count = 0;
		return result;
	    }
	}
    }

    return(KMIP_OK);
}


int
kmip_decode_locate_response_payload(KMIP *ctx, LocateResponsePayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);

    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    int i;

    value->unique_identifiers = NULL;
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);

    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    if(kmip_is_tag_next(ctx, KMIP_TAG_LOCATED_ITEMS))
    {
	result = kmip_decode_enum(ctx, KMIP_TAG_MAXIMUM_ITEMS, &value->located_items);
	CHECK_RESULT(ctx, result);
    }

    value->unique_identifiers_count = kmip_get_num_items_next(ctx, KMIP_TAG_UNIQUE_IDENTIFIER);
    value->unique_identifiers = ctx->calloc_func(ctx->state, value->unique_identifiers_count, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifiers,
	    value->unique_identifiers_count*sizeof(TextString), "UniqueIdentifier list");
    for (i = 0; i < value->unique_identifiers_count; ++i)
    {
	result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifiers +i);
	CHECK_RESULT(ctx, result);
    }

    return(KMIP_OK);
}

int
kmip_decode_get_request_payload(KMIP *ctx, GetRequestPayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_IDENTIFIER))
    {
        value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
        result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_FORMAT_TYPE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_KEY_FORMAT_TYPE, &value->key_format_type);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_FORMAT_TYPE, value->key_format_type);
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_WRAP_TYPE))
        {
            result = kmip_decode_enum(ctx, KMIP_TAG_KEY_WRAP_TYPE, &value->key_wrap_type);
            CHECK_RESULT(ctx, result);
            CHECK_ENUM(ctx, KMIP_TAG_KEY_WRAP_TYPE, value->key_wrap_type);
        }
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, &value->key_compression_type);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_KEY_COMPRESSION_TYPE, value->key_compression_type);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_KEY_WRAPPING_SPECIFICATION))
    {
        value->key_wrapping_spec = ctx->calloc_func(ctx->state, 1, sizeof(KeyWrappingSpecification));
        CHECK_NEW_MEMORY(ctx, value->key_wrapping_spec, sizeof(KeyWrappingSpecification), "KeyWrappingSpecification structure");
        result = kmip_decode_key_wrapping_specification(ctx, value->key_wrapping_spec);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_get_response_payload(KMIP *ctx, GetResponsePayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_OBJECT_TYPE, &value->object_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_OBJECT_TYPE, value->object_type);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    switch(value->object_type)
    {
        case KMIP_OBJTYPE_SYMMETRIC_KEY:
        value->object = ctx->calloc_func(ctx->state, 1, sizeof(SymmetricKey));
        CHECK_NEW_MEMORY(ctx, value->object, sizeof(SymmetricKey), "SymmetricKey structure");
        result = kmip_decode_symmetric_key(ctx, (SymmetricKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_OBJTYPE_PUBLIC_KEY:
        value->object = ctx->calloc_func(ctx->state, 1, sizeof(PublicKey));
        CHECK_NEW_MEMORY(ctx, value->object, sizeof(PublicKey), "PublicKey structure");
        result = kmip_decode_public_key(ctx, (PublicKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        case KMIP_OBJTYPE_PRIVATE_KEY:
        value->object = ctx->calloc_func(ctx->state, 1, sizeof(PrivateKey));
        CHECK_NEW_MEMORY(ctx, value->object, sizeof(PrivateKey), "PrivateKey structure");
        result = kmip_decode_private_key(ctx, (PrivateKey*)value->object);
        CHECK_RESULT(ctx, result);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    
    return(KMIP_OK);
}

int
kmip_decode_get_attributes_request_payload(KMIP *ctx, GetAttributesRequestPayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_IDENTIFIER))
    {
        value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
        result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }

    if(ctx->version < KMIP_2_0)
    {
	value->attribute_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE_NAME);

	value->attribute_names = ctx->calloc_func(ctx->state, value->attribute_count, sizeof(enum attribute_type));
	CHECK_NEW_MEMORY(ctx, value->attribute_names,
		value->attribute_count*sizeof(Attributes), "Attribute name list");
	for (int i = 0; i < value->attribute_count; ++i)
	{
	    result = kmip_decode_attribute_name(ctx, value->attribute_names + i);
	    CHECK_RESULT(ctx, result);
	}
    } else {
// XXX something weird goes here.
        return(KMIP_NOT_IMPLEMENTED);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_get_attributes_response_payload(KMIP *ctx, GetAttributesResponsePayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);

    if(ctx->version < KMIP_2_0)
    {
	value->attribute_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE);

	value->attributes = ctx->calloc_func(ctx->state, value->attribute_count, sizeof(Attribute));
	CHECK_NEW_MEMORY(ctx, value->attributes,
		value->attribute_count*sizeof(Attributes), "Attributes list");
	for (int i = 0; i < value->attribute_count; ++i)
	{
	    result = kmip_decode_attribute(ctx, value->attributes + i);
	    CHECK_RESULT(ctx, result);
	}
    } else {
        if(kmip_is_tag_next(ctx, KMIP_TAG_ATTRIBUTES))
	{
	    result = kmip_decode_attributes_2(ctx, &value->attributes, &value->attribute_count);
	    if (result != KMIP_OK)
	    {
		kmip_free_attributes_2(ctx, value->attributes, value->attribute_count);
		value->attributes = 0;
		value->attribute_count = 0;
		return result;
	    }
	}
    }
    
    return(KMIP_OK);
}

int
kmip_decode_get_attribute_list_request_payload(KMIP *ctx, GetAttributeListRequestPayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);

    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_IDENTIFIER))
    {
        value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
        result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_get_attribute_list_response_payload(KMIP *ctx, GetAttributeListResponsePayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);

    if(ctx->version < KMIP_2_0)
    {
	value->attribute_names_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTRIBUTE_NAME);

	value->attribute_names = ctx->calloc_func(ctx->state, value->attribute_names_count, sizeof(enum attribute_type));
	CHECK_NEW_MEMORY(ctx, value->attribute_names,
		value->attribute_names_count*sizeof(Attributes), "Attribute name list");
	for (int i = 0; i < value->attribute_names_count; ++i)
	{
	    result = kmip_decode_attribute_name(ctx, value->attribute_names + i);
	    CHECK_RESULT(ctx, result);
	}
    } else {
// XXX something weird goes here.
        return(KMIP_NOT_IMPLEMENTED);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_destroy_request_payload(KMIP *ctx, DestroyRequestPayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_IDENTIFIER))
    {
        value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
        result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_destroy_response_payload(KMIP *ctx, DestroyResponsePayload *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_PAYLOAD, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->unique_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->unique_identifier, sizeof(TextString), "UniqueIdentifier text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_UNIQUE_IDENTIFIER, value->unique_identifier);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_request_batch_item(KMIP *ctx, RequestBatchItem *value)
{
    CHECK_DECODE_ARGS(ctx, value);
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_BATCH_ITEM, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_OPERATION, &value->operation);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_OPERATION, value->operation);

    if(ctx->version >= KMIP_2_0)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_EPHEMERAL))
        {
            result = kmip_decode_bool(ctx, KMIP_TAG_EPHEMERAL, &value->ephemeral);
            CHECK_RESULT(ctx, result);
        }
    }

    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID))
    {
        value->unique_batch_item_id = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->unique_batch_item_id, sizeof(ByteString), "UniqueBatchItemID byte string");
        result = kmip_decode_byte_string(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID, value->unique_batch_item_id);
        CHECK_RESULT(ctx, result);
    }
    
    switch(value->operation)
    {
        case KMIP_OP_CREATE:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(CreateRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(CreateRequestPayload), "CreateRequestPayload structure");
        result = kmip_decode_create_request_payload(ctx, (CreateRequestPayload *)value->request_payload);
        break;
        
        case KMIP_OP_LOCATE:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(LocateRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(LocateRequestPayload), "LocateRequestPayload structure");
        result = kmip_decode_locate_request_payload(ctx, (LocateRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(GetRequestPayload), "GetRequestPayload structure");
        result = kmip_decode_get_request_payload(ctx, (GetRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTES:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetAttributesRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(GetAttributesRequestPayload), "GetAttributesRequestPayload structure");
        result = kmip_decode_get_attributes_request_payload(ctx, (GetAttributesRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_GET_ATTRIBUTE_LIST:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetAttributeListRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(GetAttributeListRequestPayload), "GetAttributeListRequestPayload structure");
        result = kmip_decode_get_attribute_list_request_payload(ctx, (GetAttributeListRequestPayload*)value->request_payload);
        break;
        
        case KMIP_OP_DESTROY:
        value->request_payload = ctx->calloc_func(ctx->state, 1, sizeof(DestroyRequestPayload));
        CHECK_NEW_MEMORY(ctx, value->request_payload, sizeof(DestroyRequestPayload), "DestroyRequestPayload structure");
        result = kmip_decode_destroy_request_payload(ctx, (DestroyRequestPayload*)value->request_payload);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    };
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_response_batch_item(KMIP *ctx, ResponseBatchItem *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_BATCH_ITEM, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_OPERATION))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_OPERATION, &value->operation);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_OPERATION, value->operation);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID))
    {
        value->unique_batch_item_id = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->unique_batch_item_id, sizeof(ByteString), "UniqueBatchItemID byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_UNIQUE_BATCH_ITEM_ID, value->unique_batch_item_id);
        CHECK_RESULT(ctx, result);
    }
    
    result = kmip_decode_enum(ctx, KMIP_TAG_RESULT_STATUS, &value->result_status);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_RESULT_STATUS, value->result_status);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_RESULT_REASON))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_RESULT_REASON, &value->result_reason);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_RESULT_MESSAGE))
    {
        value->result_message = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->result_message, sizeof(TextString), "ResultMessage text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_RESULT_MESSAGE, value->result_message);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ASYNCHRONOUS_CORRELATION_VALUE))
    {
        value->asynchronous_correlation_value = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->asynchronous_correlation_value, sizeof(ByteString), "AsynchronousCorrelationValue byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_ASYNCHRONOUS_CORRELATION_VALUE, value->asynchronous_correlation_value);
        CHECK_RESULT(ctx, result);
    }
    
    /* NOTE (ph) Omitting the tag check is a good way to test error output. */
    if(kmip_is_tag_next(ctx, KMIP_TAG_RESPONSE_PAYLOAD))
    {
        switch(value->operation)
        {
            case KMIP_OP_CREATE:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(CreateResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(CreateResponsePayload), "CreateResponsePayload structure");
            result = kmip_decode_create_response_payload(ctx, value->response_payload);
            break;
            
            case KMIP_OP_LOCATE:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(LocateResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(LocateResponsePayload), "LocateResponsePayload structure");
            
            result = kmip_decode_locate_response_payload(ctx, value->response_payload);
            break;
            
            case KMIP_OP_GET:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(GetResponsePayload), "GetResponsePayload structure");
            
            result = kmip_decode_get_response_payload(ctx, value->response_payload);
            break;
            
            case KMIP_OP_GET_ATTRIBUTES:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetAttributesResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(GetAttributesResponsePayload), "GetAttributesResponsePayload structure");
            
            result = kmip_decode_get_attributes_response_payload(ctx, value->response_payload);
            break;
            
            case KMIP_OP_GET_ATTRIBUTE_LIST:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(GetAttributeListResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(GetAttributeListResponsePayload), "GetAttributeListResponsePayload structure");
            
            result = kmip_decode_get_attribute_list_response_payload(ctx, value->response_payload);
            break;
            
            case KMIP_OP_DESTROY:
            value->response_payload = ctx->calloc_func(ctx->state, 1, sizeof(DestroyResponsePayload));
            CHECK_NEW_MEMORY(ctx, value->response_payload, sizeof(DestroyResponsePayload), "DestroyResponsePayload structure");
            result = kmip_decode_destroy_response_payload(ctx, value->response_payload);
            break;
            
            default:
            kmip_push_error_frame(ctx, __func__, __LINE__);
            return(KMIP_NOT_IMPLEMENTED);
            break;
        };
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_nonce(KMIP *ctx, Nonce *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_NONCE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->nonce_id = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
    CHECK_NEW_MEMORY(ctx, value->nonce_id, sizeof(ByteString), "NonceID byte string");
    
    result = kmip_decode_byte_string(ctx, KMIP_TAG_NONCE_ID, value->nonce_id);
    CHECK_RESULT(ctx, result);
    
    value->nonce_value = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
    CHECK_NEW_MEMORY(ctx, value->nonce_value, sizeof(ByteString), "NonceValue byte string");
    
    result = kmip_decode_byte_string(ctx, KMIP_TAG_NONCE_VALUE, value->nonce_value);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_username_password_credential(KMIP *ctx, UsernamePasswordCredential *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->username = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
    CHECK_NEW_MEMORY(ctx, value->username, sizeof(TextString), "Username text string");
    
    result = kmip_decode_text_string(ctx, KMIP_TAG_USERNAME, value->username);
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_PASSWORD))
    {
        value->password = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->password, sizeof(TextString), "Password text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_PASSWORD, value->password);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_device_credential(KMIP *ctx, DeviceCredential *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_DEVICE_SERIAL_NUMBER))
    {
        value->device_serial_number = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->device_serial_number, sizeof(TextString), "DeviceSerialNumber text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_DEVICE_SERIAL_NUMBER, value->device_serial_number);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_PASSWORD))
    {
        value->password = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->password, sizeof(TextString), "Password text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_PASSWORD, value->password);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_DEVICE_IDENTIFIER))
    {
        value->device_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->device_identifier, sizeof(TextString), "DeviceIdentifier text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_DEVICE_IDENTIFIER, value->device_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_NETWORK_IDENTIFIER))
    {
        value->network_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->network_identifier, sizeof(TextString), "NetworkIdentifier text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_NETWORK_IDENTIFIER, value->network_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MACHINE_IDENTIFIER))
    {
        value->machine_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->machine_identifier, sizeof(TextString), "MachineIdentifier text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_MACHINE_IDENTIFIER, value->machine_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MEDIA_IDENTIFIER))
    {
        value->media_identifier = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
        CHECK_NEW_MEMORY(ctx, value->media_identifier, sizeof(TextString), "MediaIdentifier text string");
        
        result = kmip_decode_text_string(ctx, KMIP_TAG_MEDIA_IDENTIFIER, value->media_identifier);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_attestation_credential(KMIP *ctx, AttestationCredential *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_CREDENTIAL_VALUE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->nonce = ctx->calloc_func(ctx->state, 1, sizeof(Nonce));
    CHECK_NEW_MEMORY(ctx, value->nonce, sizeof(Nonce), "Nonce structure");
    
    result = kmip_decode_nonce(ctx, value->nonce);
    CHECK_RESULT(ctx, result);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, &value->attestation_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_type);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ATTESTATION_MEASUREMENT))
    {
        value->attestation_measurement = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->attestation_measurement, sizeof(ByteString), "AttestationMeasurement byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_ATTESTATION_MEASUREMENT, value->attestation_measurement);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ATTESTATION_ASSERTION))
    {
        value->attestation_assertion = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
        CHECK_NEW_MEMORY(ctx, value->attestation_assertion, sizeof(ByteString), "AttestationAssertion byte string");
        
        result = kmip_decode_byte_string(ctx, KMIP_TAG_ATTESTATION_ASSERTION, value->attestation_assertion);
        CHECK_RESULT(ctx, result);
    }
    
    return(KMIP_OK);
}

int
kmip_decode_credential_value(KMIP *ctx, enum credential_type type, void **value)
{
    int result = 0;
    
    switch(type)
    {
        case KMIP_CRED_USERNAME_AND_PASSWORD:
        *value = ctx->calloc_func(ctx->state, 1, sizeof(UsernamePasswordCredential));
        CHECK_NEW_MEMORY(ctx, *value, sizeof(UsernamePasswordCredential), "UsernamePasswordCredential structure");
        result = kmip_decode_username_password_credential(ctx, (UsernamePasswordCredential *)*value);
        break;
        
        case KMIP_CRED_DEVICE:
        *value = ctx->calloc_func(ctx->state, 1, sizeof(DeviceCredential));
        CHECK_NEW_MEMORY(ctx, *value, sizeof(DeviceCredential), "DeviceCredential structure");
        result = kmip_decode_device_credential(ctx, (DeviceCredential *)*value);
        break;
        
        case KMIP_CRED_ATTESTATION:
        *value = ctx->calloc_func(ctx->state, 1, sizeof(AttestationCredential));
        CHECK_NEW_MEMORY(ctx, *value, sizeof(AttestationCredential), "AttestationCredential structure");
        result = kmip_decode_attestation_credential(ctx, (AttestationCredential*)*value);
        break;
        
        default:
        kmip_push_error_frame(ctx, __func__, __LINE__);
        return(KMIP_NOT_IMPLEMENTED);
        break;
    }
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_credential(KMIP *ctx, Credential *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_CREDENTIAL, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    result = kmip_decode_enum(ctx, KMIP_TAG_CREDENTIAL_TYPE, &value->credential_type);
    CHECK_RESULT(ctx, result);
    CHECK_ENUM(ctx, KMIP_TAG_CREDENTIAL_TYPE, value->credential_type);
    
    result = kmip_decode_credential_value(ctx, value->credential_type, &value->credential_value);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_authentication(KMIP *ctx, Authentication *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_AUTHENTICATION, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->credential = ctx->calloc_func(ctx->state, 1, sizeof(Credential));
    CHECK_NEW_MEMORY(ctx, value->credential, sizeof(Credential), "Credential structure");
    
    result = kmip_decode_credential(ctx, value->credential);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_request_header(KMIP *ctx, RequestHeader *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_HEADER, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->protocol_version = ctx->calloc_func(ctx->state, 1, sizeof(ProtocolVersion));
    CHECK_NEW_MEMORY(ctx, value->protocol_version, sizeof(ProtocolVersion), "ProtocolVersion structure");
    
    result = kmip_decode_protocol_version(ctx, value->protocol_version);
    CHECK_RESULT(ctx, result);
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_MAXIMUM_RESPONSE_SIZE))
    {
        result = kmip_decode_integer(ctx, KMIP_TAG_MAXIMUM_RESPONSE_SIZE, &value->maximum_response_size);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE))
        {
            value->client_correlation_value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->client_correlation_value, sizeof(TextString), "ClientCorrelationValue text string");
            
            result = kmip_decode_text_string(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE, value->client_correlation_value);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE))
        {
            value->server_correlation_value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->server_correlation_value, sizeof(TextString), "ServerCorrelationValue text string");
            
            result = kmip_decode_text_string(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE, value->server_correlation_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_ASYNCHRONOUS_INDICATOR))
    {
        result = kmip_decode_bool(ctx, KMIP_TAG_ASYNCHRONOUS_INDICATOR, &value->asynchronous_indicator);
        CHECK_RESULT(ctx, result);
    }
    
    if(ctx->version >= KMIP_1_2)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_ATTESTATION_CAPABLE_INDICATOR))
        {
            result = kmip_decode_bool(ctx, KMIP_TAG_ATTESTATION_CAPABLE_INDICATOR, &value->attestation_capable_indicator);
            CHECK_RESULT(ctx, result);
        }
        
        value->attestation_type_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTESTATION_TYPE);
        if(value->attestation_type_count > 0)
        {
            value->attestation_types = ctx->calloc_func(ctx->state, value->attestation_type_count, sizeof(enum attestation_type));
            CHECK_NEW_MEMORY(ctx, value->attestation_types, value->attestation_type_count * sizeof(enum attestation_type), "sequence of AttestationType enumerations");
            
            for(size_t i = 0; i < value->attestation_type_count; i++)
            {
                result = kmip_decode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, &value->attestation_types[i]);
                CHECK_RESULT(ctx, result);
                CHECK_ENUM(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_types[i]);
            }
        }
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_AUTHENTICATION))
    {
        value->authentication = ctx->calloc_func(ctx->state,1, sizeof(Authentication));
        CHECK_NEW_MEMORY(ctx, value->authentication, sizeof(Authentication), "Authentication structure");
        
        result = kmip_decode_authentication(ctx, value->authentication);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_BATCH_ERROR_CONTINUATION_OPTION))
    {
        result = kmip_decode_enum(ctx, KMIP_TAG_BATCH_ERROR_CONTINUATION_OPTION, &value->batch_error_continuation_option);
        CHECK_RESULT(ctx, result);
        CHECK_ENUM(ctx, KMIP_TAG_BATCH_ERROR_CONTINUATION_OPTION, value->batch_error_continuation_option);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_BATCH_ORDER_OPTION))
    {
        result = kmip_decode_bool(ctx, KMIP_TAG_BATCH_ORDER_OPTION, &value->batch_order_option);
        CHECK_RESULT(ctx, result);
    }
    
    if(kmip_is_tag_next(ctx, KMIP_TAG_TIME_STAMP))
    {
        result = kmip_decode_date_time(ctx, KMIP_TAG_TIME_STAMP, &value->time_stamp);
        CHECK_RESULT(ctx, result);
    }
    
    result = kmip_decode_integer(ctx, KMIP_TAG_BATCH_COUNT, &value->batch_count);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_response_header(KMIP *ctx, ResponseHeader *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_HEADER, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->protocol_version = ctx->calloc_func(ctx->state, 1, sizeof(ProtocolVersion));
    CHECK_NEW_MEMORY(ctx, value->protocol_version, sizeof(ProtocolVersion), "ProtocolVersion structure");
    
    result = kmip_decode_protocol_version(ctx, value->protocol_version);
    CHECK_RESULT(ctx, result);
    
    result = kmip_decode_date_time(ctx, KMIP_TAG_TIME_STAMP, &value->time_stamp);
    CHECK_RESULT(ctx, result);
    
    if(ctx->version >= KMIP_1_2)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_NONCE))
        {
            value->nonce = ctx->calloc_func(ctx->state, 1, sizeof(Nonce));
            CHECK_NEW_MEMORY(ctx, value->nonce, sizeof(Nonce), "Nonce structure");
            
            result = kmip_decode_nonce(ctx, value->nonce);
            CHECK_RESULT(ctx, result);
        }

        if(ctx->version >= KMIP_2_0)
        {
            if(kmip_is_tag_next(ctx, KMIP_TAG_SERVER_HASHED_PASSWORD))
            {
                value->server_hashed_password = ctx->calloc_func(ctx->state, 1, sizeof(ByteString));
                CHECK_NEW_MEMORY(ctx, value->server_hashed_password, sizeof(ByteString), "ByteString");

                result = kmip_decode_byte_string(ctx, KMIP_TAG_SERVER_HASHED_PASSWORD, value->server_hashed_password);
                CHECK_RESULT(ctx, result);
            }
        }

        value->attestation_type_count = kmip_get_num_items_next(ctx, KMIP_TAG_ATTESTATION_TYPE);
        if(value->attestation_type_count > 0)
        {
            value->attestation_types = ctx->calloc_func(ctx->state, value->attestation_type_count, sizeof(enum attestation_type));
            CHECK_NEW_MEMORY(ctx, value->attestation_types, value->attestation_type_count * sizeof(enum attestation_type), "sequence of AttestationType enumerations");
            
            for(size_t i = 0; i < value->attestation_type_count; i++)
            {
                result = kmip_decode_enum(ctx, KMIP_TAG_ATTESTATION_TYPE, &value->attestation_types[i]);
                CHECK_RESULT(ctx, result);
                CHECK_ENUM(ctx, KMIP_TAG_ATTESTATION_TYPE, value->attestation_types[i]);
            }
        }
    }
    
    if(ctx->version >= KMIP_1_4)
    {
        if(kmip_is_tag_next(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE))
        {
            value->client_correlation_value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->client_correlation_value, sizeof(TextString), "ClientCorrelationValue text string");
            
            result = kmip_decode_text_string(ctx, KMIP_TAG_CLIENT_CORRELATION_VALUE, value->client_correlation_value);
            CHECK_RESULT(ctx, result);
        }
        
        if(kmip_is_tag_next(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE))
        {
            value->server_correlation_value = ctx->calloc_func(ctx->state, 1, sizeof(TextString));
            CHECK_NEW_MEMORY(ctx, value->server_correlation_value, sizeof(TextString), "ServerCorrelationValue text string");
            
            result = kmip_decode_text_string(ctx, KMIP_TAG_SERVER_CORRELATION_VALUE, value->server_correlation_value);
            CHECK_RESULT(ctx, result);
        }
    }
    
    result = kmip_decode_integer(ctx, KMIP_TAG_BATCH_COUNT, &value->batch_count);
    CHECK_RESULT(ctx, result);
    
    return(KMIP_OK);
}

int
kmip_decode_request_message(KMIP *ctx, RequestMessage *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_REQUEST_MESSAGE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->request_header = ctx->calloc_func(ctx->state, 1, sizeof(RequestHeader));
    CHECK_NEW_MEMORY(ctx, value->request_header, sizeof(RequestHeader), "RequestHeader structure");
    kmip_init_request_header(value->request_header);
    result = kmip_decode_request_header(ctx, value->request_header);
    CHECK_RESULT(ctx, result);
    
    value->batch_count = kmip_get_num_items_next(ctx, KMIP_TAG_BATCH_ITEM);
    if(value->batch_count > 0)
    {
        value->batch_items = ctx->calloc_func(ctx->state, value->batch_count, sizeof(RequestBatchItem));
        CHECK_NEW_MEMORY(ctx, value->batch_items, value->batch_count * sizeof(RequestBatchItem), "sequence of RequestBatchItem structures");
        
        for(size_t i = 0; i < value->batch_count; i++)
        {
            kmip_init_request_batch_item(&value->batch_items[i]);
            result = kmip_decode_request_batch_item(ctx, &value->batch_items[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    return(KMIP_OK);
}

int
kmip_decode_response_message(KMIP *ctx, ResponseMessage *value)
{
    CHECK_BUFFER_FULL(ctx, 8);
    
    int result = 0;
    int32 tag_type = 0;
    uint32 length = 0;
    
    kmip_decode_int32_be(ctx, &tag_type);
    CHECK_TAG_TYPE(ctx, tag_type, KMIP_TAG_RESPONSE_MESSAGE, KMIP_TYPE_STRUCTURE);
    
    kmip_decode_int32_be(ctx, &length);
    CHECK_BUFFER_FULL(ctx, length);
    
    value->response_header = ctx->calloc_func(ctx->state, 1, sizeof(ResponseHeader));
    CHECK_NEW_MEMORY(ctx, value->response_header, sizeof(ResponseHeader), "ResponseHeader structure");
    
    result = kmip_decode_response_header(ctx, value->response_header);
    CHECK_RESULT(ctx, result);
    
    value->batch_count = kmip_get_num_items_next(ctx, KMIP_TAG_BATCH_ITEM);
    if(value->batch_count > 0)
    {
        value->batch_items = ctx->calloc_func(ctx->state, value->batch_count, sizeof(ResponseBatchItem));
        CHECK_NEW_MEMORY(ctx, value->batch_items, value->batch_count * sizeof(ResponseBatchItem), "sequence of ResponseBatchItem structures");
        
        for(size_t i = 0; i < value->batch_count; i++)
        {
            result = kmip_decode_response_batch_item(ctx, &value->batch_items[i]);
            CHECK_RESULT(ctx, result);
        }
    }
    
    return(KMIP_OK);
}
