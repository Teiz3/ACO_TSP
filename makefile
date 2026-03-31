CXX = g++
CXXFLAGS_COMMON = -std=c++17 -Wall -Wpedantic -Wextra -fexceptions -fopenmp
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Change to debug to compile with debugging flags
MODE = debug

ifeq ($(MODE),release)
	CXXFLAGS = $(CXXFLAGS_COMMON) $(SFMLFLAGS) -O3 -march=native -flto -mavx2 -DNDEBUG
else
	CXXFLAGS = $(CXXFLAGS_COMMON) $(SFMLFLAGS) -g
endif

CXXFLAGS += -MMD -MP
-include $(OUT_OBJS:.o=.d)

TARGET = aco

BUILDDIR = build

SRCDIR = src

SOURCES := $(wildcard $(SRCDIR)/*.cpp) \
           $(wildcard $(SRCDIR)/*/*.cpp)

OUT_OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OUT_OBJS)
	$(CXX) $(CXXFLAGS) $(OUT_OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p results
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT_OBJS) $(TARGET)
