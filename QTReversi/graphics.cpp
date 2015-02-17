#include <QtGui>
#include "graphics.h"
#include "game.h"
#include "player.h"
#include <QMessageBox>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <assert.h>

graphics::graphics()
{
        centralWindow = new QWidget(this);
        scene = new glView(this);
        infos = new infoView(this);
        list_moves = new ListMoves(this);

        HighscoreView();
        initComponent();
        createActions();
        createMenus();
        createToolBars();
        createStatusBar();
        helpDialog = new QDialog();
        aboutDialog = new QDialog();
        soundsConfiguration();
        setWindowTitle(QtVersion);
        setWindowIcon(QIcon(":/images/QtM.png"));
}

graphics::~graphics()
{
        delete centralWindow;
        delete scene;
        delete infos;
        delete list_moves;
}

void graphics::initComponent()
{
        QHBoxLayout *layout = new QHBoxLayout;
        QVBoxLayout *topverticalLayout = new QVBoxLayout;
        topverticalLayout->addWidget(infos);
        topverticalLayout->addLayout(gridLayout);
        layout->addWidget(list_moves);
        layout->addWidget(scene);
        layout->addLayout(topverticalLayout);
        centralWindow->setLayout(layout);
        setCentralWidget(centralWindow);
}

void graphics::initialization( game *ge )
{
        connecting( ge );
        readSettings();
        refreshHighScore();
        ge->initializationDisplay();
}

void graphics::connecting( game *ge )
{
        if( ge != NULL )
        {
                //Verbindung von SIGNALS-SLOTS mit Game-engine und Grafik-engine
                connect( this, SIGNAL( startNewGame() ), ge, SLOT( initialization() ) );
                connect( ge, SIGNAL( playerWins(Player*) ), this, SLOT( displayWinner(Player*) ) );
                connect( ge, SIGNAL( enableUndoMoveAction(bool) ), this, SLOT( setDisplayUndoMoveAction(bool) ) );
                connect( ge, SIGNAL( enableRedoMoveAction(bool) ), this, SLOT( setDisplayRedoMoveAction(bool) ) );
                connect( this, SIGNAL( undoMoveAsked() ), ge, SLOT( undoMoveGlobal() ) );
                connect( this, SIGNAL( redoMoveAsked() ), ge, SLOT( redoMoveGlobal() ) );

                //Verbindung der Module mit glView und InfosWindow
                scene->connecting( ge );
                infos->connecting( ge );
                list_moves->connecting(ge);
                //Erstellen der Anzeigeinformationen fuer Spiel
        }
}

