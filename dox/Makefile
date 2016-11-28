__start__:
	doxygen Doxyfile 2> doxy.log

clean:
	rm -fr doc/html doxy.log

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
