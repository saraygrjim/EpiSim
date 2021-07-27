all: init compilar

init:
	@echo ""
	@echo "Epidemic simulation"
	@echo "Uso de make:"
	@echo "make       -> Ejecutar"
	@echo "make clean -> borrar archivos intermedios"
	@echo ""

compilar: 
	@echo "Compiling..."
	@bison compiler_files/compiler.y
	@gcc compiler.tab.c -o compiler_files/compiler
	@./compiler_files/run.sh $(FILE)
	# @echo "Executing..."
	# @g++ main.cpp grid.cpp sim.cpp -lglut -lGLU -lGL
	# @./a.out
	# @echo "Generating results..."
	# @./plot.sh

clean:
	@echo "Cleaning..."
	@rm -rf a.out compiler.tab.c *Result.cpp DataStrain*