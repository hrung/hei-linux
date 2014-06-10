#############################################################################

LDFLAGS = -shared -DHEIUNIX
CFLAGS  = -fPIC -O2 -c -Wall -DHEIUNIX

PREFIX ?= $(DESTDIR)/usr
INCLUDEDIR = $(PREFIX)/include
LIBDIR  = $(PREFIX)/lib

LIBNAME = libhei
LIBFILE = $(LIBNAME).so.1.0.1
HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

#############################################################################

all: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -Wl,-soname,$(LIBNAME).so.1 -o $(LIBFILE) $(OBJECTS) -lc

clean:
	rm -vf $(OBJECTS)

distclean: clean
	rm -vf $(LIBNAME)*

%.o: %c
	$(CC) $(CFLAGS) $<

install:
	for file in $(HEADERS); do \
		install -D $$file $(INCLUDEDIR)/$$file; \
	done
	install -D $(LIBFILE) $(LIBDIR)/$(LIBFILE)
	ln -sf $(LIBFILE) $(LIBDIR)/$(LIBNAME).so.1
	ln -sf $(LIBNAME).so.1 $(LIBDIR)/$(LIBNAME).so
