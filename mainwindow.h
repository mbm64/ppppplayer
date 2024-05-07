#ifndef MainWindow_H
#define MainWindow_H

#include <QtWidgets/QWidget>
#include <QMainWindow>
#include "playbar.h"
class MpvWidget;
class QSlider;
class QPushButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
public slots:
    void openMedia();
    void seek(int pos);
    void pauseResume();
private Q_SLOTS:
    void setSliderRange(int duration);
private:
    MpvWidget *m_mpv;
	PlayBar * pb;
    QSlider *m_slider;
    QPushButton *m_openBtn;
    QPushButton *m_playBtn;
protected:
	void resizeEvent(QResizeEvent * event);
};

#endif // MainWindow_H
