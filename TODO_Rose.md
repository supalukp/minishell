
# TO DO LIST

[ ] execution_each_branch();
[ ] build in funtions
[ ] How to handle || && when execute
[ ] Handle parenthesis ()

# Step
1. split branch cmd / redirect / pipe
2. token



# Note
- branch should contain infile / outfile of each cmd (io can have more than 1)
- Make a list that give the rank for execution (rank1 && rank2) && rank3
- Shell always executes inside the parentheses first — because parentheses () mean subshell, and subshell runs first to produce a result.
- (..) mean subshell -> child process


# Sources

- Basic of AST example (Implement a mathematical expression parser)
https://stackoverflow.com/questions/75940234/correct-construction-of-ast-in-c 
- Pipe Exercution 
https://stackoverflow.com/questions/59602615/execute-pipes-recursively-in-abstract-syntax-tree 
- Lets Build a Linux Shell 
https://medium.com/@mohammedisam2000/lets-build-a-linux-shell-part-i-954c95911501 
- Writing Your Own Shell (pdf)
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf 
- Building Abstract Syntax Trees in C
https://lambda.uta.edu/cse5317/notes/node26.html
https://www.reddit.com/r/C_Programming/comments/lzq2t2/how_to_make_an_ast_in_c/


# Example cmd
(ls no_file && echo "Found" > found.txt || echo "Not found" > not_found.txt) && echo "Done" > done.txt

