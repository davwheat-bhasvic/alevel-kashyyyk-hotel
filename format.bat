REM Uses provided .clang-format file...
REM While outputting the file names it edits...
REM And formatting all C files, except the CMakeCCompilerId.c files in all directories...
REM And updating the files in place
clang-format --style=file --verbose --glob="src/**/!(CMakeCCompilerId).c" -i