/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_Locale_H
#define Patternist_Locale_H

#include <QCoreApplication>
#include <QString>
#include <QUrl>

#include <private/qcardinality_p.h>
#include <private/qnamepool_p.h>
#include <private/qprimitives_p.h>

QT_BEGIN_NAMESPACE

/**
 * @file
 * @short Contains functions used for formatting arguments, such as keywords and paths,
 * in translated strings.
 */

namespace QPatternist
{
    /**
     * @short Provides a translation context & functions for the QtXmlPatterns
     * module.
     *
     * This class is not supposed to be instantiated.
     */
    class QtXmlPatterns
    {
    public:
        Q_DECLARE_TR_FUNCTIONS(QtXmlPatterns)

    private:
        /**
         * No implementation is provided, this class is not supposed to be
         * instantiated.
         */
        inline QtXmlPatterns();
        Q_DISABLE_COPY(QtXmlPatterns)
    };

    // don't make this function static, otherwise xlC 7 cannot find it
    inline QString formatKeyword(const QString &keyword)
    {
        return QLatin1String("<span class='XQuery-keyword'>")   +
               escape(keyword)                                  +
               QLatin1String("</span>");
    }

    /**
     * @overload
     */
    static inline QString formatKeyword(const QStringRef &keyword)
    {
        return formatKeyword(keyword.toString());
    }

    static inline QString formatKeyword(const char *const keyword)
    {
        return formatKeyword(QLatin1String(keyword));
    }

    static inline QString formatKeyword(const QChar keyword)
    {
        return formatKeyword(QString(keyword));
    }

    /**
     * @short Formats element name.
     */
    static inline QString formatElement(const QString &element)
    {
        // for the moment we forward to formatKeyword, that will change later
        return formatKeyword(element);
    }

    /**
     * @overload
     */
    static inline QString formatElement(const char *const element)
    {
        return formatElement(QLatin1String(element));
    }

    /**
     * @short Formats attribute name.
     */
    static inline QString formatAttribute(const QString &attribute)
    {
        // for the moment we forward to formatKeyword, that will change later
        return formatKeyword(attribute);
    }

    /**
     * @overload
     */
    static inline QString formatAttribute(const char *const attribute)
    {
        return formatAttribute(QLatin1String(attribute));
    }

    /**
     * @short Formats ItemType and SequenceType.
     *
     * This function is not declared static, because the compiler on target
     * aix-xlc-64 won't accept it.
     */
    template<typename T>
    inline QString formatType(const NamePool::Ptr &np, const T &type)
    {
        Q_ASSERT(type);
        return QLatin1String("<span class='XQuery-type'>")  +
               escape(type->displayName(np))                +
               QLatin1String("</span>");
    }

    /**
     * @short Formats name of any type.
     */
    static inline QString formatType(const NamePool::Ptr &np, const QXmlName &name)
    {
        return QLatin1String("<span class='XQuery-type'>")  +
               escape(np->displayName(name))                +
               QLatin1String("</span>");
    }

    /**
     * @short Formats Cardinality.
     */
    static inline QString formatType(const Cardinality &type)
    {
        return QLatin1String("<span class='XQuery-type'>")                      +
               escape(type.displayName(Cardinality::IncludeExplanation))        +
               QLatin1String("</span>");
    }

    /**
     * @short Formats @p uri as a path to a resource, typically it's a filename
     * or a URI.
     */
    static inline QString formatResourcePath(const QUrl &uri)
    {
        const QString normalizedURI(escape(uri.toString(QUrl::RemovePassword)));

        return QLatin1String("<span class='XQuery-filepath'><a href='") +
               normalizedURI                                            +
               QLatin1String("'>")                                      +
               normalizedURI                                            +
               QLatin1String("</a></span>");
    }

    /**
     * @short Formats @p uri for display.
     *
     * @note It's not guaranteed that URIs being formatted are valid. That can
     * be an arbitrary string.
     */
    static inline QString formatURI(const QUrl &uri)
    {
        return QLatin1String("<span class='XQuery-uri'>")       +
               escape(uri.toString(QUrl::RemovePassword))       +
               QLatin1String("</span>");
    }

    /**
     * @short Formats @p uri, that's considered to be a URI, for display.
     *
     * @p uri does not have to be a valid QUrl or valid instance of @c
     * xs:anyURI.
     */
    static inline QString formatURI(const QString &uri)
    {
        const QUrl realURI(uri);
        return formatURI(realURI);
    }

    static inline QString formatData(const QString &data)
    {
        return QLatin1String("<span class='XQuery-data'>")  +
               escape(data)                                 +
               QLatin1String("</span>");
    }

    /**
     * This is an overload, provided for convenience.
     */
    static inline QString formatData(const xsInteger data)
    {
        return formatData(QString::number(data));
    }

    /**
     * This is an overload, provided for convenience.
     */
    static inline QString formatData(const char *const data)
    {
        return formatData(QLatin1String(data));
    }

    /**
     * This is an overload, provided for convenience.
     */
    static inline QString formatData(const QLatin1Char &data)
    {
        return formatData(QString(data));
    }

    /**
     * Formats an arbitrary expression, such as a regular expression
     * or XQuery query.
     */
    static inline QString formatExpression(const QString &expr)
    {
        return QLatin1String("<span class='XQuery-expression'>")    +
               escape(expr)                                         +
               QLatin1String("</span>");
    }

}

#ifdef Q_NO_TYPESAFE_FLAGS
#error "Patternist does not compile with Q_NO_TYPESAFE_FLAGS set, because the code uses negative enum values. qglobal.h has typedef uint Flags."
#endif

#ifdef QT_NO_EXCEPTIONS
#error "Patternist uses exceptions and cannot be built without."
#endif

QT_END_NAMESPACE
#endif
