#ifndef OURTRACK_H
#define OURTRACK_H

#include <MainList.h>

class ourtrack : public QMainWindow
{
    Q_OBJECT

public:
    ourtrack(QWidget *parent = 0);
    ~ourtrack();
    
    Ui::ourtrackClass ui;
    MainList *List;
};

#endif // OURTRACK_H
