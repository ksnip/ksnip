/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "CommandLineParserHelper.h"

void CommandLineParserHelper::addImageGrabberOptions(QCommandLineParser &parser, const QList<CaptureModes> &captureModes)
{
    // Add image grabber specific options
    if (captureModes.contains(CaptureModes::RectArea)) {
        parser.addOption({{QStringLiteral("r"), QStringLiteral("rectarea")},
                          QCoreApplication::translate("main", "Select a rectangular area from where to take a screenshot.")
                         });
    }
    if (captureModes.contains(CaptureModes::FullScreen)) {
        parser.addOption({{QStringLiteral("f"), QStringLiteral("fullscreen")},
                          QCoreApplication::translate("main", "Capture the fullscreen including all monitors.")
                         });
    }
    if (captureModes.contains(CaptureModes::CurrentScreen)) {
        parser.addOption({{QStringLiteral("m"), QStringLiteral("current")},
                          QCoreApplication::translate("main", "Capture the screen (monitor) where the mouse cursor is currently located.")
                         });
    }
    if (captureModes.contains(CaptureModes::ActiveWindow)) {
        parser.addOption({{QStringLiteral("a"), QStringLiteral("active")},
                          QCoreApplication::translate("main", "Capture the window that currently has input focus.")
                         });
    }
    if (captureModes.contains(CaptureModes::WindowUnderCursor)) {
        parser.addOption({{QStringLiteral("u"), QStringLiteral("windowundercursor")},
                          QCoreApplication::translate("main", "Capture the window that is currently under the mouse cursor.")
                         });
    }
}

void CommandLineParserHelper::addDefaultOptions(QCommandLineParser &parser)
{
    parser.addOptions({
                          {{QStringLiteral("d"), QStringLiteral("delay")},
                           QCoreApplication::translate("main", "Delay before taking the screenshot."),
                           QCoreApplication::translate("main", "seconds")
                          },
                          {{QStringLiteral("c"), QStringLiteral("cursor")},
                           QCoreApplication::translate("main", "Capture mouse cursor on screenshot."),
                          },
                          {{QStringLiteral("e"), QStringLiteral("edit")},
                           QCoreApplication::translate("main", "Edit existing image in ksnip"),
                           QCoreApplication::translate("main", "image")
                          },
                          {{QStringLiteral("s"), QStringLiteral("save")},
                           QCoreApplication::translate("main", "Save screenshot to default location without opening in editor."),
                          }
                      });
}

bool CommandLineParserHelper::isSet(QCommandLineParser &parser, const QString &option)
{
    return parser.optionNames().contains(option) && parser.isSet(option);
}
