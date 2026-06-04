# Book notes

## Parser

Start with rules, use them to generate strings that are in the grammar - strings created this way are called **derivations**, because each is derived from the rules of the grammar

Rules are called **productions** because they produce strings in the grammar

Each production in a context free grammar has a **head** (its name), and a **body** (which describes what it generates). Thy body is a list of symbols.

Kinds of symbols

- Terminal - an 'end point' (think of as a literal value - individual lexemes/tokens)
- Non-terminal - a named reference to another rule in the grammar (do X, and insert what it produces here)

Recursion in the grammar is a good sign that the language being designed is context free (instead of regular)

### Lox (initial) grammar

```text
expression    -> literal | unary | binary | grouping ;
literal       -> NUMBER | STRING | "true" | "false" | "nil" ;
grouping      -> "(" expression ")" ;
unary         -> ( "-" | "!" ) expression ;
binary        -> expression operator expression ;
operator      -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;
```

### Lox (expanded) grammar

```text
expression    -> equality ;
equality      -> comparison ( ( "!=" | "==" ) comparison )* ;
comparison    -> term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term          -> factor ( ( "-" | "+" ) factor )* ;
factor        -> unary ( ( "/" | "*" ) unary )* ;
unary         -> ( "!" | "-" ) unary | primary ;
primary       -> NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
```

### Lox statement grammar

```text
program       -> statement* EOF ;
statement     -> exprStmt | printStmt ;
exprStmt      -> expression ";" ;
printStmt     -> "print" expression ";" ;
```

### Lox (expanded) statement grammar

```text
program       -> declaration* EOF ;
declaration   -> varDecl | statement ;
statement     -> exprStmt | printStmt ;
varDecl       -> "var" IDENTIFIER ( "=" expression )? ";" ;

primary       -> NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" | IDENTIFIER ; // updated 'primary' grammar from earlier
```

### Lox assignment syntax

```text
expression    -> assignment ;
assignment    -> IDENTIFIER "=" assignment | equality ;
```

### Block syntax

```text
statement     -> exprStmt | printStmt | block ;
block         -> "{" declaration* "}" ; 
```

### If statement syntax

```text
statement     -> exprStmt | ifStmt | printStmt | block ;
ifStmt        -> "if" "(" expression ")" statement ( "else" statement )? ;
```

### Logical operator syntax

```text
expression    -> assignment ;
assignment    -> IDENTIFIER "=" assignment | logic_or ;
logic_or      -> logic_and ( "or" logic_and )* ;
logic_and     -> equality ( "and" equality )* ;
```

### While loop syntax

```text
statement     -> exprStmt | ifStmt | printStmt | whileStmt | block ;

whileStmt     -> "while" "(" expression ")" statement ;
```

## For loop syntax

```text
statement     -> exprStmt | forStmt | ifStmt | printStmt | whileStmt | block ;
forStmt       -> "for" "(" ( varDecl | exprStmt | ";" )
                 expression? ";"
                 expression? ")" statement 
