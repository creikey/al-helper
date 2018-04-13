FILE=alhelp.hpp
INSTALLLOC=/usr/local/include/

.PHONY: install uninstall

install: $(FILE)
	sudo cp $(FILE) $(INSTALLLOC)

uninstall:
	sudo rm $(INSTALLLOC)/$(FILE)
