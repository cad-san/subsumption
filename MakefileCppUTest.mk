#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = subsumption

#--- Inputs ----#
CPPUTEST_HOME = cpputest
CPP_PLATFORM = gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src\
	$(PROJECT_HOME_DIR)/src/agent\

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/tests\
	$(PROJECT_HOME_DIR)/tests/agent\

INC_DIRS = \
	$(PROJECT_HOME_DIR)/include\
	$(PROJECT_HOME_DIR)/include/agent\
	$(PROJECT_HOME_DIR)/mocks\

INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include\
	${INC_DIRS}

MOCKS_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/mocks\
	$(PROJECT_HOME_DIR)/mocks/agent\

CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
CPPUTEST_CXXFLAGS += -include tests/PreIncludeFiles.h
LD_LIBRARIES = -lpthread

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

uncrustify:
	${SILENCE} ${PROJECT_HOME_DIR}/scripts/uncrustify.sh $(SRC_DIRS)
	${SILENCE} ${PROJECT_HOME_DIR}/scripts/uncrustify.sh $(INC_DIRS)
	${SILENCE} ${PROJECT_HOME_DIR}/scripts/uncrustify.sh $(TEST_SRC_DIRS)
	${SILENCE} ${PROJECT_HOME_DIR}/scripts/uncrustify.sh $(MOCKS_SRC_DIRS)
