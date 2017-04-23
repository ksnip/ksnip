/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "CmdParser.h"

CmdParser::CmdParser()
{
}

//
// Public Functions
//

/*
 * Add option to list, is success full, returns true, otherwise, in case the
 * option was added already, returns false.
 */
bool CmdParser::addOption(const QString& name,
                          const QString& description,
                          const QString& longName)
{
    for (CmdOption option : mOptions) {
        if (option.name() == name || option.longName() == longName) {
            return false;
        }
    }

    mOptions.append(CmdOption(name, description, longName));
    return true;
}

/*
 * Checks the provided arguments and sets the options list accordingly if an
 * option has been detected it will be set (isSet).
 */
bool CmdParser::parse(const QStringList& arguments)
{
    // Points always to last set option
    CmdOption* lastOption = nullptr;

    // Loop through all arguments
    for (QString arg : arguments) {
        // The first argument if the filename, we ignore it.
        if (arg == arguments.first()) {
            continue;
        }

        // Check if we are matching a long name option
        if (arg.startsWith("--")) {
            // Check if we have a matching option, if yes, get a pointer to is
            lastOption = setOption(arg.remove("--"));

            // If this is an unknown option, the pointer will be set to nullptr
            // so let's add it to the unknown list.
            if (lastOption == nullptr) {
                setUnknownOption(arg.remove("--"));
            }
        } else
            // Check if we are matching a short name option
            if (arg.startsWith("-") && arg.count() > 1) {
                for (auto j = 1; j < arg.count(); j++) {
                    lastOption = setOption(arg.at(j));

                    if (lastOption == nullptr) {
                        setUnknownOption(arg.at(j));
                    }
                }
            } else {
                // If the argument wasn't neither a long or short option, we
                // will treat it as a value of the last option and add it
                // appropriately
                if (lastOption != nullptr) {
                    lastOption->setValue(arg);
                } else {
                    // If the last entry was not an option and we haven't seen
                    // any option earlier, we will threat this as an invalid
                    // parameter.
                    setUnknownOption(arg.remove("-"));
                }
            }
    }

    // Check if we have seen any errors, if yes, we print the error message and
    // return false.
    if (showError()) {
        showHelp();
        return false;
    }

    return true;
}

void CmdParser::showHelp() const
{
    std::cout << "Usage: " + QApplication::applicationName().toStdString() + " [options]\n\n";
    std::cout << "Options:\n";

    std::cout << std::left;

    for (CmdOption option : mOptions) {
        std::cout << "  " <<
                  std::setw(4) << "-" + option.name().toStdString() + "," <<
                  std::setw(25) << "--" + option.longName().toStdString() <<
                  std::setw(30) << option.description().toStdString() + "." << "\n";
    }
}

void CmdParser::showVersion() const
{
    std::cout << QApplication::applicationName().toStdString() +
              " " +
              QApplication::applicationVersion().toStdString()  << "\n";
}

bool CmdParser::isSet(const QString& name)
{
    for (CmdOption option : mOptions) {
        if ((option.name() == name || option.longName() == name) && option.isSet()) {
            return true;
        }
    }

    return false;
}

//
// Private Functions
//

CmdOption* CmdParser::setOption(const QString& name)
{
    for (CmdOption& option : mOptions) {
        if (option.name() == name || option.longName() == name) {
            option.set(true);
            return &option;
        }
    }

    return nullptr;
}

/*
 * Keep a list of all unknown option so we can print an error message.
 */
void CmdParser::setUnknownOption(const QString& name)
{
    for (QString str : mUnknownOptions) {
        if (str == name) {
            return;
        }
    }

    mUnknownOptions.append(name);
}

/*
 * Print error message with all unknown options.
 */
bool CmdParser::showError() const
{
    if (mUnknownOptions.count() == 0) {
        return false;
    }

    std::cout << "Unknown options: ";

    for (QString str : mUnknownOptions) {
        std::cout << " " << str.toStdString();

        if (str == mUnknownOptions.last()) {
            std::cout << ".\n";
        } else {
            std::cout << ",";
        }
    }

    return true;
}

QString CmdParser::value(const QString& name)
{
    for (CmdOption option : mOptions) {
        if ((option.name() == name || option.longName() == name) && option.isSet()) {
            return option.value();
        }
    }

    return QString();
}
