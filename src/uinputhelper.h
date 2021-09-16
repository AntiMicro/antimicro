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

#ifndef UINPUTHELPER_H
#define UINPUTHELPER_H

#include <QHash>
#include <QObject>
#include <QString>

class UInputHelper : public QObject
{
    Q_OBJECT
  public:
    static UInputHelper *getInstance();
    void deleteInstance();

    QString getDisplayString(unsigned int virtualkey);
    unsigned int getVirtualKey(QString codestring);

  protected:
    explicit UInputHelper(QObject *parent = 0);
    ~UInputHelper();

    void populateKnownAliases();

    static UInputHelper *_instance;
    QHash<QString, unsigned int> knownAliasesX11SymVK;
    QHash<unsigned int, QString> knownAliasesVKStrings;

  signals:

  public slots:
};

#endif // UINPUTHELPER_H
