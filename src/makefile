objects = main.o cv.o 

all : $(objects)
	mkdir result && g++ $(objects) -o editor 

main.o :
cv.o :

.PHONY : clean
clean :
	rm -f editor $(objects)

# how to mkdir result when there is exist a result dir or not terminal the make process
# this may can be implement by use a shell script 