void graphics::closeEvent(QCloseEvent *event)
{
        effectBounce.play();
        int r = QMessageBox::warning(this,QtVersion,tr("Do you really want to exit the game?"),
                                QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
        if(r == QMessageBox::Yes){
                writeSettings();
                event->accept();
        }
        else{
                event->ignore();
        }
}

//Menu-Buttons
void graphics::createActions()
{
        newAction = new QAction(tr("&New"), this);
        newAction->setIcon(QIcon(":/images/NewGame.png"));
        newAction->setShortcut(tr("Ctrl+N"));
        newAction->setStatusTip(tr("Play a new game"));
        connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

        saveAction = new QAction(tr("&Save"), this);
        saveAction->setIcon(QIcon(":/images/SaveGame.png"));
        saveAction->setShortcut(tr("Ctrl+S"));
        saveAction->setStatusTip(tr("Save this game"));
        connect(saveAction, SIGNAL(triggered()), this, SLOT(saveGame()));

        loadAction = new QAction(tr("&Load"), this);
        loadAction->setIcon(QIcon(":/images/LoadGame.png"));
        loadAction->setShortcut(tr("Ctrl+L"));
        loadAction->setStatusTip(tr("Load a saved game"));
        connect(loadAction, SIGNAL(triggered()), this, SLOT(loadGame()));

        exitAction = new QAction(tr("&Exit"), this);
        exitAction->setIcon(QIcon(":/images/Quit.png"));
        exitAction->setShortcut(tr("Ctrl+X"));
        exitAction->setStatusTip(tr("Exit the application"));
        connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        regularMovesAction = new QAction(tr("Regular Moves"), this);
        regularMovesAction->setCheckable(true);
        regularMovesAction->setChecked(true);
        regularMovesAction->setStatusTip(tr("Show or hide regular moves"));
        connect(regularMovesAction, SIGNAL(triggered()), this, SLOT(updateSettingRegularMoves()));

        lastMoveAction = new QAction(tr("Last Move"), this);
        lastMoveAction->setCheckable(true);
        lastMoveAction->setChecked(true);
        lastMoveAction->setStatusTip(tr("Show or hide last move"));
        connect(lastMoveAction, SIGNAL(triggered()), this, SLOT(updateSettingLastMove()));

        animationAction = new QAction(tr("Animations"), this);
        animationAction->setCheckable(true);
        animationAction->setChecked(true);
        animationAction->setStatusTip(tr("Show or hide animations"));
        connect(animationAction, SIGNAL(triggered()), this, SLOT(updateSettingAnimation()));

        volumeAction = new QAction(tr("Menu Sounds"), this);
        volumeAction->setCheckable(true);
        volumeAction->setChecked(true);
        volumeAction->setStatusTip(tr("Set the volume"));
        connect(volumeAction, SIGNAL(triggered()), this, SLOT(updateSettingVolume()));

        undoMoveAction = new QAction(tr("&Undo Move"), this);
        undoMoveAction->setIcon(QIcon(":/images/UndoMove.png"));
        undoMoveAction->setShortcut(tr("Ctrl+U"));
        undoMoveAction->setStatusTip(tr("Undo the last move"));
        connect(undoMoveAction, SIGNAL(triggered()), this, SLOT(undoMove()));
        undoMoveAction->setEnabled(false);

        redoMoveAction = new QAction(tr("&Redo Move"), this);
        redoMoveAction->setIcon(QIcon(":/images/RedoMove.png"));
        redoMoveAction->setShortcut(tr("Ctrl+R"));
        redoMoveAction->setStatusTip(tr("Redo the last move canceled"));
        connect(redoMoveAction, SIGNAL(triggered()), this, SLOT(redoMove()));
        redoMoveAction->setEnabled(false);

        preferencesAction = new QAction(tr("&Preferences"), this);
        preferencesAction->setIcon(QIcon(":/images/Preferences.png"));
        preferencesAction->setShortcut(tr("Ctrl+P"));
        preferencesAction->setStatusTip(tr("Configure the options game"));
        connect(preferencesAction, SIGNAL(triggered()), this, SLOT(preferences()));

        //fullscreen
        fullScreenAction = new QAction(tr("&Fullscreen"), this);
        fullScreenAction->setIcon(QIcon(":/images/Fullscreen.png"));
        fullScreenAction->setShortcut(tr("Ctrl+L"));
        fullScreenAction->setStatusTip(tr("Set Full Screen"));
        connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(fullScreen()));

        loadBoard = new QAction(tr("&Board"),this);
        loadBoard->setIcon(QIcon(":/images/Background.png"));
        loadBoard->setShortcut(tr("Ctrl+M"));
        loadBoard->setStatusTip(tr("Load the board background"));
        connect(loadBoard, SIGNAL(triggered()), this, SLOT(choose_pic()));

        aboutAction = new QAction(tr("&About"), this);
        aboutAction->setIcon(QIcon(":/images/Info.png"));
        aboutAction->setStatusTip(tr("About..."));
        connect(aboutAction, SIGNAL(triggered()), this, SLOT(onButtonAboutPressed()));

        helpAction = new QAction(tr("&Help"), this);
        helpAction->setIcon(QIcon(":/images/Help.png"));
        helpAction->setShortcut(tr("Ctrl+H"));
        helpAction->setStatusTip(tr("Help on line"));
        connect(helpAction, SIGNAL(triggered()), this, SLOT(onButtonHelpPressed()));

        printAction = new QAction(tr("&Print Highscores"), this);
        printAction->setIcon(QIcon(":/images/NewGame.png"));
        printAction->setStatusTip(tr("Print Highscores"));
        connect(printAction, SIGNAL(triggered()), this, SLOT(printHighScore()));

        //Highscore
        ClearHSAction = new QAction(tr("&Clear Highscores"), this);
        ClearHSAction->setIcon(QIcon(":/images/erase.png"));
        ClearHSAction->setStatusTip(tr("Clear Highscores"));
        connect(ClearHSAction, SIGNAL(triggered()), this, SLOT(deleteHighscores()));
        //button Highscore
        connect(buttonPrint, SIGNAL(clicked()), this, SLOT(printHighScore()));
}

