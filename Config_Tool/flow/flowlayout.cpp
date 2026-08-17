#include "flowlayout.h"
#include <QWidget>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    qDeleteAll(itemList);
}

void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index < 0 || index >= itemList.size())
        return nullptr;
    return itemList.takeAt(index);
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return Qt::Horizontal;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0, 0, width, 0), true);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (QLayoutItem *item : itemList)
        size = size.expandedTo(item->minimumSize());

    QMargins m = contentsMargins();
    size += QSize(m.left() + m.right(), m.top() + m.bottom());
    return size;
}

int FlowLayout::horizontalSpacing() const
{
    return (m_hSpace >= 0)
            ? m_hSpace
            : smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int FlowLayout::verticalSpacing() const
{
    return (m_vSpace >= 0)
            ? m_vSpace
            : smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    int h = doLayout(rect, false);

    // ⭐⭐⭐关键修复：让QScrollArea知道内容高度变了
    if (QWidget *w = parentWidget())
    {
        w->setMinimumHeight(h);
    }
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    QRect effectiveRect = rect.adjusted(left, top, -right, -bottom);

    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    const int spaceX = horizontalSpacing();
    const int spaceY = verticalSpacing();

    for (QLayoutItem *item : itemList)
    {
        QSize itemSize = item->sizeHint();

        int nextX = x + itemSize.width() + spaceX;

        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y += lineHeight + spaceY;
            nextX = x + itemSize.width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
        {
            item->setGeometry(QRect(QPoint(x, y), itemSize));
        }

        x = nextX;
        lineHeight = qMax(lineHeight, itemSize.height());
    }

    return y + lineHeight + bottom - rect.y();
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent)
        return -1;

    if (parent->isWidgetType())
    {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    }
    else
    {
        return static_cast<QLayout *>(parent)->spacing();
    }
}
