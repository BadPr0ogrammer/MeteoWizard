#pragma once

#include <QPushButton>

class QWidget;
class QColor;

class MeteoWizard;

class SelectColorButton : public QPushButton
{
    Q_OBJECT
public:
    MeteoWizard* m_wiz;

    SelectColorButton(MeteoWizard* wiz, QWidget* parent);

    void setColor(const QColor& color);
    const QColor& getColor();

public slots:
    void updateColor();
    void changeColor();

private:
    QColor color;
};
