
-include Makefile.local

PKGCONFIG = PKG_CONFIG_PATH="xdrpp:$${PKG_CONFIG_PATH}" pkg-config

# Seems to fix issues with the latest Xcode
LD := $(CXX)

# Don't use :=, or will break first time
XDRC = $(shell $(PKGCONFIG) --variable=xdrc xdrpp)

CPPFLAGS := `$(PKGCONFIG) --cflags xdrpp` -I.
LIBDIRS := -Llibclient
LIBS := -lclient `$(PKGCONFIG) --libs xdrpp` -ldl -L/usr/local/opt/readline/lib -lreadline -lconfig++

CFLAGS := -ggdb3 -O0 -pthread
CXXFLAGS := -ggdb3 -O0 -pthread -std=c++11 -I/usr/local/opt/readline/include
LDFLAGS := -g -pthread $(LIBDIRS)

default: all

include server/Makefile
include libclient/Makefile
include shell/Makefile

.PHONY: all clean xdrpp

all: xdrpp include/server.hh libclient/libclient.a server/server shell/shell 

include/server.hh: include/server.x
	$(XDRC) -hh -o include/server.hh $<

include/two_phrase_commit_common.hh: include/two_phrase_commit_common.x
	$(XDRC) -hh -o include/two_phrase_commit_common.hh $<

include/participant.hh: include/participant.x
	$(XDRC) -hh -o include/participant.hh $<

xdrpp:
	+git submodule update --init
	cd xdrpp; test -f Makefile || ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)"
	$(MAKE) -C xdrpp

clean:
	rm -f server/server
	rm -f server/*.o
	rm -f libclient/*.o
	rm -f libclient/libclient.a
	rm -f shell/*.o
	rm -f shell/shell
	! test -f xdrpp/Makefile || cd xdrpp && $(MAKE) clean

README.html: README.md
	-pandoc -o $@ README.md
