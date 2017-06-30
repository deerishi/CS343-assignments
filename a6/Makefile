KIND:=STACK
TYPE:=MC

CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2 -DIMPLKIND_${KIND} -DIMPLTYPE_${TYPE}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS01 = config.o  main.o printer.o WATCard.o Groupoff.o NameServer.o   Parent.o Bank.o BottlingPlant.o WATCard.o WATCardOffice.o student.o Truck.o  VendingMachine.o	# optional build of given program

EXEC01 = soda



#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

-include ImplKind

q1new.o : q1new.cc				# add flags 1st executable, ADJUST SUFFIX (.cc)
	${CXX} ${CXXFLAGS} -nodebug -c $< -o $@

ifeq (${IMPLKIND},${KIND})			# same implementation type as last time ?
${EXEC01} : ${OBJECTS01}
	${CXX} ${CXXFLAGS} -nodebug $^ -o $@
else
ifeq (${KIND},)					# no implementation type specified ?
# set type to previous type
KIND=${IMPLKIND}
${EXEC01} : ${OBJECTS01}
	${CXX} ${CXXFLAGS} -nodebug $^ -o $@
else						# implementation type has changed
.PHONY : ${EXEC01}
${EXEC01} :
	rm -f ImplKind
	touch q1new.cc
	sleep 1
	${MAKE} ${EXEC01} KIND="${KIND}"
endif
endif

ImplKind :
	echo "IMPLKIND=${KIND}" > ImplKind
	sleep 1

#############################################################



#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC01} ${EXECS} ImplKind ImplType
