# Coderunner Tricks

Suite of files to test a student function (possibly with student tests) with advanced coderunner tricks (capturing segfaults, user prints, function calls...).

The student function may have any signature, but all types involved should have a corresponding utility file. At the moment there are:
- `{int,string}.c`: utilities for integer/string arguments
- `data.{h,c}`: handler for generic types (currently char or int) to be used in containers
- `list.{h,c}`: singly-linked lists of the data type
- `tree.{h,c}`: binary trees of the data type

If further types are needed, similar units can be developed similarly. The actual test library is in `tester.{h,c}`. Three examples are provided, in:
- `{run_,sol_}string.c`: `List parityPath(Tree t)`;
- `{run_,sol_}list.c`: `List antiPrefix(List l, List r)`;
- `{run_,sol_}tree.c`: `List parityPath(Tree t)`.