void graphics::createMenus()
{
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(newAction);
        fileMenu->addAction(saveAction);
        fileMenu->addAction(loadAction);
        fileMenu->addSeparator();
        fileMenu->addAction(aboutAction);
        fileMenu->addAction(exitAction);

        viewMenu = menuBar()->addMenu(tr("&View"));
        viewMenu->addAction(regularMovesAction);
        viewMenu->addAction(lastMoveAction);
        viewMenu->addAction(animationAction);
        viewMenu->addAction(volumeAction);  //sound

        toolsMenu = menuBar()->addMenu(tr("&Tools"));
        toolsMenu->addAction(undoMoveAction);
        toolsMenu->addAction(redoMoveAction);
        toolsMenu->addSeparator();
        toolsMenu->addSeparator();
        toolsMenu->addAction(ClearHSAction);
}

void graphics::createToolBars()
{
        fileToolBar = addToolBar(tr("&File"));
        fileToolBar->addAction(newAction);
        fileToolBar->addAction(saveAction);
        fileToolBar->addAction(loadAction);
        fileToolBar->setAutoFillBackground(true);

        toolsToolBar = addToolBar(tr("&Tools"));
        toolsToolBar->addAction(undoMoveAction);
        toolsToolBar->addAction(redoMoveAction);
        toolsToolBar->addAction(preferencesAction);
        toolsToolBar->addAction(loadBoard);
        toolsToolBar->addAction(helpAction);
        toolsToolBar->addAction(fullScreenAction);
        toolsToolBar->addAction(exitAction);
}

void graphics::createStatusBar()
{
        statusBarLabel = new QLabel("");
        statusBar()->addWidget(statusBarLabel,1);
}


void graphics::writeSettings()
{
//      QSettings settings("HTW Berlin", "Reversi_v1.0");
        infos->writeSettings();
//      scene->writeSettings();
}

void graphics::readSettings()
{
//      QSettings settings("HTW Berlin", "Reversi_v1.0");
        infos->readSettings();
//      scene->readSettings(settings);
}


void graphics::newGame()
{
        effectBounce.play();

        int r = QMessageBox::warning(this,QtVersion,tr("Play new game?"),
                QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
        if(r == QMessageBox::Yes){
            effectStart.play();
            emit startNewGame();
        }
}

bool graphics::saveGame()
{
        QAction *action = qobject_cast<QAction *>(sender());
        QByteArray fileFormat = action->data().toByteArray();
        return saveFile();
}

bool graphics::saveFile()
{
    QString initialPath = QDir::currentPath() + "/untitled.dat";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                       initialPath,tr("%1 Files (*.%2);;All Files (*)").arg("dat"));
    if (fileName.isEmpty()) {
        return false;
    } else {

        savlo = new game();
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);   // serialize the data into the file
        //to do!!
        QString f = QString::fromStdString(savlo->toString());
        out << f;
        file.close();
        return true;

    }
}

void graphics::loadGame()
{
        savlo = new game();
        if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this,
                                                            tr("Open File"), QDir::currentPath());
            if (!fileName.isEmpty()){
                QFile file(fileName);
                file.open(QIODevice::ReadOnly);
                QTextStream in(&file);    // read the data serialized from the file
                qDebug() << "Stelle:" << "open called";
                QString str=in.readAll();
                std::string a = str.toStdString();

                //to do!!
                savlo->fromString(a);
                //savelofromString(a);
                savlo->initialization();
                scene->initializeGL();
                //fromString(a);
                //nextTurn();

            }
        }
}
bool graphics::maybeSave()
{
    return true;
}

void graphics::choose_pic()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" )
                );

    imageObject = new QImage();
    imageObject->load(imagePath);

    image = QPixmap::fromImage(*imageObject);
    //picCanvas->setPixmap(image);
    //picCanvas->setPixmap(image.scaled(100,100,Qt::KeepAspectRatio));
    //picPanel->addWidget(picCanvas,0,0);
}

