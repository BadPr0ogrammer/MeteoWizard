#include <QPushButton>
#include <QColor>

#include <opencv2/core/core.hpp>

#include "SelectColorButton.h"
#include "meteowizard.h";

SelectColorButton::SelectColorButton(MeteoWizard* wiz, QWidget* parent) : QPushButton(parent), m_wiz(wiz)
{
    connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void SelectColorButton::updateColor()
{
    setStyleSheet("background-color: " + color.name());
}

void SelectColorButton::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if (newColor != color)
    {
        setColor(newColor);
        m_wiz->m_arrow_color->setColor(newColor);
    }
}

void SelectColorButton::setColor(const QColor& color)
{
    this->color = color;
    updateColor();
}

const QColor& SelectColorButton::getColor()
{
    return color;
}
