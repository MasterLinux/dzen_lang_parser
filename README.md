#Dzen language parser
This library provides a parser to interpret the Dzen *in-text formating and control language*. See https://github.com/robm/dzen for more information about Dzen.
   
#How-to use
Currently there is just one entry point which accepts a cstring and returns a token list.

```c
struct dzen_token *root = dzen_parse("^fg(red)I'm red text ^fg(blue)I am blue");
```

A `dzen_token` contains a pointer to the next found token. So you can iterate over the whole token list in the following way.

```c
struct dzen_token *next = (*root).next;

while (next != NULL) {
    printf("string value: %s", (*next).string_value);
    next = (*next).next;
}
```

#Dzen token
A token represents a logical unit of the input string like a function, a text or a parameter. So the following example input `^fg(red)I'm red text ^fg(blue)I am blue` results in a list with 5 token of type:

1. DZEN_TOKEN_TYPE_ROOT
2. DZEN_TOKEN_TYPE_FUNCTION
3. DZEN_TOKEN_TYPE_TEXT
4. DZEN_TOKEN_TYPE_FUNCTION
5. DZEN_TOKEN_TYPE_TEXT
