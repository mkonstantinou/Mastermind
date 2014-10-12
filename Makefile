NAME=mastermind
SRC=main.c
RM=rm -f
OUTPUT=mastermind
#
all: 
	gcc $(SRC) -o $(OUTPUT)
clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.swp
	-$(RM) *.core
fclean:clean
re:fclean all
