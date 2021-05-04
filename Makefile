all: init compilar

init:
	@echo ""
	@echo "Epidemic simulation"
	@echo "Uso de make:"
	@echo "make       -> compilar"
	@echo "make clean -> borrar archivos intermedios"
	@echo ""

compilar: 
	# g++ main.cpp -lglut -lGLU -lGL
	# g++ main.cpp grid.cpp sim.cpp cell.cpp -lglut -lGLU -lGL
	# ./a.out

	bison compiler.y
	gcc compiler.tab.c -o compiler

clean:
	@echo "Cleaning..."
	# @rm -rf a.out
	@rm -rf compiler compiler.tab.c