void graphics::preferences()
{
    effectBounce.play();
    cout<<"test"<<endl;
//Aufruf der moeglichen Spielschwierigkeiten
        QString name_p1 = infos->getPlayer(p1)->getName(),
                        name_p2 = infos->getPlayer(p2)->getName();
        int type_p1, type_p2;
        switch( infos->getPlayer(p1)->getType() )
        {
                case AI_1:
                        type_p1 = 1;
                        break;
                case AI_2:
                        type_p1 = 2;
                        break;
                case AI_3:
                        type_p1 = 3;
                        break;
                case Local:
                default:
                        type_p1 = 0;
                        break;
        }
        switch( infos->getPlayer(p2)->getType() )
        {
                case AI_1:
                        type_p2 = 1;
                        break;
                case AI_2:
                        type_p2 = 2;
                        break;
                case AI_3:
                        type_p2 = 3;
                        break;
                case Local:
                default:
                        type_p2 = 0;
                        break;
        }

//Erstellen des Dialogs
        PlayerSetting dialog(this);

//Aktualisieren der Werte des Dialogs, der Spieler zusammengefasst
//      cout << "       name_p1: " << string(name_p1) << "      name_p2: " << string(name_p2) << endl;
//      cout << "       type_p1: " << type_p1 << "      type_p2: " << type_p2 << endl;
        dialog.setNames( name_p1, name_p2 );
        dialog.setTypes(type_p1,type_p2);


        if( dialog.exec() )
        {
                bool modif_type = false;

                if( name_p1 != dialog.lineEdit_name_p1->text() )  //Wenn der Name eines Spielers geändert wird
                {
                        infos->getPlayer(p1)->setName( dialog.lineEdit_name_p1->text() );  //Daten aktualisieren
                        infos->setNameP1( dialog.lineEdit_name_p1->text() );  //Anzeige aktualisieren
                }
                if( name_p2 != dialog.lineEdit_name_p2->text() )  //Wenn der Name des Spielers 2 geändert wird
                {
                        infos->getPlayer(p2)->setName( dialog.lineEdit_name_p2->text() );  //Daten aktualisieren
                        infos->setNameP2( dialog.lineEdit_name_p2->text() );  //Anzeige aktualisieren
                }
                if( type_p1 != dialog.comboBox_type_p1->currentIndex() )  //Wenn der Typ von Spieler 1 geändert wird
                {
                        switch( dialog.comboBox_type_p1->currentIndex() )
                        {
                                case 1:
                                        infos->getPlayer(p1)->setType( AI_1 );
                                        infos->setTypeP1( AI_1 );
                                        break;
                                case 2:
                                        infos->getPlayer(p1)->setType( AI_2 );
                                        infos->setTypeP1( AI_2 );
                                        break;
                                case 3:
                                        infos->getPlayer(p1)->setType( AI_3 );
                                        infos->setTypeP1( AI_3 );
                                        break;
                                case 0:
                                default:
                                        infos->getPlayer(p1)->setType( Local );
                                        infos->setTypeP1( Local );
                                        break;
                        }
                        modif_type = true;
                }
                if( type_p2 != dialog.comboBox_type_p2->currentIndex() )  //Wenn der Typ von Spieler 2 geändert wird
                {
                        switch( dialog.comboBox_type_p2->currentIndex() )
                        {
                                case 1:
                                        infos->getPlayer(p2)->setType( AI_1 );
                                        infos->setTypeP2( AI_1 );
                                        break;
                                case 2:
                                        infos->getPlayer(p2)->setType( AI_2 );
                                        infos->setTypeP2( AI_2 );
                                        break;
                                case 3:
                                        infos->getPlayer(p2)->setType( AI_3 );
                                        infos->setTypeP2( AI_3 );
                                        break;
                                case 0:
                                default:
                                        infos->getPlayer(p2)->setType( Local );
                                        infos->setTypeP2( Local );
                                        break;
                        }
                        modif_type = true;
                }
                if( modif_type )  //Wenn der Typ eines der Spieler geaendert wurde -> neues Spiel!
                {
                        effectStart.play();
                        emit startNewGame();
                }
        }
}


void graphics::displayWinner(Player *p)
{
        effectEnd.play();
        if( p != NULL ) //Wenn es einen Gewinner gibt
        {
            QString namo = p->getName();
            int punkte = p->getScore();
            createHighscore(namo,punkte);
            QString str = p->getName() + " win the game!";
            QMessageBox::information(this,QtVersion,str,
                    QMessageBox::Ok | QMessageBox::Default);
        }
        else //Kein Gewinner -> Unentschieden!
        {
            QMessageBox::information(this,QtVersion,tr("the result is draw!"),
                    QMessageBox::Ok | QMessageBox::Default);
        }
        //emit startNewGame();
        effectEnd.stop();
        emit preferences();
}

