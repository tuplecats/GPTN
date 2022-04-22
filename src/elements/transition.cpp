#include "position.h"
#include "transition.h"
#include "../ffi/rust.h"

Transition::Transition(const QPointF& origin, ffi::PetriNet* net, ffi::VertexIndex transition, QGraphicsItem *parent) : PetriObject(net, transition, parent), m_origin(origin) {
    this->setPos(m_origin);
}

QRectF Transition::boundingRect() const {
    return {-10, -30, 20, 60};
}

void Transition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setClipRect(boundingRect());

    painter->save();

    painter->setPen(isSelected() ? QPen(Qt::red) : Qt::NoPen);
    painter->setBrush(Qt::black);

    auto rect = boundingRect();
    rect.setSize(QSize(rect.size().width(), rect.size().height()));
    rect.setX(rect.x());
    rect.setY(rect.y());
    painter->drawRect(rect);

    painter->setPen(Qt::white);
    auto name = QString("%1").arg(this->index());
    painter->rotate(-rotation());
    painter->drawText(boundingRect(), Qt::AlignCenter, name);
    painter->restore();
}

QPointF Transition::center() {
    return this->scenePos();
}

QPointF getIntersection(qreal dx, qreal dy, qreal cx, qreal cy, qreal width, qreal height) {
    if (qAbs(dy / dx) < height / width) {
        return QPointF(cx + (dx > 0 ? width : -width), cy + dy * width / qAbs(dx));
    }
    return QPointF(cx + dx * height / qAbs(dy), cy + (dy > 0 ? height : -height));
}

QPointF Transition::connectionPos(PetriObject* to, bool reverse) {


    qreal w = QGraphicsItem::sceneBoundingRect().width() / 2.;
    qreal h = QGraphicsItem::sceneBoundingRect().height() / 2.;

    qreal xPosy = to->scenePos().x();
    qreal yPosy = to->scenePos().y();

    qreal dx = xPosy - center().x();
    qreal dy = yPosy - center().y();

    qreal cx = center().x();
    qreal cy = center().y();


    auto intersection = dx == 0. && dy == 0. ? to->scenePos() : getIntersection(dx, dy, cx, cy,w, h);

    return intersection;
}

QString Transition::name() const {
    return QString("t%1").arg(index());
}
