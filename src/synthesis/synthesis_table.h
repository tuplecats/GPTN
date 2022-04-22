#ifndef FFI_RUST_SYNTHESIS_TABLE_H
#define FFI_RUST_SYNTHESIS_TABLE_H

#include <QWidget>

namespace ffi {
    struct PetriNet;
    struct DecomposeContext;
}

class QToolBar;
class QAction;
class QTableView;
class Switch;
class SynthesisModel;

class SynthesisTable : public QWidget {

    Q_OBJECT

public:

    explicit SynthesisTable(ffi::DecomposeContext* ctx, QWidget* parent = nullptr);

    SynthesisModel* model() const;

public slots:

    void slotEvalProgram(bool);
    void slotAddProgram(bool);

signals:

    void signalSynthesisedProgram(ffi::PetriNet*, int);

private:

    QTableView* m_table = nullptr;
    ffi::DecomposeContext* m_context = nullptr;

    QToolBar* m_toolBar = nullptr;
    QAction* m_evalProgram = nullptr;
    QAction* m_addProgram = nullptr;
    Switch* m_enableLabel = nullptr;
};

#endif //FFI_RUST_SYNTHESIS_TABLE_H
