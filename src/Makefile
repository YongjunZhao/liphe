CCFLAGS = -g --std=c++11 -Wall

NTLINCDIR = ../../../ntl-10.5.0-multithread/include
NTLLIBDIR = ../../../ntl-10.5.0/src

FHEINCDIR = ../../../HElib-multithread/src
FHELIBDIR = ../../../HElib-multithread/src

LIPHEDIR = ../include

INCS = -I$(NTLINCDIR) -I$(FHEINCDIR) -I$(LIPHEDIR)

OBJ = helib_keys.o helib_number.o primes.o thread_pool.o

libliphe.a: $(OBJ)
	ar rUv libliphe.a $(OBJ)

%.o: %.cc
	g++ $(CCFLAGS) -c  $(INCS) $<

clean:
	rm -f *.o libliphe.a
