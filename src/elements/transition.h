#ifndef FFI_RUST_TRANSITION_H
#define FFI_RUST_TRANSITION_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>

class Transition : public PetriObject {

public:

    explicit Transition(const QPointF& origin, ffi::PetriNet* net, ffi::VertexIndex transition, QGraphicsItem *parent = nullptr);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPointF center() override;

    QPointF connectionPos(PetriObject*, bool reverse) override;

    ObjectType objectType() override { return PetriObject::Transition; }

    QString objectTypeStr() override { return "transition"; }

    bool allowConnection(PetriObject *other) override {
        return other->objectType() == Position;
    }

    virtual QString name() const override;

private:

    QPointF m_origin;

};

#endif //FFI_RUST_TRANSITION_H
