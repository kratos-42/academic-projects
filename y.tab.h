#define num 257
#define pal 258
#define OPM 259
#define OP 260
#define OPR 261
#define INICIO 262
#define CORPO 263
#define FIM 264
#define IF 265
#define ENDIF 266
#define WHILE 267
#define ENDWHILE 268
#define ELSE 269
#define WRITE 270
#define READ 271
#define INT 272
#define ARRAY 273
#define STRING 274
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int vali;
	char * vals;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;