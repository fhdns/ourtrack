#include "ourtrack.h"

ourtrack::ourtrack(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    List = new MainList(ui.TableResult, ui.EditFind);
}

ourtrack::~ourtrack()
{
    delete List;
}