void graphics::updateSettingRegularMoves()
{
        scene->setRegularMovesSetting( regularMovesAction->isChecked() );
}

void graphics::updateSettingLastMove()
{
        scene->setLastMoveSetting( lastMoveAction->isChecked() );
}

void graphics::updateSettingAnimation()
{
        scene->setAnimationSetting( animationAction->isChecked() );
}

//sound
void graphics::updateSettingVolume()
{
    effectBounce.setVolume(volumeAction->isChecked());
    effectEnd.setVolume(volumeAction->isChecked());
    effectNext.setVolume(volumeAction->isChecked());
    effectPrev.setVolume(volumeAction->isChecked());
    effectStart.setVolume(volumeAction->isChecked());
}

void graphics::setDisplayUndoMoveAction(bool b)
{
        undoMoveAction->setEnabled(b);
}

void graphics::setDisplayRedoMoveAction(bool b)
{
        redoMoveAction->setEnabled(b);
}

void graphics::undoMove()
{
        effectPrev.play();
        scene->setMoveAsked(false);
        emit undoMoveAsked();
}

void graphics::redoMove()
{
        effectNext.play();
        scene->setMoveAsked(false);
        emit redoMoveAsked();
}
//Help Function
void graphics::onButtonHelpPressed()
{
    effectBounce.play();    //help
    cout<<"Help"<<endl;
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QGridLayout *gridLayoutHelpDialog_2;
    QGridLayout *gridLayoutHelpDialog;
    QLabel *labelHelpDialog;
    QHBoxLayout *horizontalLayoutHelpDialog;
    QSpacerItem *horizontalSpacerHelpDialog;
    QPushButton *okButtonHelpDialog;

    if (helpDialog->objectName().isEmpty())
      helpDialog->setObjectName(QStringLiteral("helpDialog"));

    helpDialog->resize(391, 262);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(helpDialog->sizePolicy().hasHeightForWidth());
    helpDialog->setSizePolicy(sizePolicy);
    helpDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    gridLayoutHelpDialog_2 = new QGridLayout(helpDialog);
    gridLayoutHelpDialog_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayoutHelpDialog_2->setSizeConstraint(QLayout::SetFixedSize);
    gridLayoutHelpDialog = new QGridLayout();
    gridLayoutHelpDialog->setObjectName(QStringLiteral("gridLayout"));
    labelHelpDialog = new QLabel(helpDialog);
    labelHelpDialog->setObjectName(QStringLiteral("label"));
    labelHelpDialog->setWordWrap(true);

    gridLayoutHelpDialog->addWidget(labelHelpDialog, 0, 0, 1, 1);

    horizontalLayoutHelpDialog = new QHBoxLayout();
    horizontalLayoutHelpDialog->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalSpacerHelpDialog = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayoutHelpDialog->addItem(horizontalSpacerHelpDialog);

    okButtonHelpDialog = new QPushButton(helpDialog);
    okButtonHelpDialog->setObjectName(QStringLiteral("okButton"));

    horizontalLayoutHelpDialog->addWidget(okButtonHelpDialog);

    gridLayoutHelpDialog->addLayout(horizontalLayoutHelpDialog, 1, 0, 1, 1);

    gridLayoutHelpDialog_2->addLayout(gridLayoutHelpDialog, 0, 0, 1, 1);

    helpDialog->setWindowTitle(QApplication::translate("helpDialog", "Help", 0));
    labelHelpDialog->setText(QApplication::translate("helpDialog", "<html><head/><body><center><img src=':/images/Help.png' width='50' height='50'></img></center><p><span style=\" font-size:14pt;" \
        "text-decoration: underline;\">Wie wird Reversi gespielt?</span></p><p align=\"justify\"><span style=\font-size:14pt;\">Bei Reversi wir auf " \
        "seinem Spielbrett mit 8 mal 8 Spielfeldern gespielt. Die Farbe der Spielsteine " \
        "sind auf einen Seite schwarz und auf der anderen Seite weiß.Beim Spielstart sieht die Anfangssituation immer gleich aus. " \
        "Beide Spieler haben 2 Spielsteine die immer gleich in der Mitte des Spielbrettes positioniert sind. Je nach dem wie man " \
        "sich in den Spieleinstellungen als Spieler eingetragen hat beginnt man entweder als erster oder als zweiter. Nun " \
        "versucht man abwechselnd die gegnerischen Steine waagerecht, senkrecht oder diagonal einzuschließen. Es können beliebig " \
        "viele Steine des Gegners auf einmal eingeschlossen werden. Kann ein Spieler Steine des Gegners einschließen so werden " \
        "diese zu seinen eigenen verwandelt. Kann ein Spieler keine Steine setzen, so muss er aussetzen. Das Spiel ist dann beendet, " \
        "wenn alle 64 Felder belegt sind oder keiner der Spieler mehr setzen kann. Der Gewinner ist, wer am Ende des Spiels am " \
        "meisten Steine auf dem Spielbrett liegen hat.</span></p></body></html>", 0));
    okButtonHelpDialog->setText(QApplication::translate("helpDialog", "OK", 0));

    QMetaObject::connectSlotsByName(helpDialog);

    connect(okButtonHelpDialog, SIGNAL(clicked()), helpDialog, SLOT(close()));

    helpDialog->exec();

}

