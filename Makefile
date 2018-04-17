FILE=alhelp.hpp
INSTALLLOC=/usr/local/include

.PHONY: install uninstall clean

install: $(FILE)
	sudo cp $(FILE) $(INSTALLLOC)

uninstall:
	sudo rm $(INSTALLLOC)/$(FILE)

clean:
	-rm *.gch
	-rm *.o
