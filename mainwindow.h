#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Node.h"
#include "circularlist.h"
#include "pagedarray.h"

#include <QMainWindow>
#include <QtMultimedia>
#include <QtCore>
#include <QtWidgets>
#include <QTimer>
#include <QProcess>
#include <unordered_set>

extern bool doubly;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Node** createRandomArray(Node* sourceArray[], int numNodes);

    void createJsonFromArray(Node* array[], int size, const QString& filename);

private slots:
    void durationChanged(qint64 duration);

    void positionChanged(qint64 progress);

    void on_pushButton_Volume_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButton_Seek_Back_clicked();

    void on_horizontalSlider_Audio_File_Duration_valueChanged(int value);

    void on_horizontalSlider_Audio_Volume_valueChanged(int value);

    void on_tableWidget_cellClicked(int row, int column);

    void updateMemoryUsage();

    void on_checkBox_CommunityPlaylist_toggled(bool checked);

    void on_checkBox_Pagination_toggled(bool checked);
    //void on_checkBox_Pagination_toggled(bool checked, doublyLinkedList& principalLinkedList, Node* headPtr);
    void updateUniqueSingersAndSongs(const std::unordered_set<std::string>& uniqueArtists, circularList& curcularArtistList,
                             doublyLinkedList& principalLinkedList, Node* nodeArray[]);

    void updateAllSongsUI(Node* nodeArray[]);

    void showDataInTableWidget(const std::vector<Node*>& nodes);

    void updateAllSongsUIPaging(const std::string& folderPath, int allowedNodesForPage);

    void popUp();
    void popUp2();

    void showDataInTableWidgetPaging(const std::vector<int> songIndices);

public slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void playNextSong();


private:
    void updateduration(qint64 duration);
    Ui::MainWindow *ui;
    bool IS_Muted = false;
    QMediaPlayer *MPlayer;
    qint64 Mduration;
    QTimer *memoryUpdateTimer;
    doublyLinkedList principalLinkedList; // Declarar principalLinkedList como miembro privado
    const pagedArray pa;
    Node* headPtr; // Declarar headPtr como miembro privado
    int numSongs;
    Node** nodeArray;



    std::string state;
    int allowedNodesForPage;
    int allowedNodes;
    int bytesPageSize;
    std::string swapFolderPath;

};
#endif // MAINWINDOW_H
