FLAGS=-O3
# list .s source files here
SRCFILES=tabflip.c

all:	tab_flip

tabflip: $(SRCFILES) 
	gcc $(FLAGS) -o tab_flip $^ 

clean: 
	rm -f *.o tab_flip

