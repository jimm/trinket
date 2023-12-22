NAME = trinket
# DEBUG = -DDEBUG -DDEBUG_STDERR

WXFLAGS := $(shell wx-config --cxxflags)
WXLIBS := $(shell wx-config --libs)

CPP = $(shell wx-config --cxx)
CPPFLAGS += -std=c++14 -MD -MP -g $(DEBUG) $(WXFLAGS)

LD = $(shell wx-config --ld)
LIBS = -lportmidi

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin

SRC = $(wildcard src/*.cpp) $(wildcard src/pipes/*.cpp) $(wildcard src/wx/*.cpp)
OBJS = $(SRC:%.cpp=%.o)
TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJS = $(TEST_SRC:%.cpp=%.o)
TEST_OBJ_FILTERS = src/main.o
TEST_LIBS = $(LIBS) -lCatch2Main -lCatch2

CATCH_CATEGORY ?= ""

.PHONY: all test install uninstall tags clean distclean

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(WXLIBS) -o $@ $^

-include $(SRC:%.cpp=%.d)
-include $(TEST_SRC:%.cpp=%.d)

test: $(NAME)_test
	./$(NAME)_test --colour-mode=none $(CATCH_CATEGORY)

$(NAME)_test:	$(OBJS) $(TEST_OBJS)
	$(LD) $(LDFLAGS) $(TEST_LIBS) -o $@ $(filter-out $(TEST_OBJ_FILTERS),$^)

install:	$(bindir)/$(NAME)

$(bindir)/$(NAME):	$(NAME)
	cp ./$(NAME) $(bindir)
	chmod 755 $(bindir)/$(NAME)

uninstall:
	rm -f $(bindir)/$(name)

tags:	TAGS

TAGS:	$(SRC)
	etags $(SRC)

clean:
	rm -f $(NAME) $(NAME)_test src/*.o src/pipes/*.o src/wx/*.o test/*.o

distclean: clean
	rm -f src/*.d src/pipes/*.d src/wx/*.d test/*.d
