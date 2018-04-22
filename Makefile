FILE=alhelp.hpp
TMPFILE=toinstall.hpp
INSTALLLOC=/usr/local/include

.PHONY: install uninstall clean

install: $(FILE)
	sed "/#define ALHELP_IMPLEMENTATION \/\/ for linter in atom/d" $(FILE) > $(TMPFILE)
	sudo cp $(TMPFILE) $(INSTALLLOC)/$(FILE)
	rm $(TMPFILE)

uninstall:
	sudo rm $(INSTALLLOC)/$(FILE)

clean:
	-rm *.gch
	-rm *.o
