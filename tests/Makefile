CCFLAGS = -g --std=c++11 -Wall

NTLINCDIR = ../../../ntl-10.5.0-multithread/include
NTLLIBDIR = ../../../ntl-10.5.0-multithread/src

FHEINCDIR = ../../../HElib-multithread/src
FHELIBDIR = ../../../HElib-multithread/src

LIPHEINCDIR = ../include
LIPHELIBDIR = ../src

LIBS = -L$(LIPHELIBDIR) -lliphe $(FHELIBDIR)/fhe.a $(NTLLIBDIR)/ntl.a -lgmp -lpthread
INCS = -I$(NTLINCDIR) -I$(FHEINCDIR) -I$(LIPHEINCDIR)

TESTS = test_zp test_helib\
	test_spirit_zp test_spirit_helib

all: $(TESTS)

test_zp: test_zp.o

test_helib: test_helib.o

test_spirit_zp: test_spirit_zp.o

test_spirit_helib: test_spirit_helib.o


%: %.o
	g++ $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cc
	g++ $(CCFLAGS) -c  $(INCS) $<

clean:
	rm -f *.o $(TESTS)

