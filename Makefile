OUTLIB := parseargs.so
OUTAR  := parseargs.a
TARGETS := argument parser versioning parseargs

OBJECTS := $(TARGETS:%=tmp/%.o)

SEP := $(subst x, ,xxxxxxx)

all: $(OUTLIB) $(OUTAR)

$(OUTLIB): $(OBJECTS)
	@echo "LINK$(SEP)$@$(SEP)(from $^)"
	@g++ $^ -o $@ -shared -fPIC

$(OUTAR): $(OBJECTS)
	@echo "LINK$(SEP)$@$(SEP)(from $^)"
	@gcc-ar rcs $@ $^

tmp/%.o: src/%.cpp
	@echo "COMP$(SEP)$@$(SEP)(from $<)"
	@mkdir -p tmp
	@g++ $< -c -o $@ -I. -fPIC

.PHONY: clean delete_o delete_lib clean_tmp

clean_tmp: delete_o

delete_o:
	@for o in $(OBJECTS); do \
		[ -f $$o ] && echo "RM  $(SEP)$$o" && rm -f $$o; \
	done

delete_lib:
	@echo "RM  $(SEP)$(OUTLIB)"
	@rm -f $(OUTLIB)
	@echo "RM  $(SEP)$(OUTAR)"
	@rm -f $(OUTAR)

clean: delete_o delete_lib
