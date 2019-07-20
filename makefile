SFMLLIBS = -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS = -g -O0

machine.o: machine.C
	g++ -c machine.C $(CXXFLAGS)


collision.o: collision.C
	g++ -c collision.C $(CXXFLAGS)


movements.o: movements.C
	g++ -c movements.C $(CXXFLAGS)

alpha_version.o: alpha_version.C
	g++ -c alpha_version.C $(CXXFLAGS)

compile: alpha_version.o movements.o collision.o machine.o 
	g++ alpha_version.o machine.o movements.o collision.o -o alpha_version.x $(CXXFLAGS) $(SFMLLIBS)

run: alpha_version.x
	./alpha_version.x
