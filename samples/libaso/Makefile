target=a
objs=b c a

$(target): clean $(objs:%=%.o)
	g++ -o $(target) $(objs:%=%.o)

#$(objs:%=%.o):	$(objs:%=%.c)
#	gcc  -c $(@:%.o=%.c) -o $@
#

a.o:	a.c
	g++ -fPIC -c a.c -o a.o -I./

b.o:	b.c
	g++ -fPIC -c b.c -o b.o -I./

c.o:	c.c
	gcc -fPIC -c c.c -o c.o -I./


static:
	ar crv liba.a $(objs:%=%.o)

shared:
	gcc -shared -o liba.so  $(objs:%=%.o)

clean:
	rm -f $(objs:%=%.o) $(target) liba.a liba.so
