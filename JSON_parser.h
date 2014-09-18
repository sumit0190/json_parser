#ifndef JSON_PARSER_H
#define JSON_PARSER_H

/* JSON_parser.h */

#include <stddef.h>

/* Windoze testing not completed yet!! */
#ifdef JSON_PARSER_DLL
#   ifdef _MSC_VER
#	    ifdef JSON_PARSER_DLL_EXPORTS
#		    define JSON_PARSER_DLL_API __declspec(dllexport)
#	    else
#		    define JSON_PARSER_DLL_API __declspec(dllimport)
#       endif
#   else
#	    define JSON_PARSER_DLL_API 
#   endif
#else
#	define JSON_PARSER_DLL_API 
#endif

/* Non-floating point values */
#if __STDC_VERSION__ >= 199901L || HAVE_LONG_LONG == 1
typedef long long JSON_int_t;
#define JSON_PARSER_INTEGER_SSCANF_TOKEN "%lld"
#define JSON_PARSER_INTEGER_SPRINTF_TOKEN "%lld"
#else 
typedef long JSON_int_t;
#define JSON_PARSER_INTEGER_SSCANF_TOKEN "%ld"
#define JSON_PARSER_INTEGER_SPRINTF_TOKEN "%ld"
#endif


#ifdef __cplusplus
extern "C" {
#endif 

typedef enum 
{
    JSON_E_NONE = 0,
    JSON_E_INVALID_CHAR,
    JSON_E_INVALID_KEYWORD,
    JSON_E_INVALID_ESCAPE_SEQUENCE,
    JSON_E_INVALID_UNICODE_SEQUENCE,
    JSON_E_INVALID_NUMBER,
    JSON_E_NESTING_DEPTH_REACHED,
    JSON_E_UNBALANCED_COLLECTION,
    JSON_E_EXPECTED_KEY,
    JSON_E_EXPECTED_COLON,
    JSON_E_OUT_OF_MEMORY
} JSON_error;

typedef enum 
{
    JSON_T_NONE = 0,
    JSON_T_ARRAY_BEGIN,
    JSON_T_ARRAY_END,
    JSON_T_OBJECT_BEGIN,
    JSON_T_OBJECT_END,
    JSON_T_INTEGER,
    JSON_T_FLOAT,
    JSON_T_NULL,
    JSON_T_TRUE,
    JSON_T_FALSE,
    JSON_T_STRING,
    JSON_T_KEY,
    JSON_T_MAX
} JSON_type;

typedef struct JSON_value_struct {
    union {
        JSON_int_t integer_value;
        
        double float_value;
        
        struct {
            const char* value;
            size_t length;
        } str;
    } vu;
} JSON_value;

typedef struct JSON_parser_struct* JSON_parser;
typedef int (*JSON_parser_callback)(void* ctx, int type, const JSON_value* value);
typedef void* (*JSON_malloc_t)(size_t n);
typedef void (*JSON_free_t)(void* mem);
typedef struct {
    JSON_parser_callback    callback;
    void*                   callback_ctx;
    int                     depth;
    int                     allow_comments;
    int                     handle_floats_manually;
    JSON_malloc_t       malloc;
    JSON_free_t         free;
} JSON_config;


JSON_PARSER_DLL_API void init_JSON_config(JSON_config * config);
JSON_PARSER_DLL_API JSON_parser new_JSON_parser(JSON_config const* config);
JSON_PARSER_DLL_API void delete_JSON_parser(JSON_parser jc);
JSON_PARSER_DLL_API int JSON_parser_char(JSON_parser jc, int next_char);
JSON_PARSER_DLL_API int JSON_parser_done(JSON_parser jc);
JSON_PARSER_DLL_API int JSON_parser_is_legal_white_space_string(const char* s);
JSON_PARSER_DLL_API int JSON_parser_get_last_error(JSON_parser jc);
JSON_PARSER_DLL_API int JSON_parser_reset(JSON_parser jc);


#ifdef __cplusplus
}
#endif 
    

#endif /* JSON_PARSER_H */