//fullscreen
void graphics::fullScreen()
{
    effectBounce.play(); //sound
    QDialog *dlg = new QDialog(this);
    QHBoxLayout *dlg_layout = new QHBoxLayout(dlg);
        dlg_layout->setContentsMargins(0, 0, 0, 0);
        dlg_layout->addWidget(scene);
        dlg->setLayout(dlg_layout);
        dlg->showFullScreen();

        bool r = connect(dlg, SIGNAL(rejected()), this, SLOT(showGlNormal()));
        assert(r);
        r = connect(dlg, SIGNAL(accepted()), this, SLOT(showGlNormal()));
        assert(r);
        refreshHighScore();

}
//fullscreen
void graphics::showGlNormal() {
    centralWindow = new QWidget(this);
    HighscoreView();
    initComponent();
}

//Help Function
void graphics::onButtonAboutPressed()
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QGridLayout *gridLayoutAboutDialog_2;
    QGridLayout *gridLayoutAboutDialog;
    QLabel *labelAboutDialog;
    QHBoxLayout *horizontalLayoutAboutDialog;
    QSpacerItem *horizontalSpacerAboutDialog;
    QPushButton *okButtonAboutDialog;

    if (aboutDialog->objectName().isEmpty())
      aboutDialog->setObjectName(QStringLiteral("aboutDialog"));

    aboutDialog->resize(391, 262);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(aboutDialog->sizePolicy().hasHeightForWidth());
    aboutDialog->setSizePolicy(sizePolicy);
    aboutDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    gridLayoutAboutDialog_2 = new QGridLayout(aboutDialog);
    gridLayoutAboutDialog_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayoutAboutDialog_2->setSizeConstraint(QLayout::SetFixedSize);
    gridLayoutAboutDialog = new QGridLayout();
    gridLayoutAboutDialog->setObjectName(QStringLiteral("gridLayout"));
    labelAboutDialog = new QLabel(aboutDialog);
    labelAboutDialog->setObjectName(QStringLiteral("label"));
    labelAboutDialog->setWordWrap(true);

    gridLayoutAboutDialog->addWidget(labelAboutDialog, 0, 0, 1, 1);

    horizontalLayoutAboutDialog = new QHBoxLayout();
    horizontalLayoutAboutDialog->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalSpacerAboutDialog = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayoutAboutDialog->addItem(horizontalSpacerAboutDialog);

    okButtonAboutDialog = new QPushButton(aboutDialog);
    okButtonAboutDialog->setObjectName(QStringLiteral("okButton"));

    horizontalLayoutAboutDialog->addWidget(okButtonAboutDialog);

    gridLayoutAboutDialog->addLayout(horizontalLayoutAboutDialog, 1, 0, 1, 1);

    gridLayoutAboutDialog_2->addLayout(gridLayoutAboutDialog, 0, 0, 1, 1);

    aboutDialog->setWindowTitle(QApplication::translate("aboutDialog", "About", 0));
    labelAboutDialog->setText(QApplication::translate("aboutDialog", "<html><head/><body><center><img src=':/images/QtM.png' width='50' height='50'></img><p><span style=\" font-size:14pt;" \
    "text-decoration: underline;\">QtReversi</span></p><p align=\"justify\"><span style=\font-size:14pt;\"><p>Created with QtCreator</p>" \
    "<p>By Renaldo Weiser & Yoggi Firmanda</p></span></p><p>HTW Berlin 2015</p></center></body></html>", 0));
    okButtonAboutDialog->setText(QApplication::translate("aboutDialog", "OK", 0));

    QMetaObject::connectSlotsByName(aboutDialog);

    connect(okButtonAboutDialog, SIGNAL(clicked()), aboutDialog, SLOT(close()));

    aboutDialog->exec();
}

