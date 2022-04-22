#ifndef FFI_RUST_TOOL_H
#define FFI_RUST_TOOL_H

#include <QToolButton>
#include <QPainterPath>
#include <QPainter>
#include <QCursor>
#include <QToolTip>

class Tool : public QToolButton {

public:

    explicit Tool(QWidget* parent = nullptr) : QToolButton(parent) {
        this->setMouseTracking(true);
        this->setAttribute(Qt::WA_Hover);
        this->setToolTipDuration(500);
    }

    void setSize(const QSize& size) {
        this->setFixedSize(size);
        this->setIconSize(size);
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QStyleOptionToolButton opts;
        initStyleOption(&opts);

        QColor highlightedBack(0, 166, 251);
        QColor back(94, 94, 94); // E6E6E9
        QColor hover(135, 134, 134);

        if (defaultAction() && defaultAction()->isChecked()) painter.setBackground(QBrush(highlightedBack));
        else if (opts.state & QStyle::StateFlag::State_MouseOver) painter.setBackground(QBrush(hover));
        else painter.setBackground(QBrush(back));

        painter.setOpacity(0.7);

        QPainterPath path;
        path.addRoundedRect(rect(), 5, 5);
        painter.fillPath(path, painter.background());

        painter.setOpacity(1.);

        QRect iconRect = rect().adjusted(5, 5, -5, -5);
        if (defaultAction()) defaultAction()->icon().paint(&painter, iconRect);

    }

protected:

    void enterEvent(QEnterEvent *) override {
        setCursor(Qt::PointingHandCursor);
    }

    void leaveEvent(QEvent *) override {
        setCursor(Qt::ArrowCursor);
    }

};

#endif //FFI_RUST_TOOL_H
