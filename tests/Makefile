CCFLAGS = -g --std=c++11 -Wall

NTLINCDIR = /some path/ntl-11.4.1/include
NTLLIBDIR = /some path/tmp/ntl-11.4.1/src


FHEINCDIR = /some path/helib_library_install/include/helib
FHELIBDIR = /some path/helib_library_install/lib

LIPHEINCDIR = ../include
LIPHELIBDIR = ../src

#LIBS = -L$(LIPHELIBDIR) -lliphe $(FHELIBDIR)/fhe.a $(NTLLIBDIR)/ntl.a -lgmp -lpthread
LIBS = -L$(LIPHELIBDIR) -lliphe $(FHELIBDIR)/libhelib.a $(NTLLIBDIR)/ntl.a -lgmp -lpthread
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

