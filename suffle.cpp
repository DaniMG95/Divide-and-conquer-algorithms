#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
int cnt_div=0;
bool dividido=false;
int division=0;
//generador de ejemplos para el problema de la comparación de preferencias. Simplemente se genera una permutación aleatoria del vector 0,1,2,...,n-2,n-1


double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}
int fuerzabruta(int A[], int n){
	int cnt=0;
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(A[i]>A[j]){
				cnt++;
			}
		}
	}
return cnt;
}



void Comparacion(int A[], int inicio, int fin){
  	for(int i=inicio;i<fin-1;i++){
		for(int j=i+1;j<fin;j++){
			if(A[i]>A[j]){
				cnt_div++;
    			}
  		}
	}
}
void comparacion_final(int inicio, int fin, int B[], int C[], int division){
  for(int i=0;i<division;i++){
		for(int j=0;j<fin-division;j++){
			if(B[i]>C[j]){
				cnt_div++;
    			}
  		}
	}
}

void divide_venceras(int A[], int inicio,int fin ,int umbral)
{
  if (fin- inicio < umbral)
    {
      Comparacion(A, inicio,fin );
    } else {
      		int *B;
		int *C;
		division=(fin-inicio)/2;
		if((fin-inicio)%2==0){
		B = new int[division];	
		C = new int[division];
		}
		else{
		B = new int[division];	
		C = new int[division+1];
		}
		for(int i=0;i<division;i++){
			B[i]=A[i];
		}
		int j=division;
		for(int i=0;i<fin-division;i++){
			C[i]=A[j];
			j++;
		}
      divide_venceras(B, 0, division, umbral);
      divide_venceras(C, 0, fin - division, umbral);
      comparacion_final(inicio, fin, B, C,division);
      delete [] B;
      delete [] C;
    }
}
  


int main(int argc, char * argv[])
{
int contador;
  clock_t tantes,tdespues;
  double tiempo_transcurrido;
  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int * A = new int[n];
  assert(A);
srand(time(0));

for (int j=0; j<n; j++) A[j]=j;
//for (int j=0; j<n; j++) {cout << T[j] << " ";}
//algoritmo de random shuffling the Knuth (permutación aleatoria)
for (int j=n-1; j>0; j--) {
   double u=uniforme();
   int k=(int)(j*u);
   int tmp=A[j];
   A[j]=A[k];
   A[k]=tmp;
}
//for (int j=0; j<n; j++) {cout << T[j] << " ";}
//algoritmo de random shuffling the Knuth (permutación aleatoria)






tantes = clock();
//contador=fuerzabruta(A,n);
divide_venceras(A,0,n,n-1);
  tdespues = clock();
tiempo_transcurrido=(double)(tdespues - tantes) / CLOCKS_PER_SEC;
  cout<<n<<" "<<tiempo_transcurrido<<endl;
}
