//Autor: Lucas Kovalczuk Paulino
//Mestrando em Computação Aplciada - UDESC - 2020
//Contato para dúvidas - lucaskpaulino@gmail.com

#include <complex>
#include <iostream>
#include <omp.h>
#include <stdio.h>
using namespace std;

// comparação de desempenho ao utilizar threads - openmp
// eixo X ---> num threads --> 1, 2, 3, ,4 ..... 8
// eixo Y ---> aceleração que foi obtida ---> tempo serial (1 thread) / tempo (N threads)
// 3 linhas no gráfico (statico, dinamico, guided)
// tamanh0 do chunk -> 1 (default)
// parametros 2300 - 7900 - 240 ->Contidos em mandelbrot.in

// comando para executar -> ./mandelbrot < mandelbrot.in

int main(){
	int max_row, max_column, max_n; //compatilhar
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;
	double inicio;
	double fim;

	char **mat = (char**)malloc(sizeof(char*)*max_row); // compartilhado

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column); 

	// ***Comandos úteis***

	//tail -f * -> acomopanhar exec
	//lshw -> printar hardware
	//Exemplo de script simples:
	//for i in `seq 1 8`; do for j in `seq 1 10`; do export OMP_NUM_THREADS=$i; ./mandelbrot < mandelbrot.in >> resultado-proc-$i$j.txt; done; done
	

	//foi mudado o tipo de schedule a cada execução dos scripts em anexo
	//inicio parallel/temporizador
	inicio = omp_get_wtime();
	#pragma omp parallel for schedule (guided) shared (max_row, max_column, max_n, mat)
	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c){
			complex<float> z;
			int n = 0;
			while(abs(z) < 2 && ++n < max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1);
			mat[r][c]=(n == max_n ? '#' : '.');
		}
	}
	fim = omp_get_wtime();
	//fim do parallel/temporizador
	//Imprime o tempo
	cout << (fim-inicio);

//****Desenhar Fractais****

//	for(int r = 0; r < max_row; ++r){
//		for(int c = 0; c < max_column; ++c)
//			std::cout << mat[r][c];
//		cout << '\n';
//	}	
}


