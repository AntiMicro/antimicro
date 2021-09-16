/* antimicro Gamepad to KB+M event mapper
 * Copyright (C) 2015 Travis Nickles <nickles.travis@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XMLCONFIGWRITER_H
#define XMLCONFIGWRITER_H

#include <QFile>
#include <QObject>
#include <QXmlStreamWriter>

#include "common.h"
#include "inputdevice.h"

class XMLConfigWriter : public QObject
{
    Q_OBJECT
  public:
    explicit XMLConfigWriter(QObject *parent = 0);
    ~XMLConfigWriter();
    void setFileName(QString filename);
    bool hasError();
    QString getErrorString();

  protected:
    QXmlStreamWriter *xml;
    QString fileName;
    QFile *configFile;
    InputDevice *joystick;
    bool writerError;
    QString writerErrorString;

  signals:

  public slots:
    void write(InputDevice *joystick);
};

#endif // XMLCONFIGWRITER_H
