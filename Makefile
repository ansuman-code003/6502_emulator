CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/gio-unix-2.0 -pthread -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I./cJSON 
LDFLAGS := $(shell pkg-config --libs gtk+-3.0)

# Include directories
CXXFLAGS += -I./cJSON 

TARGET := main
SRCS := main.cpp cJSON/cJSON.c
OBJS := $(SRCS:.cpp=.o) $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: cJSON/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
