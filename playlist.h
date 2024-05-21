#include<QWidget>
#include<QListWidget>
#include <QShowEvent>
#include "mpvcontroller.h"
class PlaylistWindow : public QWidget{
	Q_OBJECT
	public:
		PlaylistWindow(MpvController* controller, QWidget* parent = nullptr);
	private:
		QListWidget * playlist;
		MpvController * controller;
	protected:
		void showEvent(QShowEvent * event);
		
};
