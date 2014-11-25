#Dzen language parser
This library provides a parser to interpret the Dzen *in-text formating and control language*. See https://github.com/robm/dzen for more information about Dzen.
   
#How-to use
###The beginning
Currently there is just one entry point which accepts a cstring and returns a token list.

```c
dzen_list *list = dzen_parse("^fg(red)I'm red text ^fg(blue)I am blue");
```

###Token iteration
To iterate through a `dzen_list` you can use a `dzen_list_iterator` which is created with the help of `dzen_list_iterator_create(dzen_list *list)`.

```c
dzen_list_iterator *it = dzen_list_iterator_create(list);
```

Now you can iterate from the first token to the last or backward.

```c
// iterate forward
while (dzen_list_iterate_forward(it)) {
    char *string_val = it->token->string_value;
}

// iterate backward
while (dzen_list_iterate_backward(it)) {
    char *string_val = it->token->string_value;
}
```

###The end
After working with the token list and an iterator you have to de-allocated these. Whenever you use an iterator you can use `dzen_list_iterator_destroy(dzen_list_iterator *iterator)`. This function frees the list, too. So it isn't required to destroy the list also. If you don't use an iterator you can use 'dzen_list_destroy(dzen_list *list)' to destroy the list.

```c
// free iterator and list
dzen_list_iterator_destroy(it);

// this call isn't required anymore
// dzen_list_destroy(list);
```

#Dzen language token
A language token represents a logical unit of the input string like a function, a text or a parameter. So the following example input `"^fg(red)I'm red text ^fg(blue)I am blue"` results in a list with 4 token:

1. Function \>\> `DZEN_TOKEN_TYPE_FUNCTION` \>\> `^fg(red)`
2. Text \>\> `DZEN_TOKEN_TYPE_TEXT` \>\> `I'm red text `
3. Function \>\> `DZEN_TOKEN_TYPE_FUNCTION` \>\> `^fg(blue)`
4. Text \>\> `DZEN_TOKEN_TYPE_TEXT` \>\> `I am blue`

##Token structure
A token consists of the following information.

```c
struct dzen_lang_token {
    dzen_token_type type;
    dzen_token_value_modifier value_modifier;
    char *value;
    struct dzen_token *parameter_list;
};
```

* `type`
  * The type of the token like a function or a text
* `value_modifier`
  * A value modifier which is used as an additional info for the value
  * For example this modifier is used to represent the `+` or `-` in the `^p(+-X)` function
* `value`
  * The value of the token, like the name of a function. Could be `NULL`
* `parameter_list` 
  * A list of parameter. Could be `NULL`
  * This field is usually used for parameter with multiple info like the size parameter `2x3` where `2` is the first token in this list and `3` the second one   

##Token types
###Function
A function consists of a name and a parameter list.
