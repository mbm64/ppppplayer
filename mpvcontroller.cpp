#include "mpvcontroller.h"
#include <QFileDialog>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <cstdlib>
#include <QFileInfo>
#include <QDir>
MpvController::MpvController(MpvWidget *mpv_widget,QWidget *parent): QWidget(parent){
	mpv = mpv_widget;
	this ->parent = parent;	
	connect(mpv_widget, &MpvWidget::mpv_event_signal, this, &MpvController::handle_mpv_event);
	volume = settings.value("play/volume",100).toInt();
	mpv -> setProperty("volume", volume);

	//routing mpv backend through controller

}
//event handler 
//{{{
void MpvController::handle_mpv_event(mpv_event *event)
{
	QTextStream out(stdout);
    switch (event->event_id) {
    case MPV_EVENT_PROPERTY_CHANGE: {
        mpv_event_property *prop = (mpv_event_property *)event->data;
        if (strcmp(prop->name, "time-pos/full") == 0) {
            if (prop->format == MPV_FORMAT_DOUBLE) {
                double time = *(double *)prop->data;
				//out << QString("\n%1\n").arg(mpv -> getProperty("ao-volume").toInt());
				emit time_pos_change(time);
                
            }
        } else if (strcmp(prop->name, "duration/full") == 0) {
            if (prop->format == MPV_FORMAT_DOUBLE) {
                double time = *(double *)prop->data;
               	emit duration_change(time); 
            }
        }
        break;
    }
	case MPV_EVENT_START_FILE:{

		break;
							  }								
    default: ;
        // Ignore uninteresting or unknown events.
    }
}
//}}}
//file load func
//{{{
void MpvController::file_open(){
	QString lastopened = settings.value("history/lastdir","").toString();
	QString file_name = QFileDialog::getOpenFileName(0,"Open A Video",lastopened);
	if(file_name.isEmpty()) return;
	QFileInfo * file_info = new QFileInfo(file_name);
	settings.setValue("history/lastdir", file_info->absolutePath());	
	mpv ->command(QStringList() << "loadfile" << file_name);
}
void MpvController::folder_open(){
	QString lastopened = settings.value("history/lastdir","").toString();
	QString file_dir = QFileDialog::getExistingDirectory(0,"Choose A Directory",lastopened);
	if(file_dir.isEmpty()) return;
	QDir * dir = new QDir(file_dir);
	QTextStream out(stdout);
	settings.setValue("history/lastdir", file_dir);
	stop();
	QFileInfoList list = dir->entryInfoList();
	for(int i = 0; i<list.size(); i++){
		mpv -> command(QStringList() <<"loadfile"<<list.at(i).absoluteFilePath()<<"append-play");
		//out << QString("adding %1 to list")

	}
	

}
//}}}
//play/pause/stop 
//{{{
void MpvController::pause(){
	const bool paused = mpv -> getProperty("pause").toBool();
	mpv ->setProperty("pause", !paused);

}
void MpvController::stop(){
	mpv -> command("stop");
}
//}}}

//clip functionality 
//{{{
void MpvController::get_start_time(){
	const int timems =(int) (1000 * mpv -> getProperty("time-pos").toDouble()); 
	clipstart = new QTime(timems/3600000,timems / 60000,timems / 1000,timems %1000); 

	//std::cout << "uhhhhhhh"<<std::endl;
	emit set_start_time(clipstart->toString("hh:mm:ss.zzz"));
	//std::cout <<std::endl<<timestr.toStdString()<<std::endl;
	QTextStream cout(stdout);
	cout << timems <<Qt::endl;
	cout << clipstart -> toString("hh:mm:ss.zzz")<<Qt::endl;
}
void MpvController::get_end_time(){
	const int timems =(int) (1000 * mpv -> getProperty("time-pos").toDouble());
	clipend = new QTime(timems/3600000,timems / 60000,timems / 1000,timems %1000); 
	//std::cout << "uhhhhhhh"<<std::endl;
	emit set_end_time(clipend ->toString("hh:mm:ss.zzz"));
	//const dou time = mpv -> getProperty("time-pos");
	//std::cout << "uhhhhhhh"<<std::endl;
	//emit set_start_time(time);
	//std::cout<<std::endl<<time<<std::endl;
}
void MpvController::clip_it(){
	QString file_name = mpv -> getProperty("path").toString();
	QString output_name = "clip-"+mpv -> getProperty("filename/no-ext").toString()+QDate::currentDate().toString("-d-M-yyyy-")
		+QTime::currentTime().toString("hh:mm:ss");
	QString start_time = clipstart->toString("hh:mm:ss.zzz");
	QString end_time = clipend->toString("hh:mm:ss.zzz");
	QString extention = settings.value("clips/ext","webm").toString();
	QString location = settings.value("clips/dir").toString();
	QString command = QString("ffmpeg -i '%1' -ss %2 -to %3 -c copy '%4/%5.%6'").arg(file_name,start_time,end_time,location,output_name,extention);
	QTextStream out(stdout);
	out << Qt::endl << command << Qt::endl;
	std::system(qPrintable(command));

}
//}}}
//volume functionality
//{{{
void MpvController::set_volume(int vol){
	mpv ->setProperty("volume", vol);
	volume = vol;
	settings.setValue("play/volume", vol);
}
//}}}
//seek functionality
//{{{
void MpvController::seek(int pos){
	mpv -> command(QVariantList() << "seek" << pos/1000 <<"absolute");
}
void MpvController::seek_pause(){
	seek_paused = mpv ->getProperty("pause").toBool();
	mpv -> setProperty("pause", true);
}
void MpvController::seek_unpause(){
	mpv->setProperty("pause", seek_paused);
}


void MpvController::seek_forward(){
	seek_time(5);
}
void MpvController::seek_backward(){
	seek_time(-5);
}
void MpvController::seek_time(int secs){
	mpv ->command(QVariantList() << "seek" <<secs <<"");
}
//}}}


//util 
//{{{
QVariant MpvController::getProperty(QString property){
	return mpv ->getProperty(property);	
}
void MpvController::setProperty(QString property, QVariant value){
	mpv -> setProperty(property, value);
}
//}}}
