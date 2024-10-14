set listsize 25
set confirm off
set pagination off
set print pretty on
set print element 0
set logging overwrite on
set logging redirect on

skip -gfile /usr/include/*
skip -gfile /usr/include/c++/*/*/*
skip -gfile /usr/include/c++/*/*
skip -gfile /usr/include/c++/*

alias -a ib = info b
alias -a ia = info args
alias -a il = info locals
