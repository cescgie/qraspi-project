#include <QApplication>
#include <QtWidgets>
#include "graphics.h"
#include "game.h"
#include "ai.h"
#include "infoview.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <mpi.h>
using namespace std;

int main( int argc, char *argv[])
{
    srand( time(NULL) );
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    QApplication app(argc, argv);

    game *ge = new game();
    graphics *grap = new graphics();
    ai *aieng = new ai();

    grap->initialization( ge );
    aieng->connecting( ge );

    if(world_rank==0){
        grap->show();
    }

    MPI_Finalize();
    return app.exec();
}
