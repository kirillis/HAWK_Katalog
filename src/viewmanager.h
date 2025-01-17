#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "ofMain.h"
#include "constants.h"
#include "customevent.h"
#include "mainmenu.h"
#include "overview.h"
#include "worldview.h"

class ViewManager
{
public:
    ViewManager();
    void setCursor(HandCursor &_cursor);
    viewsEnum currentView;

protected:
private:
    void deptChanged(CustomEvent &e);
    void viewChanged(CustomEvent &e);
    void deleteOldView(viewsEnum oldView);

    std::string currentDept;
    MainMenu* m_view;
    Overview* o_view;
    WorldView* w_view;

    HandCursor* cursor;
};

#endif // VIEWMANAGER_H
