# minishell

[x] when .
[x] && or any double --> and also modify when get exit_status=2 and exit

[x] "" and . => execve permission denied

[x] *

[x] $ creates loop
[x] export --> print export KEY="value"
[ ] when change PATH=value still should be able to run  absolute path
[SANDY] exit si tu met un argument invalid genre "a" "a" doit mettre not numberc ...
[x]je veux unet PWD par pitie
[x]ctrl + d doit pas mettre le status a 131
[x]le is_directory doit etre a 126
[x] env -i ./minishell -> $OLDPWD -> segfault
[x]"bash: /: Is a directory
$>"    126
 got 127

[ ] bash: : command not found    127
got 2  --> not sure what is this

[x] || => create a segfault and broke the program
{space}|{space} => segfault

[It is no problem] echo "          " | cat -e
=> Memcheck, a memory error detector

[x] env -i ./minishell + unset everything but PWD still stay; 

[x] Leak in pipe when minishell[0]> ls | dfs
dfs: command not found

[x] " " only this segfault
[x] .d minishell[126]> .d execve failed: No such file or directory -> command not found
