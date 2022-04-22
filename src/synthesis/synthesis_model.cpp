#include "synthesis_model.h"
#include "../ffi/rust.h"

SynthesisModel::SynthesisModel(ffi::DecomposeContext *ctx, QObject *parent) : QAbstractTableModel(parent), m_ctx(ctx) {

}

int SynthesisModel::rowCount(const QModelIndex &parent) const {
    return static_cast<int>(m_ctx->programs());
}

int SynthesisModel::columnCount(const QModelIndex &parent) const {
    return static_cast<int>(m_ctx->transitions()) + static_cast<int>(m_ctx->positions());
}

QVariant SynthesisModel::data(const QModelIndex &index, int role) const {

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return m_ctx->program_value(index.row(), index.column());
    }

    return {};
}

QVariant SynthesisModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_ctx->program_header_name(section, m_enableLabels);
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags SynthesisModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool SynthesisModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        m_ctx->set_program_value(index.row(), index.column(), value.toInt());
        return true;
    }

    return QAbstractItemModel::setData(index, value, role);
}

bool SynthesisModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    m_ctx->add_program();
    endInsertRows();

    return true;
}

void SynthesisModel::slotEnableLabels(bool checked) {
    m_enableLabels = checked;
    emit headerDataChanged(Qt::Horizontal, 0, columnCount(QModelIndex()));
}
