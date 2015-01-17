#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QTime>
#include <QSqlRecord>
#include <QString>
#include <QDebug>

class Highscore : public QObject
{
  Q_OBJECT

private:
  QSqlDatabase *_highscores;
  QSqlQueryModel *_queryModel;

public:
  explicit Highscore(QObject *parent = 0);
  virtual ~Highscore();

  bool insertHighscore(QString name, int turns);
  QSqlQueryModel *getHighscore();
  bool clearHighscores();

signals:

public slots:

};

#endif // HIGHSCORE_H
