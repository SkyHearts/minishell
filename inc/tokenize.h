# ifndef TOKENIZE_H
# define TOKENIZE_H

typedef struct token_s
{
    struct source_s *src;       /* source of input */
    int    text_len;            /* length of token text */
    char   *text;               /* token text */
    int     type;               /* type of input [cmd]/[operator] */
    int     precedence;         /* priority of cmdsdfglj */
}       token_t;

#endif