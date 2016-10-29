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

#include "ImgurUploader.h"
#include <iostream>

ImgurUploader::ImgurUploader( QObject *parent ) : QObject( parent ),
    mAccessManager( new QNetworkAccessManager( this ) )
{
    connect( mAccessManager, SIGNAL( finished( QNetworkReply * ) ), 
             this, SLOT( handleReply( QNetworkReply * ) ) );
    mClientID = "16d41e28a3ba71e";
}

void ImgurUploader::startUploadAnonymous( QImage image )
{
//     if (mAccessManager->networkAccessible() != QNetworkAccessManager::Accessible){
//         emit uploadFinished("No access to network, unable to proceed", Error);
//         return;
//     }
    
    std::cout << mAccessManager->networkAccessible() << "\n";
    
    // Convert the image into a byteArray
    QByteArray imageByteArray;
    QBuffer buffer( &imageByteArray );
    image.save( &buffer, "PNG" );

    // Create the params that will be sent with the image
    QList<QPair<QString, QString> > urlQuery;
    urlQuery.append( qMakePair( QString( "title" ), QString( "Ksnip Upload" ) ) );
    urlQuery.append( qMakePair( QString( "description" ), QString( "Screenshot uploaded by Ksnip" ) ) );

    // Create the network request for posting the image
    QNetworkRequest request;
    QUrl url( "https://api.imgur.com/3/upload.xml" );
    url.setQueryItems( urlQuery );
    request.setUrl( url );
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/xml" );
    request.setRawHeader( "Authorization", "Client-ID " + mClientID );

    // Post the image
    
    mAccessManager->post( request, imageByteArray );
}

/*
 * This function will be called when we've got the reply from imgur
 */
void ImgurUploader::handleReply( QNetworkReply *reply )
{
    // Check return code for any network errors
    if ( reply->error() != QNetworkReply::NoError ) {
        emit uploadFinished( "Network Error: " + reply->error(), Error);
        reply->deleteLater();
        return;
    }
    
    // Check if we have got a 200OK reply back from server, anything else is an error
    if ( reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt() != 200 ) {
        emit uploadFinished( "A none 200 OK reply was received from server, unable to proceed.", 
                             Error );
        reply->deleteLater();
        return;
    }

    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;

    // Try to parse reply into xml reader
    if ( !doc.setContent( reply->readAll(), false, &errorMessage, &errorLine, &errorColumn ) ) {
        emit uploadFinished( "Parse error: " + errorMessage +
                          ", line:" + errorLine +
                          ", column:" + errorColumn,
                          Error);
        reply->deleteLater();
        return;
    }

    // See if we have an upload reply, or an error
    QDomElement rootElem = doc.documentElement();

    if ( rootElem.tagName() == "data" ) {
        if ( !rootElem.elementsByTagName( "link" ).isEmpty() ) {
            emit uploadFinished( rootElem.elementsByTagName( "link" ).at( 0 ).toElement().text(), 
                                 Successful );
        }
        else {
            emit uploadFinished( "No Link from image in reply provided.", Error );
        }
    }
    else
        if ( rootElem.tagName() == "error" && !rootElem.elementsByTagName( "message" ).isEmpty() ) {
            emit uploadFinished( rootElem.elementsByTagName( "message" ).at( 0 ).toElement().text(), 
                                 Error );
        }
        else {
            emit uploadFinished( "Reccived unexpected reply from web service.", Error );
        }

    reply->deleteLater();
}

/*
 * Prints all currently relevant headers, mostly for troubleshooting.
 */
void ImgurUploader::printHeader( QNetworkReply *reply )
{
    std::cout << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toString().toStdString() << "\n";
    std::cout << reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString().toStdString() << "\n";
    std::cout << reply->attribute( QNetworkRequest::RedirectionTargetAttribute ).toString().toStdString() << "\n";
//     std::cout << "Reply code: " << QString(reply->readAll()).toStdString()<< "\n";
    std::cout << "-------------------------------------------------------------\n";

    for ( int i = 0; i < reply->rawHeaderList().count(); i++ ) {
        std::cout << QString( reply->rawHeaderPairs().at( i ).first ).toStdString() << " "
                  << QString( reply->rawHeaderPairs().at( i ).second ).toStdString() << "\n";
    }
}