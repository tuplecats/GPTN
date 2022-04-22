#include "DecomposeModelTab.h"
#include "../view/graphic_scene.h"
#include "../synthesis/synthesis_table.h"
#include "../DockSystem/DockToolbar.h"
#include <QGridLayout>
#include <QSplitter>
#include <DockAreaWidget.h>
#include <QLabel>

DecomposeModelTab::DecomposeModelTab(NetModelingTab* mainTab, QWidget *parent) : QWidget(parent)
    , m_netModelingTab(mainTab)
{
    m_ctx = mainTab->ctx()->decompose_ctx();

    m_dockManager = new ads::CDockManager(this);

    auto linearBaseFragmentsScene = new GraphicScene(m_ctx->linear_base_fragments());
    auto linearBaseFragmentsView = new GraphicsView;
    linearBaseFragmentsView->setScene(linearBaseFragmentsScene);
    linearBaseFragmentsView->setToolBoxVisibility(false);
    m_linearBaseFragmentsView = new DockWidget("LBF");
    m_linearBaseFragmentsView->setWidget(linearBaseFragmentsView);

    auto primitiveNetScene = new GraphicScene(m_ctx->primitive_net());
    auto primitiveNetView = new GraphicsView;
    primitiveNetView->setScene(primitiveNetScene);
    primitiveNetView->setToolBoxVisibility(false);
    m_primitiveNetView = new DockWidget("Primitive view");
    m_primitiveNetView->setWidget(primitiveNetView);

    auto synthesisTable = new SynthesisTable(m_ctx);
    connect(synthesisTable, &SynthesisTable::signalSynthesisedProgram, this, &DecomposeModelTab::slotSynthesisedProgram);
    m_synthesisTable = new DockWidget("Synthesis table");
    m_synthesisTable->setWidget(synthesisTable);

    auto synthesisedProgramView = new GraphicsView;
    synthesisedProgramView->setToolBoxVisibility(false);
    m_synthesisedProgramView = new DockWidget("Synthesised program");
    m_synthesisedProgramView->setWidget(synthesisedProgramView);

    auto area = m_dockManager->addDockWidget(ads::LeftDockWidgetArea, m_linearBaseFragmentsView);
    area->setWindowTitle("Линейно-базовые фрагменты");
    area->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    area = m_dockManager->addDockWidget(ads::RightDockWidgetArea, m_primitiveNetView, area);
    area->setWindowTitle("Примитивная система");
    area->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    area = m_dockManager->addDockWidget(ads::BottomDockWidgetArea, m_synthesisTable);
    area->setWindowTitle("Программы синтеза");
    area->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    area = m_dockManager->addDockWidget(ads::RightDockWidgetArea, m_synthesisedProgramView, area);
    area->setWindowTitle("Синтезированная структура");
    area->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    setLayout(new QGridLayout(this));
    layout()->addWidget(m_dockManager);
    layout()->setContentsMargins(0, 0, 0, 0);
}

void DecomposeModelTab::slotSynthesisedProgram(ffi::PetriNet *net, int index) {
    auto newScene = new GraphicScene(net);
    auto oldScene = dynamic_cast<GraphicsView*>(m_synthesisedProgramView->widget())->scene();

    dynamic_cast<GraphicsView*>(m_synthesisedProgramView->widget())->setScene(newScene);
    delete oldScene;
}