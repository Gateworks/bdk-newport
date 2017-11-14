
src:=
src+=bdk.txt
src+=bdk-release-notes.txt

pdfs:=$(patsubst %.txt,%.pdf,$(src))

default: $(pdfs) api-docs lua-modules

clean:
	rm -rf $(pdfs) api-docs lua-modules

%.html: %.txt
	asciidoc -d book -a toc2 -a theme=flask -a toclevels=2 -a numbered -o $@ $^

%.pdf: %.txt
	a2x -f pdf --fop $^

api-docs: Doxyfile
	doxygen

LUA_FILES:=$(wildcard ${BDK_ROOT}/lua-modules/*)
# ldoc below will use luarocks, which expect shell environment variables tweaked
lua-modules: $(LUA_FILES)
	eval `luarocks path --bin` && ldoc -p "BDK Lua Modules" -t "BDK Lua Module Reference" -f discount -d $@ ${BDK_ROOT}/lua-modules
	touch $@

.PHONY: copy
copy:
	rm -rf /var/www/html/thunder/bdk/*
	cp -r $(pdfs) api-docs lua* /var/www/html/thunder/bdk/
