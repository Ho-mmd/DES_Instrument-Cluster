
#include <QPainter>
#include "speedometer.h"


Speedometer::Speedometer(QQuickItem *parent)
    :QQuickPaintedItem(parent),
      m_SpeedometerSize(400), // touch screen is 800 x 480
      m_StartAngle(50),
      m_AlignAngle(260), // it should be 360 - m_StartAngle*3 for good looking
      m_LowestRange(0),
      m_HighestRange(4000),
      m_Speed(2430),
      m_ArcWidth(20),
      m_OuterColor(QColor(12,16,247)),
      m_InnerColor(QColor(51,88,255,80)),
      m_TextColor(QColor("silver")),
      m_BackgroundColor(Qt::transparent)
{

}


void Speedometer::draw_battery_level(int level, QPainter *painter,  QRectF *rect, QPen *pen)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    if (level <= 20)
    {
                painter->setBrush(QBrush(Qt::red));
                painter->drawRect(200, 400, 100, 20);
    }
    else if (20 < level and level <= 40)
    {
                painter->setBrush(QBrush(Qt::yellow));
                painter->drawRect(200, 400, 100, 20);
                painter->drawRect(200, 375, 100, 20);
    }
    else if (40 < level and level <= 60)
    {
                painter->setBrush(QBrush(Qt::green));
                painter->drawRect(200, 400, 100, 20);
                painter->drawRect(200, 375, 100, 20);
                painter->drawRect(200, 350, 100, 20);
    }
    else if (60 < level and level <= 80)
    {
                painter->setBrush(QBrush(Qt::green));
                painter->drawRect(200, 400, 100, 20);
                painter->drawRect(200, 375, 100, 20);
                painter->drawRect(200, 350, 100, 20);
                painter->drawRect(200, 325, 100, 20);
    }
    else if (80 < level and level <= 100)
    {
                painter->setBrush(QBrush(Qt::green));
                painter->drawRect(200, 400, 100, 20);
                painter->drawRect(200, 375, 100, 20);
                painter->drawRect(200, 350, 100, 20);
                painter->drawRect(200, 325, 100, 20);
                painter->drawRect(200, 300, 100, 20);
    }
    else
                return;

    pen->setColor("silver");
//    painter->setPen(pen);
    QFont font2("Halvetica",14,QFont::Bold);
    painter->setFont(font2);
    painter->setPen(*pen);
    painter->drawText(rect->adjusted(-100, 350, 100, 20), Qt::AlignCenter, QString::number(level,'i', 0) + "%");
    QFont font3("Halvetica",10,QFont::Bold);
    painter->setFont(font3);
    painter->setPen(*pen);
    painter->drawText(rect->adjusted(-100, 390, 100, 20), Qt::AlignCenter, "battery level");
    painter->restore();
}

void Speedometer::paint(QPainter *painter)
{

    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle - 40;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter->setPen(pen);
   // painter->drawRect(rect);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();


//    int rectSize = m_SpeedometerSize/5;
    //inner rectrangle
    painter->save();
    pen.setWidth(m_ArcWidth/2);
    pen.setColor(m_OuterColor);
    painter->setBrush(m_InnerColor);
    painter->setPen(pen);
    painter->drawRect(150, 150, 200, 100);
//    painter->drawRect(rect.adjusted(0, 0, 0, 0));
    painter->restore();
    //text which shows the value
    painter->save();
    QFont font("Halvetica",52,QFont::Bold);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/30, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter  ,QString::number((m_Speed/40),'i', 0));

    QFont font3("Halvetica",10,QFont::Bold);
    painter->setFont(font3);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_SpeedometerSize/30 + 140, m_SpeedometerSize/30 + 80, -m_SpeedometerSize/30, -m_SpeedometerSize/4), Qt::AlignCenter, "km/h");

    painter->restore();

    //current active progress
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_OuterColor);
    qreal valueToAngle = ((m_Speed - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, valueToAngle * 16);
    painter->restore();



    // Bar Background
    painter->save();
    int battery_level = 75;
    draw_battery_level(battery_level, painter, &rect, &pen);
    painter->restore();
}


qreal Speedometer::getSpeedometerSize()
{
    return m_SpeedometerSize;
}

qreal Speedometer::getStartAngle()
{
    return m_StartAngle;
}


qreal Speedometer::getAlignAngle()
{
    return m_AlignAngle;
}


qreal Speedometer::getLowestRange()
{
    return m_LowestRange;
}

qreal Speedometer::getHighestRange()
{
    return m_HighestRange;
}

qreal Speedometer::getSpeed()
{
    return m_Speed;
}

int Speedometer::getArcWidth()
{
    return m_ArcWidth;
}

QColor Speedometer::getOuterColor()
{
    return m_OuterColor;
}

QColor Speedometer::getInnerColor()
{
    return m_InnerColor;
}

QColor Speedometer::getTextColor()
{
    return m_TextColor;
}

QColor Speedometer::getBackgroundColor()
{
    return m_BackgroundColor;
}



void Speedometer::setSpeedometerSize(qreal size)
{
    if(m_SpeedometerSize == size)
        return;
    m_SpeedometerSize = size;

    emit speedometerSizeChanged();
}

void Speedometer::setStartAngle(qreal startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;

    emit startAngleChanged();
}

void Speedometer::setAlignAngle(qreal angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;

    emit alignAngleChanged();
}

void Speedometer::setLowestRange(qreal lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;

    emit lowestRangeChanged();
}

void Speedometer::setHighestRange(qreal highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;

    emit highestRangeChanged();
}

void Speedometer::setSpeed(qreal speed)
{
    if(m_Speed == speed)
        return;

    m_Speed = speed;
    update();
    emit speedChanged();
}

void Speedometer::setArcWidth(int arcWidth)
{
    if(m_ArcWidth == arcWidth)
        return;

    m_ArcWidth = arcWidth;

    emit arcWidthChanged();
}

void Speedometer::setOuterColor(QColor outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;

    emit outerColorChanged();
}

void Speedometer::setInnerColor(QColor innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;

    emit innerColorChanged();
}

void Speedometer::setTextColor(QColor textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;

    emit textColorChanged();
}

void Speedometer::setBackgroundColor(QColor backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;

    emit backgroundColorChanged();
}
