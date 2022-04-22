#ifndef FFI_RUST_CLOSE_ON_INACTIVE_H
#define FFI_RUST_CLOSE_ON_INACTIVE_H

#include <QWidget>
#include <QFocusEvent>
#include <QPushButton>

class CloseOnInActive : public QWidget {

public:
    explicit CloseOnInActive(QWidget* parent = nullptr): QWidget(parent) {
        setWindowTitle("Title");
        //setWindowFlags(Qt::FramelessWindowHint);
        setFocusPolicy(Qt::StrongFocus);
        auto button = new QPushButton("Hello");
    }

protected:

//    void changeEvent(QEvent *event) override {
////        if (event->type() == QEvent::ActivationChange) {
////            if (!isActiveWindow()) {
////                qDebug() << "CloseOnInActive: Window close";
////                close();
////            }
////        }
//    }

};


#endif //FFI_RUST_CLOSE_ON_INACTIVE_H
