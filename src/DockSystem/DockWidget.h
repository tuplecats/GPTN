#ifndef FFI_RUST_DOCKWIDGET_H
#define FFI_RUST_DOCKWIDGET_H

#include <DockWidget.h>

class DockWidget : public ads::CDockWidget {

public:

    explicit DockWidget(const QString& name, QWidget *parent = nullptr);

public slots:

    void onWindowTitleChanged(const QString &title);

};


#endif //FFI_RUST_DOCKWIDGET_H
