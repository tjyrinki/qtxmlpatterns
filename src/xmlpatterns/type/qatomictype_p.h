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

#ifndef Patternist_AtomicType_H
#define Patternist_AtomicType_H

#include <private/qanysimpletype_p.h>
#include <private/qatomiccasterlocator_p.h>
#include <private/qatomiccomparatorlocator_p.h>
#include <private/qatomicmathematicianlocator_p.h>
#include <private/qatomictypedispatch_p.h>
#include <private/qitemtype_p.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    class Item;
    class SourceLocationReflection;

    /**
     * @short Base class for all classes that implements atomic types.
     *
     * AtomicType does not implement @c xs:anyAtomicType, it is the C++
     * base class for classes that implement atomic types, such as @c xs:anyAtomicType.
     *
     * @ingroup Patternist_types
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class AtomicType : public ItemType,
                       public AnySimpleType
    {
    public:

        typedef QExplicitlySharedDataPointer<AtomicType> Ptr;

        virtual ~AtomicType();

        /**
         * Implements a generic algorithm which relies on wxsTypeMatches().
         *
         * @returns @c true depending on if @p item is an atomic type, and that
         * AtomicValue::itemType()'s SequenceType::itemType() matches this type.
         */
        virtual bool itemMatches(const Item &item) const;

        /**
         * @returns the result of SharedQXmlName::displayName(), of the SharedQName
         * object returned from the name() function.
         */
        virtual QString displayName(const NamePool::Ptr &np) const;

        /**
         * returns always @c false
         */
        virtual bool isNodeType() const;

        /**
         * returns always @c true
         */
        virtual bool isAtomicType() const;

        /**
         * Determines whether @p other is equal to this type, or is a
         * sub-type of this type.
         *
         * The implementation is generic, relying on operator==()
         * and xdtSuperType().
         */
        virtual bool xdtTypeMatches(const ItemType::Ptr &other) const;

        /**
         * @returns always 'this'
         */
        virtual ItemType::Ptr atomizedType() const;

        /**
         * @returns always SchemaType::SimpleTypeAtomic
         */
        virtual TypeCategory category() const;

        /**
         * @returns DerivationRestriction
         */
        virtual DerivationMethod derivationMethod() const;

        virtual AtomicTypeVisitorResult::Ptr
        accept(const QExplicitlySharedDataPointer<AtomicTypeVisitor> &visitor,
               const SourceLocationReflection *const) const = 0;

        virtual AtomicTypeVisitorResult::Ptr
        accept(const ParameterizedAtomicTypeVisitor::Ptr &visitor,
               const qint16 param,
               const SourceLocationReflection *const) const = 0;

        virtual AtomicComparatorLocator::Ptr comparatorLocator() const = 0;
        virtual AtomicMathematicianLocator::Ptr mathematicianLocator() const = 0;
        virtual AtomicCasterLocator::Ptr casterLocator() const = 0;

    protected:
        AtomicType();

    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
