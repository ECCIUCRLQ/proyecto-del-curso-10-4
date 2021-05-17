# include <cstdlib>
# include <cmath>
# include <ctime>
# include <omp.h>
# include <iostream>
# include <vector>
using namespace std;

void prime_table(int prime_num, vector< int >& primes);
void sine_table(int sine_num, vector< double >& sines);

int main() {
	int prime_num;
	vector< int > primes;
	int sine_num;
	vector< double > sines;
	double wtime;
	double wtime1;
	double wtime2;

	cout << endl;
	cout << "MULTITASK_OPENMP:" << endl;
	cout << "  Demuestra cómo OpenMP puede hacer \"multitasking\" usando la directiva " << endl;
	cout << "  SECTIONS para ejecutar varias tareas diferentes en paralelo." << endl;

	cout << "Digite la cantidad de primos a encontrar: ";
	cin >> prime_num; cout << endl;

	cout << "Digite la cantidad de valores de la función \"sin\" a encontrar: ";
	cin >> sine_num; cout << endl;

	// se asigna tamaño apropiado a los vectores
	primes.resize(prime_num, 0);
	sines.resize(sine_num, 0);

	wtime = omp_get_wtime();

# pragma omp parallel shared ( prime_num, primes, sine_num, sines )
	{
# pragma omp single
		{
			int num_hilos = omp_get_num_threads();
			cout << "Cantidad de hilos en ejecución: " << num_hilos << endl;
		}
# pragma omp sections
		{
# pragma omp section
			{
				int my_id = omp_get_thread_num();
# pragma omp critical
				{
					cout << "El hilo: " << my_id << " ejecuta primos." << endl;
				}
				wtime1 = omp_get_wtime();
				prime_table(prime_num, primes);
				wtime1 = omp_get_wtime() - wtime1;
			}
# pragma omp section
			{
				int my_id = omp_get_thread_num();
# pragma omp critical
				{
					cout << "El hilo: " << my_id << " ejecuta valores de sin." << endl;
				}
				wtime2 = omp_get_wtime();
				sine_table(sine_num, sines);
				wtime2 = omp_get_wtime() - wtime2;
			}
		}
	}
	wtime = omp_get_wtime() - wtime;

	cout << endl;
	cout << "  El último primo encontrado fue " << primes[prime_num - 1] << endl;
	cout << "  El último valor de \"sin\" encontrado fue " << sines[sine_num - 1] << endl;
	cout << endl;
	cout << "  Tiempo transcurrido = " << wtime << "\n";
	cout << "  Tiempo de la tarea de primos = " << wtime1 << "\n";
	cout << "  Tiempo de la tarea de valores de \"sin\" = " << wtime2 << "\n";

	// para que no termine cerrando la consola inmediatamente:
	int int_falso;
	cin >> int_falso;
}

// REQ: prime_num > 0
// EFE: retorna por referencia el vector primes con los primos encontrados.
void prime_table(int prime_num, vector< int >& primes) {
	int i, p, prime;
	p = 0;

	i = 2;
	while (p < prime_num)
	{
		prime = 1;

		for (int j = 2; j < i; j++)
		{
			if ((i % j) == 0)
			{
				prime = 0;
				break;
			}
		}

		if (prime)
		{
			primes[p] = i;
			p = p + 1;
		}
		i = i + 1;
	}
}

// REQ: sine_num > 0
// EFE: retorna por referencia el vector primes con los valores de sin encontrados.
void sine_table(int sine_num, vector< double >& sines) {
	double a;
	double pi = 3.141592653589793;

	for (int i = 0; i < sine_num; i++)
	{
		sines[i] = 0.0;
		for (int j = 0; j <= i; j++)
		{
			a = (double)(j)* pi / (double)(sine_num - 1);
			sines[i] = sines[i] + sin(a);
		}
	}
}