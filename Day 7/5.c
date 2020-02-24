	
   #include "mpi.h"
   #include <stdio.h>
   #define SIZE 2

   int main(int argc, char *argv[])  {
    int numtasks, rank, sendcount, recvcount, source;
    float sendbuf[SIZE][SIZE] = {
        {1.0, 2.0},
        {5.0, 6.0}        
    };
    float recvbuf[SIZE];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {
        // define source task and elements to send/receive, then perform collective scatter
        source = 1;
        sendcount = SIZE;
        recvcount = SIZE;
        MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount,
                    MPI_FLOAT,source,MPI_COMM_WORLD);

        printf("rank= %d  Results: %f %f\n",rank,recvbuf[0],
                recvbuf[1]);
        }
    else
        printf("Must specify %d processors. Terminating.\n",SIZE);

    MPI_Finalize();
   }