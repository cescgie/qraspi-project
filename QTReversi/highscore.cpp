#include "highscore.h"

Highscore::Highscore(QObject *parent) :
  QObject(parent)
{
  _highscores = new QSqlDatabase();
  *_highscores = QSqlDatabase::addDatabase("QSQLITE");
  _highscores->setHostName("localhost");
  _highscores->setDatabaseName("Highscores");

  _highscores->open();

  if(_highscores->lastError().isValid())
    qDebug() << "Failed to open the database: " << _highscores->lastError().text();

  QSqlQuery query;

  query.exec("CREATE TABLE Highscoreentries(Name varchar, Datum date, Points integer, Time time, ID integer primary key)");

  _queryModel = new QSqlQueryModel();
}

Highscore::~Highscore()
{
  _highscores->close();
  delete _highscores;
  delete _queryModel;
}

bool Highscore::insertHighscore(QString name, int points)
{
  QSqlQuery query;

  query.prepare("INSERT INTO Highscoreentries(Name, Datum, Points, Time) VALUES (:name, :date, :points, :time)");
  query.bindValue(":name", name);
  query.bindValue(":date", QDate::currentDate().toString("dd.MM.yyyy"));
  query.bindValue(":points", points);
  query.bindValue(":time", QTime::currentTime().toString("HH:mm:ss"));

  return query.exec();
}

QSqlQueryModel* Highscore::getHighscore()
{
  _queryModel->setQuery("SELECT Name, Points, Datum, Time FROM Highscoreentries ORDER BY Points DESC");
  _queryModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
  _queryModel->setHeaderData(1, Qt::Horizontal, tr("Points/64"));
  _queryModel->setHeaderData(2, Qt::Horizontal, tr("Date"));
  _queryModel->setHeaderData(3, Qt::Horizontal, tr("Time"));

  return _queryModel;
}

bool Highscore::clearHighscores()
{
  QSqlQuery query;

  query.prepare("DELETE FROM Highscoreentries");

  return query.exec();
}
