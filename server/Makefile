
SERVER_SRC := server/server.cc \
			  server/serverimpl.cc \
			  server/participant.cc \
			  server/serverdb.cc \
			  server/sqlstmt.cc \
			  server/sqlite3.c  \
			  server/utils.cc  \
			  server/coordinator.cc

SERVER_OBJ := $(SERVER_SRC:.c=.o)
SERVER_OBJ := $(SERVER_OBJ:.cc=.o)
$(SERVER_OBJ): include/server.hh

server/%.o: server/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

server/%.o: server/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Generate initial files to be edited
server-scaffold: include/server.x xdrpp
	mv server/serverimpl.hh server/serverimpl.hh-bak
	mv server/serverimpl.cc server/serverimpl.cc-bak
	$(XDRC) -serverhh -o server/serverimpl.hh $<
	$(XDRC) -servercc -o server/serverimpl.cc $<

participant-scaffold: include/participant.x xdrpp
	mv server/participant.hh server/participant.hh-bak
	mv server/participant.cc server/participant.cc-bak
	$(XDRC) -serverhh -o server/participant.hh $<
	$(XDRC) -servercc -o server/participant.cc $<

server/server: $(SERVER_OBJ)
	$(LD) -o $@ $(LDFLAGS) $(SERVER_OBJ) $(LIBS)
