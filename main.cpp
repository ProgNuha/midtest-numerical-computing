/* ==========================================================
	Sumber kode https://www.codesansar.com/numerical-methods 
 	Diedit oleh
	Mufida Nuha Salimah 
	171511050 
	Komputasi Numerik
   ========================================================== */

#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

/* Diberikan persamaan sistem persamaan linear (SPL)
   x + 19y + 14z = 26
   2x + 3y + 6z = 27
   6x - y - 3z = 3
*/

/* Diubah ke bentuk persamaan:
   x = (26-19y-14z)
   y = (27-2x-6z)/3
   z = (3-6x+y)/-3
*/

/* Mendefinisikan fungsi */
#define f1(x,y,z)  (26-19*y-14*z)
#define f2(x,y,z)  (27-2*x-6*z)/3
#define f3(x,y,z)  (3-6*x+y)/-3

/* Mendefinisikan ordo maksimum matriks */
#define   SIZE   10

/* Mendefinisikan prosedur */
void jacobi_iteration();
void gauss_seidel_iteration();
void gauss_elimination();
void birge_vieta();

/* Kelengkapan */
void welcome();
void equation();
void menu(int no_menu);
int input_menu();

float p[6], ply[6],q[6];

float synth(int m, float r){
    int i;
    q[0] = p[0];
    for(i=1;i<=m;i++){
                    q[i] = (q[i-1]*r)+p[i];
    }

    printf("\n");
    for(i=0;i<m;i++){
                    printf("\t%f",q[i]);
    }
    printf("\t%f",q[m]);
    return(q[m]);
}


int main(){
	menu(input_menu());


}

void welcome(){
	printf("==========Remedial Evaluasi Tengah Semester========\n");
	printf("================Komputasi Numerik==================\n");
	printf("===============Mufida Nuha Salimah=================\n");
	printf("====================171511050======================\n\n\n");
}

void equation(){
	printf("Diberikan persamaan sistem persamaan linear (SPL)\n");
	printf("  x + 19y + 14z = 26\n");
	printf("  2x + 3y + 6z = 27\n");
	printf("  6x - y - 3z = 3\n");
}

int input_menu(){
	int menu_,no_menu;
	
	welcome();
	printf("1. Metode Bierge-Vieta\n"); 
	printf("2. Metode Jacobi\n"); 
	printf("3. Metode Gauss - Siedel\n"); 
	printf("4. Eliminasi Gauss\n"); 
	printf("\nTampilkan jawaban dari no\n > ");
	scanf("%d", &no_menu);
	
   switch (no_menu) 
   { 
       case 1: 	menu_ = 1;
               	break; 
       case 2: 	menu_ = 2;
                break; 
       case 3: 	menu_ = 3;
	   			break; 
       case 4: 	menu_ = 4;
	   			break; 
       default: printf("Input Error"); 
       			exit(0);
   } 

	return menu_;
}

void menu(int no_menu){
	
   switch (no_menu) 
   { 
       case 1: 	printf("1. Metode Bierge-Vieta"); 
       			system("cls");
       			birge_vieta();
               	break; 
       case 2: 	printf("2. Metode Jacobi"); 
       			system("cls");
       			equation();
       			jacobi_iteration();
                break; 
       case 3: 	printf("3. Metode Gauss - Siedel"); 
       			system("cls");
       			equation();
       			gauss_seidel_iteration();
               	break; 
       case 4: 	printf("4. Eliminasi Gauss"); 
       			system("cls");
       			gauss_elimination();
       			break; 
       default: printf("Input Error"); 
       			exit(0);
   } 
}


/* Iterasi Birge-Vieta */
void birge_vieta(){
	int m,i,flag=0;
    float r, x,x1, fx, fdx;
    
    /*header*/
    printf("\t\tMETODE BIRGE-VIETA");
    
    /* Input koefisien tertinggi */
    printf("\n Input koefisien tertinggi dari sebuah persamaan polinom (max 5): ");
    scanf("%d",&m);
    
    /* Input nilai dari masing-masing koefisien */
    for(i=0;i<=m;i++){
		printf("\n Koefisien x^%d = ",m-i);
		scanf("%f",&p[i]);
		ply[i] = p[i];
    }
    
    /* Input nilai tebakan awal */
    printf("\n Input tebakan awal x0 : ");
    scanf("%f",&r);
    x = r;

	/* Perhitungan */
    do{
		printf("\n%f\n",x);
		fx = synth(m,x);
		
	    for(i=0;i<=m;i++){
	    	p[i]=q[i];
	    }
	    
		fdx = synth(m-1,x);
		x1 = x - (fx/fdx);

		if(fabs(x1-x) <= 0.0009){
			flag = 1;
		}
       	
		x = x1;

		for(i=0;i<=5;i++){
			p[i]=ply[i];
		}

    }while(flag!=1);

}

/* Iterasi Jacobi */
void jacobi_iteration(){
	float x0=0, y0=0, z0=0, x1, y1, z1;
	int count=1;
	
	/*header*/
	printf("\n\nDengan menggunakan METODE JACOBI\n");
	printf("\nIterasi   x\t  y\t  z\n  ke-\n");
	
	/*Iterasi Jacobi*/
	for(int i=0;i<2;i++){
		/* Perhitungan */
		x1 = f1(x0,y0,z0);
		y1 = f2(x0,y0,z0);
		z1 = f3(x0,y0,z0);
		printf("  %d\t%0.2f\t%0.2f\t%0.2f\n",count, x1,y1,z1);
		
		/* Iterasi */
		count++;
		
		/* Untuk iterasi selanjutnya, input nilai baru */
		x0 = x1;
		y0 = y1;
		z0 = z1;	
	}
}

/* Iterasi Gauss Seidel */
void gauss_seidel_iteration(){
	float x0=0, y0=0, z0=0, x1, y1, z1;
	int count=1;
	
	/*header*/
	printf("Dengan menggunakan METODE GAUSS SEIDEL");
	printf("\nIterasi   x\t  y\t  z\n  ke-\n");
	
	/*Iterasi Gauss Seidel*/
	for(int i=0;i<2;i++){
		/* Perhitungan */
		x1 = f1(x0,y0,z0);
		y1 = f2(x1,y0,z0);
		z1 = f3(x1,y1,z0);
		printf("  %d\t%0.2f\t%0.2f\t%0.2f\n",count, x1,y1,z1);
		
		/* Iterasi */
		count++;
		
		/* Untuk iterasi selanjutnya, input nilai baru */
		x0 = x1;
		y0 = y1;
		z0 = z1;	
	}
}

/* Metode faktorisasi segitiga dengan menggunakan eliminasi Gauss dengan menerapkan strategi (partial) pivoting*/
void gauss_elimination(){
	float a[SIZE][SIZE], x[SIZE], ratio;
	int i,j,k,n;
//	system("cls");
	
	 /* Inputs */
	 
	 /* 1. Membaca hasil input ordo matriks*/
	 printf("Input ordo matriks: ");
	 scanf("%d", &n);
	 
	 /* 2. Input isi matirks*/
	 for(i=1;i<=n;i++){
		  for(j=1;j<=n+1;j++){
			   printf("a[%d][%d] = ",i,j);
			   scanf("%f", &a[i][j]);
		  }
	 }
	 
	/* Eliminasi Gauss */
	 for(i=1;i<=n-1;i++){
		  if(a[i][i] == 0.0){
			   printf("Mathematical Error!");
			   exit(0);
		  }
		  for(j=i+1;j<=n;j++){
			   ratio = a[j][i]/a[i][i];
			   
			   for(k=1;k<=n+1;k++){
			  		a[j][k] = a[j][k] - ratio*a[i][k];
			   }
		  }
	 }
	 
	 /* Memperoleh solusi dengan "Back Subsitution" */
	 x[n] = a[n][n+1]/a[n][n];
	
	 for(i=n-1;i>=1;i--){
		  x[i] = a[i][n+1];
		  for(j=i+1;j<=n;j++){
		  		x[i] = x[i] - a[i][j]*x[j];
		  }
		  x[i] = x[i]/a[i][i];
	 }
	 
	 /* Menampilakan solusi */ 
	 
	 printf("\nSolusi :\n");
	 for(i=1;i<=n;i++)
	 {
	  	printf("x[%d] = %0.3f\n",i, x[i]);
	 }
	 getch();
}
