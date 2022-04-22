#ifndef FFI_RUST_GRAPHICS_VIEW_ZOOM_H
#define FFI_RUST_GRAPHICS_VIEW_ZOOM_H

#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>

class GraphicsViewZoom : public QObject {

    Q_OBJECT

public:
    explicit GraphicsViewZoom(QGraphicsView* view);

    void gentleZoom(double factor);

    void set_modifier(Qt::KeyboardModifiers modifiers);

    void set_zoom_factor_base(double value);

private:

    QGraphicsView* m_view;
    Qt::KeyboardModifiers m_modifiers;
    double m_zoom_factor_base;
    QPointF target_scene_pos, target_viewport_pos;

    bool eventFilter(QObject* object, QEvent* event);

signals:

    void zoomed();


};


#endif //FFI_RUST_GRAPHICS_VIEW_ZOOM_H
