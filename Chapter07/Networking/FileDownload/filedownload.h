#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QWidget>

class FileDownload : public QWidget
{
    Q_OBJECT

public:
    FileDownload(QWidget *parent = nullptr);
private slots:
    void startDownload();
    void downloadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network_manager = nullptr;
    QPlainTextEdit *m_edit;
};
#endif // FILEDOWNLOAD_H
