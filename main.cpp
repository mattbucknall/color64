// Copyright (c) 2017 Matthew T. Bucknall
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISIN
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QDialog>
#include <QSlider>
#include <QString>

#include "swatch.hpp"


static QSlider* m_red;
static QSlider* m_green;
static QSlider* m_blue;
static Swatch* m_swatch;
static QLabel* m_index;


static void valueChanged(int value)
{
    (void) value;
    
    quint8 r = m_red->value();
    quint8 g = m_green->value();
    quint8 b = m_blue->value();
    int encoded;
    
    QColor c(r * 85, g * 85, b * 85);
    
    encoded = r | (g << 2) | (b << 4);
    
    m_swatch->setColor(c);
    m_index->setText(QString("%1").arg(encoded));
}


static QSlider* make_slider(void)
{
    QSlider* slider = new QSlider(Qt::Horizontal);
    
    slider->setMinimum(0);
    slider->setMaximum(3);
    slider->setTickInterval(1);
    
    QObject::connect(slider, &QSlider::valueChanged, valueChanged);
    
    return slider;
}


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QDialog* dialog = new QDialog();
    QGridLayout* layout = new QGridLayout();
    
    m_swatch = new Swatch();
    m_index = new QLabel();
    
    m_index->setAlignment(Qt::AlignHCenter);
    
    m_red = make_slider();
    m_green = make_slider();
    m_blue = make_slider();
    
    dialog->setLayout(layout);;
    
    layout->addWidget(new QLabel("Red"), 0, 0);
    layout->addWidget(m_red, 0, 1, 1, 2);
    
    layout->addWidget(new QLabel("Green"), 1, 0);
    layout->addWidget(m_green, 1, 1, 1, 2);
    
    layout->addWidget(new QLabel("Blue"), 2, 0);
    layout->addWidget(m_blue, 2, 1, 1, 2);
    
    layout->addWidget(m_swatch, 0, 3, 2, 1);
    layout->addWidget(m_index, 2, 3, 1, 1);
    
    dialog->setWindowTitle("Color 64");
    dialog->show();
    
    return app.exec();
}
