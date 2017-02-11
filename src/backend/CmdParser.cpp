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
 * Add option to list, is success full, returns true, otherwise, in case the option was added
 * already, returns false.
 */
bool CmdParser::addOption(QString name, QString description, QString longName)
{
    for (int i = 0; i < mOptions.count(); i++) {
        if (mOptions.at(i).name() == name || mOptions.at(i).longName() == longName) {
            return false;
        }
    }

    mOptions.append(CmdOption(name, description, longName));
    return true;
}

/*
 * Checks the provided arguments and sets the options list accordingly if an option has been
 * detected it will be set (isSet).
 */
bool CmdParser::parse(QStringList arguments)
{
    // Points always to last set option
    CmdOption* lastOption = NULL;

    // Loop through all arguments
    for (int i = 1; i < arguments.count(); i++) {
        // Check if we are matching a long name option
        if (arguments.at(i).startsWith("--") /*&& arguments.at( i ).count() > 2*/) {
            // Check if we have a matching option, if yes, get a pointer to is
            lastOption = setOption(arguments[i].remove("--"));

            // If this is an unknown option, the pointer will be set to NULL so let's add it to the
            // unknown list.
            if (lastOption == NULL) {
                setUnknownOption(arguments[i].remove("--"));
            }
        } else
            // Check if we are matching a short name option
            if (arguments.at(i).startsWith("-") && arguments.at(i).count() > 1) {
                for (int j = 1; j < arguments.at(i).count(); j++) {
                    lastOption = setOption(arguments.at(i).at(j));

                    if (lastOption == NULL) {
                        setUnknownOption(arguments.at(i).at(j));
                    }
                }
            } else {
                // If the argument wasn't neither a long or short option, we will treat it as a value
                // of the last option and add it appropriately
                if (lastOption != NULL) {
                    lastOption->setValue(arguments.at(i));
                } else {
                    // If the last entry was not an option and we haven't seen any option earlier,
                    // we will threat this as an invalid parameter.
                    setUnknownOption(arguments[i].remove("-"));
                }
            }
    }

    // Check if we have seen any errors, if yes, we print the error message and return false.
    if (showError()) {
        showHelp();
        return false;
    }

    return true;
}

void CmdParser::showHelp()
{
    std::cout << "Usage: " + QApplication::applicationName().toStdString() + " [options]\n\n";
    std::cout << "Options:\n";

    std::cout << std::left;

    for (int i = 0; i < mOptions.count(); i++) {
        std::cout << "  " <<
                  std::setw(4) << "-" + mOptions.at(i).name().toStdString() + "," <<
                  std::setw(25) << "--" + mOptions.at(i).longName().toStdString() <<
                  std::setw(30) << mOptions.at(i).description().toStdString() + "." << "\n";
    }
}

void CmdParser::showVersion()
{
    std::cout << QApplication::applicationName().toStdString() +
              " " +
              QApplication::applicationVersion().toStdString()  << "\n";
}

bool CmdParser::isSet(QString name)
{
    for (int i = 0; i < mOptions.count(); i++) {
        if ((mOptions.at(i).name() == name || mOptions.at(i).longName() == name) && mOptions.at(i).isSet()) {
            return true;
        }
    }

    return false;
}

//
// Private Functions
//

CmdOption* CmdParser::setOption(QString name)
{
    for (int i = 0; i < mOptions.count(); i++) {
        if (mOptions.at(i).name() == name || mOptions.at(i).longName() == name) {
            mOptions[i].set(true);
            return &mOptions[i];
        }
    }

    return NULL;
}

/*
 * Keep a list of all unknown option so we can print an error message.
 */
void CmdParser::setUnknownOption(QString name)
{
    for (int i = 0; i < mUnknownOptions.count(); i++) {
        if (mUnknownOptions.at(i) == name) {
            return;
        }
    }

    mUnknownOptions.append(name);
}

/*
 * Print error message with all unknown options.
 */
bool CmdParser::showError()
{
    if (mUnknownOptions.count() == 0) {
        return false;
    }

    std::cout << "Unknown options: ";

    for (int i = 0; i < mUnknownOptions.count(); i++) {
        std::cout << " " << mUnknownOptions.at(i).toStdString();

        if (i == mUnknownOptions.count() - 1) {
            std::cout << ".\n";
        } else {
            std::cout << ",";
        }
    }

    return true;
}

QString CmdParser::value(QString name)
{
    for (int i = 0; i < mOptions.count(); i++) {
        if ((mOptions.at(i).name() == name || mOptions.at(i).longName() == name) && mOptions.at(i).isSet()) {
            return mOptions.at(i).value();
        }
    }

    return QString();
}
