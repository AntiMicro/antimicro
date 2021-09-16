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

#include <QMenu>

#include "joybuttoncontextmenu.h"
#include "joycontrolstick.h"
#include "joycontrolstickbuttonpushbutton.h"

JoyControlStickButtonPushButton::JoyControlStickButtonPushButton(JoyControlStickButton *button, bool displayNames,
                                                                 QWidget *parent)
    : FlashButtonWidget(displayNames, parent)
{
    this->button = button;

    refreshLabel();
    enableFlashes();

    tryFlash();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

    // connect(button, SIGNAL(slotsChanged()), this, SLOT(refreshLabel()));
    connect(button, SIGNAL(propertyUpdated()), this, SLOT(refreshLabel()));
    connect(button, SIGNAL(activeZoneChanged()), this, SLOT(refreshLabel()));
    connect(button->getStick()->getModifierButton(), SIGNAL(activeZoneChanged()), this, SLOT(refreshLabel()));
}

JoyControlStickButton *JoyControlStickButtonPushButton::getButton() { return button; }

void JoyControlStickButtonPushButton::setButton(JoyControlStickButton *button)
{
    disableFlashes();
    if (this->button)
    {
        // disconnect(this->button, SIGNAL(slotsChanged()), this, SLOT(refreshLabel()));
        disconnect(button, SIGNAL(propertyUpdated()), this, SLOT(refreshLabel()));
        disconnect(this->button, SIGNAL(activeZoneChanged()), this, SLOT(refreshLabel()));
    }

    this->button = button;
    refreshLabel();
    enableFlashes();
    // connect(button, SIGNAL(slotsChanged()), this, SLOT(refreshLabel()));
    connect(button, SIGNAL(propertyUpdated()), this, SLOT(refreshLabel()));
    connect(button, SIGNAL(activeZoneChanged()), this, SLOT(refreshLabel()), Qt::QueuedConnection);
}

void JoyControlStickButtonPushButton::disableFlashes()
{
    if (button)
    {
        disconnect(button, SIGNAL(clicked(int)), this, SLOT(flash()));
        disconnect(button, SIGNAL(released(int)), this, SLOT(unflash()));
    }
    this->unflash();
}

void JoyControlStickButtonPushButton::enableFlashes()
{
    if (button)
    {
        connect(button, SIGNAL(clicked(int)), this, SLOT(flash()), Qt::QueuedConnection);
        connect(button, SIGNAL(released(int)), this, SLOT(unflash()), Qt::QueuedConnection);
    }
}

/**
 * @brief Generate the string that will be displayed on the button
 * @return Display string
 */
QString JoyControlStickButtonPushButton::generateLabel()
{
    QString temp;
    if (button)
    {
        if (!button->getActionName().isEmpty() && displayNames)
        {
            temp = button->getActionName().replace("&", "&&");
        } else
        {
            temp = button->getCalculatedActiveZoneSummary().replace("&", "&&");
        }
    }

    return temp;
}

void JoyControlStickButtonPushButton::showContextMenu(const QPoint &point)
{
    QPoint globalPos = this->mapToGlobal(point);
    JoyButtonContextMenu *contextMenu = new JoyButtonContextMenu(button, this);
    contextMenu->buildMenu();
    contextMenu->popup(globalPos);
}

void JoyControlStickButtonPushButton::tryFlash()
{
    if (button->getButtonState())
    {
        flash();
    }
}
