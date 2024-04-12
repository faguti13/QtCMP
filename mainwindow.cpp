#include "mainwindow.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutex>
#include "Node.h"

#include "pagedarray.h"

#include "circularlist.h"
#include "principallist.h"
#include "serverconnection.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
#include <unordered_set>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <QMetaType>

Q_DECLARE_METATYPE(std::string)

namespace pt = boost::property_tree;
QMutex listMutex;
bool doubly = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(1250,660);
    ui->setupUi(this);

    // Configurar el temporizador para actualizar la memoria cada segundo
    memoryUpdateTimer = new QTimer(this);
    connect(memoryUpdateTimer, SIGNAL(timeout()), this, SLOT(updateMemoryUsage()));
    memoryUpdateTimer->start(1000); // Actualizar cada segundo

    // Inicializar la información de memoria
    updateMemoryUsage();

    MPlayer = new QMediaPlayer();

    // Conectar la señal mediaStatusChanged a handleMediaStatusChanged
    connect(MPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);

    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Back->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->horizontalSlider_Audio_Volume->setMinimum(1);
    ui->horizontalSlider_Audio_Volume->setMaximum(100);
    ui->horizontalSlider_Audio_Volume->setValue(30);

    MPlayer->setVolume(ui->horizontalSlider_Audio_Volume->value());

    connect(MPlayer,&QMediaPlayer::durationChanged,this, &MainWindow::durationChanged);
    connect(MPlayer,&QMediaPlayer::positionChanged,this, &MainWindow::positionChanged);

    connect(ui->checkBox_Pagination, &QCheckBox::toggled, this, &MainWindow::on_checkBox_Pagination_toggled);


    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(on_tableWidget_cellClicked(int, int)));

    ui->horizontalSlider_Audio_File_Duration->setRange(0,MPlayer->duration()/1000);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    //doublyLinkedList principalLinkedList; // Instancia de la clase doublyLinkedList. Acá todavía está vacía

    principalList principal(principalLinkedList); // Instancia de la clase principalList. principalLinkedList ya tiene elementos

    headPtr = principalLinkedList.getHead(); // Guarda el puntero al nodo inicial de la lista doblemente enlazada
    numSongs = principalLinkedList.getNodeCount();

    //std::cout<< headPtr<<std::endl;

    nodeArray = principalLinkedList.getArrayList(headPtr);

    //principalLinkedList.getPointerToDoublyLinkedList();

    circularList circularArtistList; // Instancia de la clase circularList

    circularArtistList.findArtists(circularArtistList, headPtr); // Acá se crean las listas circulares

    std::unordered_set<std::string> uniqueArtists = circularArtistList.getUniqueArtists(headPtr); //Acá están los nombres de los dif. artistas

    circularArtistList.findArtists(circularArtistList,headPtr); // Acá se crean las listas circulares


    updateUniqueSingersAndSongs(uniqueArtists, circularArtistList, principalLinkedList, nodeArray);
    updateAllSongsUI(nodeArray);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::updateduration(qint64 duration)
{
    QString timestr;
    if (duration || Mduration)
    {
        QTime CurrentTime((duration / 3600) % 60,(duration/60) %60, duration % 60, (duration * 1000) % 1000);
        QTime totalTime((Mduration / 3600) % 60, (Mduration / 60) %60, Mduration % 60, (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if (Mduration > 3600)
            format = "hh:mm:ss";
        ui ->label_Value_1->setText(CurrentTime.toString(format));
        ui ->label_Value_2->setText(totalTime.toString(format));
    }
}


void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;
    ui->horizontalSlider_Audio_File_Duration->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider_Audio_File_Duration->isSliderDown())
    {
        ui->horizontalSlider_Audio_File_Duration->setValue(progress/1000);
    }

    updateduration(progress / 1000);
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if (IS_Muted == false)
    {
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        IS_Muted = true;
        MPlayer->setMuted(true);
    }
    else
    {
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        IS_Muted = false;
        MPlayer->setMuted(false);
    }
}

void MainWindow::on_pushButton_Play_clicked()
{
    MPlayer->play();
}


void MainWindow::on_pushButton_Pause_clicked()
{
    MPlayer->pause();
}


void MainWindow::on_pushButton_Stop_clicked()
{
    MPlayer->stop();
}

// Declaración de variables miembro en la clase MainWindow para mantener el índice actual
int currentSongIndex = -1; // Inicializado en -1 para indicar que no hay canción en reproducción

