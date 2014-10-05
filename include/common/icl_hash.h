/*
 * author: xiemin
 * file_name: icl_map.h
 * company:ifeng
 * date:2014-09-29
 *
 */


#ifndef ICL_HASH_H_
#define ICL_HASH_H_


#define icl_int64 long long int
#define icl_uint64 unsigned long long int


unsigned icl_hash_crc32(const void *buffer, size_t len);
icl_int64 icl_hash_crc64(const void *buffer, size_t len);
unsigned icl_hash_bin(const void *key, size_t len);
unsigned icl_hash_test(const void *key, size_t len);
unsigned icl_hash_func2(const void *key, size_t len);
unsigned icl_hash_func3(const void *key, size_t len);
unsigned icl_hash_func4(const void *key, size_t len);
unsigned icl_hash_func5(const void *key, size_t len);
unsigned icl_hash_func6(const void *key, size_t len);




#endif /*ICL_HASH_H_*/

