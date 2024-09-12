grep -v readline valgrind-output.txt| grep -v rl | grep -v '/usr' |\
 grep -v strdup.c | grep -v rl | grep -v xmalloc | grep -v display.c |\
 grep -v bind.c | grep -v tsearch.c | grep -v history.c | grep -v terminal.c |\
 grep -v main.c | egrep -v ' $' | egrep -v '[0-9]$' > valgrind-output.txt
