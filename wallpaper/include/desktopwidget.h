#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QPixmap>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <qstackedwidget.h>
class DesktopWidget  : public QWidget
{
	Q_OBJECT

public:
	DesktopWidget(QWidget *parent = nullptr);
	~DesktopWidget();

	static QSet<QString> imageFormats;
	static QSet<QString> videoFormats;

	HWND GetBackground();
	void SetBackground(HWND child);	

	void SetimageMode(const int& iamgeMode) { imageMode_ = iamgeMode; };
	void SetfilePath(const QString& filePath) { filePath_ = filePath; };

	int screenWidth;
	int screenHeight;

private:
	QLabel* bklabel;//放壁纸
	int imageMode_;
	QString filePath_;

	QMediaPlaylist* playlist;
	QMediaPlayer* videoPlayer;
	QVideoWidget* videoWidget;
	QWidget* imageWidget;
	QStackedWidget* stackedWidget;
	
	void showImage(QString filePath);
	void showVideo(QString filePath);

	void resizeEvent(QResizeEvent* event);

public slots:
	void UpdateWallpaper();
	//void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};