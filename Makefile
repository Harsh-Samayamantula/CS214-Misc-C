sort:
	gcc sort.c -o sort -g -Wall -Wvla -fsanitize=address
grep:
	gcc grep.c -o grep -g -Wall -Wvla -fsanitize=address
uniq:
	gcc uniq.c -o uniq -g -Wall -Wvla -fsanitize=address
monster:
	gcc monster.c -o monster -g -Wall -Wvla -fsanitize=address
factor:
	gcc factor.c -o factor -g -Wall -Wvla -fsanitize=address

test: 
	make monster && ./monster 8 7 1 4 7 3 7 1