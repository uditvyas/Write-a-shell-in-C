default: all

all: dir terminal ls mv cp cd grep mkdir rm chmod pwd cat
	@echo "Navigate into the directory created: 'Terminal'"

dir:
	@mkdir Terminal

terminal:
	gcc -o Terminal/terminal source/terminal.c

ls: 
	gcc -o Terminal/ls source/myls.c

mv: 
	gcc -o Terminal/mv source/mymv.c

pwd:
	gcc -o Terminal/pwd source/mypwd.c

cd:
	gcc -o Terminal/cd source/mycd.c

cp:
	gcc -o Terminal/cp source/mycp.c

grep:
	gcc -o Terminal/grep source/mygrep.c

chmod:
	gcc -o Terminal/chmod source/mychmod.c

mkdir:
	gcc -o Terminal/mkdir source/mymkdir.c

rm:
	gcc -o Terminal/rm source/myrm.c

cat:
	gcc -o Terminal/cat source/mycat.c

run:
	cd Terminal
	./Terminal/terminal
clean:
	rm -r Terminal