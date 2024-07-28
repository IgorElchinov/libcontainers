

TARGET=avl
CC=gcc
MAINDIR=example
SRCDIR=lib/src
BINDIR=lib/bin
HEADDIR=lib/headers
FLAGS= -g -Wall -iquote $(HEADDIR)
ADD=
DEPENDENCIES=

all: make_dirs $(TARGET)_example.out

make_dirs:
	mkdir -p  $(BINDIR)

$(TARGET)_example.out: $(TARGET)_example.o lib$(TARGET).so $(TARGET)_dependencies # final compilation
	$(CC) $< -L$(BINDIR) -o $@ -l$(TARGET) $(DEPENDENCIES)

$(TARGET)_example.o: $(MAINDIR)/$(TARGET)_example.c                               # compiling example
	$(CC) -c $< -o $@ $(FLAGS)

$(TARGET).so: $(HEADDIR)/$(TARGET).h

lib$(TARGET).so: $(SRCDIR)/$(TARGET).c $(TARGET)_dependencies                     # compiling dynamic library
	$(CC) -c --shared $< -o $(BINDIR)/$@ $(FLAGS) -fPIC $(DEPENDENCIES)

lib: lib$(TARGET).so

superlib: libcontainers.so                                                        # target to compile whole library

libcontainers.so: $(HEADDIR)/containers.h

libcontainers.so: $(SRCDIR)/*.c
	$(CC) --shared $^ -o $(BINDIR)/$@ $(FLAGS) -L$(BINDIR) -fPIC

run: all                                                                          # target to run code
	./runner $(TARGET)_example.out

clean:                                                                            # target to clean binary files
	rm -f *.out *.o

#         === dependencies ===

unordered_set_dependencies:
	$(eval DEPENDENCIES += -llist_str)
	$(eval DEPENDENCIES += -lhash_table)

hash_table_dependencies:
	$(eval DEPENDENCIES += -llist_str)

list_of_map_nodes_dependencies:
	$(eval DEPENDENCIES += -lmap_node)

unordered_map_dependencies:
	$(eval DEPENDENCIES += -llist_of_map_nodes)
	$(eval DEPENDENCIES += -lmap_node)
	$(eval DEPENDENCIES += -lhash_table)
	$(eval DEPENDENCIES += -llist_str)
list_str_dependencies:

vector_dependencies:

avl_dependencies:
	$(eval DEPENDENCIES += -lvector)

list_dependencies:

l2_dependencies:

deque_dependencies:

heap_dependencies:

queue_dependencies:
	$(eval DEPENDENCIES += -ldeque)

bst_dependencies:
	$(eval DEPENDENCIES += -lvector)

map_node_dependencies:

stack_dependencies:
	$(eval DEPENDENCIES += -ldeque)

vector_uint8_dependencies:
