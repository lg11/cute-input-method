#include "context.h"

int main( int argc, char** argv ) {
    gtk_init( &argc, &argv ) ;
    g_debug( "new start" ) ;
    Context* context = context_new() ;
    g_debug( "new done" ) ;
}

