SRC_DIR=./src/
ALL:
	
	g++ -o kvp-server ${SRC_DIR}activeclients.cpp ${SRC_DIR}logthread.cpp ${SRC_DIR}mainthread.cpp ${SRC_DIR}message.cpp ${SRC_DIR}notifythread.cpp ${SRC_DIR}queue.cpp ${SRC_DIR}senderthread.cpp ${SRC_DIR}typemesparser.cpp  -lpthread
install: 
	mkdir -p $(DESTDIR)/usr/bin
	mkdir -p $(DESTDIR)/usr/share/kvp-server/
	install -m0755  kvp-server $(DESTDIR)/usr/bin/
	install -m0755 contacts.txt $(DESTDIR)/usr/share/kvp-server/
clean:
	rm -f kvp-server
