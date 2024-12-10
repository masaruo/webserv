set listsize 25
set confirm off
set pagination on
set print pretty on
set print element 0
set logging overwrite on
set logging redirect on

wh src -5

skip -gfile /usr/include/*
skip -gfile /usr/include/c++/*/*/*
skip -gfile /usr/include/c++/*/*
skip -gfile /usr/include/c++/*

alias -a ib = info b
alias -a ia = info args
alias -a il = info locals
