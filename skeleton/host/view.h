#ifndef VIEW_H
#define VIEW_H

#include <QDeclarativeView>

namespace view {

class View : public QDeclarativeView {
    Q_OBJECT
public :
    View( QWidget* parent = NULL ) ;
} ;

}

#endif
