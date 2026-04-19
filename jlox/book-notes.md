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

expression    -> literal | unary | binary | grouping;
literal       -> NUMBER | STRING | "true" | "false" | "nil";
grouping      -> "(" expression ")";
unary         -> ( "-" | "!" ) expression;
binary        -> expression operator expression;
operator      -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/";
