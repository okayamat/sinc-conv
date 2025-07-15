# Makefile ( n source file 1 execute file version )

PACKAGE	= SE_ex6
SRCS	= $(PACKAGE).cpp SE_trans.cpp polevl.cpp fresnl.cpp
HEADS	= SE_trans.h mconf.h
OBJS	= $(SRCS:.cpp=.o)
FILES	= $(PACKAGE).mak $(HEADS) $(SRCS)
VER	= `date +%Y%m%d`


### command and flags ###
# uncomment when debugging
#DEBUG	= -ggdb -pg # -lefence

# common (*.o)
LD	= g++
EIG_LD	= `pkg-config --libs eigen3`
LDFLAGS	= -g $(DEBUG) $(EIG_LD)
#LDLIBS	= -lm

# C (*.c)
CC	= gcc
OPTIMIZE= #-O2
CFLAGS	= -g $(OPTIMIZE) -Wall $(DEBUG)
CPPFLAGS= -I.

# C++ (*.cpp)
CXX	= g++
EIG_FL	= `pkg-config --cflags eigen3`
CXXFLAGS= -g $(OPTIMIZE) -Wall $(DEBUG) $(EIG_FL)

# Fortran77 (*.f)
FC	= f77
FFLAGS	= -Wall $(DEBUG)

# Pascal (*.p)
PC	= pc
PFLAGS	= -Wall $(DEBUG)

# etc
SHELL	= /bin/sh
RM	= rm -f
PROF	= gprof


### rules ###

.SUFFIXES:
.SUFFIXES: .o .c .cpp .f .p

all: $(PACKAGE)

$(PACKAGE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(OBJS): $(HEADS) $(PACKAGE).mak

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
.cpp.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
.f.o:
	$(FC) $(FFLAGS) -c $< -o $@
.p.o:
	$(PC) $(PFLAGS) $(CPPFLAGS) -c $< -o $@


### useful commands ###

clean:
	$(RM) $(PACKAGE) $(OBJS)
	$(RM) core gmon.out *~ #*#

tar:
	@echo $(PACKAGE)-$(VER) > .package
	@$(RM) -r `cat .package`
	@mkdir `cat .package`
	@ln $(FILES) `cat .package`
	tar cvf - `cat .package` | gzip -9 > `cat .package`.tar.gz
	@$(RM) -r `cat .package` .package

zip:
	zip -9 $(PACKAGE)-$(VER).zip $(FILES)


prof: run
	$(PROF) $(PACKAGE) | less

run: all
#	./$(PACKAGE) < sample-data | less
	./$(PACKAGE)