void graphics::soundsConfiguration()
{
    //sound
    effectBounce.setSource(QUrl::fromLocalFile(":/sounds/bounce.wav"));
    effectBounce.setLoopCount(1);

    effectStart.setSource(QUrl::fromLocalFile(":/sounds/start.wav"));
    effectStart.setLoopCount(1);

    effectEnd.setSource(QUrl::fromLocalFile(":/sounds/win.wav"));
    effectEnd.setLoopCount(1);

    effectNext.setSource(QUrl::fromLocalFile(":/sounds/next.wav"));
    effectNext.setLoopCount(1);

    effectPrev.setSource(QUrl::fromLocalFile(":/sounds/prev.wav"));
    effectPrev.setLoopCount(1);

    setUnifiedTitleAndToolBarOnMac ( true );
}

QSqlQueryModel* graphics::getHighscores()
{
  return _highscore.getHighscore();
}

/**
 * This function deletes all highscores from the database.
 */
void graphics::deleteHighscores()
{
    int r = QMessageBox::warning(this,QtVersion,tr("Clear Highscore?"),
                            QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
    if(r == QMessageBox::Yes){
       _highscore.clearHighscores();
    }
}

void graphics::createHighscore(QString nam, int punk)
{
    cout<<"punk :"<<punk<<endl;
  _highscore.insertHighscore(nam, punk);
}

void graphics::refreshHighScore()
{
    tableViewHighscores->setModel(getHighscores());
    tableViewHighscores->resizeColumnToContents(1);

}
//highscore
void graphics::cleanHighScore()
{
    _highscore.clearHighscores();
}

//highscore
void graphics::printHighScore()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *printDialog = new QPrintDialog(&printer);
    QTextDocument *document = new QTextDocument();

    printDialog->setWindowTitle(tr("Print Document"));

    if (printDialog->exec() == QDialog::Accepted)
    {
      QString text = "<table border=10 align='center'>";

      text.append("<h3 align='center'>Reversi Highscore</h3><hr><br>");
      text.append("<tr>");
      text.append("<th>Player</th>");
      text.append("<th>Points/64</th>");
      text.append("<th>Date</th>");
      text.append("<th>Time</th>");
      text.append("</tr>");

      for (int i = 0; i < tableViewHighscores->model()->rowCount(); ++i)
      {
        text.append("<tr>");

        for (int j = 0; j < tableViewHighscores->model()->columnCount(); ++j)
        {
          text.append("<td align='center'>");
          text.append(tableViewHighscores->model()->index(i, j).data().toString());
          text.append("</td>");
        }

        text.append("</tr>");
      }

      text.append("</table>");

      document->setHtml(text);
      document->print(&printer);
    }
}

void graphics::HighscoreView()
{
    gridLayout = new QGridLayout();
    groupBoxHighscores = new QGroupBox();
    horizontalLayout = new QHBoxLayout(groupBoxHighscores);
    horizontalLayout->setAlignment(Qt::AlignHCenter);
    tableViewHighscores = new QTableView(groupBoxHighscores);
    horizontalLayout->addWidget(tableViewHighscores);
    buttonPrint = new QPushButton("Print Highscore",this);
    highscoresLabel = new QLabel("Highscores");
    highscoresLabel->setAlignment(Qt::AlignHCenter);
    buttonLayout = new QHBoxLayout();\
    buttonLayout->addWidget(buttonPrint);
    verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(highscoresLabel);
    verticalLayout->addStretch();
    verticalLayout->addWidget(tableViewHighscores);
    verticalLayout->addStretch();
    verticalLayout->addLayout(buttonLayout);
    verticalLayout->addStretch();
    gridLayout->addLayout(verticalLayout,0, 0, 1, 1);
}
