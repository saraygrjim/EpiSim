all: init compilar

init:
	@echo ""
	@echo "Epidemic simulation"
	@echo "Uso de make:"
	@echo "make       -> compilar"
	@echo "make clean -> borrar archivos intermedios"
	@echo ""

compilar: 
	# @echo "Compiling..."
	# bison compiler.y
	# gcc compiler.tab.c -o compiler
	# ./run.sh
	@echo "Executing..."
	# g++ main.cpp -lglut -lGLU -lGL
	g++ main.cpp grid.cpp sim.cpp -lglut -lGLU -lGL
	./a.out

clean:
	@echo "Cleaning..."
	@rm -rf a.out compiler.tab.c *Result.cpp DataStrain*