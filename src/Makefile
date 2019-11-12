CCFLAGS = -g --std=c++11 -Wall

NTLINCDIR = ~/some path/ntl-11.4.1/include
NTLLIBDIR = ~/some path/ntl-11.4.1/src


FHEINCDIR = ~/some path/helib_library_install/include/helib
FHELIBDIR = ~/some path/helib_library_install/lib

LIPHEDIR = ../include

INCS = -I$(NTLINCDIR) -I$(FHEINCDIR) -I$(LIPHEDIR)

OBJ = helib_keys.o helib_number.o primes.o thread_pool.o

libliphe.a: $(OBJ)
	ar rUv libliphe.a $(OBJ)

%.o: %.cc
	g++ $(CCFLAGS) -c  $(INCS) $<

clean:
	rm -f *.o libliphe.a