void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    int nextIndex = currentSongIndex + 1;

    if (nextIndex >= ui->tableWidget->rowCount()) {
        if (not doubly) {
            nextIndex = 0;
        } else {}
    }

    bool paginationEnabled = ui->checkBox_Pagination->isChecked();
    if (paginationEnabled) {

        if (nextIndex < ui->tableWidget->rowCount()) {
            currentSongIndex = nextIndex;

            QTableWidgetItem *nextItem = ui->tableWidget->item(nextIndex, 0);

            if (nextItem && nextItem->data(Qt::UserRole).isValid()) {
                // Obtener el path del archivo de la siguiente canción
                std::string filePath = nextItem->data(Qt::UserRole).toString().toStdString();

                // Obtener la información de la siguiente canción
                std::string songName = nextItem->text().toStdString();
                std::string artistName = ui->tableWidget->item(nextIndex, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(nextIndex, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(nextIndex, 3)->text().toStdString();

                // Establecer la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establecer la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Iniciar la reproducción de la siguiente canción
                MPlayer->play();
            }
        }

    } else {

        if (nextIndex < ui->tableWidget->rowCount()) {
            currentSongIndex = nextIndex;

            QTableWidgetItem *nextItem = ui->tableWidget->item(nextIndex, 0);

            if (nextItem && nextItem->data(Qt::UserRole).isValid()) {
                // Obtén el nodo asociado a la celda de la siguiente canción
                Node* nextNode = qvariant_cast<Node*>(nextItem->data(Qt::UserRole));

                // Obtén la información de la siguiente canción
                std::string songName = nextItem->text().toStdString();
                std::string artistName = ui->tableWidget->item(nextIndex, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(nextIndex, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(nextIndex, 3)->text().toStdString();

                // Establece la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                // Obtén el path del archivo de la siguiente canción
                std::string filePath = nextNode->reference;

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establece la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Inicia la reproducción de la siguiente canción
                MPlayer->play();
            }
        }

    }



}

void MainWindow::on_pushButton_Seek_Back_clicked()
{
    int prevIndex = currentSongIndex - 1;

    if (prevIndex < 0) {
        if (not doubly) {
            prevIndex = ui->tableWidget->rowCount() - 1;
        } else {}
    }


    bool paginationEnabled = ui->checkBox_Pagination->isChecked();
    if (paginationEnabled) {


        if (prevIndex >= 0) {
            currentSongIndex = prevIndex;

            QTableWidgetItem *prevItem = ui->tableWidget->item(prevIndex, 0);

            if (prevItem && prevItem->data(Qt::UserRole).isValid()) {
                // Nodo asociado a la celda de la canción anterior
                std::string filePath = prevItem->data(Qt::UserRole).toString().toStdString();


                //  información de la canción anterior
                std::string songName = prevItem->text().toStdString();
                std::string artistName = ui->tableWidget->item(prevIndex, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(prevIndex, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(prevIndex, 3)->text().toStdString();

                // Establece la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establece la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Inicia la reproducción de la canción anterior
                MPlayer->play();
            }
        }

    } else {
        if (prevIndex >= 0) {
            currentSongIndex = prevIndex;

            QTableWidgetItem *prevItem = ui->tableWidget->item(prevIndex, 0);

            if (prevItem && prevItem->data(Qt::UserRole).isValid()) {
                // Nodo asociado a la celda de la canción anterior
                Node* prevNode = qvariant_cast<Node*>(prevItem->data(Qt::UserRole));

                //  información de la canción anterior
                std::string songName = prevItem->text().toStdString();
                std::string artistName = ui->tableWidget->item(prevIndex, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(prevIndex, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(prevIndex, 3)->text().toStdString();

                // Establece la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                //  del archivo de la canción anterior
                std::string filePath = prevNode->reference;

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establece la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Inicia la reproducción de la canción anterior
                MPlayer->play();
            }
        }

    }



}


void MainWindow::on_horizontalSlider_Audio_File_Duration_valueChanged(int value)
{
    // Obtener la duración total de la canción en milisegundos
    qint64 duration = MPlayer->duration();

    // Obtener el valor máximo del slider
    int maxValue = ui->horizontalSlider_Audio_File_Duration->maximum();

    // Calcular la posición basada en la duración total de la canción y el valor del slider
    double position = (static_cast<double>(value) / maxValue) * duration;

    // Establecer la posición de reproducción
    MPlayer->setPosition(position);
}

void MainWindow::on_horizontalSlider_Audio_Volume_valueChanged(int value)
{
    MPlayer->setVolume(value);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    bool paginationEnabled = ui->checkBox_Pagination->isChecked();
    if (paginationEnabled) { // Cuando se trabaja con paginacion
        if (column == 0) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);

            // Verifica si el elemento tiene datos asociados
            if (item && item->data(Qt::UserRole).isValid()) {
                // Obtener la información de la canción directamente del QTableWidgetItem
                std::string songName = item->text().toStdString();
                std::string artistName = ui->tableWidget->item(row, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(row, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(row, 3)->text().toStdString();
                std::string reference = item->data(Qt::UserRole).toString().toStdString(); // Obtener la referencia del archivo

                // Establece la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                // Obtiene el path del archivo de la canción
                std::string filePath = reference;
                //std::cout<< "file path en reproducir" << filePath <<std::endl;

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establece la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Inicia la reproducción
                MPlayer->play();
            }
        }

    } else { // Cuando se trabaja con listas enlazadas

        if (column == 0) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);

            // Verifica si el elemento tiene datos asociados
            if (item && item->data(Qt::UserRole).isValid()) {
                // Obtén el nodo asociado a la celda
                Node* node = qvariant_cast<Node*>(item->data(Qt::UserRole));

                // Obtener la información de la canción
                std::string songName = item->text().toStdString();
                std::string artistName = ui->tableWidget->item(row, 1)->text().toStdString();
                std::string albumName = ui->tableWidget->item(row, 2)->text().toStdString();
                std::string genre = ui->tableWidget->item(row, 3)->text().toStdString();

                // Establece la información en el label
                QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
                ui->label_File_Name->setText(songInfo);

                // Obtiene el path del archivo de la canción
                std::string filePath = node->reference;

                // Convierte la ruta a un formato compatible con URI
                QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

                // Establece la URL en el reproductor multimedia
                MPlayer->setMedia(fileUrl);

                // Inicia la reproducción
                MPlayer->play();
            }
        }
    }
}

void MainWindow::updateMemoryUsage()
{
    QFile file("/proc/self/statm");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString result = in.readLine();
        file.close();

        QStringList tokens = result.split(" ", QString::SkipEmptyParts);
        if (tokens.size() >= 1) {
            qint64 pages = tokens.at(0).toLongLong();
            qint64 pageSize = 4; // Tamaño de página típico en Linux (en kilobytes)
            qint64 memoryInKB = pages * pageSize;
            double memoryInMB = static_cast<double>(memoryInKB) / 1024;

            ui->memorylabel->setText(QString("Memoria en uso: %1 MB").arg(memoryInMB, 0, 'f', 2));
        }
    }
}

Server server;

void MainWindow::on_checkBox_CommunityPlaylist_toggled(bool checked)
{
    bool paginationEnabled = ui->checkBox_Pagination->isChecked();
    if (paginationEnabled) {
        if (checked == true) {
            popUp2();

        } else {
            MPlayer->stop();
            std::cout << "Community playlist off" << std::endl;
            server.stopServer();
            updateAllSongsUI(nodeArray);
        }

    } else {

        if (checked == true) {
            MPlayer->stop();
            std::cout << "Community playlist on" << std::endl;
            server.startServer();
            Node **communityArray = principalLinkedList.getRandomArrayList(headPtr);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->setRowCount(10);
            for (int i = 0; i < 10; ++i) {
                QTableWidgetItem *itemTitle = new QTableWidgetItem(
                    QString::fromStdString(communityArray[i]->title));
                QTableWidgetItem *itemArtist = new QTableWidgetItem(
                    QString::fromStdString(communityArray[i]->artist));
                QTableWidgetItem *itemAlbum = new QTableWidgetItem(
                    QString::fromStdString(communityArray[i]->album));
                QTableWidgetItem *itemGenre = new QTableWidgetItem(
                    QString::fromStdString(communityArray[i]->genre));
                QTableWidgetItem *itemUpVotes = new QTableWidgetItem(
                    QString::number(communityArray[i]->upVotes));
                QTableWidgetItem *itemDownVotes = new QTableWidgetItem(
                    QString::number(communityArray[i]->downVotes));

                // Almacena la referencia del nodo en la columna 0
                itemTitle->setData(Qt::UserRole, QVariant::fromValue(communityArray[i]));

                ui->tableWidget->setItem(i, 0, itemTitle);
                ui->tableWidget->setItem(i, 1, itemArtist);
                ui->tableWidget->setItem(i, 2, itemAlbum);
                ui->tableWidget->setItem(i, 3, itemGenre);
                ui->tableWidget->setItem(i, 4, itemUpVotes);
                ui->tableWidget->setItem(i, 5, itemDownVotes);
            }
            createJsonFromArray(communityArray, 10, "communityArray.json");

        } else {
            MPlayer->stop();
            std::cout << "Community playlist off" << std::endl;
            server.stopServer();
            updateAllSongsUI(nodeArray);
        }
    }
}

void MainWindow::on_checkBox_Pagination_toggled(bool checked)
{
    if(checked == true){
        std::cout<<"Pagination on"<<std::endl;



        try {
            pt::ptree tree;
            pt::ini_parser::read_ini("/home/asly/Desktop/QtCMP/config.ini", tree); // CAMBIAR POR RUTA RELATIVA

            state = tree.get<std::string>("pagination.state");
            allowedNodes = std::stoi(tree.get<std::string>("pagination.allowedNodesForPage"));
            bytesPageSize = std::stoi(tree.get<std::string>("pagination.bytesPageSize"));
            swapFolderPath = tree.get<std::string>("pagination.swapFolderPath");

        } catch(const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }

        if ((bytesPageSize % 478 == 0) & ((bytesPageSize / 474)==allowedNodes)) { //Condición para que los nodos quepan completos
            std::cout<<"Pagination aprobada"<<std::endl;
            allowedNodesForPage = bytesPageSize / 474;
            //std::cout<< allowedNodesForPage<<std::endl;

            pa.toBinary(pa, swapFolderPath.c_str(), headPtr, allowedNodesForPage);

            updateAllSongsUIPaging(swapFolderPath,allowedNodesForPage);

            //principalLinkedList.clear();

        } else{
            popUp();
            std::cout<<"Saliendo"<<std::endl;
            return;
        }
    }
    else
    {
        updateAllSongsUI(nodeArray);
        std::cout<<"Pagination off"<<std::endl;
    }
}

void MainWindow::popUp() {
    QMessageBox::information(this, "Warning", "Make sure that the size set in the .ini for each binary page is a multiple of 478");
}

void MainWindow::popUp2() {
    QMessageBox::information(this, "Warning", "The community player option is not available to use with pagination, wait for new updates");
}


void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        playNextSong();
    }
}

void MainWindow::playNextSong()
{
    int nextIndex = currentSongIndex + 1;

    if (nextIndex < ui->tableWidget->rowCount()) {
        currentSongIndex = nextIndex;

        QTableWidgetItem *nextItem = ui->tableWidget->item(nextIndex, 0);

        if (nextItem && nextItem->data(Qt::UserRole).isValid()) {
            Node* nextNode = qvariant_cast<Node*>(nextItem->data(Qt::UserRole));
            std::string songName = nextItem->text().toStdString();
            std::string artistName = ui->tableWidget->item(nextIndex, 1)->text().toStdString();
            std::string albumName = ui->tableWidget->item(nextIndex, 2)->text().toStdString();
            std::string genre = ui->tableWidget->item(nextIndex, 3)->text().toStdString();

            QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
            ui->label_File_Name->setText(songInfo);

            std::string filePath = nextNode->reference;
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            MPlayer->setMedia(fileUrl);
            MPlayer->play();
        }
    }
}

void MainWindow::updateUniqueSingersAndSongs(const std::unordered_set<std::string>& uniqueArtists,
                                     circularList& circularArtistList,
                                     doublyLinkedList& principalLinkedList, Node* nodeArray[]) {
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Botón con todos los artistas
    QPushButton *button = new QPushButton("Todos los artistas");
    ui->verticalLayout->addWidget(button);

    connect(button, &QPushButton::clicked, [=]() {

        bool paginationEnabled = ui->checkBox_Pagination->isChecked();
        if (paginationEnabled) {

            updateAllSongsUIPaging(swapFolderPath,allowedNodesForPage);
            std::cout << "Paginacion activa. botón de todos los artistas" << std::endl;

        } else {
            updateAllSongsUI(nodeArray);

        }
    });

    // Itera sobre los nombres de los artistas y agregar un botón para cada uno al layout vertical
    for (const auto& artist : uniqueArtists) {
        QPushButton *button = new QPushButton(QString::fromStdString(artist));
        ui->verticalLayout->addWidget(button);

        // Conectar la señal de clic del botón a una función para manejar el evento
        connect(button, &QPushButton::clicked, [=]() {

            bool paginationEnabled = ui->checkBox_Pagination->isChecked();

            if (paginationEnabled) {
                std::cout << "Paginacion activa. Clic en el botón de " << artist << std::endl;
                circularArtistList.printCircularList(artist, circularArtistList);
                std::vector<int> songIndices = circularArtistList.getSongIndices(artist, circularArtistList);
                /*for (int index : songIndices) {
                    std::cout << " indice guardado " << index;
                }
                std::cout << std::endl;*/

                showDataInTableWidgetPaging(songIndices);

            } else {
                circularArtistList.printCircularList(artist, circularArtistList);
                std::vector<int> songIndices = circularArtistList.getSongIndices(artist, circularArtistList);
                std::vector<Node*> nodes = principalLinkedList.getNodesAtIndices(songIndices, principalLinkedList);

                showDataInTableWidget(nodes);
            }
        });
    }
}

void MainWindow::updateAllSongsUI(Node *array[])
{
    doubly = true;
    int numNodes = 0;
    while (array[numNodes] != nullptr) {
        ++numNodes;
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(array[i]->title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(
            QString::fromStdString(array[i]->artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(array[i]->album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(array[i]->genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(array[i]->upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(array[i]->downVotes));

        // Almacena la referencia del nodo en la columna 0
        itemTitle->setData(Qt::UserRole, QVariant::fromValue(array[i]));

        ui->tableWidget->setItem(i, 0, itemTitle);
        ui->tableWidget->setItem(i, 1, itemArtist);
        ui->tableWidget->setItem(i, 2, itemAlbum);
        ui->tableWidget->setItem(i, 3, itemGenre);
        ui->tableWidget->setItem(i, 4, itemUpVotes);
        ui->tableWidget->setItem(i, 5, itemDownVotes);
    }

    ui->tableWidget->setColumnWidth(0, 290);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 290);
    ui->tableWidget->setColumnWidth(3, 120);
    ui->tableWidget->setColumnWidth(4, 25);
    ui->tableWidget->setColumnWidth(5, 25);
}

void MainWindow::showDataInTableWidget(const std::vector<Node*>& nodes) {
    doubly = false;
    // Limpia el contenido actual del tableWidget
    ui->tableWidget->clear();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Configurael número de filas del tableWidget
    ui->tableWidget->setRowCount(nodes.size());

    // Itera sobre los nodos y mostra los datos en el tableWidget
    for (size_t i = 0; i < nodes.size(); ++i) {
        Node* node = nodes[i];
        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(node->title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(QString::fromStdString(node->artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(node->album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(node->genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(node->upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(node->downVotes));

        // Almacena la referencia del nodo en la columna 0
        itemTitle->setData(Qt::UserRole, QVariant::fromValue(nodes[i]));

        ui->tableWidget->setItem(i, 0, itemTitle);
        ui->tableWidget->setItem(i, 1, itemArtist);
        ui->tableWidget->setItem(i, 2, itemAlbum);
        ui->tableWidget->setItem(i, 3, itemGenre);
        ui->tableWidget->setItem(i, 4, itemUpVotes);
        ui->tableWidget->setItem(i, 5, itemDownVotes);
    }

    ui->tableWidget->setColumnWidth(0, 290);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 290);
    ui->tableWidget->setColumnWidth(3, 120);
    ui->tableWidget->setColumnWidth(4, 25);
    ui->tableWidget->setColumnWidth(5, 25);
}




void MainWindow::updateAllSongsUIPaging(const std::string& folderPath, int allowedNodesForPage) {

    doubly = false;
    int pagenum = 1;
    int node = 0;
    int i;
    std::string binaryFile;

    ui->tableWidget->clear(); // Limpia el contenido actual del tableWidget
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(numSongs); // Configura el número de filas del tableWidget

    // Itera sobre los nodos y mostra los datos en el tableWidget
    for (i = 0; i < numSongs; ++i) {

        if (node == allowedNodesForPage) { // Verificar si se alcanzó el número máximo de nodos por página
            node = 0; // Reiniciar el contador de nodos
        }

        if (node == 0){
            binaryFile = std::string(folderPath) + "/page" + std::to_string(pagenum++) + ".bin";
        }

        //std::cout << "Llamada:  " << i << " / Valor de node " << node
                  //<< " / archivo usado  " << binaryFile <<std::endl;

        std::string title = pa.readTitle(binaryFile, node); //guardar la info del .bin
        std::string artist = pa.readArtist(binaryFile, node);
        std::string album = pa.readAlbum(binaryFile, node);
        std::string genre = pa.readGenre(binaryFile, node);
        std::string reference = pa.readReference(binaryFile, node);
        int upVotes = pa.readUpVotes(binaryFile, node);
        int downVotes = pa.readDownVotes(binaryFile, node);

        node++;

        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(QString::fromStdString(artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(downVotes));

        // Almacena la referencia del nodo en la columna 0
        //itemTitle->setData(Qt::UserRole, QVariant::fromValue(reference));
        itemTitle->setData(Qt::UserRole, QVariant::fromValue(QString::fromStdString(reference)));

        //std::cout<<reference<<std::endl;

        ui->tableWidget->setItem(i, 0, itemTitle);
        ui->tableWidget->setItem(i, 1, itemArtist);
        ui->tableWidget->setItem(i, 2, itemAlbum);
        ui->tableWidget->setItem(i, 3, itemGenre);
        ui->tableWidget->setItem(i, 4, itemUpVotes);
        ui->tableWidget->setItem(i, 5, itemDownVotes);
        }

        ui->tableWidget->setColumnWidth(0, 290);
        ui->tableWidget->setColumnWidth(1, 150);
        ui->tableWidget->setColumnWidth(2, 290);
        ui->tableWidget->setColumnWidth(3, 120);
        ui->tableWidget->setColumnWidth(4, 25);
        ui->tableWidget->setColumnWidth(5, 25);
}

void MainWindow::showDataInTableWidgetPaging(const std::vector<int> songIndices) {
    doubly = false;
    int i;
    std::string binaryFile;
    int pagenum;

    // Limpia el contenido actual del tableWidget
    ui->tableWidget->clear();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Configurael número de filas del tableWidget
    ui->tableWidget->setRowCount(songIndices.size());

    // Itera sobre los nodos y mostra los datos en el tableWidget
    for (i = 0; i < songIndices.size(); ++i) {

        int node = (songIndices[i]-1) % allowedNodes;
        pagenum = (songIndices[i] + allowedNodes -1) / allowedNodes;

        binaryFile = std::string(swapFolderPath) + "/page" + std::to_string(pagenum) + ".bin";


        //std::cout << "Llamada:  " << songIndices[i] << " / Valor de node " << node
                //<< " / archivo usado  " << binaryFile <<std::endl;


        std::string title = pa.readTitle(binaryFile, node); //guardar la info del .bin
        std::string artist = pa.readArtist(binaryFile, node);
        std::string album = pa.readAlbum(binaryFile, node);
        std::string genre = pa.readGenre(binaryFile, node);
        std::string reference = pa.readReference(binaryFile, node);
        int upVotes = pa.readUpVotes(binaryFile, node);
        int downVotes = pa.readDownVotes(binaryFile, node);

        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(QString::fromStdString(artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(downVotes));

        itemTitle->setData(Qt::UserRole, QVariant::fromValue(QString::fromStdString(reference)));

        ui->tableWidget->setItem(i, 0, itemTitle);
        ui->tableWidget->setItem(i, 1, itemArtist);
        ui->tableWidget->setItem(i, 2, itemAlbum);
        ui->tableWidget->setItem(i, 3, itemGenre);
        ui->tableWidget->setItem(i, 4, itemUpVotes);
        ui->tableWidget->setItem(i, 5, itemDownVotes);
    }

    ui->tableWidget->setColumnWidth(0, 290);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 290);
    ui->tableWidget->setColumnWidth(3, 120);
    ui->tableWidget->setColumnWidth(4, 25);
    ui->tableWidget->setColumnWidth(5, 25);
}

void MainWindow::createJsonFromArray(Node *array[], int size, const QString &filename) {
    // Crear el objeto JSON y agregar los elementos del array
    QJsonArray jsonArray;
    for (int i = 0; i < size; ++i) {
        QJsonObject jsonObj;
        jsonObj["title"] = QString::fromStdString(array[i]->title);
        jsonObj["upVotes"] = array[i]->upVotes;
        jsonObj["downVotes"] = array[i]->downVotes;
        jsonArray.append(jsonObj);
    }

    // Crear el documento JSON y guardarlo en un archivo
    QJsonDocument jsonDoc(jsonArray);
    QFile jsonFile(filename);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening JSON file for writing:" << jsonFile.errorString();
        return;
    }

    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();

    // Imprimir el contenido del JSON creado
    qDebug() << "JSON content:";
    qDebug().noquote() << jsonDoc.toJson(QJsonDocument::Indented);

}
