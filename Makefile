CC = gcc
CXX = g++
INCLUDE=include
COMMON_FLAGS=-Wall -std=c++17
CFLAGS = -I $(INCLUDE)  $(COMMON_FLAGS)
CXXFLAGS = -I $(INCLUDE) $(COMMON_FLAGS)

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(filter %.c,$(SOURCES))) \
           $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter %.cpp,$(SOURCES)))
TARGETS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(filter %.c,$(SOURCES))) \
           $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(filter %.cpp,$(SOURCES)))

.PHONY: all clean

all: $(TARGETS)

$(BINDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGETS)