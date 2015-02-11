//     *********************************
//     *    Matrix Multiply Project    *
//     *                               *
//     *********************************

//     ** MAIN PROGRAM  **


//     *************************************************
//     ** Any changes you make to this code must      **
//     ** maintain the correctness of the matrix      **
//     ** multiply computed by the original version.  **
//     **                                             **
//     ** You may assume m = n = k for your matrices  **
//     *************************************************

#include<stdio.h>

double **dmatrix(int nrl,int nrh,int ncl,int nch);
void nerror(char *error_text);

int main(int argc, char** argv)  {
 
      int l,m,n,k;
      int i,j;
      double temp;
      double **A, **B, **C;


     //  ****************************************************
     //  * The following allows matrix parameters to be     *
     //  * entered on the command line to take advantage    *
     //  * of dynamically allocated memory.  You may modify *
     //  * or remove it as you wish.                        *
     //  ****************************************************

     if (argc != 4) {
       nerror("Usage:  <executable> <m-value> <n-value> <k-value>");
     }
      m = atoi(argv[1]);
      n = atoi(argv[2]);
      k = atoi(argv[3]);

      // *********************************************************
      // * Call the dmatrix() subroutine to dynamically allocate *
      // * storage for the matrix sizes specified by m, n, and k *  
      // *********************************************************

      A=dmatrix(0,m-1,0,k-1);
      B=dmatrix(0,k-1,0,n-1);
      C=dmatrix(0,m-1,0,n-1);

      // *********************************************************
      //  * Initialize matrix elements so compiler does not      *
      //  * optimize out                                         *
      // *********************************************************

      for(j=0;j<k;j++) {
        for(i=0;i<m;i++) {
          A[i][j] = i+j+4.0;
        }
      }

      for(j=0;j<n;j++) {
        for(i=0;i<k;i++) {
          B[i][j] = i+j+5.0;
        }
      }

      for(j=0;j<n;j++) {
        for(i=0;i<m;i++) {
          C[i][j] = 0.0;
        }
      }
          
      // ******************************
      // * Start embedded timing here *
      // ******************************

      // **********************************
      // * Perform simple matrix multiply *
      // **********************************
      for(j=0;j<n;j++) {
        for(l=0;l<k;l++) {
          for(i=0;i<m;i++) {
            C[i][j] = C[i][j] + B[l][j]*A[i][l];
          }
        }
      }
      // ******************************
      // * Stop embedded timing here  *
      // ******************************

      // **************************************************
      // * Print out a 10 x 10 matrix for testing only    *
      // * Comment out when timing                        *
      // **************************************************

      fprintf(stdout, "Here is the matrix A:\n\n");
      for(i=0;i<m;i++) {
        for(j=0;j<k;j++) {
          fprintf(stdout, "%10.2f ",A[i][j]);
        }
        fprintf(stdout, "\n");
      }
      fprintf(stdout, "Here is the matrix B:\n\n");
      for(i=0;i<k;i++) {
        for(j=0;j<n;j++) {
          fprintf(stdout, "%10.2f",B[i][j]);
        }
        fprintf(stdout, "\n");
      }
      fprintf(stdout, "Here is the matrix C:\n\n");
      for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
          fprintf(stdout, "%10.2f",C[i][j]);
        }
        fprintf(stdout, "\n");
      }


}
//     **  END MAIN PROGRAM  **

//     ********************************************************
//     *******    BEGIN SUBROUTINES    ************************
//     ********************************************************

double **dmatrix(int nrl,int nrh,int ncl,int nch)
// Allocates a double matrix with range [nrl..nrh][ncl..nch]
{
  int i;
  double **m;

//    Allocate pointers to rows
  m=(double **) malloc((unsigned)(nrh-nrl+1)*sizeof(double *));
  if (!m) nerror("allocation failure in malloc in dmatrix()");
  m -= nrl;
//    Allocate rows and set pointers to them
  for(i=nrl;i<=nrh;i++) {
    m[i]=(double*) malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i]) nerror("allocaion failure in malloc in dmatrix()");
    m[i] -= ncl;
  }
  return m;
}

void nerror(char *error_text)
{
  void exit();
  fprintf(stderr, "Run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"Exiting...\n");
  exit(1);
}
