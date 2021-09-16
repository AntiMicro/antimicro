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

#ifndef GAMECONTROLLERDPAD_H
#define GAMECONTROLLERDPAD_H

#include <QObject>

#include "vdpad.h"

class GameControllerDPad : public VDPad
{
    Q_OBJECT
  public:
    explicit GameControllerDPad(JoyButton *upButton, JoyButton *downButton, JoyButton *leftButton, JoyButton *rightButton,
                                int index, int originset, SetJoystick *parentSet, QObject *parent = 0);

    virtual QString getName(bool forceFullFormat, bool displayName);
    virtual QString getXmlName();

    void readJoystickConfig(QXmlStreamReader *xml);

    static const QString xmlName;

  signals:

  public slots:
};

#endif // GAMECONTROLLERDPAD_H
